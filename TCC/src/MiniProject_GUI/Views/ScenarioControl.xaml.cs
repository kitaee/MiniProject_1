using MiniProject_GUI.ViewModels;
using System.Windows.Controls;

namespace MiniProject_GUI.Views
{
    /// <summary>
    /// ATS 연동 확인 버튼과 ACK 상태 표시등 View (code-behind).
    ///
    /// [MVVM 전환 후 code-behind의 역할]
    /// DataContext = ViewModelLocator.AckStatus (ViewModel이 DataContext)
    /// 현재 MVVM:
    ///   DataContext = AckStatusViewModel → XAML이 ViewModel 속성에 직접 바인딩
    ///   Command="{Binding CheckAtsConnectionCommand}" → 로직이 ViewModel에 있음
    ///   code-behind에는 InitializeComponent + DataContext 설정만 남음
    ///
    /// [확장 가이드]
    /// 새 ViewModel을 이 View에 연결하려면 ViewModelLocator에 ViewModel을 추가하고
    /// DataContext를 바꾸면 된다. code-behind를 건드릴 필요가 없다.
    /// </summary>
    public partial class ScenarioControl : UserControl
    {
        public ScenarioControl()
        {
            InitializeComponent();

            // ViewModel을 DataContext로 설정한다.
            // XAML의 {Binding IsAtsAckReceived}, {Binding CheckAtsConnectionCommand} 등은
            // 모두 이 AckStatusViewModel 인스턴스에서 속성을 찾는다.
            DataContext = ViewModelLocator.AckStatus;
        }
    }
}
