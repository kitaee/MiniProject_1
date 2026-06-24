using MiniProject_GUI.Models.Converter;
using nframework.nom;

namespace MiniProject_GUI.Models.Simualation
{
    /// <summary>
    /// 모의기 → TCC: 시뮬레이션 시작 ACK 메시지 (NOM ID: 0x04)
    ///
    /// [확장 가이드]
    /// ScenarioSendAck와 동일한 구조(INOMConvertible + SimulatorID)이므로,
    /// 같은 방식으로 처리할 수 있다.
    ///
    /// 수신 흐름:
    ///   MainWindow.OnNOMMessageReceived("StartSimulationAck")
    ///   → SimulationService.ReceiveStartSimulationAck()
    ///   → EventAggregator.Publish&lt;SimulationStartAck&gt;()
    ///   → 구독자(ViewModel 또는 View)가 처리
    /// </summary>
    internal class SimulationStartAck : INOMConvertible
    {
        /// <summary>ACK를 보낸 시뮬레이터 ID (ATS=102, LCS=101 등)</summary>
        public ushort SimulatorID { get; set; }

        public SimulationStartAck() { }

        public void Import(NOM nom)
        {
            SimulatorID = nom.getValue("SimulatorID").toUShort();
        }
    }
}
