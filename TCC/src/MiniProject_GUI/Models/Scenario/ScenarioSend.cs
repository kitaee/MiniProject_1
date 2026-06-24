namespace MiniProject_GUI.Models.Scenario
{
    internal class ScenarioSend
    {
        public const uint MessageId = 1001;
        public const uint MessageLengthBytes = 52;

        public uint AirthreatID { get; set; }
        public float AirthreatVelocity { get; set; }
        public float StartLatitude { get; set; }
        public float StartLongitude { get; set; }
        public float EndLatitude { get; set; }
        public float EndLongitude { get; set; }
        public float RadarPositionLatitude { get; set; }
        public float RadarPositionLongitude { get; set; }
        public float LauncherPositionLatitude { get; set; }
        public float LauncherPositionLongitude { get; set; }
        public float MissileVelocity { get; set; }

        public ScenarioSend()
        {
            AirthreatID = 1;
        }
    }
}
