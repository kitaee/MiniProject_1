using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Shapes;
using System.Windows.Threading;
using nframework.nom;
using NOMHandlerLib.Concrete;
using NOMHandlerLib.Core;

namespace TCC_GUI;

public partial class MainWindow : Window
{
    private const uint HeaderLength = 8u;
    private const uint DeployScenarioLength = 48u;
    private const uint DefaultMissileQuantity = 4u;
    private const double RadarDetectionRangeKm = 230.0;
    private const double RadarSectorMinDegrees = -45.0;
    private const double RadarSectorMaxDegrees = 45.0;
    private const double MinMapSpanDegrees = 0.045;
    private const double RenderBlendSeconds = 1.0;
    private const int MaxTrailPoints = 160;

    private readonly NOMHandler nomHandler;
    private readonly ScenarioViewState scenario = new();
    private readonly EntityState threat = new();
    private readonly EntityState missile = new();
    private readonly List<(float Lat, float Lon)> threatTrail = new();
    private readonly List<(float Lat, float Lon)> missileTrail = new();
    private readonly DispatcherTimer renderTimer = new() { Interval = TimeSpan.FromMilliseconds(100) };

    private bool nfConnectStarted;
    private bool simulationRunning;
    private bool missileLaunched;
    private bool targetDetected;
    private bool targetKilled;

    public MainWindow()
    {
        var nomFilePaths = new List<string>
        {
            Environment.CurrentDirectory + @"\UIManager\UIManager.xml"
        };

        nomHandler = new NOMHandler(nomFilePaths);
        nomHandler.MessageSent += OnNOMMessageSent;
        nomHandler.MessageReceived += OnNOMMessageReceived;

        Loaded += MainWindow_Loaded;
        Closed += MainWindow_Closed;
        InitializeComponent();

        renderTimer.Tick += (_, _) =>
        {
            if (simulationRunning || missileLaunched || targetKilled)
                UpdateMap();
        };
    }

    private void MainWindow_Loaded(object sender, RoutedEventArgs e)
    {
        (PresentationSource.FromVisual(this) as HwndSource)?.AddHook(nomHandler.WndProcCallback);

        if (!nomHandler.CreateNFConnect())
        {
            SetStatus("실패: nFConnect 생성 실패. nFConnect.ini와 DLL 구성을 확인하세요.");
            MessageBox.Show(
                "nFConnect 생성에 실패했습니다.\ntcc\\bin의 nFConnect.ini와 nFramework DLL 구성을 확인하세요.",
                "TCC",
                MessageBoxButton.OK,
                MessageBoxImage.Error);
            return;
        }

        nomHandler.DoPlugIn();
        nomHandler.SetWindowHandle(new WindowInteropHelper(this).Handle);
        nomHandler.ExecStart();
        nfConnectStarted = true;

        StoreScenarioFromInputs(updateText: false);
        UpdateLaunchButtonState();
        UpdateMap();
        renderTimer.Start();

        SetStatus("준비 완료. 시나리오 배포 후 모의를 시작하세요.");
        Log("nFConnect started (UIManager + UDPCommunicationManager).");
    }

    private void MainWindow_Closed(object? sender, EventArgs e)
    {
        renderTimer.Stop();

        if (!nfConnectStarted)
            return;

        nomHandler.ExecStop();
        nomHandler.DoPlugOut();
        nomHandler.DestroyNFConnect();
    }

    private void DeployScenarioButton_Click(object sender, RoutedEventArgs e)
    {
        try
        {
            StoreScenarioFromInputs(updateText: true);
            ResetEngagementView();

            var nomInstance = CreateInteraction("DeployScenarioRequest", 1001u, DeployScenarioLength);

            nomInstance.setValue("Airthreat.AirthreatID", new NUInteger(scenario.AirthreatId));
            nomInstance.setValue("Airthreat.StartLatitude", new NFloat(scenario.StartLat));
            nomInstance.setValue("Airthreat.StartLongitude", new NFloat(scenario.StartLon));
            nomInstance.setValue("Airthreat.EndLatitude", new NFloat(scenario.EndLat));
            nomInstance.setValue("Airthreat.EndLongitude", new NFloat(scenario.EndLon));
            nomInstance.setValue("Airthreat.AirthreatVelocity", new NFloat(scenario.AirthreatVelocity));
            nomInstance.setValue("RadarPositionLatitude", new NFloat(scenario.RadarLat));
            nomInstance.setValue("RadarPositionLongitude", new NFloat(scenario.RadarLon));
            nomInstance.setValue("LauncherPositionLatitude", new NFloat(scenario.LauncherLat));
            nomInstance.setValue("LauncherPositionLongitude", new NFloat(scenario.LauncherLon));

            SendInteraction(nomInstance, "DeployScenarioRequest");
            EngagementStateText.Text = "시나리오 배포";
            UpdateMap();
        }
        catch (Exception ex)
        {
            ShowSendError("DeployScenarioRequest", ex);
        }
    }

