using MiniProject_GUI.Infrastructure;
using MiniProject_GUI.Models.Converter;
using MiniProject_GUI.Models.Scenario;
using nframework.nom;

namespace MiniProject_GUI.Services
{
    internal class ScenarioService
    {
        // 0x01
        public static void SendSendScenario(ScenarioSend scenarioSend)
        {
            EventAggregator.Instance.Publish(scenarioSend);
        }

        // 0x02
        public static void ReceiveSendScenarioAck(NOM nomMsg)
        {
            EventAggregator.Instance.Publish
            (
                NOMConverter.Import<ScenarioSendAck>(nomMsg)
            );
        }
    }
}
