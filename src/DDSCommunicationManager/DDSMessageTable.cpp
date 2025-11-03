#include "DDSMessageTable.h"

/************************************************************************
	constructor / destructor
************************************************************************/
DDSMessageTable::DDSMessageTable(void)
{
	initialize();
}

DDSMessageTable::~DDSMessageTable(void)
{
	release();
}

/************************************************************************
	initialize / release
************************************************************************/
void
DDSMessageTable::initialize()
{
	createMsgNameTable();
}

void
DDSMessageTable::release()
{
	removeMsgNameTable();
}

/************************************************************************
	these methods for managing messages
************************************************************************/
void
DDSMessageTable::createMsgNameTable()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("DDSCommunicationManager/ICD.ini"));

	unsigned int numOfMessages = iniHandler.readInteger(_T("ICD"), _T("Count"));

	for (unsigned int cnt = 1; cnt <= numOfMessages; cnt++)
	{
		tstringstream msgPrefix;
		msgPrefix << _T("Msg_") << cnt;

		tstring msgIdx;
		msgPrefix >> msgIdx;

		unsigned int msgID = iniHandler.readInteger(msgIdx, _T("ID"));
		tstring msgName = iniHandler.readString(msgIdx, _T("Name"));

		ID_NameTable.emplace(msgID, msgName);
	}
}

void
DDSMessageTable::removeMsgNameTable()
{
	ID_NameTable.clear();
}

tstring
DDSMessageTable::getMsgName(unsigned int msgID)
{
	tstring msgName;
	auto itr = ID_NameTable.find(msgID);

	if(itr != ID_NameTable.end())
	{
		msgName = itr->second;
	}
	else
	{
		msgName = _T("");
	}

	return msgName;
}
