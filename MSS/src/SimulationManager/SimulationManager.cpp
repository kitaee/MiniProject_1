#include "SimulationManager.h"

SimulationManager::SimulationManager()
{
	initialize();
}

SimulationManager::~SimulationManager()
{
	release();
}

std::shared_ptr<NOM> SimulationManager::registerMsg(tstring str)
{
	tcout << _T("[") << _T(__FUNCTION__) << _T("] ") << str << "\n";

	std::shared_ptr<NOM> nomMsg = mec->registerMsg(str);
	registeredMsgMap.emplace(nomMsg->getInstanceID(), nomMsg);
	return nomMsg;
}

void SimulationManager::discoverMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << "\n";
}

void SimulationManager::updateMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << "\n";
}

void SimulationManager::reflectMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << "\n";
}

void SimulationManager::deleteMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << "\n";
}

void SimulationManager::removeMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << "\n";
}

void SimulationManager::sendMsg(std::shared_ptr<NOM> nomMsg)
{
	tcout << _T("[") << _T(__FUNCTION__) << _T("] ") << nomMsg->getName() << "\n";
}

void SimulationManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
	if (auto iter = funcMap.find(nomMsg->getName()); iter != funcMap.end())
	{
		iter->second(nomMsg);
	}
}

void SimulationManager::setUserName(tstring userName)
{
	name = userName;
}

tstring SimulationManager::getUserName()
{
	return name;
}

void SimulationManager::setData(void* data)
{
	tcout << _T("[") << _T(__FUNCTION__) << _T("] ") << "\n";
}

bool SimulationManager::start()
{
	IniHandler iniHandler;
	iniHandler.readIni(_T("SimulationManager/SimulationManager.ini")); // ※주의 작업디렉터리: Main.exe가 있는 경로

	tcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;

	return true;
}

bool SimulationManager::stop()
{
	return true;
}

void SimulationManager::setMEBComponent(IMEBComponent* realMEB)
{
	meb = realMEB;
	mec->setMEB(meb);
}

void SimulationManager::initialize()
{
	tcout << _T("[") << _T(__FUNCTION__) << _T("] ") << std::endl;

	setUserName(_T("SimulationManager"));

	// design by contract
	mec = new MECComponent;
	mec->setUser(this);

	funcMapInit();
}

void SimulationManager::release()
{
	delete mec;
	mec = nullptr;
	meb = nullptr;

	funcMap.clear();
}

void SimulationManager::funcMapInit()
{
	function<void(shared_ptr<NOM>)> msgProc;

	msgProc = bind(&SimulationManager::recvInnerSendScenario, this, placeholders::_1);
	funcMap.insert({ _T("InnerSendScenario"), msgProc });

	msgProc = bind(&SimulationManager::recvInnerStartSimulation, this, placeholders::_1);
	funcMap.insert({ _T("InnerStartSimulation"), msgProc });

	msgProc = bind(&SimulationManager::recvInnerStopSimulation, this, placeholders::_1);
	funcMap.insert({ _T("InnerStopSimulation"), msgProc });
}


void SimulationManager::recvInnerSendScenario(std::shared_ptr<NOM> nomMsg)
{
	auto nomMsgToModel = meb->getNOMInstance(name, _T("InnerSendScenarioToModel"));

	NDouble temp = nomMsg->getValue(_T("Scenario.WayPoint0_X"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.WayPoint0_X"), &temp);
	temp = nomMsg->getValue(_T("Scenario.WayPoint0_Y"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.WayPoint0_Y"), &temp);
	temp = nomMsg->getValue(_T("Scenario.WayPoint1_X"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.WayPoint1_X"), &temp);
	temp = nomMsg->getValue(_T("Scenario.WayPoint1_Y"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.WayPoint1_Y"), &temp);
	temp = nomMsg->getValue(_T("Scenario.WayPoint2_X"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.WayPoint2_X"), &temp);
	temp = nomMsg->getValue(_T("Scenario.WayPoint2_Y"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.WayPoint2_Y"), &temp);
	temp = nomMsg->getValue(_T("Scenario.WayPoint3_X"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.WayPoint3_X"), &temp);
	temp = nomMsg->getValue(_T("Scenario.WayPoint3_Y"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.WayPoint3_Y"), &temp);
	temp = nomMsg->getValue(_T("Scenario.OriginLat"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.OriginLat"), &temp);
	temp = nomMsg->getValue(_T("Scenario.OriginLng"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.OriginLng"), &temp);

	temp = nomMsg->getValue(_T("Scenario.WayPoint0_Lat"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.WayPoint0_Lat"), &temp);


	temp = nomMsg->getValue(_T("Scenario.WayPoint0_Lng"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.WayPoint0_Lng"), &temp);


	temp = nomMsg->getValue(_T("Scenario.WayPoint1_Lat"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.WayPoint1_Lat"), &temp);


	temp = nomMsg->getValue(_T("Scenario.WayPoint1_Lng"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.WayPoint1_Lng"), &temp);


	temp = nomMsg->getValue(_T("Scenario.WayPoint2_Lat"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.WayPoint2_Lat"), &temp);


	temp = nomMsg->getValue(_T("Scenario.WayPoint2_Lng"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.WayPoint2_Lng"), &temp);


	temp = nomMsg->getValue(_T("Scenario.WayPoint3_Lat"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.WayPoint3_Lat"), &temp);


	temp = nomMsg->getValue(_T("Scenario.WayPoint3_Lng"))->toDouble();
	nomMsgToModel->setValue(_T("Scenario.WayPoint3_Lng"), &temp);


	mec->sendMsg(nomMsgToModel);

	auto nomMsgAck = meb->getNOMInstance(name, _T("InnerSendScenarioAck"));
	NUShort simulatorID = NUShort((ushort)SimulatorID::ATS);
	nomMsgAck->setValue(_T("SimulatorID"), &simulatorID);

	mec->sendMsg(nomMsgAck);
}

void SimulationManager::recvInnerStartSimulation(std::shared_ptr<NOM> nomMsg)
{
	auto nomMsgToModel = meb->getNOMInstance(name, _T("InnerStartSimulationToModel"));

	mec->sendMsg(nomMsgToModel);


	auto nomMsgAck = meb->getNOMInstance(name, _T("InnerStartSimulationAck"));
	NUShort simulatorID = NUShort((ushort)SimulatorID::ATS);

	nomMsgAck->setValue(_T("SimulatorID"), &simulatorID);

	mec->sendMsg(nomMsgAck);
}

void SimulationManager::recvInnerStopSimulation(std::shared_ptr<NOM> nomMsg)
{
	auto nomMsgToModel = meb->getNOMInstance(name, _T("InnerStopSimulationToModel"));

	mec->sendMsg(nomMsgToModel);


	auto nomMsgAck = meb->getNOMInstance(name, _T("InnerStopSimulationAck"));
	NUShort simulatorID = NUShort((ushort)SimulatorID::ATS);

	nomMsgAck->setValue(_T("SimulatorID"), &simulatorID);

	mec->sendMsg(nomMsgAck);
}

extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
	return new SimulationManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
	delete userManager;
}