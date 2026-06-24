#pragma once
#include <nFramework/util/IniHandler.h>

class DDSMessageTable
{
public:
	DDSMessageTable(void);
	~DDSMessageTable(void);

	tstring getMsgName(unsigned int msgID);

private:

	void initialize();
	void release();
	void createMsgNameTable();
	void removeMsgNameTable();

private:
	std::map<unsigned int, tstring> ID_NameTable;
};
