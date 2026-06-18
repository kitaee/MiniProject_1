#pragma once
#include <map>
#include <nFramework/util/util.h>
using namespace std;
class CommMessageHandler
{
public:
	CommMessageHandler();
	~CommMessageHandler();

	tstring getMsgName(unsigned long msgID);
	void setIDNameTable(unsigned long msgID, tstring msgName);

private:
	void initialize();
	void release();

private:
	map<unsigned long, tstring > idNameTable;
};

