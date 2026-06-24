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
	//setIDNameTable(20512, _T("LTE_SEND_MESSAGE_UDP"));
	//setIDNameTable(20528, _T("RTI_SEND_MESSAGE_UDP"));
}

void
CommMessageHandler::release()
{
	idNameTable.clear();
}

/************************************************************************
	ID_Name table management
************************************************************************/
void CommMessageHandler::setIDNameTable(
	std::uint32_t msgID,
	const tstring& msgName)
{
	idNameTable[msgID] = msgName;
}

tstring CommMessageHandler::getMsgName(
	std::uint32_t msgID) const
{
	const auto itr = idNameTable.find(msgID);

	if (itr == idNameTable.end())
		return _T("");

	return itr->second;
}