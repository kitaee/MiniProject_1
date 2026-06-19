#include "UDPCommunicationManager.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "UDPCommunicationManagerIntelliVal.h"

using namespace std::filesystem;

static path resolveModuleDirectory()
{
	wchar_t modulePath[MAX_PATH]{};
	HMODULE module = nullptr;
	if (GetModuleHandleExW(
		GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
		reinterpret_cast<LPCWSTR>(&resolveModuleDirectory),
		&module) && module != nullptr)
	{
		GetModuleFileNameW(module, modulePath, MAX_PATH);
	}
	return absolute(path(modulePath).parent_path());
}

static std::wstring resolveSchemaRegistryPath()
{
	return absolute(resolveModuleDirectory() / L".." / L"SchemaRegistryData.xml").wstring();
}

static std::wstring resolveCommLinkInfoPath()
{
	return absolute(resolveModuleDirectory() / L"CommLinkInfo.ini").wstring();
}

static std::wstring resolveNomXmlPath(const std::wstring& userName)
{
	return absolute(resolveModuleDirectory() / (userName + L".xml")).wstring();
}

static void appendUdpTrace(const std::wstring& line)
{
	std::wofstream trace(resolveModuleDirectory() / L".." / L"udp_trace.log", std::ios::app);
	trace << line << L'\n';
}

/************************************************************************
	Constructor / Destructor
************************************************************************/
UDPCommunicationManager::UDPCommunicationManager(void)
{
	init();
}

UDPCommunicationManager::~UDPCommunicationManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
UDPCommunicationManager::init()
{
	std::wstringstream s; s << "[" << __FUNCTIONT__ << "] " ;
	l.info(s);
	setUserName(L"UDPCommunicationManager");

	// by contract
	mec = new MECComponent;
	mec->setUser(this);

	commConfig = new CommunicationConfig;
	commConfig->setIni(resolveCommLinkInfoPath());

	//socket issue
	//commInterface = new NCommInterface(this);

	//NOM 메시지 등록
	const std::wstring schRegFilePath = resolveSchemaRegistryPath();
	nomParser = std::make_unique<NOMParser>();
	nomParser->setNOMFile(schRegFilePath);

	nomParser->parseNote();
	auto noteMap = nomParser->getNoteMap();
	nomParser->parseDataType();
	auto dataTypeMap = nomParser->getDataTypeMap();

	//NOM 파싱 (DLL 디렉터리 기준 — cwd 무관)
	const std::wstring nomFilePath = resolveNomXmlPath(getUserName());
	nomParser->setNOMFile(nomFilePath);

	if (nomParser->parse(dataTypeMap, noteMap))
		//if (nomParser->parse())
	{
		list<NMessage*> msgList = nomParser->getMessageList();
		list<NMessage*>::iterator itr;
		for (itr = msgList.begin(); itr != msgList.end(); itr++)
		{
			NMessage* nMsg = *itr;
			commMsgHandler.setIDNameTable(nMsg->getMessageID(), nMsg->getName());
		}
	}
}

void
UDPCommunicationManager::release()
{
	delete commConfig;

	//socket issue
	//delete commInterface;

	meb = nullptr;
	delete mec;
	mec = nullptr;
}

/************************************************************************
	Inherit Function
************************************************************************/
shared_ptr<NOM>
UDPCommunicationManager::registerMsg(std::wstring msgName)
{
	shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsg.insert(pair<unsigned int, shared_ptr<NOM>>(nomMsg->getInstanceID(), nomMsg));

	return nomMsg;
}

void
UDPCommunicationManager::discoverMsg(shared_ptr<NOM> nomMsg)
{
	discoveredMsg.insert(pair<unsigned int, shared_ptr<NOM>>(nomMsg->getInstanceID(), nomMsg));
	commInterface->registerCommMsg(nomMsg);
}

void
UDPCommunicationManager::updateMsg(shared_ptr<NOM> nomMsg)
{
	unsigned int oid = getObjectInstanceID(nomMsg);

	if (oid > 0)
	{
		nomMsg->setInstanceID(oid);
		mec->updateMsg(nomMsg);
	}
	else
	{
		printf("oid error:%u\n", oid);
	}
}

void
UDPCommunicationManager::reflectMsg(shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << L"UDPCommunicationManager::Message is reflected." ;
	l.info(s);
	commInterface->updateCommMsg(nomMsg);
}

void
UDPCommunicationManager::deleteMsg(shared_ptr<NOM> nomMsg)
{
	mec->deleteMsg(nomMsg);
	registeredMsg.erase(nomMsg->getInstanceID());
}

void
UDPCommunicationManager::removeMsg(shared_ptr<NOM> nomMsg)
{
	map<unsigned int, shared_ptr<NOM>>::iterator itr;
	itr = discoveredMsg.find(nomMsg->getInstanceID());

	if(itr != discoveredMsg.end())
	{
		discoveredMsg.erase(nomMsg->getInstanceID());
	}
	else
	{
		std::wstringstream s; s << L"UDPCommunicationManager::Message was removed." ;
		l.info(s);
	}
}

