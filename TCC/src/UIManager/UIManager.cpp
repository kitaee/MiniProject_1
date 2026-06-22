#include "UIManager.h"
#include "UIMessageEnum.h"
#include <cassert>

/************************************************************************
	constructor / destructor
************************************************************************/
UIManager::UIManager(void)
{
	initialize();
}

UIManager::~UIManager(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
UIManager::initialize(void)
{
	UIManager::setUserName(_T("UIManager"));
	uiTrackHandler = std::make_unique<UITrackHandler>(this);

	// design by contract
	mec = std::make_unique<MECComponent>();
	mec->setUser(this);
}

void
UIManager::release()
{
	meb = nullptr;
	winHandle = nullptr;
}

/************************************************************************
	inherited functions
************************************************************************/
std::shared_ptr<NOM>
UIManager::registerMsg(tstring msgName)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << msgName << std::endl;

	std::shared_ptr<NOM> nomMsg = mec->registerMsg(msgName);
	registeredMsg.emplace(nomMsg->getInstanceID(), nomMsg);
	return nomMsg;
}

void
UIManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	if (winHandle != nullptr)
	{
		uint nomLen = 0;
		byte* nomBytes = nomMsg->serialize(nomLen);

		NOMInfo nomInfo;

		_tcscpy(nomInfo.MsgName, nomMsg->getName().c_str());
		nomInfo.MsgID = nomMsg->getMessageID();
		nomInfo.MsgInstanceID = nomMsg->getInstanceID();
		nomInfo.MsgLen = nomLen;

		::SendMessage(winHandle, WM_DISCOVERED_MSG_DATA, (WPARAM)&nomInfo, (LPARAM)nomBytes);

		delete[] nomBytes;
	}
}

void
UIManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	nomMsg->setInstanceName(this->getUserName());
	mec->updateMsg(nomMsg);
}

void
UIManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;

	if (winHandle != nullptr && nomMsg != nullptr)
	{
		uint nomLen = 0;
		byte* nomBytes = nomMsg->serialize(nomLen);

		NOMInfo nomInfo;

		_tcscpy(nomInfo.MsgName, nomMsg->getName().c_str());
		nomInfo.MsgID = nomMsg->getMessageID();
		nomInfo.MsgInstanceID = nomMsg->getInstanceID();
		nomInfo.MsgLen = nomLen;
		
		::SendMessage(winHandle, WM_SEND_DATA, (WPARAM)&nomInfo, (LPARAM)nomBytes);
		ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
		delete[] nomBytes;
	}
}

void
UIManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	mec->deleteMsg(nomMsg);
	registeredMsg.erase(nomMsg->getInstanceID());
}

void
UIManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;

	if (winHandle != nullptr && nomMsg != nullptr)
	{
		uint nomLen = 0;
		byte* nomBytes = nomMsg->serialize(nomLen);

		NOMInfo nomInfo;

		_tcscpy(nomInfo.MsgName, nomMsg->getName().c_str());
		nomInfo.MsgID = nomMsg->getMessageID();
		nomInfo.MsgInstanceID = nomMsg->getInstanceID();
		nomInfo.MsgLen = nomLen;

		::SendMessage(winHandle, WM_REMOVED_MSG_DATA, (WPARAM)&nomInfo, (LPARAM)nomBytes);

		delete[] nomBytes;
	}
}

void
UIManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;

	mec->sendMsg(nomMsg);
}


//* Msg send
void
UIManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	ntcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << std::endl;
	
	if (winHandle != nullptr)
	{
		uint nomLen = 0;
		byte* nomBytes = nomMsg->serialize(nomLen);

		NOMInfo nomInfo;

		_tcscpy(nomInfo.MsgName, nomMsg->getName().c_str());
		nomInfo.MsgID = nomMsg->getMessageID();
		nomInfo.MsgLen = nomLen;
		nomInfo.MsgInstanceID = nomMsg->getInstanceID();

		// 직렬화하여 데이터 송신 (C# WPF NOMHandler 에서 수신하여 역직렬화)
		::SendMessage(winHandle, WM_SEND_DATA, (WPARAM)&nomInfo, (LPARAM)nomBytes);

		delete[] nomBytes;
	}
}

void
UIManager::setUserName(tstring userName)
{
	managerName = userName;
}

tstring
UIManager::getUserName()
{
	return managerName;
}

void
UIManager::setData(void* data)
{
	this->winHandle = (HWND)data;
	assert("HWND == 0" && winHandle);
}

bool
UIManager::start()
{
	return true;
}

bool
UIManager::stop()
{
	this->winHandle = nullptr;
	return true;
}

void
UIManager::setMEBComponent(IMEBComponent* realMEB)
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
	return new UIManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager * userManager)
{
	delete userManager;
}