using MiniProject_GUI.Infrastructure;
using MiniProject_GUI.Models.Enum;
using MiniProject_GUI.Models.Scenario;
using MiniProject_GUI.Services;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.Runtime.CompilerServices;
using System.Text;
using System.Windows;
using System.Windows.Input;

namespace MiniProject_GUI.ViewModels
{
    public class AckStatusViewModel : INotifyPropertyChanged, IDisposable
    {
        private const string ScenarioIncompleteMessage =
            "시나리오 입력이 완료되지 않았습니다. 레이다·발사대·공중위협을 모두 입력하고 저장한 뒤 모의 모드로 전환하세요.";

        private bool _isEditMode;
        private bool _hasUnsavedChanges;
        private bool _isScenarioDeployed;
        private bool _isLoadingInputs;
        private ScenarioSend _savedScenario;
        private string _selectedMapTarget = "Radar";

        private string _radarLatitudeText = "";
        private string _radarLongitudeText = "";
        private string _launcherLatitudeText = "";
        private string _launcherLongitudeText = "";
        private string _startLatitudeText = "";
        private string _startLongitudeText = "";
        private string _endLatitudeText = "";
        private string _endLongitudeText = "";
        private string _airthreatVelocityText = "";

        public AckStatusViewModel()
        {
            EventAggregator.Instance.Subscribe<ScenarioSendAck>(OnScenarioSendAck);

            EditScenarioCommand = new RelayCommand(EnterEditMode, () => !IsEditMode);
            SwitchToSimulationModeCommand = new RelayCommand(EnterSimulationMode, () => IsEditMode);
            SaveScenarioCommand = new RelayCommand(SaveScenario, () => IsEditMode && HasUnsavedChanges);
            DeployScenarioCommand = new RelayCommand(DeployScenario, () => !IsEditMode && HasSavedScenario);
            SelectRadarCommand = new RelayCommand(() => SelectMapTarget("Radar"));
            SelectLauncherCommand = new RelayCommand(() => SelectMapTarget("Launcher"));
            SelectAirthreatStartCommand = new RelayCommand(() => SelectMapTarget("AirthreatStart"));
            SelectAirthreatEndCommand = new RelayCommand(() => SelectMapTarget("AirthreatEnd"));

            CheckAtsConnectionCommand = DeployScenarioCommand;
        }

        public ICommand EditScenarioCommand { get; }
        public ICommand SwitchToSimulationModeCommand { get; }
        public ICommand SaveScenarioCommand { get; }
        public ICommand DeployScenarioCommand { get; }
        public ICommand SelectRadarCommand { get; }
        public ICommand SelectLauncherCommand { get; }
        public ICommand SelectAirthreatStartCommand { get; }
        public ICommand SelectAirthreatEndCommand { get; }
        public ICommand CheckAtsConnectionCommand { get; }

        public bool IsEditMode
        {
            get => _isEditMode;
            private set
            {
                if (_isEditMode == value) return;
                _isEditMode = value;
                OnPropertyChanged();
                OnPropertyChanged(nameof(IsSimulationMode));
                OnPropertyChanged(nameof(ModeText));
                RefreshCommandState();
            }
        }

        public bool IsSimulationMode => !IsEditMode;

        public bool HasSavedScenario => _savedScenario != null;

        public bool HasUnsavedChanges
        {
            get => _hasUnsavedChanges;
            private set
            {
                if (_hasUnsavedChanges == value) return;
                _hasUnsavedChanges = value;
                OnPropertyChanged();
                OnPropertyChanged(nameof(SimulationStatusText));
                RefreshCommandState();
            }
        }

        public bool IsScenarioDeployed
        {
            get => _isScenarioDeployed;
            private set
            {
                if (_isScenarioDeployed == value) return;
                _isScenarioDeployed = value;
                OnPropertyChanged();
                OnPropertyChanged(nameof(DeploymentStatusText));
                RefreshCommandState();
            }
        }

        public string ModeText => IsEditMode ? "편집" : "모의";

        public string SimulationStatusText =>
            HasSavedScenario && !HasUnsavedChanges ? "완료" : "대기";

