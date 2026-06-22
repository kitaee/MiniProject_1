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
                nomInstance.setValue("MessageHeader.MessageID", new NUInteger(ScenarioSend.MessageId));
                nomInstance.setValue("MessageHeader.MessageLength", new NUInteger(ScenarioSend.MessageLengthBytes));

                nomInstance.setValue("Airthreat.AirthreatID", new NUInteger(scenarioSend.AirthreatID));
                nomInstance.setValue("Airthreat.AirthreatVelocity", new NFloat(scenarioSend.AirthreatVelocity));
                nomInstance.setValue("Airthreat.StartLatitude", new NFloat(scenarioSend.StartLatitude));
                nomInstance.setValue("Airthreat.StartLongitude", new NFloat(scenarioSend.StartLongitude));
                nomInstance.setValue("Airthreat.EndLatitude", new NFloat(scenarioSend.EndLatitude));
                nomInstance.setValue("Airthreat.EndLongitude", new NFloat(scenarioSend.EndLongitude));

                nomInstance.setValue("RadarPositionLatitude", new NFloat(scenarioSend.RadarPositionLatitude));
                nomInstance.setValue("RadarPositionLongitude", new NFloat(scenarioSend.RadarPositionLongitude));
                nomInstance.setValue("LauncherPositionLatitude", new NFloat(scenarioSend.LauncherPositionLatitude));
                nomInstance.setValue("LauncherPositionLongitude", new NFloat(scenarioSend.LauncherPositionLongitude));
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
            var nomInstance = nomHandler.GetNMessage("StartSimulation")?.createNOMInstance();
            if (nomInstance == null) return;

            try
            {
                nomInstance.setValue("Header.MessageID", new NUShort(0x03));
                nomInstance.setValue("Header.MessageLength", new NUShort(2));
                nomHandler.SendNOMMessage(nomInstance);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        public void StopSimulation(SimulationStop _)
        {
            var nomInstance = nomHandler.GetNMessage("StopSimulation")?.createNOMInstance();
            if (nomInstance == null) return;

            try
            {
                nomInstance.setValue("Header.MessageID", new NUShort(0x05));
                nomInstance.setValue("Header.MessageLength", new NUShort(2));
                nomHandler.SendNOMMessage(nomInstance);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
    }
}