    private void StartSimulationButton_Click(object sender, RoutedEventArgs e)
    {
        if (!scenario.Deployed)
        {
            SetStatus("시나리오 배포 후 모의를 시작할 수 있습니다.");
            return;
        }

        try
        {
            SendInteraction(CreateInteraction("StartSimulationRequest", 1002u, HeaderLength), "StartSimulationRequest");
            simulationRunning = true;
            EngagementStateText.Text = "모의 진행";
            UpdateLaunchButtonState();
            UpdateMap();
        }
        catch (Exception ex)
        {
            ShowSendError("StartSimulationRequest", ex);
        }
    }

    private void StopSimulationButton_Click(object sender, RoutedEventArgs e)
    {
        try
        {
            SendInteraction(CreateInteraction("StopSimulationRequest", 1003u, HeaderLength), "StopSimulationRequest");
            ReturnToScenarioDeployedState();
        }
        catch (Exception ex)
        {
            ShowSendError("StopSimulationRequest", ex);
        }
    }

    private void LaunchMissileButton_Click(object sender, RoutedEventArgs e)
    {
        if (!targetDetected)
        {
            SetStatus("레이다 탐지 범위 안에서만 발사할 수 있습니다.");
            return;
        }

        try
        {
            missile.Id = ParseUInt(MissileIdTextBox.Text, "유도탄 ID");
            _ = ParseUInt(LaunchCountTextBox.Text, "발사 수량");
            missile.SetPosition(scenario.LauncherLat, scenario.LauncherLon, 0.0f, 650.0f);
            AddTrailPoint(missileTrail, missile.Lat, missile.Lon);

            SendInteraction(CreateInteraction("LaunchMissileRequest", 1401u, HeaderLength), "LaunchMissileRequest");
            missileLaunched = true;
            MissileStateText.Text = "발사 명령";
            UpdateMap();
        }
        catch (Exception ex)
        {
            ShowSendError("LaunchMissileRequest", ex);
        }
    }

    private NOM CreateInteraction(string messageName, uint messageId, uint messageLength)
    {
        if (!nfConnectStarted)
            throw new InvalidOperationException("nFConnect가 아직 시작되지 않았습니다.");

        var nomInstance = nomHandler.GetNMessage(messageName)?.createNOMInstance();
        if (nomInstance == null)
            throw new InvalidOperationException($"{messageName} 메시지가 UIManager.xml에 없습니다.");

        nomInstance.setValue("MessageHeader.MessageID", new NUInteger(messageId));
        nomInstance.setValue("MessageHeader.MessageLength", new NUInteger(messageLength));
        return nomInstance;
    }

    private void SendInteraction(NOM nomInstance, string messageName)
    {
        nomHandler.SendNOMMessage(nomInstance);
        SetStatus($"{messageName} 송신 완료.");
        Log($"TX {messageName} (id={GetMessageIdText(nomInstance)}).");
    }

    private void OnNOMMessageSent(NOM nomInstance, EMessageOperation operation)
    {
        if (operation == EMessageOperation.Send)
        {
            var messageName = nomInstance.name;
            RunOnUiThread(() => Log($"nFramework sent {messageName}."));
        }
    }

    private void OnNOMMessageReceived(NOM nomInstance, EMessageOperation operation)
    {
        var snapshot = CreateSnapshot(nomInstance, operation);
        RunOnUiThread(() =>
        {
            var applied = ApplySnapshot(snapshot);
            Log($"{(applied ? "RX" : "RX ignored")} {snapshot.Operation}: {snapshot.Name} (id={snapshot.MessageId}).");
            if (applied)
                SetStatus($"수신: {snapshot.Name}");
        });
    }

    private ReceivedNomSnapshot CreateSnapshot(NOM nomInstance, EMessageOperation operation)
    {
        var snapshot = new ReceivedNomSnapshot
        {
            Name = nomInstance.name,
            MessageId = GetMessageIdText(nomInstance),
            Operation = operation.ToString()
        };

        AddUInt(snapshot, nomInstance, "MessageHeader.MessageID");
        AddFloat(snapshot, nomInstance, "RadarDetection.TargetID");
        AddFloat(snapshot, nomInstance, "RadarDetection.TargetXPos");
        AddFloat(snapshot, nomInstance, "RadarDetection.TargetYPos");
        AddFloat(snapshot, nomInstance, "RadarDetection.TargetZPos");
        AddFloat(snapshot, nomInstance, "RadarDetection.DetectedFlag");
        AddFloat(snapshot, nomInstance, "RadarDetection.TargetVelocity");
        AddFloat(snapshot, nomInstance, "DownlinkInfo.MissleID");
        AddFloat(snapshot, nomInstance, "DownlinkInfo.MissileVelocity");
        AddFloat(snapshot, nomInstance, "DownlinkInfo.MissleXPos");
        AddFloat(snapshot, nomInstance, "DownlinkInfo.MissleYPos");
        AddFloat(snapshot, nomInstance, "DownlinkInfo.MissleZPos");
        AddFloat(snapshot, nomInstance, "MissileQuantity");
        AddFloat(snapshot, nomInstance, "MissleID");
        AddFloat(snapshot, nomInstance, "TargetID");

        return snapshot;
    }

