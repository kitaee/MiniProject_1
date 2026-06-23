namespace MiniProject_GUI.Models.Simualation
{
    internal class UplinkInfo
    {
        public const uint MessageId = 1501;
        public const uint MessageLengthBytes = 28;

        public uint AirthreatID { get; set; }
        public float AirthreatXPos { get; set; }
        public float AirthreatYPos { get; set; }
        public uint MissileID { get; set; }
        public float AirthreatVelocity { get; set; }
    }
}
