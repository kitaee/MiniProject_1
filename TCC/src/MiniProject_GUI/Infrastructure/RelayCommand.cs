using System;
using System.Windows.Input;

namespace MiniProject_GUI.Infrastructure
{
    /// <summary>
    /// ICommand의 범용 구현체.
    ///
    /// ICommand란?
    /// WPF에서 버튼 클릭 같은 사용자 동작을 ViewModel에 연결하는 인터페이스.
    /// Click="Handler" 대신 Command="{Binding SomeCommand}" 를 사용하면
    /// View가 ViewModel을 직접 참조하지 않아도 동작이 실행된다.
    ///
    /// [사용 예시]
    /// ViewModel 생성자:
    ///   MyCommand = new RelayCommand(ExecuteMyAction);
    ///   MyCommand = new RelayCommand(ExecuteMyAction, () => CanExecute);
    ///
    /// XAML:
    ///   <Button Command="{Binding MyCommand}"/>
    /// </summary>
    public class RelayCommand : ICommand
    {
        private readonly Action _execute;
        private readonly Func<bool> _canExecute;

        /// <param name="execute">Command 실행 시 호출할 메서드</param>
        /// <param name="canExecute">실행 가능 여부를 반환하는 메서드 (null이면 항상 가능)</param>
        public RelayCommand(Action execute, Func<bool> canExecute = null)
        {
            _execute    = execute ?? throw new ArgumentNullException(nameof(execute));
            _canExecute = canExecute;
        }

        /// <summary>
        /// WPF가 버튼 활성화 여부를 다시 평가할 때 자동으로 호출된다.
        /// CommandManager.RequerySuggested에 연결하면 상태 변경 시 UI가 자동으로 갱신된다.
        /// </summary>
        public event EventHandler CanExecuteChanged
        {
            add    => CommandManager.RequerySuggested += value;
            remove => CommandManager.RequerySuggested -= value;
        }

        public bool CanExecute(object parameter) => _canExecute == null || _canExecute();
        public void Execute(object parameter)    => _execute();
    }
}
