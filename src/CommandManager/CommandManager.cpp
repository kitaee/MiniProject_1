#pragma once
#include "CommandManager.h"
#include <nFramework/util/IniHandler.h>



using namespace nframework;
using namespace nom;
using namespace std::chrono;

/************************************************************************
	Constructor / Destructor
************************************************************************/
CommandManager::CommandManager(void)
{
	init();
}

CommandManager::~CommandManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
CommandManager::init()
{
	
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;
	
	
	setUserName(_T("CommandManager"));


	// by contract
	mec = new MECComponent;
	mec->setUser(this);
}

void
CommandManager::release()
{
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	Inherit Function
************************************************************************/
std::shared_ptr<NOM>
CommandManager::registerMsg(tstring msgName)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << msgName << std::endl;
	
	
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsg.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
CommandManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	
	discoveredMsg.emplace(nomMsg->getInstanceID(), nomMsg);
}

void
CommandManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	mec->updateMsg(nomMsg);
}

void
CommandManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
	//if (nomMsg->getName() == _T("AirThreatInformation")) {
	//	auto objectCount = nomMsg->getValue(_T("ObjectCount"))->toUShort();
	//	tcout << _T(__FUNCTION__) << _T(" ") << objectCount << std::endl;
	//}
	//tcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	// if need be, write your code
}

void
CommandManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << __FUNCTIONT__ _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	
	mec->deleteMsg(nomMsg);
	registeredMsg.erase(nomMsg->getInstanceID());
}

void
CommandManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	
	std::map<unsigned int, std::shared_ptr<NOM>>::iterator itr;
	itr = discoveredMsg.find(nomMsg->getInstanceID());

	if(itr != discoveredMsg.end())
	{
		discoveredMsg.erase(nomMsg->getInstanceID());
	}
	else
	{
		tcerr << _T("[CommandManager] ") << _T("message was not removed.") << std::endl;
	}
}

void
CommandManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	mec->sendMsg(nomMsg);
}

void
CommandManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	//tcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << endl;
	//tcout << _T("[") << _T(__FUNCTION__) << _T("] ")<< nomMsg->getInstanceName() << endl;
	// if need be, write your code
}

void
CommandManager::setUserName(tstring userName)
{
	name = userName; 
}

tstring
CommandManager::getUserName()
{
	return name;
}

void
CommandManager::setData(void* data)
{
	// if need be, write your code
}

bool
CommandManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("CommandManager/CommandManager.ini")); // ※주의 작업디렉터리: Main.exe가 있는 경로

	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;
	
	

	unsigned int numOfSimulators = iniHandler.readInteger(_T("Simulators"), _T("Count"));


	for (unsigned int cnt = 1; cnt <= numOfSimulators; cnt++)
	{
		tstringstream dllPrefix;
		dllPrefix << _T("Simulator_") << cnt;

		tstring dllIndex;
		dllPrefix >> dllIndex;

		tstring simulator = iniHandler.readString(dllIndex, _T("Simulator"));

		weapons.emplace_back(simulator);
	}

	std::shared_ptr<NOM> dds_obj;
	tstring cmdStr;

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	nTimer = &(NTimer::getInstance());
	int timerHandle = 0;
	tstring prompt = _T("cmd input (e.g., register, delete, update. send, break, quit, etc.):");
	ntcerr << prompt << std::endl;

	while (tcin >> cmdStr)
	{

		if (cmdStr == _T("register"))
		{
			testObjNOM = this->registerMsg(_T("BaseEntity.PhysicalEntity.Platform.Aircraft"));
		}
		else if (cmdStr == _T("delete"))
		{
			this->deleteMsg(testObjNOM);
		}
		else if (cmdStr == _T("update"))
		{
			if (testObjNOM.get())
			{
				testObjNOM->setValue(_T("WorldLocation.X"), &NDouble(10.0));
				this->updateMsg(testObjNOM);
			}
			else
			{
				tcerr << _T("message is not registered.");
			}
		}
		else if (cmdStr == _T("send"))
		{
			/*STDFUNCTION testPeriodic = std::bind(&CommandManager::testSend, this);
			timerHandle = nTimer->addPeriodicTask(1000, testPeriodic);
			this->testSend();*/
			wchar_t* args = _T("SAAM");
			STDFUNCTION testPeriodic = std::bind(&CommandManager::testSendArgs, this, args);
			timerHandle = nTimer->addPeriodicTask(1000, testPeriodic, (void*)args);
			this->testSendArgs(args);
		}
		else if (cmdStr == _T("break"))
		{
			nTimer->removeTask(timerHandle);
		}
		else if (cmdStr == _T("quit"))
		{
			break;
		}
		else
		{
			tcerr << _T("[") << _T(__FUNCTION__) << _T("] ") << _T("command is not valid.") << std::endl;
		}
	}

	return true;
}

bool
CommandManager::stop()
{
	return true;
}

void
CommandManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void
CommandManager::testSend()
{
	std::shared_ptr<NOM> testIntrNOM = meb->getNOMInstance(getUserName(), _T("EventReport"));
	NUShort id = 7;
	testIntrNOM->setValue(_T("OriginatingEntity.FederateIdentifier.SiteID"), &id);
	NEnum evtType = 101;
	testIntrNOM->setValue(_T("EventType"), &evtType);

	//shared_ptr<NOM> testIntrNOM = meb->getNOMInstance(getUserName(), _T("SetData"));
	//NUShort id = 7;
	//testIntrNOM->setValue(_T("OriginatingEntity.FederateIdentifier.SiteID"), &id);
	//NUInteger requestIdentifier = 101;
	//testIntrNOM->setValue(_T("RequestIdentifier"), &requestIdentifier);

	this->sendMsg(testIntrNOM);
}

void
CommandManager::testSendArgs(wchar_t* arg)
{
	ntcout << arg << std::endl;
	
	
	std::shared_ptr<NOM> testIntrNOM = meb->getNOMInstance(getUserName(), _T("EventReport"));
	NUShort id = 7;
	testIntrNOM->setValue(_T("OriginatingEntity.FederateIdentifier.SiteID"), &id);
	NEnum evtType = 101;
	testIntrNOM->setValue(_T("EventType"), &evtType);

	//shared_ptr<NOM> testIntrNOM = meb->getNOMInstance(getUserName(), _T("SetData"));
	//NUShort id = 7;
	//testIntrNOM->setValue(_T("OriginatingEntity.FederateIdentifier.SiteID"), &id);
	//NUInteger requestIdentifier = 101;
	//testIntrNOM->setValue(_T("RequestIdentifier"), &requestIdentifier);

	this->sendMsg(testIntrNOM);
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new CommandManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}

