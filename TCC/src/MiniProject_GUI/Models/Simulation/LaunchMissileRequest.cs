namespace MiniProject_GUI.Models.Simualation
{
    internal class LaunchMissileRequest
    {
        public const uint CommandMessageId = 9004;
        public const uint MessageId = 1401;
        public const uint MessageLengthBytes = 24;

        public uint AirthreatID { get; set; }
        public float AirthreatXPos { get; set; }
        public float AirthreatYPos { get; set; }
        public uint MissileID { get; set; }
    }
}
