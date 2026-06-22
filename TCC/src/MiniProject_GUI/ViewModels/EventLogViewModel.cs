using MiniProject_GUI.Infrastructure;
using MiniProject_GUI.Models;
using MiniProject_GUI.Models.Enum;
using MiniProject_GUI.Models.Scenario;
using MiniProject_GUI.Models.Simualation;
using System;
using System.Collections.ObjectModel;

namespace MiniProject_GUI.ViewModels
{
    /// <summary>
    /// 수신된 이벤트 로그를 관리하는 ViewModel.
    ///
    /// 실습 포인트 —> EventAggregator 구독 패턴
    /// EventAggregator.Subscribe&lt;T&gt;(핸들러)를 사용하면
    /// Service가 발행(Publish)하는 이벤트를 이 ViewModel에서 받을 수 있다.
    /// Service와 ViewModel이 서로를 직접 알 필요 없이 이벤트 타입만으로 통신한다.
    ///
    /// [확장 가이드]
    /// 새 이벤트를 로그에 추가하려면:
    ///   1. Subscribe&lt;새Model&gt;(새핸들러) 추가
    ///   2. 핸들러에서 AddLog(메시지) 호출
    ///   3. Dispose()에 Unsubscribe 추가
    /// </summary>
    public class EventLogViewModel : IDisposable
    {
        private bool _subscribed = false;

        /// <summary>
        /// WPF ItemsControl이 이 컬렉션을 바인딩한다.
        /// ObservableCollection은 항목이 추가·삭제될 때 UI에 자동으로 변경을 알린다.
        /// </summary>
        public ObservableCollection<EventLogEntry> Logs { get; set; }
            = new ObservableCollection<EventLogEntry>();

        public EventLogViewModel()
        {
            if (_subscribed) return;
            _subscribed = true;

            // ── 현재 구독 중인 이벤트 ──
            // ScenarioSendAck: ATS 연동 확인 시 ACK 수신 로그
            EventAggregator.Instance.Subscribe<ScenarioSendAck>(OnScenarioSendAck);

            // ── [확장 가이드] 아래 구독을 활성화하여 기능 확장 가능 ──
            // 시뮬레이션 시작·종료 ACK 로그:
            // EventAggregator.Instance.Subscribe<SimulationStartAck>(OnSimulationStartAck);
            // EventAggregator.Instance.Subscribe<SimulationStopAck>(OnSimulationStopAck);
        }

        // ────────────────────────────────────────────
        // 내부 유틸리티
        // ────────────────────────────────────────────

        /// <summary>
        /// 로그 항목을 맨 앞에 삽입한다. 최신 이벤트가 위에 표시된다.
        /// </summary>
        private void AddLog(string message)
        {
            Logs.Insert(0, new EventLogEntry
            {
                Time    = "[" + DateTime.Now.ToString("HH:mm:ss") + "]",
                Message = message
            });

            // 메모리 과부하를 방지하기 위해 최대 1000개를 유지한다.
            if (Logs.Count > 1_000)
                Logs.RemoveAt(Logs.Count - 1);
        }

        /// <summary>시뮬레이터 ID를 이름 문자열로 변환한다.</summary>
        private string GetSimulatorName(ushort simulatorID)
        {
            switch ((SimulatorID)simulatorID)
            {
                case SimulatorID.TCC:  return "TCC";
                case SimulatorID.LCS:  return "LCS";
                case SimulatorID.ATS:  return "ATS";
                case SimulatorID.MSS:  return "MSS";
                case SimulatorID.MFRS: return "MFRS";
                default:               return "Unknown";
            }
        }

        // ────────────────────────────────────────────
        // 이벤트 핸들러
        // ────────────────────────────────────────────

        /// <summary>
        /// SendScenarioAck 수신 시 호출된다.
        /// 어떤 시뮬레이터가 ACK를 응답했는지 로그에 기록한다.
        /// </summary>
        private void OnScenarioSendAck(ScenarioSendAck ack)
        {
            AddLog("[" + GetSimulatorName(ack.SimulatorID) + "] 시나리오 배포 ACK 수신");
        }

        // 확장 가이드, 아래 메서드들을 활성화하면 시뮬레이션 시작·종료 로그를 표시할 수 있다.
        //
        // private void OnSimulationStartAck(SimulationStartAck ack)
        //     => AddLog("[" + GetSimulatorName(ack.SimulatorID) + "] 시뮬레이션 시작");
        //
        // private void OnSimulationStopAck(SimulationStopAck ack)
        //     => AddLog("[" + GetSimulatorName(ack.SimulatorID) + "] 시뮬레이션 종료");

        // ────────────────────────────────────────────
        // 정리 (IDisposable)
        // ────────────────────────────────────────────

        public void Dispose()
        {
            // Subscribe와 쌍으로 반드시 Unsubscribe 해야 메모리 누수를 방지할 수 있다.
            EventAggregator.Instance.Unsubscribe<ScenarioSendAck>(OnScenarioSendAck);
        }
    }
}
