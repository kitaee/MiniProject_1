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
	//setIDNameTable(20480, _T("LTE_SEND_MESSAGE"));
	//setIDNameTable(20496, _T("RTI_SEND_MESSAGE"));
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
CommMessageHandler::setIDNameTable(unsigned short msgID, tstring msgName)
{
	idNameTable.insert(pair<unsigned short, tstring>(msgID, msgName));
}

tstring
CommMessageHandler::getMsgName(unsigned short msgID)
{
	tstring msgName;
	if (auto itr = idNameTable.find(msgID); itr != idNameTable.end())
	{
		msgName = itr->second;
	}
	else
	{
		msgName = _T("");
	}

	return msgName;
}