    private bool ApplySnapshot(ReceivedNomSnapshot snapshot)
    {
        if (IsLiveTrackSnapshot(snapshot) && !simulationRunning)
        {
            UpdateMap();
            return false;
        }

        if (snapshot.Name == "RadarDetectionInfo")
        {
            threat.Id = (uint)GetValue(snapshot, "RadarDetection.TargetID", scenario.AirthreatId);
            var lat = (float)GetValue(snapshot, "RadarDetection.TargetXPos", threat.Lat);
            var lon = (float)GetValue(snapshot, "RadarDetection.TargetYPos", threat.Lon);
            var alt = (float)GetValue(snapshot, "RadarDetection.TargetZPos", threat.Alt);
            var velocity = (float)GetValue(snapshot, "RadarDetection.TargetVelocity", threat.Velocity);
            threat.SetPosition(lat, lon, alt, velocity);
            AddTrailPoint(threatTrail, threat.Lat, threat.Lon);

            targetDetected = GetValue(snapshot, "RadarDetection.DetectedFlag", 0.0) > 0.5;
            DetectionStateText.Text = targetDetected ? "탐지" : "범위 밖";
            ThreatStateText.Text = targetDetected
                ? $"ID {threat.Id} / {threat.Lat:F4}, {threat.Lon:F4}"
                : $"ID {threat.Id} / 추적 대기";
            UpdateLaunchButtonState();
        }
        else if (snapshot.Name == "DownlinkInfo_5103" || snapshot.Name == "DownlinkInfo" || snapshot.MessageId == "5103")
        {
            missileLaunched = true;
            missile.Id = (uint)GetValue(snapshot, "DownlinkInfo.MissleID", missile.Id);
            var velocity = (float)GetValue(snapshot, "DownlinkInfo.MissileVelocity", missile.Velocity);
            var lat = (float)GetValue(snapshot, "DownlinkInfo.MissleXPos", missile.Lat);
            var lon = (float)GetValue(snapshot, "DownlinkInfo.MissleYPos", missile.Lon);
            var alt = (float)GetValue(snapshot, "DownlinkInfo.MissleZPos", missile.Alt);
            missile.SetPosition(lat, lon, alt, velocity);
            AddTrailPoint(missileTrail, missile.Lat, missile.Lon);

            if (!targetKilled)
                MissileStateText.Text = $"비행 / ID {missile.Id} / {missile.Lat:F4}, {missile.Lon:F4}";
        }
        else if (snapshot.Name == "MissileQuantityInfo")
        {
            var quantity = (uint)GetValue(snapshot, "MissileQuantity", 0.0);
            InventoryStateText.Text = $"{quantity} 발";
        }
        else if (snapshot.Name == "DetonationInfo" || snapshot.MessageId == "3201")
        {
            targetKilled = true;
            targetDetected = false;
            var missileId = (uint)GetValue(snapshot, "MissleID", missile.Id);
            var targetId = (uint)GetValue(snapshot, "TargetID", threat.Id);
            EngagementStateText.Text = "격추";
            DetectionStateText.Text = "격추";
            ThreatStateText.Text = $"표적 {targetId} 격추";
            MissileStateText.Text = $"유도탄 {missileId} 명중";
            UpdateLaunchButtonState();
        }
        else if (snapshot.Name.StartsWith("ScenarioACK", StringComparison.Ordinal) && !simulationRunning)
        {
            EngagementStateText.Text = scenario.Deployed ? "시나리오 배포" : "ACK 수신";
        }

        UpdateMap();
        return true;
    }

    private void StoreScenarioFromInputs(bool updateText)
    {
        scenario.AirthreatId = ParseUInt(AirthreatIdTextBox.Text, "위협 ID");
        scenario.AirthreatVelocity = ParseFloat(AirthreatVelocityTextBox.Text, "위협 속도");
        scenario.StartLat = ParseFloat(StartLatitudeTextBox.Text, "시작 위도");
        scenario.StartLon = ParseFloat(StartLongitudeTextBox.Text, "시작 경도");
        scenario.EndLat = ParseFloat(EndLatitudeTextBox.Text, "종료 위도");
        scenario.EndLon = ParseFloat(EndLongitudeTextBox.Text, "종료 경도");
        scenario.RadarLat = ParseFloat(RadarLatitudeTextBox.Text, "레이다 위도");
        scenario.RadarLon = ParseFloat(RadarLongitudeTextBox.Text, "레이다 경도");
        scenario.LauncherLat = ParseFloat(LauncherLatitudeTextBox.Text, "발사대 위도");
        scenario.LauncherLon = ParseFloat(LauncherLongitudeTextBox.Text, "발사대 경도");
        scenario.Deployed = updateText || scenario.Deployed;

        threat.Id = scenario.AirthreatId;
        threat.SetPosition(scenario.StartLat, scenario.StartLon, 10.0f, scenario.AirthreatVelocity);

        if (updateText)
        {
            ThreatStateText.Text = $"ID {scenario.AirthreatId} / 배포";
            DetectionStateText.Text = "대기";
            InventoryStateText.Text = "-";
        }
    }

    private void ResetEngagementView()
    {
        simulationRunning = false;
        missile.Reset();
        missileLaunched = false;
        targetDetected = false;
        targetKilled = false;
        threatTrail.Clear();
        missileTrail.Clear();
        BlastMarker.Visibility = Visibility.Collapsed;
        BlastLabel.Visibility = Visibility.Collapsed;
        MissileStateText.Text = "대기";
        EngagementStateText.Text = "시나리오 배포";
        UpdateLaunchButtonState();
    }

