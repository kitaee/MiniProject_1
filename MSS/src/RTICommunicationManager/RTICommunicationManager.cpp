#include "RTICommunicationManager.h"
#include <nFramework/util/IniHandler.h>

using namespace nframework::nom;

/************************************************************************
	constructor / destructor
************************************************************************/
RTICommunicationManager::RTICommunicationManager(void)
{
	initialize();
}

RTICommunicationManager::~RTICommunicationManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
RTICommunicationManager::initialize(void)
{
	setUserName(_T("RTICommunicationManager"));	
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;
	
	
	continueSimFlag.store(true);

	// design by contract
	mec = new MECComponent; 
	mec->setUser(this);

	*isStarted = false;
}

void
RTICommunicationManager::release()
{
	continueSimFlag.store(false);

	resignFed();
	delete mec;
	mec = nullptr;
	meb = nullptr;
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
RTICommunicationManager::registerMsg(tstring msgName)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << msgName << std::endl;
	
	
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsg.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
RTICommunicationManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	
	discoveredMsg.emplace(nomMsg->getInstanceID(), nomMsg);
	if (*isStarted && hlaCommunicator) {
		hlaCommunicator->registerCommMsg(nomMsg);
	}
}

void
RTICommunicationManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	
	mec->updateMsg(nomMsg);
}

void
RTICommunicationManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	
	if (*isStarted && hlaCommunicator) {
		hlaCommunicator->updateCommMsg(nomMsg);
	}
}

void
RTICommunicationManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	
	mec->deleteMsg(nomMsg);
	registeredMsg.erase(nomMsg->getInstanceID());
}

void
RTICommunicationManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	
	if (auto result = discoveredMsg.erase(nomMsg->getInstanceID());
		result != 0) {
		if (*isStarted && hlaCommunicator) {
			hlaCommunicator->deleteCommMsg(nomMsg);
		}
	}
}

void
RTICommunicationManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	
	mec->sendMsg(nomMsg);
}

void
RTICommunicationManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	
	if (*isStarted && hlaCommunicator) {
		hlaCommunicator->sendCommMsg(nomMsg);
	}
}

void
RTICommunicationManager::setUserName(tstring userName)
{
	name = userName; 
}

tstring
RTICommunicationManager::getUserName()
{
	return name;
}

void
RTICommunicationManager::setData(void* data)
{
	// if need be, write your code
}

bool
RTICommunicationManager::start()
{
	joinFed();

	*isStarted = true;
	return true;
}

bool
RTICommunicationManager::stop()
{ 
	resignFed();

	return true;
}

void
RTICommunicationManager::resignFed()
{
	std::lock_guard<std::mutex> lock(mut);
	continueSimFlag.store(false);

	if (hlaCommunicator && hlaCommConfig) {
		hlaCommunicator->releaseNetEnv(hlaCommConfig);

		hlaCommunicator.reset();
		delete hlaCommConfig;
		hlaCommConfig = nullptr;
	}
}

void
RTICommunicationManager::joinFed()
{
	std::lock_guard<std::mutex> lock(mut);
	continueSimFlag.store(true);

	// The code below includes use of the middleware such as RTI
	if (!hlaCommunicator && !hlaCommConfig) {
		tcerr << "[" __FUNCTIONT__ << "] " << " Try to join federation." << std::endl;
		hlaCommConfig = new CommunicationConfig;
		hlaCommConfig->setIni(_T("RTICommunicationManager/HLAFed.ini"));
		hlaCommunicator = std::make_unique<HLACommInterface>(this);
		hlaCommunicator->setMEBComponent(meb);

		if (!hlaCommunicator->initNetEnv(hlaCommConfig)) {
			hlaCommunicator.reset();
			delete hlaCommConfig;
			hlaCommConfig = nullptr;
		}
		else {
			// else
		}
	}
	else
	{
		// else
	}

	if (hlaCommunicator && hlaCommConfig)
	{
		*isStarted = true;
	}
	else
	{
		// else
	}
}

void
RTICommunicationManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}



/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new RTICommunicationManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}