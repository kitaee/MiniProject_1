using MiniProject_GUI.ViewModels;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace MiniProject_GUI.Views
{
    /// <summary>
    /// SimulatorState 하트비트 기반 연결 상태 표시 View (code-behind).
    ///
    /// DataContext = StatusViewModel
    /// XAML의 {Binding IsLauncherConnected} 등은 StatusViewModel 속성에 직접 바인딩된다.
    /// </summary>
    public partial class StatusView : UserControl
    {
        public StatusView()
        {
            InitializeComponent();
            DataContext = ViewModelLocator.AckStatus;
        }

        private void ScenarioAckCard_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            if (sender is FrameworkElement element && element.Tag is string simulatorName)
                ViewModelLocator.AckStatus.ToggleScenarioAck(simulatorName);
        }
    }
}
