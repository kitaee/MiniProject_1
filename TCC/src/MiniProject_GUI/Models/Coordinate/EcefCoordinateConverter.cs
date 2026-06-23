using System;

namespace MiniProject_GUI.Models.Coordinate
{
    internal struct EcefXYCoordinate
    {
        public float XPos { get; }
        public float YPos { get; }

        public EcefXYCoordinate(double xPos, double yPos)
        {
            XPos = (float)xPos;
            YPos = (float)yPos;
        }
    }

    internal struct GeoCoordinate
    {
        public float Latitude { get; }
        public float Longitude { get; }

        public GeoCoordinate(double latitude, double longitude)
        {
            Latitude = (float)latitude;
            Longitude = (float)longitude;
        }
    }

    internal static class EcefCoordinateConverter
    {
        private const double EarthSemiMajorAxisMeters = 6378137.0;
        private const double EarthFlattening = 1.0 / 298.257223563;
        private const double EarthEccentricitySquared = EarthFlattening * (2.0 - EarthFlattening);

        public static EcefXYCoordinate ToEcefXY(float latitudeDegrees, float longitudeDegrees)
        {
            double latitudeRadians = ToRadians(latitudeDegrees);
            double longitudeRadians = ToRadians(longitudeDegrees);
            double sinLatitude = Math.Sin(latitudeRadians);
            double cosLatitude = Math.Cos(latitudeRadians);
            double radius = EarthSemiMajorAxisMeters /
                Math.Sqrt(1.0 - EarthEccentricitySquared * sinLatitude * sinLatitude);

            double xPos = radius * cosLatitude * Math.Cos(longitudeRadians);
            double yPos = radius * cosLatitude * Math.Sin(longitudeRadians);

            return new EcefXYCoordinate(xPos, yPos);
        }

        public static GeoCoordinate ToLatitudeLongitude(float xPos, float yPos, bool northernHemisphere = true)
        {
            double planarRadius = Math.Sqrt((double)xPos * xPos + (double)yPos * yPos);
            double longitudeDegrees = ToDegrees(Math.Atan2(yPos, xPos));
            double latitudeRadians = EstimateLatitudeFromPlanarRadius(planarRadius);

            if (!northernHemisphere)
            {
                latitudeRadians = -latitudeRadians;
            }

            return new GeoCoordinate(ToDegrees(latitudeRadians), longitudeDegrees);
        }

        private static double EstimateLatitudeFromPlanarRadius(double planarRadius)
        {
            if (planarRadius <= 0.0)
            {
                return Math.PI / 2.0;
            }

            if (planarRadius >= EarthSemiMajorAxisMeters)
            {
                return 0.0;
            }

            double low = 0.0;
            double high = Math.PI / 2.0;

            for (int i = 0; i < 64; i++)
            {
                double mid = (low + high) / 2.0;
                double midRadius = RadiusAtLatitude(mid) * Math.Cos(mid);

                if (midRadius > planarRadius)
                {
                    low = mid;
                }
                else
                {
                    high = mid;
                }
            }

            return (low + high) / 2.0;
        }

        private static double RadiusAtLatitude(double latitudeRadians)
        {
            double sinLatitude = Math.Sin(latitudeRadians);
            return EarthSemiMajorAxisMeters /
                Math.Sqrt(1.0 - EarthEccentricitySquared * sinLatitude * sinLatitude);
        }

        private static double ToRadians(double degrees)
        {
            return degrees * Math.PI / 180.0;
        }

        private static double ToDegrees(double radians)
        {
            return radians * 180.0 / Math.PI;
        }
    }
}
