using MiniProject_GUI.Infrastructure;
using MiniProject_GUI.Models;
using MiniProject_GUI.Models.Enum;
using MiniProject_GUI.Models.Simulation;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using System.Timers;
using System.Windows;

namespace MiniProject_GUI.ViewModels
{
    public class StatusViewModel : INotifyPropertyChanged, IDisposable
    {
        private bool _subscribed = false;
        private readonly Dictionary<SimulatorID, DateTime> _lastReceived = new Dictionary<SimulatorID, DateTime>();
        private readonly Timer _statusCheckTimer;

        public StatusViewModel()
        {
            if (_subscribed) return;
            _subscribed = true;

            // SimulatorID 메시지 구독
            EventAggregator.Instance.Subscribe<SimulatorState>(ReceiveSimulatorState);

            _statusCheckTimer = new Timer(1000);
            _statusCheckTimer.Elapsed += CheckConnectionTimeouts;
            _statusCheckTimer.Start();
        }

        private bool _isLauncherConnected;
        private bool _isMissileConnected;
        private bool _isRadarConnected;
        private bool _isAirThreatConnected;

        public bool IsLauncherConnected
        {
            get => _isLauncherConnected;
            set { _isLauncherConnected = value; OnPropertyChanged(); }
        }

        public bool IsMissileConnected
        {
            get => _isMissileConnected;
            set { _isMissileConnected = value; OnPropertyChanged(); }
        }

        public bool IsRadarConnected
        {
            get => _isRadarConnected;
            set { _isRadarConnected = value; OnPropertyChanged(); }
        }

        public bool IsAirThreatConnected
        {
            get => _isAirThreatConnected;
            set { _isAirThreatConnected = value; OnPropertyChanged(); }
        }

        private void ReceiveSimulatorState(SimulatorState simulatorState)
        {
            SimulatorID id = (SimulatorID)simulatorState.SimulatorID;
            _lastReceived[id] = DateTime.Now;
            string timeStr = DateTime.Now.ToString("HH:mm:ss");

            Application.Current.Dispatcher.Invoke(() =>
            {
                switch (id)
                {
                    case SimulatorID.LCS: IsLauncherConnected = true; break;
                    case SimulatorID.MSS: IsMissileConnected = true; break;
                    case SimulatorID.MFRS: IsRadarConnected = true; break;
                    case SimulatorID.ATS: IsAirThreatConnected = true; break;
                }
            });

            //Console.WriteLine($"{timeStr} | {id} 상태 수신 ✅");
        }


        private void CheckConnectionTimeouts(object sender, ElapsedEventArgs e)
        {
            DateTime now = DateTime.Now;
            double timeout = 1.5; // 1Hz 기준 약 1.5초 초과 시 끊김 처리

            Application.Current.Dispatcher.Invoke(() =>
            {
                IsLauncherConnected = IsAlive(SimulatorID.LCS, now, timeout);
                IsMissileConnected = IsAlive(SimulatorID.MSS, now, timeout);
                IsRadarConnected = IsAlive(SimulatorID.MFRS, now, timeout);
                IsAirThreatConnected = IsAlive(SimulatorID.ATS, now, timeout);
            });
        }
        private bool IsAlive(SimulatorID id, DateTime now, double limitSeconds)
        {
            if (_lastReceived.TryGetValue(id, out DateTime last))
            {
                double elapsed = (now - last).TotalSeconds;
                if (elapsed > limitSeconds)
                {
                    Console.WriteLine($"{now:HH:mm:ss} | {id} 끊김 ❌ ({elapsed:F1}s)");
                    return false;
                }
                return true;
            }
            return false; // 한 번도 수신 안 됨
        }
        public void Dispose()
        {
            EventAggregator.Instance.Unsubscribe<SimulatorState>(ReceiveSimulatorState);
            _statusCheckTimer?.Stop();
            _statusCheckTimer?.Dispose();
        }

        public event PropertyChangedEventHandler PropertyChanged;
        private void OnPropertyChanged([CallerMemberName] string name = null)
            => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
    }
}
