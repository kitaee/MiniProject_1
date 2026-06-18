#include "CommMessageHandler.h"

/************************************************************************
	initialize / release
************************************************************************/
CommMessageHandler::CommMessageHandler()
{
	initialize();
}

CommMessageHandler::~CommMessageHandler()
{
	release();
}

void
CommMessageHandler::initialize()
{
	// if need be, write your code
	//setIDNameTable(20512, L"LTE_SEND_MESSAGE_UDP");
	//setIDNameTable(20528, L"RTI_SEND_MESSAGE_UDP");
}

void
CommMessageHandler::release()
{
	idNameTable.clear();
}

/************************************************************************
	ID_Name table management
************************************************************************/
void
CommMessageHandler::setIDNameTable(unsigned long msgID, std::wstring msgName)
{
	idNameTable.insert(pair<unsigned long, std::wstring>(msgID, msgName));
}

std::wstring
CommMessageHandler::getMsgName(unsigned long msgID)
{
	std::wstring msgName;
	if (auto itr = idNameTable.find(msgID); itr != idNameTable.end())
	{
		msgName = itr->second;
	}
	else
	{
		msgName = L"";
	}

	return msgName;
}