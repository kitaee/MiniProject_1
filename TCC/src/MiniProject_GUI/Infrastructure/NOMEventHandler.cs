using MiniProject_GUI.Models.Scenario;
using MiniProject_GUI.Models.Simualation;
using MiniProject_GUI.Models.Coordinate;
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

                var startPosition = EcefCoordinateConverter.ToEcefXY(
                    scenarioSend.StartLatitude,
                    scenarioSend.StartLongitude);
                var endPosition = EcefCoordinateConverter.ToEcefXY(
                    scenarioSend.EndLatitude,
                    scenarioSend.EndLongitude);
                var radarPosition = EcefCoordinateConverter.ToEcefXY(
                    scenarioSend.RadarPositionLatitude,
                    scenarioSend.RadarPositionLongitude);
                var launcherPosition = EcefCoordinateConverter.ToEcefXY(
                    scenarioSend.LauncherPositionLatitude,
                    scenarioSend.LauncherPositionLongitude);

                nomInstance.setValue("Airthreat.AirthreatID", new NUInteger(scenarioSend.AirthreatID));
                nomInstance.setValue("Airthreat.AirthreatVelocity", new NFloat(scenarioSend.AirthreatVelocity));
                nomInstance.setValue("Airthreat.StartXPos", new NFloat(startPosition.XPos));
                nomInstance.setValue("Airthreat.StartYPos", new NFloat(startPosition.YPos));
                nomInstance.setValue("Airthreat.EndXPos", new NFloat(endPosition.XPos));
                nomInstance.setValue("Airthreat.EndYPos", new NFloat(endPosition.YPos));

                nomInstance.setValue("RadarXPos", new NFloat(radarPosition.XPos));
                nomInstance.setValue("RadarYPos", new NFloat(radarPosition.YPos));
                nomInstance.setValue("LauncherXPos", new NFloat(launcherPosition.XPos));
                nomInstance.setValue("LauncherYPos", new NFloat(launcherPosition.YPos));
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
    }
}
