using MiniProject_GUI.Infrastructure;
using MiniProject_GUI.Models.Enum;
using MiniProject_GUI.Models.Scenario;
using MiniProject_GUI.Services;
using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows.Input;

namespace MiniProject_GUI.ViewModels
{
    /// <summary>
    /// ATS SendScenarioAck 수신 상태를 관리하고 WPF 표시등을 제어하는 ViewModel.
    ///
    /// ┌──────────────────────────────────────────────────────────────────────────┐
    /// │  [MVVM 구조에서 이 클래스의 역할]                                          │
    /// │                                                                          │
    /// │  View(ScenarioControl.xaml)는 이 ViewModel을 DataContext로 사용한다.      │
    /// │  View는 상태를 직접 보관하지 않고 Binding과 Command로만 ViewModel에 접근.  │
    /// │                                                                          │
    /// │  버튼 클릭 → Command → ViewModel 메서드 실행 (Click 이벤트 없음)          │
    /// │  상태 변경 → INotifyPropertyChanged → WPF Binding → UI 자동 갱신         │
    /// └──────────────────────────────────────────────────────────────────────────┘
    ///
    /// ┌──────────────────────────────────────────────────────────────────────────┐
    /// │  ATS 연동 확인 전체 흐름                                                   │
    /// │                                                                          │
    /// │  버튼 클릭 → CheckAtsConnectionCommand.Execute()                          │
    /// │    → Reset() + ScenarioService.SendSendScenario()                        │
    /// │    → NOMEventHandler.SendScenario() → UDP 송신                           │
    /// │                                                                          │
    /// │  ATS → SendScenarioAck(SimulatorID=102)                                 │
    /// │    → MainWindow → ScenarioService → EventAggregator.Publish             │
    /// │    → OnScenarioSendAck() → IsAtsAckReceived = true                      │
    /// │    → PropertyChanged → DataTrigger → Ellipse.Fill: Gray → LimeGreen   │
    /// └──────────────────────────────────────────────────────────────────────────┘
    ///
    /// 
    /// 같은 패턴으로 StartSimulationAck, StopSimulationAck 상태를 관리하는
    /// SimulationViewModel을 추가할 수 있다.
    /// </summary>
    public class AckStatusViewModel : INotifyPropertyChanged, IDisposable
    {
        private bool _isAtsAckReceived = false;

        public AckStatusViewModel()
        {
            EventAggregator.Instance.Subscribe<ScenarioSendAck>(OnScenarioSendAck);

            // 실습 포인트 —> ICommandScenarioService
            // View의 버튼이 Command="{Binding CheckAtsConnectionCommand}"로 연결된다.
            // 버튼 클릭 시 Click 이벤트 핸들러(code-behind) 없이 Execute()가 호출된다.
            CheckAtsConnectionCommand = new RelayCommand(ExecuteCheckAtsConnection);
        }

        // ────────────────────────────────────────────
        // Command (View → ViewModel 동작 바인딩)
        // ────────────────────────────────────────────

        /// <summary>
        /// "ATS 연동 확인" 버튼에 바인딩되는 Command.
        /// XAML: Command="{Binding CheckAtsConnectionCommand}"
        ///
        ///  
        /// Click="Handler" 방식과 달리, 실행 로직이 code-behind가 아닌
        /// ViewModel 안에 있으므로 View를 띄우지 않고도 동작을 테스트할 수 있다.
        /// </summary>
        public ICommand CheckAtsConnectionCommand { get; }

        private void ExecuteCheckAtsConnection()
        {
            Reset();
            ScenarioService.SendSendScenario(new ScenarioSend());
        }

        // ────────────────────────────────────────────
        // WPF Binding 대상 속성
        // ────────────────────────────────────────────

        /// <summary>
        /// ATS ACK 수신 여부.
        /// XAML DataTrigger가 이 값을 감시한다:
        ///   false → Ellipse.Fill = Gray
        ///   true  → Ellipse.Fill = LimeGreen
        /// </summary>
        public bool IsAtsAckReceived
        {
            get => _isAtsAckReceived;
            private set
            {
                if (_isAtsAckReceived == value) return;
                _isAtsAckReceived = value;
                OnPropertyChanged();
                OnPropertyChanged(nameof(AtsAckStatusText));
            }
        }

        /// <summary>
        /// 표시등 옆 문구. IsAtsAckReceived 변경 시 함께 갱신된다.
        /// XAML: Text="{Binding AtsAckStatusText}"
        /// </summary>
        public string AtsAckStatusText =>
            IsAtsAckReceived ? "ATS 연동 성공" : "ATS ACK 대기";

        // ────────────────────────────────────────────
        // 공개 메서드
        // ────────────────────────────────────────────

        /// <summary>새 연동 확인 전에 이전 상태를 초기화한다.</summary>
        public void Reset() => IsAtsAckReceived = false;

        // ────────────────────────────────────────────
        // 이벤트 핸들러
        // ────────────────────────────────────────────

        private void OnScenarioSendAck(ScenarioSendAck ack)
        {
            if ((SimulatorID)ack.SimulatorID != SimulatorID.ATS) return;

            Console.WriteLine("[AckStatusViewModel] ATS SendScenarioAck 수신");

            System.Windows.Application.Current.Dispatcher.Invoke(() =>
            {
                IsAtsAckReceived = true;
            });
        }

        // ────────────────────────────────────────────
        // INotifyPropertyChanged
        // ────────────────────────────────────────────

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged([CallerMemberName] string name = null)
            => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));

        // ────────────────────────────────────────────
        // IDisposable
        // ────────────────────────────────────────────

        public void Dispose()
        {
            EventAggregator.Instance.Unsubscribe<ScenarioSendAck>(OnScenarioSendAck);
        }
    }
}