    private void ReturnToScenarioDeployedState()
    {
        simulationRunning = false;
        targetDetected = false;
        missileLaunched = false;
        targetKilled = false;
        missile.Reset();
        threatTrail.Clear();
        missileTrail.Clear();
        threat.Id = scenario.AirthreatId;
        threat.SetPosition(scenario.StartLat, scenario.StartLon, 10.0f, scenario.AirthreatVelocity);
        EngagementStateText.Text = "시나리오 배포";
        DetectionStateText.Text = "대기";
        ThreatStateText.Text = $"ID {scenario.AirthreatId} / 배포";
        MissileStateText.Text = "대기";
        InventoryStateText.Text = $"{DefaultMissileQuantity} 발";
        BlastMarker.Visibility = Visibility.Collapsed;
        BlastLabel.Visibility = Visibility.Collapsed;
        UpdateLaunchButtonState();
        UpdateMap();
    }

    private void UpdateLaunchButtonState()
    {
        if (LaunchMissileButton == null)
            return;

        LaunchMissileButton.IsEnabled = nfConnectStarted
            && scenario.Deployed
            && simulationRunning
            && targetDetected
            && !targetKilled;
    }

    private void UpdateMap()
    {
        if (MapCanvas == null)
            return;

        DrawMapBackground();

        var start = Project(scenario.StartLat, scenario.StartLon);
        var end = Project(scenario.EndLat, scenario.EndLon);
        ThreatPathLine.X1 = start.X;
        ThreatPathLine.Y1 = start.Y;
        ThreatPathLine.X2 = end.X;
        ThreatPathLine.Y2 = end.Y;

        var radar = Project(scenario.RadarLat, scenario.RadarLon);
        DrawRadarSector();
        SetMarker(RadarMarker, radar, 18, 18);
        SetText(RadarLabel, radar, 13, -22);

        var launcher = Project(scenario.LauncherLat, scenario.LauncherLon);
        SetMarker(LauncherMarker, launcher, 18, 18);
        SetText(LauncherLabel, launcher, 13, 8);
        SetTrail(ThreatTrackLine, threatTrail);
        SetTrail(MissileTrackLine, missileTrail);
        DrawTrailDots(threatTrail, "#DC2626");
        DrawTrailDots(missileTrail, "#16A34A");

        Point? threatPoint = null;
        if (threat.Valid)
        {
            var displayThreat = threat.GetRenderPosition();
            threatPoint = Project(displayThreat.Lat, displayThreat.Lon);
            SetMarker(ThreatMarker, threatPoint.Value, 28, 32);
            ThreatMarker.RenderTransform = new RotateTransform(GetThreatBearingDegrees());
            SetText(ThreatLabel, threatPoint.Value, 14, -24);
            ThreatMarker.Visibility = targetKilled ? Visibility.Collapsed : Visibility.Visible;
            ThreatLabel.Visibility = targetKilled ? Visibility.Collapsed : Visibility.Visible;

            if (targetKilled)
            {
                SetMarker(BlastMarker, threatPoint.Value, 36, 36);
                SetText(BlastLabel, threatPoint.Value, 20, -30);
                BlastMarker.Visibility = Visibility.Visible;
                BlastLabel.Visibility = Visibility.Visible;
            }
        }

        if (missile.Valid && missileLaunched && !targetKilled)
        {
            var displayMissile = missile.GetRenderPosition();
            var missilePoint = Project(displayMissile.Lat, displayMissile.Lon);
            SetMarker(MissileMarker, missilePoint, 24, 24);
            SetText(MissileLabel, missilePoint, 16, 6);
            MissileMarker.Visibility = Visibility.Visible;
            MissileLabel.Visibility = Visibility.Visible;

            if (threatPoint.HasValue)
            {
                GuidanceLine.X1 = missilePoint.X;
                GuidanceLine.Y1 = missilePoint.Y;
                GuidanceLine.X2 = threatPoint.Value.X;
                GuidanceLine.Y2 = threatPoint.Value.Y;
                GuidanceLine.Visibility = Visibility.Visible;
            }
        }
        else
        {
            MissileMarker.Visibility = Visibility.Collapsed;
            MissileLabel.Visibility = Visibility.Collapsed;
            GuidanceLine.Visibility = Visibility.Collapsed;
        }
    }

    private void DrawRadarSector()
    {
        var center = Project(scenario.RadarLat, scenario.RadarLon);
        var figure = new PathFigure
        {
            StartPoint = center,
            IsClosed = true
        };

        const int steps = 36;
        for (var i = 0; i <= steps; i++)
        {
            var bearing = RadarSectorMinDegrees + (RadarSectorMaxDegrees - RadarSectorMinDegrees) * i / steps;
            var point = DestinationPoint(scenario.RadarLat, scenario.RadarLon, bearing, RadarDetectionRangeKm);
            figure.Segments.Add(new LineSegment(Project((float)point.Lat, (float)point.Lon), true));
        }

        RadarSectorPath.Data = new PathGeometry(new[] { figure });
    }

    private void SetTrail(Polyline polyline, List<(float Lat, float Lon)> trail)
    {
        polyline.Points.Clear();
        foreach (var point in trail)
            polyline.Points.Add(Project(point.Lat, point.Lon));

        polyline.Visibility = trail.Count > 1 ? Visibility.Visible : Visibility.Collapsed;
    }

    private void DrawTrailDots(List<(float Lat, float Lon)> trail, string color)
    {
        if (trail.Count == 0)
            return;

        var start = Math.Max(0, trail.Count - 20);
        for (var i = start; i < trail.Count; i++)
        {
            var radius = i == trail.Count - 1 ? 4.0 : 2.4;
            var point = Project(trail[i].Lat, trail[i].Lon);
            AddCircle(MapBackground, point, radius, color, color, 0, i == trail.Count - 1 ? 0.9 : 0.45);
        }
    }

    private void AddTrailPoint(List<(float Lat, float Lon)> trail, float lat, float lon)
    {
        if (trail.Count > 0)
        {
            var last = trail[^1];
            if (Math.Abs(last.Lat - lat) < 0.00001f && Math.Abs(last.Lon - lon) < 0.00001f)
                return;
        }

        trail.Add((lat, lon));
        if (trail.Count > MaxTrailPoints)
            trail.RemoveAt(0);
    }

    private double GetThreatBearingDegrees()
    {
        if (threatTrail.Count >= 2)
        {
            var from = threatTrail[^2];
            var to = threatTrail[^1];
            return BearingDegrees(from.Lat, from.Lon, to.Lat, to.Lon);
        }

        return BearingDegrees(scenario.StartLat, scenario.StartLon, scenario.EndLat, scenario.EndLon);
    }

    private void DrawMapBackground()
    {
        if (MapBackground == null)
            return;

        var width = MapCanvas.ActualWidth > 40 ? MapCanvas.ActualWidth : 720;
        var height = MapCanvas.ActualHeight > 40 ? MapCanvas.ActualHeight : 420;
        var bounds = GetMapBounds();
        MapBackground.Children.Clear();

        AddRect(MapBackground, 0, 0, width, height, "#EAF3F8", null, 0);

        for (var i = 0; i <= 6; i++)
        {
            var x = width * i / 6.0;
            var y = height * i / 6.0;
            var edge = i == 0 || i == 6;
            AddLine(MapBackground, x, 0, x, height, edge ? "#94A3B8" : "#C9D7E2", edge ? 1.2 : 0.8);
            AddLine(MapBackground, 0, y, width, y, edge ? "#94A3B8" : "#C9D7E2", edge ? 1.2 : 0.8);

            if (i > 0 && i < 6)
            {
                var lon = bounds.MinLon + (bounds.MaxLon - bounds.MinLon) * i / 6.0;
                var lat = bounds.MaxLat - (bounds.MaxLat - bounds.MinLat) * i / 6.0;
                AddText(MapBackground, FormatDegree(lon, "E", "W"), x + 5, height - 24, "#475569", 11);
                AddText(MapBackground, FormatDegree(lat, "N", "S"), 8, y + 5, "#475569", 11);
            }
        }

        AddText(MapBackground, "대한민국 기준 전술상황도", 14, 12, "#1E293B", 13, FontWeights.SemiBold);
        AddText(
            MapBackground,
            $"{FormatDegree(bounds.MinLat, "N", "S")}~{FormatDegree(bounds.MaxLat, "N", "S")} / {FormatDegree(bounds.MinLon, "E", "W")}~{FormatDegree(bounds.MaxLon, "E", "W")}",
            14,
            32,
            "#64748B",
            11);

        AddLine(MapBackground, width - 48, 44, width - 48, 16, "#334155", 2);
        AddLine(MapBackground, width - 48, 16, width - 54, 28, "#334155", 2);
        AddLine(MapBackground, width - 48, 16, width - 42, 28, "#334155", 2);
        AddText(MapBackground, "N", width - 54, 46, "#334155", 12, FontWeights.SemiBold);

        var midLat = (bounds.MinLat + bounds.MaxLat) / 2.0;
        var scaleKm = HaversineKm(midLat, bounds.MinLon, midLat, bounds.MaxLon) / 5.0;
        AddLine(MapBackground, 18, height - 42, 118, height - 42, "#334155", 3);
        AddText(MapBackground, $"약 {scaleKm:F1} km", 18, height - 62, "#475569", 11);
    }

    private Point Project(float lat, float lon)
    {
        var width = MapCanvas.ActualWidth > 40 ? MapCanvas.ActualWidth : 720;
        var height = MapCanvas.ActualHeight > 40 ? MapCanvas.ActualHeight : 420;
        const double padding = 52.0;
        var bounds = GetMapBounds();

        var x = padding + (lon - bounds.MinLon) / (bounds.MaxLon - bounds.MinLon) * (width - padding * 2);
        var y = height - padding - (lat - bounds.MinLat) / (bounds.MaxLat - bounds.MinLat) * (height - padding * 2);
        return new Point(x, y);
    }

    private (double MinLat, double MaxLat, double MinLon, double MaxLon) GetMapBounds()
    {
        double minLat = Math.Min(Math.Min(scenario.StartLat, scenario.EndLat), Math.Min(scenario.RadarLat, scenario.LauncherLat));
        double maxLat = Math.Max(Math.Max(scenario.StartLat, scenario.EndLat), Math.Max(scenario.RadarLat, scenario.LauncherLat));
        double minLon = Math.Min(Math.Min(scenario.StartLon, scenario.EndLon), Math.Min(scenario.RadarLon, scenario.LauncherLon));
        double maxLon = Math.Max(Math.Max(scenario.StartLon, scenario.EndLon), Math.Max(scenario.RadarLon, scenario.LauncherLon));

        IncludeEntity(threat);
        IncludeEntity(missile);
        IncludeTrail(threatTrail);
        IncludeTrail(missileTrail);

        var latSpan = Math.Max(maxLat - minLat, MinMapSpanDegrees);
        var lonSpan = Math.Max(maxLon - minLon, MinMapSpanDegrees);
        var centerLat = (minLat + maxLat) / 2.0;
        var centerLon = (minLon + maxLon) / 2.0;

        var width = MapCanvas?.ActualWidth > 40 ? MapCanvas.ActualWidth : 720;
        var height = MapCanvas?.ActualHeight > 40 ? MapCanvas.ActualHeight : 420;
        var desiredRatio = Math.Max(1.0, width / Math.Max(1.0, height));

        if (lonSpan / latSpan < desiredRatio)
            lonSpan = latSpan * desiredRatio;
        else
            latSpan = lonSpan / desiredRatio;

        latSpan *= 1.28;
        lonSpan *= 1.28;
        return (centerLat - latSpan / 2.0, centerLat + latSpan / 2.0, centerLon - lonSpan / 2.0, centerLon + lonSpan / 2.0);

        void IncludeEntity(EntityState entity)
        {
            if (!entity.Valid)
                return;
            Include((entity.Lat, entity.Lon));
        }

        void IncludeTrail(List<(float Lat, float Lon)> trail)
        {
            foreach (var point in trail)
                Include((point.Lat, point.Lon));
        }

        void Include((double Lat, double Lon) point)
        {
            minLat = Math.Min(minLat, point.Lat);
            maxLat = Math.Max(maxLat, point.Lat);
            minLon = Math.Min(minLon, point.Lon);
            maxLon = Math.Max(maxLon, point.Lon);
        }
    }

    private static void SetMarker(FrameworkElement element, Point point, double width, double height)
    {
        element.Width = width;
        element.Height = height;
        Canvas.SetLeft(element, point.X - width / 2);
        Canvas.SetTop(element, point.Y - height / 2);
    }

    private static void SetText(TextBlock textBlock, Point point, double dx, double dy)
    {
        Canvas.SetLeft(textBlock, point.X + dx);
        Canvas.SetTop(textBlock, point.Y + dy);
    }

    private static void AddRect(Canvas canvas, double x, double y, double width, double height, string fill, string? stroke, double strokeThickness)
    {
        var rect = new Rectangle
        {
            Width = width,
            Height = height,
            Fill = (Brush)new BrushConverter().ConvertFromString(fill)!,
            Stroke = stroke == null ? null : (Brush)new BrushConverter().ConvertFromString(stroke)!,
            StrokeThickness = strokeThickness
        };
        Canvas.SetLeft(rect, x);
        Canvas.SetTop(rect, y);
        canvas.Children.Add(rect);
    }

    private static void AddPolygon(Canvas canvas, string fill, string stroke, double strokeThickness, params Point[] points)
    {
        var polygon = new Polygon
        {
            Fill = (Brush)new BrushConverter().ConvertFromString(fill)!,
            Stroke = (Brush)new BrushConverter().ConvertFromString(stroke)!,
            StrokeThickness = strokeThickness
        };

        foreach (var point in points)
            polygon.Points.Add(point);

        canvas.Children.Add(polygon);
    }

    private static void AddCircle(
        Canvas canvas,
        Point center,
        double radius,
        string fill,
        string stroke,
        double strokeThickness,
        double opacity = 1.0)
    {
        var circle = new Ellipse
        {
            Width = radius * 2,
            Height = radius * 2,
            Fill = (Brush)new BrushConverter().ConvertFromString(fill)!,
            Stroke = (Brush)new BrushConverter().ConvertFromString(stroke)!,
            StrokeThickness = strokeThickness,
            Opacity = opacity
        };
        Canvas.SetLeft(circle, center.X - radius);
        Canvas.SetTop(circle, center.Y - radius);
        canvas.Children.Add(circle);
    }

    private static void AddLine(Canvas canvas, double x1, double y1, double x2, double y2, string stroke, double strokeThickness)
    {
        canvas.Children.Add(new Line
        {
            X1 = x1,
            Y1 = y1,
            X2 = x2,
            Y2 = y2,
            Stroke = (Brush)new BrushConverter().ConvertFromString(stroke)!,
            StrokeThickness = strokeThickness
        });
    }

    private static void AddPolyline(Canvas canvas, string stroke, double strokeThickness, bool dashed, params Point[] points)
    {
        var polyline = new Polyline
        {
            Stroke = (Brush)new BrushConverter().ConvertFromString(stroke)!,
            StrokeThickness = strokeThickness,
            StrokeStartLineCap = PenLineCap.Round,
            StrokeEndLineCap = PenLineCap.Round,
            StrokeLineJoin = PenLineJoin.Round
        };

        if (dashed)
            polyline.StrokeDashArray = new DoubleCollection { 3, 3 };

        foreach (var point in points)
            polyline.Points.Add(point);

        canvas.Children.Add(polyline);
    }

    private static void AddText(
        Canvas canvas,
        string text,
        double x,
        double y,
        string foreground,
        double fontSize = 12,
        FontWeight? fontWeight = null)
    {
        var block = new TextBlock
        {
            Text = text,
            FontSize = fontSize,
            FontWeight = fontWeight ?? FontWeights.Normal,
            Foreground = (Brush)new BrushConverter().ConvertFromString(foreground)!
        };
        Canvas.SetLeft(block, x);
        Canvas.SetTop(block, y);
        canvas.Children.Add(block);
    }

    private static string FormatDegree(double value, string positiveSuffix, string negativeSuffix)
    {
        var suffix = value >= 0 ? positiveSuffix : negativeSuffix;
        return $"{Math.Abs(value):F3}°{suffix}";
    }

    private static (double Lat, double Lon) DestinationPoint(double lat, double lon, double bearingDegrees, double distanceKm)
    {
        const double earthRadiusKm = 6371.0;
        var angularDistance = distanceKm / earthRadiusKm;
        var bearing = ToRadians(NormalizeBearing(bearingDegrees));
        var lat1 = ToRadians(lat);
        var lon1 = ToRadians(lon);

        var lat2 = Math.Asin(
            Math.Sin(lat1) * Math.Cos(angularDistance)
            + Math.Cos(lat1) * Math.Sin(angularDistance) * Math.Cos(bearing));
        var lon2 = lon1 + Math.Atan2(
            Math.Sin(bearing) * Math.Sin(angularDistance) * Math.Cos(lat1),
            Math.Cos(angularDistance) - Math.Sin(lat1) * Math.Sin(lat2));

        return (ToDegrees(lat2), NormalizeLongitude(ToDegrees(lon2)));
    }

    private static double BearingDegrees(double fromLat, double fromLon, double toLat, double toLon)
    {
        var lat1 = ToRadians(fromLat);
        var lat2 = ToRadians(toLat);
        var deltaLon = ToRadians(toLon - fromLon);
        var y = Math.Sin(deltaLon) * Math.Cos(lat2);
        var x = Math.Cos(lat1) * Math.Sin(lat2)
            - Math.Sin(lat1) * Math.Cos(lat2) * Math.Cos(deltaLon);
        return NormalizeBearing(ToDegrees(Math.Atan2(y, x)));
    }

    private static double HaversineKm(double lat1, double lon1, double lat2, double lon2)
    {
        const double earthRadiusKm = 6371.0;
        var dLat = ToRadians(lat2 - lat1);
        var dLon = ToRadians(lon2 - lon1);
        var rLat1 = ToRadians(lat1);
        var rLat2 = ToRadians(lat2);
        var a = Math.Sin(dLat / 2.0) * Math.Sin(dLat / 2.0)
            + Math.Cos(rLat1) * Math.Cos(rLat2) * Math.Sin(dLon / 2.0) * Math.Sin(dLon / 2.0);
        var clamped = Math.Min(1.0, Math.Max(0.0, a));
        return earthRadiusKm * 2.0 * Math.Atan2(Math.Sqrt(clamped), Math.Sqrt(1.0 - clamped));
    }

    private static double ToRadians(double degrees) => degrees * Math.PI / 180.0;
    private static double ToDegrees(double radians) => radians * 180.0 / Math.PI;

    private static double NormalizeBearing(double degrees)
    {
        var value = degrees % 360.0;
        return value < 0 ? value + 360.0 : value;
    }

    private static double NormalizeLongitude(double degrees)
    {
        return (degrees + 540.0) % 360.0 - 180.0;
    }

    private static bool IsLiveTrackSnapshot(ReceivedNomSnapshot snapshot)
    {
        return snapshot.Name == "RadarDetectionInfo"
            || snapshot.Name == "DownlinkInfo_5103"
            || snapshot.Name == "DownlinkInfo"
            || snapshot.MessageId == "5103"
            || snapshot.Name == "DetonationInfo"
            || snapshot.MessageId == "3201";
    }

    private void MapCanvas_SizeChanged(object sender, SizeChangedEventArgs e)
    {
        UpdateMap();
    }

    private void ShowSendError(string messageName, Exception ex)
    {
        SetStatus($"{messageName} 송신 실패.");
        Log($"{messageName} error: {ex.Message}");
        MessageBox.Show(ex.Message, messageName, MessageBoxButton.OK, MessageBoxImage.Error);
    }

    private static uint ParseUInt(string text, string fieldName)
    {
        if (uint.TryParse(text, NumberStyles.Integer, CultureInfo.InvariantCulture, out var value))
            return value;

        throw new FormatException($"{fieldName} 값이 올바른 정수가 아닙니다.");
    }

    private static float ParseFloat(string text, string fieldName)
    {
        if (float.TryParse(text, NumberStyles.Float, CultureInfo.InvariantCulture, out var value))
            return value;

        throw new FormatException($"{fieldName} 값이 올바른 숫자가 아닙니다.");
    }

    private static string GetMessageIdText(NOM nomInstance)
    {
        try
        {
            return nomInstance.getValue("MessageHeader.MessageID").toUInt().ToString(CultureInfo.InvariantCulture);
        }
        catch
        {
            return "?";
        }
    }

    private static void AddUInt(ReceivedNomSnapshot snapshot, NOM nomInstance, string fieldName)
    {
        try
        {
            snapshot.Values[fieldName] = nomInstance.getValue(fieldName).toUInt();
        }
        catch
        {
            // Optional field.
        }
    }

    private static void AddFloat(ReceivedNomSnapshot snapshot, NOM nomInstance, string fieldName)
    {
        try
        {
            snapshot.Values[fieldName] = nomInstance.getValue(fieldName).toFloat();
        }
        catch
        {
            try
            {
                snapshot.Values[fieldName] = nomInstance.getValue(fieldName).toUInt();
            }
            catch
            {
                // Optional field.
            }
        }
    }

    private static double GetValue(ReceivedNomSnapshot snapshot, string fieldName, double fallback)
    {
        return snapshot.Values.TryGetValue(fieldName, out var value) ? value : fallback;
    }

    private void SetStatus(string text)
    {
        StatusText.Text = text;
    }

    private void RunOnUiThread(Action action)
    {
        if (Dispatcher.CheckAccess())
        {
            action();
            return;
        }

        Dispatcher.BeginInvoke(action);
    }

    private void Log(string message)
    {
        if (!Dispatcher.CheckAccess())
        {
            Dispatcher.BeginInvoke(new Action(() => Log(message)));
            return;
        }

        var line = $"[{DateTime.Now:HH:mm:ss}] {message}";
        Console.WriteLine(line);

        if (LogList != null)
        {
            LogList.Items.Add(line);
            if (LogList.Items.Count > 500)
                LogList.Items.RemoveAt(0);
            LogList.ScrollIntoView(line);
        }

        try
        {
            var path = System.IO.Path.Combine(Environment.CurrentDirectory, "tcc_runtime.log");
            File.AppendAllText(path, line + Environment.NewLine);
        }
        catch
        {
            // UI logging should never interrupt simulation control.
        }
    }

    private sealed class ScenarioViewState
    {
        public uint AirthreatId { get; set; } = 1;
        public float AirthreatVelocity { get; set; } = 300.0f;
        public float StartLat { get; set; } = 37.5000f;
        public float StartLon { get; set; } = 127.0000f;
        public float EndLat { get; set; } = 37.6000f;
        public float EndLon { get; set; } = 127.1000f;
        public float RadarLat { get; set; } = 37.5500f;
        public float RadarLon { get; set; } = 127.0500f;
        public float LauncherLat { get; set; } = 37.5200f;
        public float LauncherLon { get; set; } = 127.0200f;
        public bool Deployed { get; set; }
    }

    private sealed class EntityState
    {
        public bool Valid { get; private set; }
        public uint Id { get; set; } = 1;
        public float Lat { get; private set; }
        public float Lon { get; private set; }
        public float Alt { get; private set; }
        public float Velocity { get; private set; }

        private float previousLat;
        private float previousLon;
        private float previousAlt;
        private DateTime lastUpdateUtc = DateTime.UtcNow;

        public void SetPosition(float lat, float lon, float alt, float velocity)
        {
            if (Valid)
            {
                var rendered = GetRenderPosition();
                previousLat = rendered.Lat;
                previousLon = rendered.Lon;
                previousAlt = rendered.Alt;
            }
            else
            {
                previousLat = lat;
                previousLon = lon;
                previousAlt = alt;
            }

            Lat = lat;
            Lon = lon;
            Alt = alt;
            Velocity = velocity;
            Valid = true;
            lastUpdateUtc = DateTime.UtcNow;
        }

        public (float Lat, float Lon, float Alt) GetRenderPosition()
        {
            if (!Valid)
                return (Lat, Lon, Alt);

            var t = Math.Clamp((DateTime.UtcNow - lastUpdateUtc).TotalSeconds / RenderBlendSeconds, 0.0, 1.0);
            var eased = t * t * (3.0 - 2.0 * t);
            return (
                (float)(previousLat + (Lat - previousLat) * eased),
                (float)(previousLon + (Lon - previousLon) * eased),
                (float)(previousAlt + (Alt - previousAlt) * eased));
        }

        public void Reset()
        {
            Valid = false;
            Lat = 0.0f;
            Lon = 0.0f;
            Alt = 0.0f;
            Velocity = 0.0f;
            previousLat = 0.0f;
            previousLon = 0.0f;
            previousAlt = 0.0f;
            lastUpdateUtc = DateTime.UtcNow;
        }
    }

    private sealed class ReceivedNomSnapshot
    {
        public string Name { get; init; } = "";
        public string MessageId { get; init; } = "?";
        public string Operation { get; init; } = "";
        public Dictionary<string, double> Values { get; } = new();
    }
}
