#include "DDSCommunicationManager.h"

/************************************************************************
	Constructor / Destructor
************************************************************************/
DDSCommunicationManager::DDSCommunicationManager(void)
{
	init();
}

DDSCommunicationManager::~DDSCommunicationManager(void)
{
	release();
}

/************************************************************************
	Export Function
************************************************************************/
void
DDSCommunicationManager::init()
{
	setUserName(_T("DDSCommunicationManager"));

	// by contract
	mec = new MECComponent;
	mec->setUser(this);
}

void
DDSCommunicationManager::release()
{
	meb = NULL;
	delete mec;
	mec = NULL;
}


void
DDSCommunicationManager::sendJoinStatus(bool joinStatus)
{
	std::shared_ptr<NOM> nomMsg = meb->getNOMInstance(getUserName(), _T("DDSJoinStatus"));
	nomMsg->setValue(_T("JoinStatus"), &NBool(joinStatus));
	sendMsg(nomMsg);
}

/************************************************************************
	Inherit Function
************************************************************************/
std::shared_ptr<NOM>
DDSCommunicationManager::registerMsg(tstring msgName)
{
	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsg.emplace(nomMsg->getInstanceID(), nomMsg);

	return nomMsg;
}

void
DDSCommunicationManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	discoveredMsg.emplace(nomMsg->getInstanceID(), nomMsg);
}

void
DDSCommunicationManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	//if (nomMsg->getName() == _T("AirThreatInformation")) {
	//	auto objectCount = nomMsg->getValue(_T("ObjectCount"))->toUShort();
	//	tcout << _T(__FUNCTION__) << _T(" ") << objectCount << std::endl;
	//}
	mec->updateMsg(nomMsg);
}

void
DDSCommunicationManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
	ddsMsgHandler->processMessageSent(nomMsg);
}

void
DDSCommunicationManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	mec->deleteMsg(nomMsg);
	registeredMsg.erase(nomMsg->getInstanceID());
}

void
DDSCommunicationManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	discoveredMsg.erase(nomMsg->getInstanceID());
}

void
DDSCommunicationManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	mec->sendMsg(nomMsg);
}

void
DDSCommunicationManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	ddsMsgHandler->processMessageSent(nomMsg);
}

void
DDSCommunicationManager::setUserName(tstring userName)
{
	name = userName;
}

tstring
DDSCommunicationManager::getUserName()
{
	return name;
}

void
DDSCommunicationManager::setData(void* data)
{
	// if need be, write your code
}

bool
DDSCommunicationManager::start()
{
	ddsMsgHandler = new DDSMessageHandler(this);

	bool initResult = (ddsMsgHandler != nullptr);
	sendJoinStatus(initResult);

	return true;
}

bool
DDSCommunicationManager::stop()
{
	delete ddsMsgHandler;
	return true;
}

void
DDSCommunicationManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

/************************************************************************
	Export Function
************************************************************************/
extern "C" BASEMGRDLL_API
BaseManager * createObject()
{
	return new DDSCommunicationManager();
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager * userManager)
{
	delete userManager;
}