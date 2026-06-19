#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#include "UDPCommunicationManager.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <Windows.h>
#include "UDPCommunicationManagerIntelliVal.h"

#pragma comment(lib, "Ws2_32.lib")

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

static path resolveRouteInfoPath()
{
	return absolute(resolveModuleDirectory() / L"RouteInfo.ini");
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

static std::string trimCopy(const std::string& value)
{
	const auto first = std::find_if_not(value.begin(), value.end(), [](unsigned char ch) { return std::isspace(ch); });
	const auto last = std::find_if_not(value.rbegin(), value.rend(), [](unsigned char ch) { return std::isspace(ch); }).base();
	if (first >= last)
		return {};
	return std::string(first, last);
}

static std::wstring widenAscii(const std::string& value)
{
	return std::wstring(value.begin(), value.end());
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
	loadRouteInfo();

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
	commConfig = nullptr;

	//socket issue
	//delete commInterface;

	meb = nullptr;
	delete mec;
	mec = nullptr;
}

void
UDPCommunicationManager::loadRouteInfo()
{
	routeTable.clear();

	const auto routePath = resolveRouteInfoPath();
	std::ifstream routeFile(routePath);
	if (!routeFile.is_open())
	{
		appendUdpTrace(L"RouteInfo.ini not found: " + routePath.wstring());
		return;
	}

	std::string line;
	while (std::getline(routeFile, line))
	{
		const auto commentPos = line.find_first_of(";#");
		if (commentPos != std::string::npos)
			line = line.substr(0, commentPos);

		line = trimCopy(line);
		if (line.empty())
			continue;

		const auto equalsPos = line.find('=');
		if (equalsPos == std::string::npos)
			continue;

		const auto idText = trimCopy(line.substr(0, equalsPos));
		const auto endpointsText = trimCopy(line.substr(equalsPos + 1));
		if (idText.empty() || endpointsText.empty())
			continue;

		unsigned int messageId = 0;
		try
		{
			messageId = static_cast<unsigned int>(std::stoul(idText));
		}
		catch (...)
		{
			continue;
		}

		std::stringstream endpointStream(endpointsText);
		std::string endpointText;
		while (std::getline(endpointStream, endpointText, ','))
		{
			endpointText = trimCopy(endpointText);
			const auto colonPos = endpointText.rfind(':');
			if (colonPos == std::string::npos)
				continue;

			auto ip = trimCopy(endpointText.substr(0, colonPos));
			auto portText = trimCopy(endpointText.substr(colonPos + 1));
			if (ip.empty() || portText.empty())
				continue;

			try
			{
				const auto port = static_cast<uint16_t>(std::stoul(portText));
				routeTable[messageId].push_back({ ip, port });
			}
			catch (...)
			{
				continue;
			}
		}
	}

	appendUdpTrace(L"RouteInfo.ini loaded routes=" + std::to_wstring(routeTable.size()));
}

bool
UDPCommunicationManager::sendRoutedUdp(shared_ptr<NOM> nomMsg)
{
	if (!nomMsg)
		return false;

	const auto routeItr = routeTable.find(nomMsg->getMessageID());
	if (routeItr == routeTable.end() || routeItr->second.empty())
		return false;

	const auto messageId = nomMsg->getMessageID();
	uint32_t payloadLength = nomMsg->getLength();
	if (payloadLength == 0)
	{
		appendUdpTrace(L"routed send skipped: zero length id=" + std::to_wstring(messageId));
		return false;
	}

	std::vector<uint8_t> payload(payloadLength);
	if (!nomMsg->serialize(payload.data(), payloadLength))
	{
		appendUdpTrace(L"routed send serialize failed id=" + std::to_wstring(messageId));
		return false;
	}

	WSADATA wsaData{};
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		appendUdpTrace(L"routed send WSAStartup failed id=" + std::to_wstring(messageId));
		return false;
	}

	SOCKET udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (udpSocket == INVALID_SOCKET)
	{
		appendUdpTrace(L"routed send socket failed id=" + std::to_wstring(messageId));
		WSACleanup();
		return false;
	}

	for (const auto& endpoint : routeItr->second)
	{
		sockaddr_in remoteAddress{};
		remoteAddress.sin_family = AF_INET;
		remoteAddress.sin_port = htons(endpoint.port);

		if (inet_pton(AF_INET, endpoint.ip.c_str(), &remoteAddress.sin_addr) != 1)
		{
			appendUdpTrace(L"routed send invalid endpoint " + widenAscii(endpoint.ip) + L":" + std::to_wstring(endpoint.port));
			continue;
		}

		const int sentBytes = sendto(
			udpSocket,
			reinterpret_cast<const char*>(payload.data()),
			static_cast<int>(payload.size()),
			0,
			reinterpret_cast<sockaddr*>(&remoteAddress),
			sizeof(remoteAddress));

		if (sentBytes == SOCKET_ERROR)
		{
			appendUdpTrace(L"routed send failed id=" + std::to_wstring(messageId)
				+ L" to " + widenAscii(endpoint.ip) + L":" + std::to_wstring(endpoint.port)
				+ L" wsa=" + std::to_wstring(WSAGetLastError()));
			continue;
		}

		appendUdpTrace(L"routed send id=" + std::to_wstring(messageId)
			+ L" name=" + nomMsg->getName()
			+ L" to " + widenAscii(endpoint.ip) + L":" + std::to_wstring(endpoint.port)
			+ L" bytes=" + std::to_wstring(sentBytes));
	}

	closesocket(udpSocket);
	WSACleanup();

	return true;
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
	if (sendRoutedUdp(nomMsg))
		return;
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

	if (sendRoutedUdp(nomMsg))
		return;

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

	// Wire header matches NOM serialize / sendCommMsg (little-endian on Windows x86).
	// Do NOT use ntohl/ntohs here — LE 0x000003E9 (1001) becomes 0xE9030000 with ntohl.
	if (IDSize == 2)
	{
		unsigned short tmpMsgID = 0;
		memcpy(&tmpMsgID, data + IDPos, IDSize);
		msgID = static_cast<unsigned long>(tmpMsgID);
	}
	else if (IDSize == 4)
	{
		unsigned long tmpMsgID = 0;
		memcpy(&tmpMsgID, data + IDPos, IDSize);
		msgID = tmpMsgID;
	}
	else
	{
		return;
	}

	const auto msgName = commMsgHandler.getMsgName(msgID);
	appendUdpTrace(L"msgID=" + std::to_wstring(msgID) + L" name=" + msgName);
	std::wcout << L"[UDPCommunicationManager] processRecvMessage: msgID=" << msgID
	       << L" name=" << msgName << L" size=" << size << std::endl;

	if (msgName.empty())
	{
		std::wstringstream s; s << L"undefined message id=" << msgID;
		l.info(s);
		std::wcout << L"[UDPCommunicationManager] undefined message id=" << msgID << std::endl;
		appendUdpTrace(L"undefined message id=" + std::to_wstring(msgID) + L" (no name)");
		return;
	}

	auto nomMsg = meb->getNOMInstance(name, msgName);

	if (nomMsg.get())
	{
		if (nomMsg->getType() == nframework::nom::ENOMType::NOM_TYPE_OBJECT)
		{
			nomMsg->deserialize(data, size);
			auto nomMsgCP = nomMsg->clone();
			nomMsgCP->setOwner(name);
			appendUdpTrace(L"object sendMsg: " + nomMsgCP->getName());
			this->sendMsg(nomMsgCP);
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
		std::wstringstream s; s << L"getNOMInstance failed for " << msgName;
		l.info(s);
		appendUdpTrace(L"getNOMInstance failed: " + msgName);
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

