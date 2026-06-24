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
	setIDNameTable(1001, _T("DeployScenarioRequest"));
	setIDNameTable(1002, _T("StartSimulationRequest"));
	setIDNameTable(1003, _T("StopSimulationRequest"));
	setIDNameTable(3201, _T("DetonationInfo"));
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