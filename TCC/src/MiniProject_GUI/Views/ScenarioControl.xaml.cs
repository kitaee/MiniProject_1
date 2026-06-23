using GMap.NET;
using GMap.NET.MapProviders;
using GMap.NET.WindowsPresentation;
using MaterialDesignThemes.Wpf;
using MiniProject_GUI.ViewModels;
using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;

namespace MiniProject_GUI.Views
{
    public partial class ScenarioControl : UserControl
    {
        private const double RadarCoverageKm = 230.0;
        private const double RadarCoverageStartBearing = -45.0;
        private const double RadarCoverageEndBearing = 45.0;
        private const double EarthRadiusKm = 6371.0;

        private readonly Dictionary<string, GMapMarker> markers = new Dictionary<string, GMapMarker>();
        private GMapPolygon radarCoverage;
        private GMapRoute airthreatRoute;

        public ScenarioControl()
        {
            InitializeComponent();
            DataContext = ViewModelLocator.AckStatus;
            InitializeMap();
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
            ScenarioMap.DragButton = MouseButton.Right;
            ScenarioMap.MouseWheelZoomEnabled = true;
            ScenarioMap.MouseWheelZoomType = MouseWheelZoomType.MousePositionWithoutCenter;
            ScenarioMap.ShowCenter = false;
        }

        private void ScenarioMap_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
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

        private void SetMarker(string key, string label, PointLatLng coordinate)
        {
            if (markers.TryGetValue(key, out GMapMarker existingMarker))
                ScenarioMap.Markers.Remove(existingMarker);

            var marker = new GMapMarker(coordinate)
            {
                Offset = new Point(-14, -14),
                Shape = CreateMarkerShape(key, label)
            };

            markers[key] = marker;
            ScenarioMap.Markers.Add(marker);
        }

        private void SetRadarCoverage(PointLatLng radarPosition)
        {
            if (radarCoverage != null)
                ScenarioMap.Markers.Remove(radarCoverage);

            radarCoverage = new GMapPolygon(CreateRadarCoveragePoints(radarPosition))
            {
                ZIndex = -1000,
                Shape = new Path
                {
                    Stroke = new SolidColorBrush(Color.FromArgb(0xCC, 0x1E, 0x88, 0xE5)),
                    StrokeThickness = 2,
                    Fill = new SolidColorBrush(Color.FromArgb(0x45, 0x1E, 0x88, 0xE5)),
                    IsHitTestVisible = false
                }
            };

            ScenarioMap.Markers.Add(radarCoverage);
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
                default:
                    return PackIconKind.MapMarker;
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
                default:
                    return Color.FromRgb(0x90, 0xA4, 0xAE);
            }
        }
    }
}
