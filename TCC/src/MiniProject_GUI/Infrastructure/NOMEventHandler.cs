using MiniProject_GUI.Models.Scenario;
using MiniProject_GUI.Models.Simualation;
using nframework.nom;
using NOMHandlerLib.Concrete;
using System;
using System.Windows;

namespace MiniProject_GUI.Infrastructure
{
    internal class NOMEventHandler
    {
        private NOMHandler nomHandler = null;

        public NOMEventHandler() { }

        public NOMEventHandler(NOMHandler nomHandler)
        {
            this.nomHandler = nomHandler;
        }

        public void SetNOMEventHandler(NOMHandler nomHandler)
        {
            this.nomHandler = nomHandler;
        }

        public void SendScenario(ScenarioSend scenarioSend)
        {
            var nomInstance = nomHandler.GetNMessage("DeployScenarioRequest")?.createNOMInstance();
            if (nomInstance == null)
            {
                MessageBox.Show(
                    "DeployScenarioRequest NOM 정의를 찾을 수 없습니다.\nUIManager/UDPCommunicationManager NOM XML 로딩 경로를 확인하세요.",
                    "NOM 메시지 오류",
                    MessageBoxButton.OK,
                    MessageBoxImage.Warning);
                return;
            }

            try
            {
                nomInstance.owner = "UIManager";
                nomInstance.setValue("MessageHeader.MessageID", new NUInteger(ScenarioSend.MessageId));
                nomInstance.setValue("MessageHeader.MessageLength", new NUInteger(ScenarioSend.MessageLengthBytes));

                nomInstance.setValue("Airthreat.AirthreatID", new NUInteger(scenarioSend.AirthreatID));
                nomInstance.setValue("Airthreat.AirthreatVelocity", new NFloat(scenarioSend.AirthreatVelocity));
                nomInstance.setValue("Airthreat.StartXPos", new NFloat(scenarioSend.StartLongitude));
                nomInstance.setValue("Airthreat.StartYPos", new NFloat(scenarioSend.StartLatitude));
                nomInstance.setValue("Airthreat.EndXPos", new NFloat(scenarioSend.EndLongitude));
                nomInstance.setValue("Airthreat.EndYPos", new NFloat(scenarioSend.EndLatitude));

                nomInstance.setValue("RadarXPos", new NFloat(scenarioSend.RadarPositionLongitude));
                nomInstance.setValue("RadarYPos", new NFloat(scenarioSend.RadarPositionLatitude));
                nomInstance.setValue("LauncherXPos", new NFloat(scenarioSend.LauncherPositionLongitude));
                nomInstance.setValue("LauncherYPos", new NFloat(scenarioSend.LauncherPositionLatitude));
                nomInstance.setValue("MissileVelocity", new NFloat(scenarioSend.MissileVelocity));

                nomHandler.SendNOMMessage(nomInstance);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        public void StartSimulation(SimulationStart _)
        {
            var nomInstance = nomHandler.GetNMessage("StartSimulationCommand")?.createNOMInstance();
            if (nomInstance == null) return;

            try
            {
                nomInstance.owner = "UIManager";
                nomInstance.setValue("MessageHeader.MessageID", new NUInteger(SimulationStart.CommandMessageId));
                nomInstance.setValue("MessageHeader.MessageLength", new NUInteger(SimulationStart.MessageLengthBytes));
                nomHandler.SendNOMMessage(nomInstance);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        public void StopSimulation(SimulationStop _)
        {
            var nomInstance = nomHandler.GetNMessage("StopSimulationCommand")?.createNOMInstance();
            if (nomInstance == null) return;

            try
            {
                nomInstance.owner = "UIManager";
                nomInstance.setValue("MessageHeader.MessageID", new NUInteger(SimulationStop.CommandMessageId));
                nomInstance.setValue("MessageHeader.MessageLength", new NUInteger(SimulationStop.MessageLengthBytes));
                nomHandler.SendNOMMessage(nomInstance);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        public void LaunchMissile(LaunchMissileRequest launchMissileRequest)
        {
            var nomInstance = nomHandler.GetNMessage("LaunchMissileCommand")?.createNOMInstance();
            if (nomInstance == null) return;

            try
            {
                nomInstance.owner = "UIManager";
                nomInstance.setValue("MessageHeader.MessageID", new NUInteger(LaunchMissileRequest.CommandMessageId));
                nomInstance.setValue("MessageHeader.MessageLength", new NUInteger(LaunchMissileRequest.MessageLengthBytes));
                nomInstance.setValue("AirthreatID", new NUInteger(launchMissileRequest.AirthreatID));
                nomInstance.setValue("AirthreatXPos", new NFloat(launchMissileRequest.AirthreatXPos));
                nomInstance.setValue("AirthreatYPos", new NFloat(launchMissileRequest.AirthreatYPos));
                nomInstance.setValue("MissileID", new NUInteger(launchMissileRequest.MissileID));
                nomHandler.SendNOMMessage(nomInstance);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        public void SendUplinkInfo(UplinkInfo uplinkInfo)
        {
            var nomInstance = nomHandler.GetNMessage("UplinkInfo")?.createNOMInstance();
            if (nomInstance == null) return;

            try
            {
                nomInstance.owner = "UIManager";
                nomInstance.setValue("MessageHeader.MessageID", new NUInteger(UplinkInfo.MessageId));
                nomInstance.setValue("MessageHeader.MessageLength", new NUInteger(UplinkInfo.MessageLengthBytes));
                nomInstance.setValue("UplinkInfo.AirthreatID", new NUInteger(uplinkInfo.AirthreatID));
                nomInstance.setValue("UplinkInfo.AirthreatXPos", new NFloat(uplinkInfo.AirthreatXPos));
                nomInstance.setValue("UplinkInfo.AirthreatYPos", new NFloat(uplinkInfo.AirthreatYPos));
                nomInstance.setValue("UplinkInfo.MissileID", new NUInteger(uplinkInfo.MissileID));
                nomInstance.setValue("UplinkInfo.AirthreatVelocity", new NFloat(uplinkInfo.AirthreatVelocity));
                nomHandler.SendNOMMessage(nomInstance);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
    }
}