        public string DeploymentStatusText => IsScenarioDeployed ? "배포" : "미배포";

        public bool HasRadarLocation => HasCoordinate(RadarLatitudeText, RadarLongitudeText);

        public bool HasLauncherLocation => HasCoordinate(LauncherLatitudeText, LauncherLongitudeText);

        public bool HasAirthreatStartLocation => HasCoordinate(StartLatitudeText, StartLongitudeText);

        public bool HasAirthreatEndLocation => HasCoordinate(EndLatitudeText, EndLongitudeText);

        public string SelectedMapTarget
        {
            get => _selectedMapTarget;
            private set
            {
                if (_selectedMapTarget == value) return;
                _selectedMapTarget = value;
                OnPropertyChanged();
                OnPropertyChanged(nameof(SelectedMapTargetText));
            }
        }

        public string SelectedMapTargetText
        {
            get
            {
                switch (SelectedMapTarget)
                {
                    case "Radar":
                        return "레이다";
                    case "Launcher":
                        return "발사대";
                    case "AirthreatStart":
                        return "공중위협 시작";
                    case "AirthreatEnd":
                        return "공중위협 도착";
                    default:
                        return "레이다";
                }
            }
        }

        public string SavedScenarioSummaryText
        {
            get
            {
                if (_savedScenario == null)
                    return "저장된 시나리오가 없습니다.";

                return string.Join(Environment.NewLine, new[]
                {
                    $"레이다: 위도 {Format(_savedScenario.RadarPositionLatitude)}, 경도 {Format(_savedScenario.RadarPositionLongitude)}",
                    $"발사대: 위도 {Format(_savedScenario.LauncherPositionLatitude)}, 경도 {Format(_savedScenario.LauncherPositionLongitude)}",
                    $"공중위협 시작: 위도 {Format(_savedScenario.StartLatitude)}, 경도 {Format(_savedScenario.StartLongitude)}",
                    $"공중위협 도착: 위도 {Format(_savedScenario.EndLatitude)}, 경도 {Format(_savedScenario.EndLongitude)}",
                    $"공중위협 속도: {Format(_savedScenario.AirthreatVelocity)} m/s"
                });
            }
        }

        public string RadarLatitudeText
        {
            get => _radarLatitudeText;
            set => SetInputText(ref _radarLatitudeText, value);
        }

        public string RadarLongitudeText
        {
            get => _radarLongitudeText;
            set => SetInputText(ref _radarLongitudeText, value);
        }

        public string LauncherLatitudeText
        {
            get => _launcherLatitudeText;
            set => SetInputText(ref _launcherLatitudeText, value);
        }

        public string LauncherLongitudeText
        {
            get => _launcherLongitudeText;
            set => SetInputText(ref _launcherLongitudeText, value);
        }

        public string StartLatitudeText
        {
            get => _startLatitudeText;
            set => SetInputText(ref _startLatitudeText, value);
        }

        public string StartLongitudeText
        {
            get => _startLongitudeText;
            set => SetInputText(ref _startLongitudeText, value);
        }

        public string EndLatitudeText
        {
            get => _endLatitudeText;
            set => SetInputText(ref _endLatitudeText, value);
        }

        public string EndLongitudeText
        {
            get => _endLongitudeText;
            set => SetInputText(ref _endLongitudeText, value);
        }

        public string AirthreatVelocityText
        {
            get => _airthreatVelocityText;
            set => SetInputText(ref _airthreatVelocityText, value);
        }

        public void SetMapCoordinate(double latitude, double longitude)
        {
            if (!IsEditMode)
                EnterEditMode();

            string target = SelectedMapTarget;
            string latitudeText = FormatCoordinate(latitude);
            string longitudeText = FormatCoordinate(longitude);

            switch (target)
            {
                case "Radar":
                    RadarLatitudeText = latitudeText;
                    RadarLongitudeText = longitudeText;
                    break;
                case "Launcher":
                    LauncherLatitudeText = latitudeText;
                    LauncherLongitudeText = longitudeText;
                    break;
                case "AirthreatStart":
                    StartLatitudeText = latitudeText;
                    StartLongitudeText = longitudeText;
                    break;
                case "AirthreatEnd":
                    EndLatitudeText = latitudeText;
                    EndLongitudeText = longitudeText;
                    break;
            }

            AdvanceMapTargetAfter(target);
        }

