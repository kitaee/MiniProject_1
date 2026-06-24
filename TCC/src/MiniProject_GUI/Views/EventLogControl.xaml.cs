using MiniProject_GUI.ViewModels;
using System.Windows.Controls;

namespace MiniProject_GUI.Views
{
    /// <summary>
    /// 수신 이벤트 이력 표시 View (code-behind).
    ///
    /// DataContext = EventLogViewModel
    /// XAML의 {Binding Logs}는 EventLogViewModel.Logs에 직접 바인딩된다.
    /// </summary>
    public partial class EventLogControl : UserControl
    {
        public EventLogControl()
        {
            InitializeComponent();
            DataContext = ViewModelLocator.EventLog;
        }
    }
}
