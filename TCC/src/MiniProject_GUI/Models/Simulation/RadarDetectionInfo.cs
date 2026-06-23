using MiniProject_GUI.Models.Converter;
using nframework.nom;

namespace MiniProject_GUI.Models.Simulation
{
    internal class RadarDetectionInfo : INOMConvertible
    {
        public const uint MessageId = 5102;

        public uint TargetID { get; set; }
        public float TargetXPos { get; set; }
        public float TargetYPos { get; set; }
        public uint DetectedFlag { get; set; }
        public float TargetVelocity { get; set; }

        public void Import(NOM nom)
        {
            TargetID = nom.getValue("RadarDetection.TargetID").toUInt();
            TargetXPos = nom.getValue("RadarDetection.TargetXPos").toFloat();
            TargetYPos = nom.getValue("RadarDetection.TargetYPos").toFloat();
            DetectedFlag = nom.getValue("RadarDetection.DetectedFlag").toUInt();
            TargetVelocity = nom.getValue("RadarDetection.TargetVelocity").toFloat();
        }
    }
}