        private void EnterEditMode()
        {
            LoadSavedScenarioIntoInputs();
            IsEditMode = true;
        }

        private void SelectMapTarget(string target)
        {
            SelectedMapTarget = target;
        }

        private void AdvanceMapTargetAfter(string target)
        {
            switch (target)
            {
                case "Radar":
                    SelectMapTarget("Launcher");
                    break;
                case "Launcher":
                    SelectMapTarget("AirthreatStart");
                    break;
                case "AirthreatStart":
                    SelectMapTarget("AirthreatEnd");
                    break;
            }
        }

        private void EnterSimulationMode()
        {
            if (!HasSavedScenario || HasUnsavedChanges)
            {
                MessageBox.Show(
                    ScenarioIncompleteMessage,
                    "시나리오 입력 필요",
                    MessageBoxButton.OK,
                    MessageBoxImage.Warning);
                return;
            }

            IsEditMode = false;
        }

        private void SaveScenario()
        {
            if (!TryCreateScenario(out ScenarioSend scenario, out string errorMessage))
            {
                MessageBox.Show(
                    errorMessage,
                    "시나리오 입력 오류",
                    MessageBoxButton.OK,
                    MessageBoxImage.Warning);
                return;
            }

            _savedScenario = scenario;
            HasUnsavedChanges = false;
            IsScenarioDeployed = false;

            OnPropertyChanged(nameof(HasSavedScenario));
            OnPropertyChanged(nameof(SimulationStatusText));
            OnPropertyChanged(nameof(SavedScenarioSummaryText));
            RefreshCommandState();
        }

        private void DeployScenario()
        {
            if (_savedScenario == null) return;

            ScenarioService.SendSendScenario(_savedScenario);
            IsScenarioDeployed = true;
        }

        private bool TryCreateScenario(out ScenarioSend scenario, out string errorMessage)
        {
            scenario = null;

            var errors = new List<string>();

            float radarLatitude = ParseLatitude(RadarLatitudeText, "레이다 위도", errors);
            float radarLongitude = ParseLongitude(RadarLongitudeText, "레이다 경도", errors);
            float launcherLatitude = ParseLatitude(LauncherLatitudeText, "발사대 위도", errors);
            float launcherLongitude = ParseLongitude(LauncherLongitudeText, "발사대 경도", errors);
            float startLatitude = ParseLatitude(StartLatitudeText, "공중위협 시작 위도", errors);
            float startLongitude = ParseLongitude(StartLongitudeText, "공중위협 시작 경도", errors);
            float endLatitude = ParseLatitude(EndLatitudeText, "공중위협 도착 위도", errors);
            float endLongitude = ParseLongitude(EndLongitudeText, "공중위협 도착 경도", errors);
            float airthreatVelocity = ParsePositiveFloat(AirthreatVelocityText, "공중위협 속도", errors);

            if (errors.Count == 0 &&
                Math.Abs(startLatitude - endLatitude) < float.Epsilon &&
                Math.Abs(startLongitude - endLongitude) < float.Epsilon)
            {
                errors.Add("공중위협 시작 위치와 도착 위치가 같습니다.");
            }

            if (errors.Count > 0)
            {
                var builder = new StringBuilder();
                builder.AppendLine("유효하지 않은 값이 있습니다.");
                foreach (string error in errors)
                    builder.AppendLine("- " + error);

                errorMessage = builder.ToString();
                return false;
            }

            scenario = new ScenarioSend
            {
                AirthreatID = 1,
                AirthreatVelocity = airthreatVelocity,
                StartLatitude = startLatitude,
                StartLongitude = startLongitude,
                EndLatitude = endLatitude,
                EndLongitude = endLongitude,
                RadarPositionLatitude = radarLatitude,
                RadarPositionLongitude = radarLongitude,
                LauncherPositionLatitude = launcherLatitude,
                LauncherPositionLongitude = launcherLongitude,
                // UI 요구사항에 유도탄 속도 입력이 없어 ID 1001 필드는 고정값 0m/s로 채운다.
                MissileVelocity = 0f
            };

            errorMessage = null;
            return true;
        }