void
UDPCommunicationManager::sendMsg(shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() ;
	l.info(s);

	mec->sendMsg(nomMsg);
}

void
UDPCommunicationManager::recvMsg(shared_ptr<NOM> nomMsg)
{
	std::wstringstream s; s << "[" << __FUNCTIONT__ << "] " << nomMsg->getName() ;
	l.info(s);
	std::wcout << L"[UDPCommunicationManager] recvMsg -> sendCommMsg: " << nomMsg->getName()
	       << L" (id=" << nomMsg->getMessageID() << L")" << std::endl;
	appendUdpTrace(L"recvMsg -> sendCommMsg: " + nomMsg->getName());

	commInterface->sendCommMsg(nomMsg);
}

void
UDPCommunicationManager::setUserName(std::wstring userName)
{
	name = userName; 
}

std::wstring
UDPCommunicationManager::getUserName()
{
	return name;
}

void
UDPCommunicationManager::setData(void* data)
{
	// if need be
}

bool
UDPCommunicationManager::start()
{
	std::wstringstream s; s << "[" << __FUNCTIONT__ << "] " ;
	l.info(s);

	//socket issue
	commInterface = new NCommInterface(this);
	
	commInterface->setMEBComponent(meb);
	MessageProcessor msgProcessor = bind(&UDPCommunicationManager::processRecvMessage, this, placeholders::_1, placeholders::_2);
	commConfig->setMsgProcessor(msgProcessor);
	commInterface->initNetEnv(commConfig);

	// object만 register (interaction은 sendMsg/recvMsg 경로 — MiniProject 동일)
	list<NMessage*> msgList = nomParser->getObjectList();
	for (auto* nMsg : msgList)
	{
		if (nMsg->getSharing() == ESharing::ENUM_SHARING_PUBLISHSUBSCRIBE
			|| nMsg->getSharing() == ESharing::ENUM_SHARING_PUBLISH)
		{
			this->registerMsg(nMsg->getName());
		}
	}

	return true;
}

bool
UDPCommunicationManager::stop()
{
	commInterface->releaseNetEnv(commConfig);

	//socket issue
	delete commInterface;
	return true;
}

void
UDPCommunicationManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void
UDPCommunicationManager::processRecvMessage(unsigned char* data, int size)
{
	appendUdpTrace(L"processRecvMessage called size=" + std::to_wstring(size));
	//auto HeaderSize = commConfig->getHeaderSize();
	auto IDPos = commConfig->getHeaderIDPos();
	auto IDSize = commConfig->getHeaderIDSize();

	unsigned long msgID = 0;

	//ID 형식이 ushort인 경우 처리
	if (IDSize == 2)
	{
		unsigned short tmpMsgID = 0;
		memcpy(&tmpMsgID, data + IDPos, IDSize);
		msgID = static_cast<unsigned long>(ntohs(tmpMsgID));
	}
	//ID 형식이 ulong인 경우 처리
	else if (IDSize == 4)
	{
		unsigned long tmpMsgID = 0;
		memcpy(&tmpMsgID, data + IDPos, IDSize);
		msgID = ntohl(tmpMsgID);
	}
	else
	{
		return;
	}

	const auto msgName = commMsgHandler.getMsgName(msgID);
	appendUdpTrace(L"msgID=" + std::to_wstring(msgID) + L" name=" + msgName);
	std::wcout << L"[UDPCommunicationManager] processRecvMessage: msgID=" << msgID
	       << L" name=" << msgName << L" size=" << size << std::endl;

	auto nomMsg = meb->getNOMInstance(name, msgName);

	if (nomMsg.get())
	{
		if (nomMsg->getType() == nframework::nom::ENOMType::NOM_TYPE_OBJECT)
		{
			nomMsg->deserialize(data, size);
			this->updateMsg(nomMsg);
		}
		else
		{
			auto nomMsgCP = nomMsg->clone();
			nomMsgCP->deserialize(data, size);
			nomMsgCP->setOwner(name);
			appendUdpTrace(L"interaction sendMsg: " + nomMsgCP->getName());
			this->sendMsg(nomMsgCP);
		}
	}
	else
	{
		std::wstringstream s; s << L"undefined message id=" << msgID << L" name=" << msgName;
		l.info(s);
		std::wcout << L"[UDPCommunicationManager] undefined message id=" << msgID
		       << L" name=" << msgName << std::endl;
		appendUdpTrace(L"undefined message id=" + std::to_wstring(msgID) + L" name=" + msgName);
	}
}

unsigned int
UDPCommunicationManager::getObjectInstanceID(shared_ptr<NOM> nomMsg)
{
	unsigned int oid = 0;
	map<unsigned int, shared_ptr<NOM>>::iterator itr;
	for (itr = registeredMsg.begin(); itr != registeredMsg.end(); itr++)
	{
		unsigned int key = itr->first;
		shared_ptr<NOM> nom = itr->second;

		if (nom->getMessageID() == nomMsg->getMessageID())
		{
			printf("[TCPCommunicationManager]Found object instance id : %u\n", key);
			oid = key;
			break;
		}
	}

	return oid;
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new UDPCommunicationManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}

