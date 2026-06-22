using MiniProject_GUI.Infrastructure;
using MiniProject_GUI.Models.Converter;
using MiniProject_GUI.Models.Simualation;
using MiniProject_GUI.Models.Simulation;
using nframework.nom;

namespace MiniProject_GUI.Services
{
    /// <summary>
    /// 시뮬레이션 제어 관련 NOM 메시지를 처리하는 서비스.
    ///
    /// [Service의 역할]
    /// Service는 NOM 계층과 GUI 내부(EventAggregator) 사이의 경계를 만든다.
    ///   수신: NOM → C# Model로 변환 → EventAggregator.Publish
    ///   송신: EventAggregator.Publish → NOMEventHandler가 NOM 메시지 생성·송신
    ///
    /// [확장 가이드]
    /// 시뮬레이션 시작/종료 기능을 UI에 연결하려면:
    ///   1. SimulationControl.xaml(.cs) View 추가
    ///   2. 버튼 클릭 핸들러에서 SendStartSimulation() / SendStopSimulation() 호출
    ///   3. ViewModels/에 SimulationViewModel 추가하여 ACK 상태 관리
    ///   4. MainWindow.xaml에 SimulationControl 배치
    /// </summary>
    internal class SimulationService
    {
        // ────────────────────────────────────────────
        // 송신 (TCC → 모의기)
        // ────────────────────────────────────────────

        /// <summary>
        /// 시뮬레이션 시작 요청을 EventAggregator로 발행한다. (NOM ID: 0x03)
        /// NOMEventHandler.StartSimulation()이 구독하여 NOM 메시지를 생성·송신한다.
        /// </summary>
        public static void SendStartSimulation()
        {
            EventAggregator.Instance.Publish(new SimulationStart());
        }

        /// <summary>
        /// 시뮬레이션 종료 요청을 EventAggregator로 발행한다. (NOM ID: 0x05)
        /// </summary>
        public static void SendStopSimulation()
        {
            EventAggregator.Instance.Publish(new SimulationStop());
        }

        // ────────────────────────────────────────────
        // 수신 (모의기 → TCC)
        // ────────────────────────────────────────────

        /// <summary>
        /// 시뮬레이션 시작 ACK 수신 처리. (NOM ID: 0x04)
        /// NOM → SimulationStartAck 변환 후 EventAggregator로 발행.
        /// ViewModel에서 Subscribe&lt;SimulationStartAck&gt;()로 구독하여 상태 변경 가능.
        /// </summary>
        public static void ReceiveStartSimulationAck(NOM nomMsg)
        {
            EventAggregator.Instance.Publish(
                NOMConverter.Import<SimulationStartAck>(nomMsg)
            );
        }

        /// <summary>
        /// 시뮬레이션 종료 ACK 수신 처리. (NOM ID: 0x06)
        /// </summary>
        public static void ReceiveStopSimulationAck(NOM nomMsg)
        {
            EventAggregator.Instance.Publish(
                NOMConverter.Import<SimulationStopAck>(nomMsg)
            );
        }

        /// <summary>
        /// 각 시뮬레이터의 하트비트 상태 메시지 수신 처리. (NOM ID: 0x0b)
        ///
        /// [동작 설명]
        /// ATS, LCS 등의 모의기가 1초 주기로 SimulatorState를 송신한다.
        /// StatusViewModel이 이를 구독하여 표시등의 연결 상태를 판단한다.
        /// 1.5초 이상 수신이 없으면 해당 모의기를 "끊김"으로 처리한다.
        /// </summary>
        public static void ReceiveSimulatorState(NOM nomMsg)
        {
            EventAggregator.Instance.Publish(
                NOMConverter.Import<SimulatorState>(nomMsg)
            );
        }
    }
}
