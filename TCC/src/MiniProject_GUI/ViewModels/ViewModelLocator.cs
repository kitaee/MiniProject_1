using System;

namespace MiniProject_GUI.ViewModels
{
    /// <summary>
    /// 앱 전체에서 공유하는 ViewModel 인스턴스를 관리하는 레지스트리.
    ///
    /// [Lazy&lt;T&gt; 패턴 — 지연 초기화 싱글톤]
    /// Lazy&lt;T&gt;는 해당 속성에 처음 접근하는 순간 딱 한 번만 인스턴스를 생성한다.
    /// 이후에는 항상 같은 인스턴스를 반환하므로, 여러 View가 동일한 ViewModel 상태를 공유한다.
    ///
    /// [사용 예시]
    /// code-behind: public AckStatusViewModel AckVM => ViewModelLocator.AckStatus;
    /// XAML:        {Binding AckVM.IsAtsAckReceived}
    ///
    /// [확장 가이드]
    /// 새 ViewModel을 추가하려면:
    ///   1. private static Lazy&lt;NewViewModel&gt; _newViewModel = Create(() => new NewViewModel());
    ///   2. public static NewViewModel New => _newViewModel.Value;
    ///   3. View의 code-behind에 public NewViewModel NewVM => ViewModelLocator.New; 추가
    /// </summary>
    public static class ViewModelLocator
    {
        static ViewModelLocator() { }

        // ── 현재 사용 중인 ViewModel ──────────────────────────────────────────

        /// <summary>StatusView: SimulatorState 하트비트 기반 연결 상태 표시</summary>
        private static Lazy<StatusViewModel> _statusViewModel
            = Create(() => new StatusViewModel());

        /// <summary>EventLogControl: 수신 이벤트 이력 표시</summary>
        private static Lazy<EventLogViewModel> _eventLogViewModel
            = Create(() => new EventLogViewModel());

        /// <summary>
        ///  
        /// AckStatusViewModel: ATS SendScenarioAck 수신 상태 → 표시등 제어
        /// </summary>
        private static Lazy<AckStatusViewModel> _ackStatusViewModel
            = Create(() => new AckStatusViewModel());

        // ── 공개 접근자 ───────────────────────────────────────────────────────

        public static StatusViewModel    Status    => _statusViewModel.Value;
        public static EventLogViewModel  EventLog  => _eventLogViewModel.Value;

        /// <summary>
        /// ScenarioControl.xaml.cs에서 ViewModelLocator.AckStatus 로 접근한다.
        /// </summary>
        public static AckStatusViewModel AckStatus => _ackStatusViewModel.Value;

        // ─────────────────────────────────────────────────────────────────────

        private static Lazy<T> Create<T>(Func<T> factory) => new Lazy<T>(factory);
    }
}
