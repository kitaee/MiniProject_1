#include "UIManager.h"

// 역할: C# WPF ↔ MEB 브릿지
// BaseManager MEC 위임만 구현. 업무 로직은 추후 reflectMsg/recvMsg/start 에 추가.

UIManager::UIManager()
{
    mec = new MECComponent;
    mec->setUser(this);
    setUserName(L"UIManager");
}

UIManager::~UIManager()
{
    delete mec;
    mec = nullptr;
    meb = nullptr;
}

std::shared_ptr<NOM> UIManager::registerMsg(std::wstring msgName) { return mec->registerMsg(msgName); }
void UIManager::discoverMsg(std::shared_ptr<NOM> nomMsg) { mec->discoverMsg(nomMsg); }
void UIManager::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void UIManager::reflectMsg(std::shared_ptr<NOM>) {}
void UIManager::deleteMsg(std::shared_ptr<NOM> nomMsg) { mec->deleteMsg(nomMsg); }
void UIManager::removeMsg(std::shared_ptr<NOM> nomMsg) { mec->removeMsg(nomMsg); }
void UIManager::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }
void UIManager::recvMsg(std::shared_ptr<NOM>) {}
void UIManager::setUserName(std::wstring userName) { name = userName; }
tstring UIManager::getUserName() { return name; }
void UIManager::setData(void*) {}
bool UIManager::start() { return true; }
bool UIManager::stop() { return true; }
void UIManager::setMEBComponent(IMEBComponent* realMEB) { meb = realMEB; mec->setMEB(meb); }

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new UIManager; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }