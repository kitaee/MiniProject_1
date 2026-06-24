using GMap.NET;
using GMap.NET.MapProviders;
using GMap.NET.WindowsPresentation;
using MaterialDesignThemes.Wpf;
using MiniProject_GUI.ViewModels;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace MiniProject_GUI.Views
{
    public partial class ScenarioControl : UserControl
    {
        private const double RadarCoverageKm = 230.0;
        private const double RadarCoverageStartBearing = -45.0;
        private const double RadarCoverageEndBearing = 45.0;
        private const double EarthRadiusKm = 6371.0;
        private const double RadarSweepStepDegrees = 2.2;
        private const double RadarSweepTailDegrees = 6.5;
        private const double RadarSweepMidTailDegrees = 26.0;
        private const double RadarSweepSoftTailDegrees = 34.0;
        private const double RadarSweepFrontFaceSpacingDegrees = 4.0;
        private const int RadarSweepSliceCount = 7;

        private readonly Dictionary<string, GMapMarker> markers = new Dictionary<string, GMapMarker>();
        private readonly List<GMapRoute> radarHudRoutes = new List<GMapRoute>();
        private readonly List<GMapPolygon> radarSweepPolygons = new List<GMapPolygon>();
        private readonly List<GMapRoute> radarSweepRoutes = new List<GMapRoute>();
        private GMapPolygon radarCoverage;
        private GMapRoute airthreatRoute;
        private DispatcherTimer radarSweepTimer;
        private double radarSweepBearing = RadarCoverageStartBearing;

        public ScenarioControl()
        {
            InitializeComponent();
            DataContext = ViewModelLocator.AckStatus;
            ViewModelLocator.AckStatus.PropertyChanged += OnViewModelPropertyChanged;
            Unloaded += OnUnloaded;
            InitializeMap();
            InitializeRadarSweepTimer();
        }

        private void InitializeMap()
        {
            GMapProvider.UserAgent = "MiniProject-TCC/1.0 (GMap.NET; Windows WPF)";
            GMaps.Instance.Mode = AccessMode.ServerOnly;

            CustomMapProvider.Instance.CustomServerUrl = "https://{0}.tile.openstreetmap.org/{z}/{x}/{y}.png";
            CustomMapProvider.Instance.CustomServerLetters = "abc";
            CustomMapProvider.Instance.RefererUrl = "https://www.openstreetmap.org/";
            CustomMapProvider.Instance.BypassCache = true;
            CustomMapProvider.Instance.MinZoom = 1;
            CustomMapProvider.Instance.MaxZoom = 19;
            CustomMapProvider.Instance.Copyright = "(c) OpenStreetMap contributors";

            ScenarioMap.MapProvider = CustomMapProvider.Instance;
            ScenarioMap.Position = new PointLatLng(36.5, 127.8);
            ScenarioMap.MinZoom = 4;
            ScenarioMap.MaxZoom = 18;
            ScenarioMap.Zoom = 6;
            ScenarioMap.CanDragMap = true;
            ScenarioMap.DragButton = MouseButton.Middle;
            ScenarioMap.MouseWheelZoomEnabled = true;
            ScenarioMap.MouseWheelZoomType = MouseWheelZoomType.MousePositionWithoutCenter;
            ScenarioMap.ShowCenter = false;
        }

        private void OnUnloaded(object sender, RoutedEventArgs e)
        {
            ViewModelLocator.AckStatus.PropertyChanged -= OnViewModelPropertyChanged;
            radarSweepTimer?.Stop();
            if (radarSweepTimer != null)
                radarSweepTimer.Tick -= RadarSweepTimer_Tick;
            Unloaded -= OnUnloaded;
        }

        private void OnViewModelPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == nameof(AckStatusViewModel.HasRadarDetection) ||
                e.PropertyName == nameof(AckStatusViewModel.DetectedFlag) ||
                e.PropertyName == nameof(AckStatusViewModel.DetectedTargetLatitude) ||
                e.PropertyName == nameof(AckStatusViewModel.DetectedTargetLongitude))
            {
                RefreshDetectedTargetMarker();
            }

            if (e.PropertyName == nameof(AckStatusViewModel.HasDownlinkInfo) ||
                e.PropertyName == nameof(AckStatusViewModel.DownlinkMissileLatitude) ||
                e.PropertyName == nameof(AckStatusViewModel.DownlinkMissileLongitude))
            {
                RefreshMissileMarker();
            }
        }

        private void RefreshDetectedTargetMarker()
        {
            if (!(DataContext is AckStatusViewModel viewModel)) return;

            if (!viewModel.HasRadarDetection)
            {
                RemoveMarker("DetectedTarget");
                return;
            }

            SetMarker(
                "DetectedTarget",
                viewModel.RadarDetectionStatusText,
                new PointLatLng(viewModel.DetectedTargetLatitude, viewModel.DetectedTargetLongitude));
        }

        private void RefreshMissileMarker()
        {
            if (!(DataContext is AckStatusViewModel viewModel)) return;

            if (!viewModel.HasDownlinkInfo)
            {
                RemoveMarker("Missile");
                return;
            }

            SetMarker(
                "Missile",
                "MSS",
                new PointLatLng(viewModel.DownlinkMissileLatitude, viewModel.DownlinkMissileLongitude));
        }

        private void ScenarioMap_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (IsControlKeyDown())
                return;

            if (!(DataContext is AckStatusViewModel viewModel)) return;
            if (viewModel.IsScenarioLocationLocked)
            {
                e.Handled = true;
                return;
            }

            Point point = e.GetPosition(ScenarioMap);
            PointLatLng coordinate = ScenarioMap.FromLocalToLatLng((int)point.X, (int)point.Y);
            string target = viewModel.SelectedMapTarget;
            string label = viewModel.SelectedMapTargetText;

            viewModel.SetMapCoordinate(coordinate.Lat, coordinate.Lng);
            SetMarker(target, label, coordinate);
            RefreshAirthreatRoute();

            if (target == "Radar")
                SetRadarCoverage(coordinate);
        }

        private void ScenarioMap_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (IsControlKeyDown())
                ScenarioMap.DragButton = MouseButton.Left;
        }

        private void ScenarioMap_PreviewMouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            ScenarioMap.DragButton = MouseButton.Middle;
        }

        private bool IsControlKeyDown()
        {
            return (Keyboard.Modifiers & ModifierKeys.Control) == ModifierKeys.Control;
        }

        private void InitializeRadarSweepTimer()
        {
            radarSweepTimer = new DispatcherTimer
            {
                Interval = TimeSpan.FromMilliseconds(55)
            };
            radarSweepTimer.Tick += RadarSweepTimer_Tick;
        }

        private void RadarSweepTimer_Tick(object sender, EventArgs e)
        {
            radarSweepBearing += RadarSweepStepDegrees;

            if (radarSweepBearing > RadarCoverageEndBearing)
                radarSweepBearing = RadarCoverageStartBearing;

            RefreshRadarSweepVisuals();
        }

        private void SetMarker(string key, string label, PointLatLng coordinate)
        {
            RemoveMarker(key);

            var marker = new GMapMarker(coordinate)
            {
                Offset = new Point(-14, -14),
                Shape = CreateMarkerShape(key, label)
            };

            markers[key] = marker;
            ScenarioMap.Markers.Add(marker);
        }

        private void RemoveMarker(string key)
        {
            if (!markers.TryGetValue(key, out GMapMarker existingMarker))
                return;

            ScenarioMap.Markers.Remove(existingMarker);
            markers.Remove(key);
        }

        private void SetRadarCoverage(PointLatLng radarPosition)
        {
            if (radarCoverage != null)
                ScenarioMap.Markers.Remove(radarCoverage);

            ClearRadarHud();
            ClearRadarSweepVisuals();
            radarSweepBearing = RadarCoverageStartBearing;

            radarCoverage = new GMapPolygon(CreateRadarCoveragePoints(radarPosition))
            {
                ZIndex = -1000,
                Shape = new Path
                {
                    Stroke = new SolidColorBrush(Color.FromArgb(0x90, 0x58, 0xE6, 0xD8)),
                    StrokeThickness = 1.3,
                    Fill = new SolidColorBrush(Color.FromArgb(0x0C, 0x2C, 0xD6, 0xCC)),
                    Effect = new System.Windows.Media.Effects.DropShadowEffect
                    {
                        Color = Color.FromRgb(0x48, 0xE6, 0xD8),
                        BlurRadius = 5,
                        ShadowDepth = 0,
                        Opacity = 0.35
                    },
                    IsHitTestVisible = false
                }
            };

            ScenarioMap.Markers.Add(radarCoverage);
            AddRadarHud(radarPosition);
            RefreshRadarSweepVisuals();
            radarSweepTimer.Start();
        }

        private void AddRadarHud(PointLatLng radarPosition)
        {
            AddRadarHudRoute(CreateRangeArcPoints(radarPosition, RadarCoverageKm * 0.25), 0x34, 0.8, null);
            AddRadarHudRoute(CreateRangeArcPoints(radarPosition, RadarCoverageKm * 0.50), 0x42, 0.9, null);
            AddRadarHudRoute(CreateRangeArcPoints(radarPosition, RadarCoverageKm * 0.75), 0x38, 0.8, null);
            AddRadarHudRoute(CreateRangeArcPoints(radarPosition, RadarCoverageKm), 0x80, 1.2, null);

            for (double bearing = RadarCoverageStartBearing; bearing <= RadarCoverageEndBearing; bearing += 15.0)
            {
                bool boundary = Math.Abs(bearing - RadarCoverageStartBearing) < 0.1 ||
                    Math.Abs(bearing - RadarCoverageEndBearing) < 0.1;

                AddRadarHudRoute(new List<PointLatLng>
                {
                    radarPosition,
                    GetDestinationPoint(radarPosition, bearing, RadarCoverageKm)
                }, boundary ? (byte)0x70 : (byte)0x36, boundary ? 1.0 : 0.75, boundary ? null : new DoubleCollection { 4, 6 });
            }

            for (double bearing = RadarCoverageStartBearing; bearing <= RadarCoverageEndBearing; bearing += 5.0)
            {
                bool majorTick = Math.Abs(bearing % 15.0) < 0.1;
                double innerDistance = RadarCoverageKm * (majorTick ? 0.93 : 0.965);

                AddRadarHudRoute(new List<PointLatLng>
                {
                    GetDestinationPoint(radarPosition, bearing, innerDistance),
                    GetDestinationPoint(radarPosition, bearing, RadarCoverageKm)
                }, majorTick ? (byte)0x9A : (byte)0x58, majorTick ? 1.15 : 0.7, null);
            }
        }

        private void AddRadarHudRoute(List<PointLatLng> points, byte opacity, double strokeThickness, DoubleCollection dashArray)
        {
            var route = new GMapRoute(points)
            {
                ZIndex = -930,
                Shape = new Path
                {
                    Stroke = new SolidColorBrush(Color.FromArgb(opacity, 0x7C, 0xE7, 0xD9)),
                    StrokeThickness = strokeThickness,
                    StrokeDashArray = dashArray,
                    StrokeStartLineCap = PenLineCap.Round,
                    StrokeEndLineCap = PenLineCap.Round,
                    Effect = new System.Windows.Media.Effects.DropShadowEffect
                    {
                        Color = Color.FromRgb(0x48, 0xE6, 0xD8),
                        BlurRadius = 4,
                        ShadowDepth = 0,
                        Opacity = 0.28
                    },
                    IsHitTestVisible = false
                }
            };

            radarHudRoutes.Add(route);
            ScenarioMap.Markers.Add(route);
        }

        private void RefreshRadarSweepVisuals()
        {
            ClearRadarSweepVisuals();

            if (!markers.TryGetValue("Radar", out GMapMarker radarMarker))
                return;

            PointLatLng radarPosition = radarMarker.Position;

            AddRadarSweepLayer(radarPosition, radarSweepBearing - 5.0, RadarSweepSoftTailDegrees, 0.56, 0x2B, 0xC8, 0xD2, -845);
            AddRadarSweepLayer(radarPosition, radarSweepBearing - 2.0, RadarSweepMidTailDegrees, 0.78, 0x31, 0xDD, 0xD6, -835);

            AddRadarSweepLayer(radarPosition, radarSweepBearing - RadarSweepFrontFaceSpacingDegrees * 2, RadarSweepTailDegrees, 0.58, 0x74, 0xFF, 0xEC, -827);
            AddRadarSweepLayer(radarPosition, radarSweepBearing - RadarSweepFrontFaceSpacingDegrees, RadarSweepTailDegrees, 0.76, 0x74, 0xFF, 0xEC, -826);
            AddRadarSweepLayer(radarPosition, radarSweepBearing, RadarSweepTailDegrees, 0.98, 0x74, 0xFF, 0xEC, -825);
        }

        private void AddRadarSweepLayer(PointLatLng radarPosition, double leadingBearing, double tailDegrees, double opacityScale, byte red, byte green, byte blue, int zIndex)
        {
            for (int i = 0; i < RadarSweepSliceCount; i++)
            {
                double sliceStart = leadingBearing - tailDegrees * (i + 1) / RadarSweepSliceCount;
                double sliceEnd = leadingBearing - tailDegrees * i / RadarSweepSliceCount;

                if (sliceEnd < RadarCoverageStartBearing || sliceStart > RadarCoverageEndBearing)
                    continue;

                sliceStart = Math.Max(RadarCoverageStartBearing, sliceStart);
                sliceEnd = Math.Min(RadarCoverageEndBearing, sliceEnd);

                double progress = (double)(i + 1) / RadarSweepSliceCount;
                byte opacity = (byte)(5 + Math.Pow(progress, 2.0) * 46 * opacityScale);
                AddRadarSweepSlice(radarPosition, sliceStart, sliceEnd, opacity, red, green, blue, zIndex);
            }
        }

        private void AddRadarSweepSlice(PointLatLng radarPosition, double startBearing, double endBearing, byte opacity, byte red, byte green, byte blue, int zIndex)
        {
            var sweep = new GMapPolygon(CreateRadarSweepSlicePoints(radarPosition, startBearing, endBearing))
            {
                ZIndex = zIndex,
                Shape = new Path
                {
                    Stroke = new SolidColorBrush(Color.FromArgb((byte)Math.Min(0x58, (int)opacity + 12), red, green, blue)),
                    StrokeThickness = 0.35,
                    Fill = new SolidColorBrush(Color.FromArgb(opacity, red, green, blue)),
                    Effect = new System.Windows.Media.Effects.DropShadowEffect
                    {
                        Color = Color.FromRgb(red, green, blue),
                        BlurRadius = 6,
                        ShadowDepth = 0,
                        Opacity = 0.32
                    },
                    IsHitTestVisible = false
                }
            };

            radarSweepPolygons.Add(sweep);
            ScenarioMap.Markers.Add(sweep);
        }

        private double WrapRadarBearing(double bearing)
        {
            double span = RadarCoverageEndBearing - RadarCoverageStartBearing;

            while (bearing < RadarCoverageStartBearing)
                bearing += span;

            while (bearing > RadarCoverageEndBearing)
                bearing -= span;

            return bearing;
        }

        private void AddRadarSweepRoute(List<PointLatLng> points, byte opacity, double strokeThickness, double blurRadius)
        {
            var route = new GMapRoute(points)
            {
                ZIndex = -780,
                Shape = new Path
                {
                    Stroke = new SolidColorBrush(Color.FromArgb(opacity, 0xDB, 0xF8, 0xFF)),
                    StrokeThickness = strokeThickness,
                    StrokeStartLineCap = PenLineCap.Round,
                    StrokeEndLineCap = PenLineCap.Round,
                    Effect = new System.Windows.Media.Effects.DropShadowEffect
                    {
                        Color = Color.FromRgb(0x63, 0xD8, 0xFF),
                        BlurRadius = blurRadius,
                        ShadowDepth = 0,
                        Opacity = 0.75
                    },
                    IsHitTestVisible = false
                }
            };

            radarSweepRoutes.Add(route);
            ScenarioMap.Markers.Add(route);
        }

        private void ClearRadarHud()
        {
            foreach (GMapRoute route in radarHudRoutes)
                ScenarioMap.Markers.Remove(route);

            radarHudRoutes.Clear();
        }

        private void ClearRadarSweepVisuals()
        {
            foreach (GMapPolygon sweep in radarSweepPolygons)
                ScenarioMap.Markers.Remove(sweep);

            radarSweepPolygons.Clear();

            foreach (GMapRoute route in radarSweepRoutes)
                ScenarioMap.Markers.Remove(route);

            radarSweepRoutes.Clear();
        }

        private void RefreshAirthreatRoute()
        {
            if (airthreatRoute != null)
            {
                ScenarioMap.Markers.Remove(airthreatRoute);
                airthreatRoute = null;
            }

            if (!markers.TryGetValue("AirthreatStart", out GMapMarker startMarker) ||
                !markers.TryGetValue("AirthreatEnd", out GMapMarker endMarker))
            {
                return;
            }

            airthreatRoute = new GMapRoute(new List<PointLatLng>
            {
                startMarker.Position,
                endMarker.Position
            })
            {
                ZIndex = -900,
                Shape = new Path
                {
                    Stroke = new SolidColorBrush(Color.FromRgb(0xFF, 0x5B, 0x7F)),
                    StrokeThickness = 2.5,
                    StrokeDashArray = new DoubleCollection { 6, 3 },
                    IsHitTestVisible = false
                }
            };

            ScenarioMap.Markers.Add(airthreatRoute);
        }

        private List<PointLatLng> CreateRadarCoveragePoints(PointLatLng center)
        {
            var points = new List<PointLatLng> { center };

            for (double bearing = RadarCoverageStartBearing; bearing <= RadarCoverageEndBearing; bearing += 3.0)
                points.Add(GetDestinationPoint(center, bearing, RadarCoverageKm));

            points.Add(center);
            return points;
        }

        private List<PointLatLng> CreateRangeArcPoints(PointLatLng center, double distanceKm)
        {
            var points = new List<PointLatLng>();

            for (double bearing = RadarCoverageStartBearing; bearing <= RadarCoverageEndBearing; bearing += 2.0)
                points.Add(GetDestinationPoint(center, bearing, distanceKm));

            return points;
        }

        private List<PointLatLng> CreateRadarSweepSlicePoints(PointLatLng center, double startBearing, double endBearing)
        {
            var points = new List<PointLatLng> { center };

            for (double bearing = startBearing; bearing <= endBearing; bearing += 1.0)
                points.Add(GetDestinationPoint(center, bearing, RadarCoverageKm));

            points.Add(GetDestinationPoint(center, endBearing, RadarCoverageKm));
            points.Add(center);
            return points;
        }

        private PointLatLng GetDestinationPoint(PointLatLng start, double bearingDegrees, double distanceKm)
        {
            double angularDistance = distanceKm / EarthRadiusKm;
            double bearing = ToRadians(bearingDegrees);
            double startLatitude = ToRadians(start.Lat);
            double startLongitude = ToRadians(start.Lng);

            double destinationLatitude = Math.Asin(
                Math.Sin(startLatitude) * Math.Cos(angularDistance) +
                Math.Cos(startLatitude) * Math.Sin(angularDistance) * Math.Cos(bearing));

            double destinationLongitude = startLongitude + Math.Atan2(
                Math.Sin(bearing) * Math.Sin(angularDistance) * Math.Cos(startLatitude),
                Math.Cos(angularDistance) - Math.Sin(startLatitude) * Math.Sin(destinationLatitude));

            return new PointLatLng(
                ToDegrees(destinationLatitude),
                NormalizeLongitude(ToDegrees(destinationLongitude)));
        }

        private double ToRadians(double degrees) => degrees * Math.PI / 180.0;

        private double ToDegrees(double radians) => radians * 180.0 / Math.PI;

        private double NormalizeLongitude(double longitude) =>
            ((longitude + 540.0) % 360.0) - 180.0;

        private UIElement CreateMarkerShape(string key, string label)
        {
            return new Border
            {
                Width = 28,
                Height = 28,
                CornerRadius = new CornerRadius(14),
                Background = new SolidColorBrush(GetMarkerColor(key)),
                BorderBrush = Brushes.White,
                BorderThickness = new Thickness(1.5),
                ToolTip = label,
                Child = new PackIcon
                {
                    Kind = GetMarkerIcon(key),
                    Width = 16,
                    Height = 16,
                    Foreground = Brushes.White,
                    HorizontalAlignment = HorizontalAlignment.Center,
                    VerticalAlignment = VerticalAlignment.Center
                }
            };
        }

        private void ZoomIn_Click(object sender, RoutedEventArgs e)
        {
            ChangeZoom(1);
        }

        private void ZoomOut_Click(object sender, RoutedEventArgs e)
        {
            ChangeZoom(-1);
        }

        private void ChangeZoom(double delta)
        {
            double nextZoom = ScenarioMap.Zoom + delta;

            if (nextZoom < ScenarioMap.MinZoom)
                nextZoom = ScenarioMap.MinZoom;
            else if (nextZoom > ScenarioMap.MaxZoom)
                nextZoom = ScenarioMap.MaxZoom;

            ScenarioMap.Zoom = nextZoom;
        }

        private PackIconKind GetMarkerIcon(string key)
        {
            switch (key)
            {
                case "Radar":
                    return PackIconKind.Radar;
                case "Launcher":
                    return PackIconKind.RocketLaunch;
                case "AirthreatStart":
                    return PackIconKind.AirplaneTakeoff;
                case "AirthreatEnd":
                    return PackIconKind.Target;
                case "DetectedTarget":
                    return GetDetectedTargetIcon();
                case "Missile":
                    return PackIconKind.RocketLaunch;
                default:
                    return PackIconKind.MapMarker;
            }
        }

        private PackIconKind GetDetectedTargetIcon()
        {
            uint detectedFlag = (DataContext as AckStatusViewModel)?.DetectedFlag ?? 0;

            switch (detectedFlag)
            {
                case 1:
                    return PackIconKind.AirplaneAlert;
                case 2:
                    return PackIconKind.Bomb;
                default:
                    return PackIconKind.AirplaneOff;
            }
        }

        private Color GetMarkerColor(string key)
        {
            switch (key)
            {
                case "Radar":
                    return Color.FromRgb(0x4C, 0xAF, 0x50);
                case "Launcher":
                    return Color.FromRgb(0xFF, 0xC1, 0x07);
                case "AirthreatStart":
                    return Color.FromRgb(0x21, 0x96, 0xF3);
                case "AirthreatEnd":
                    return Color.FromRgb(0xE9, 0x1E, 0x63);
                case "DetectedTarget":
                    return GetDetectedTargetColor();
                case "Missile":
                    return Color.FromRgb(0xAB, 0x47, 0xBC);
                default:
                    return Color.FromRgb(0x90, 0xA4, 0xAE);
            }
        }

        private Color GetDetectedTargetColor()
        {
            uint detectedFlag = (DataContext as AckStatusViewModel)?.DetectedFlag ?? 0;

            switch (detectedFlag)
            {
                case 1:
                    return Color.FromRgb(0xE5, 0x39, 0x35);
                case 2:
                    return Color.FromRgb(0xFF, 0x6D, 0x00);
                default:
                    return Color.FromRgb(0x78, 0x86, 0x94);
            }
        }
    }
}