        private float ParsePositiveFloat(string text, string displayName, List<string> errors)
        {
            if (!TryParseFloat(text, displayName, errors, out float value))
                return 0;

            if (value <= 0)
                errors.Add(displayName + "는 0보다 커야 합니다.");

            return value;
        }

        private float ParseLatitude(string text, string displayName, List<string> errors)
        {
            if (!TryParseFloat(text, displayName, errors, out float value))
                return 0;

            if (value < -90 || value > 90)
                errors.Add(displayName + "는 -90부터 90 사이여야 합니다.");

            return value;
        }

        private float ParseLongitude(string text, string displayName, List<string> errors)
        {
            if (!TryParseFloat(text, displayName, errors, out float value))
                return 0;

            if (value < -180 || value > 180)
                errors.Add(displayName + "는 -180부터 180 사이여야 합니다.");

            return value;
        }

        private bool TryParseFloat(string text, string displayName, List<string> errors, out float value)
        {
            if ((float.TryParse(text, NumberStyles.Float, CultureInfo.CurrentCulture, out value) ||
                 float.TryParse(text, NumberStyles.Float, CultureInfo.InvariantCulture, out value)) &&
                !float.IsNaN(value) &&
                !float.IsInfinity(value))
            {
                return true;
            }

            errors.Add(displayName + "는 숫자로 입력해야 합니다.");
            return false;
        }

        private void LoadSavedScenarioIntoInputs()
        {
            if (_savedScenario == null) return;

            _isLoadingInputs = true;
            try
            {
                RadarLatitudeText = Format(_savedScenario.RadarPositionLatitude);
                RadarLongitudeText = Format(_savedScenario.RadarPositionLongitude);
                LauncherLatitudeText = Format(_savedScenario.LauncherPositionLatitude);
                LauncherLongitudeText = Format(_savedScenario.LauncherPositionLongitude);
                StartLatitudeText = Format(_savedScenario.StartLatitude);
                StartLongitudeText = Format(_savedScenario.StartLongitude);
                EndLatitudeText = Format(_savedScenario.EndLatitude);
                EndLongitudeText = Format(_savedScenario.EndLongitude);
                AirthreatVelocityText = Format(_savedScenario.AirthreatVelocity);
            }
            finally
            {
                _isLoadingInputs = false;
            }

            OnScenarioInputChanged();
        }

        private void SetInputText(ref string storage, string value, [CallerMemberName] string propertyName = null)
        {
            if (storage == value) return;

            storage = value;
            OnPropertyChanged(propertyName);

            if (_isLoadingInputs) return;

            HasUnsavedChanges = true;
            IsScenarioDeployed = false;
            OnScenarioInputChanged();
        }

        private void OnScenarioInputChanged()
        {
            OnPropertyChanged(nameof(HasRadarLocation));
            OnPropertyChanged(nameof(HasLauncherLocation));
            OnPropertyChanged(nameof(HasAirthreatStartLocation));
            OnPropertyChanged(nameof(HasAirthreatEndLocation));
        }

        private bool HasCoordinate(string latitudeText, string longitudeText) =>
            !string.IsNullOrWhiteSpace(latitudeText) && !string.IsNullOrWhiteSpace(longitudeText);

        private string Format(float value) =>
            value.ToString("0.######", CultureInfo.CurrentCulture);

        private string FormatCoordinate(double value) =>
            value.ToString("0.######", CultureInfo.CurrentCulture);

        private void OnScenarioSendAck(ScenarioSendAck ack)
        {
            if ((SimulatorID)ack.SimulatorID != SimulatorID.ATS) return;
        }

        private void RefreshCommandState() => CommandManager.InvalidateRequerySuggested();

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged([CallerMemberName] string name = null)
            => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));

        public void Dispose()
        {
            EventAggregator.Instance.Unsubscribe<ScenarioSendAck>(OnScenarioSendAck);
        }
    }
}
