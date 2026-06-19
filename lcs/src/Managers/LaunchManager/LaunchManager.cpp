#include "LaunchManager.h"
#include <iostream>

// 역할: 발사 제어
// BaseManager MEC 위임만 구현. 업무 로직은 추후 reflectMsg/recvMsg/start 에 추가.

LaunchManager::LaunchManager()
{
    mec = new MECComponent;
    mec->setUser(this);
    setUserName(L"LaunchManager");
}

LaunchManager::~LaunchManager()
{
    delete mec;
    mec = nullptr;
    meb = nullptr;
}

std::shared_ptr<NOM> LaunchManager::registerMsg(std::wstring msgName) { return mec->registerMsg(msgName); }
void LaunchManager::discoverMsg(std::shared_ptr<NOM> nomMsg) { mec->discoverMsg(nomMsg); }
void LaunchManager::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void LaunchManager::reflectMsg(std::shared_ptr<NOM>) {}
void LaunchManager::deleteMsg(std::shared_ptr<NOM> nomMsg) { mec->deleteMsg(nomMsg); }
void LaunchManager::removeMsg(std::shared_ptr<NOM> nomMsg) { mec->removeMsg(nomMsg); }
void LaunchManager::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }

void LaunchManager::sendLaunchMissile()
{
    if (!meb)
    {
        std::wcout << L"[LaunchManager] LaunchMissile skipped: MEB is not set." << std::endl;
        return;
    }

    auto launch = meb->getNOMInstance(name, L"LaunchMissile");
    if (!launch)
    {
        std::wcout << L"[LaunchManager] LaunchMissile skipped: NOM instance not found." << std::endl;
        return;
    }

    nframework::nom::NUInteger messageId(launch->getMessageID());
    nframework::nom::NUInteger messageLength(launch->getLength());
    nframework::nom::NUInteger airthreatId(1u);
    nframework::nom::NFloat airthreatX(0.0f);
    nframework::nom::NFloat airthreatY(0.0f);
    nframework::nom::NFloat airthreatZ(0.0f);
    nframework::nom::NUInteger missileId(1u);
    nframework::nom::NFloat lcsX(0.0f);
    nframework::nom::NFloat lcsY(0.0f);
    nframework::nom::NFloat lcsZ(0.0f);

    launch->setValue(L"MessageHeader.MessageID", &messageId);
    launch->setValue(L"MessageHeader.MessageLength", &messageLength);
    launch->setValue(L"AirthreatID", &airthreatId);
    launch->setValue(L"AirthreatXpos", &airthreatX);
    launch->setValue(L"AirthreatYPos", &airthreatY);
    launch->setValue(L"AirthreatZPos", &airthreatZ);
    launch->setValue(L"MissleID", &missileId);
    launch->setValue(L"LCSXpos", &lcsX);
    launch->setValue(L"LCSYPos", &lcsY);
    launch->setValue(L"LCSZPos", &lcsZ);

    sendMsg(launch);
    std::wcout << L"[LaunchManager] LaunchMissile sent (MessageID=" << launch->getMessageID() << L")" << std::endl;
}

void LaunchManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
    if (!nomMsg)
        return;

    std::wcout << L"[LaunchManager] recvMsg: " << nomMsg->getName() << std::endl;

    if (nomMsg->getName() == L"LaunchMissileRequest")
        sendLaunchMissile();
}
void LaunchManager::setUserName(std::wstring userName) { name = userName; }
tstring LaunchManager::getUserName() { return name; }
void LaunchManager::setData(void*) {}
bool LaunchManager::start() { return true; }
bool LaunchManager::stop() { return true; }
void LaunchManager::setMEBComponent(IMEBComponent* realMEB) { meb = realMEB; mec->setMEB(meb); }

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new LaunchManager; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }
