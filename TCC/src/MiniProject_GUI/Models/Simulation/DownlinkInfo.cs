using MiniProject_GUI.Models.Converter;
using nframework.nom;

namespace MiniProject_GUI.Models.Simulation
{
    internal class DownlinkInfo : INOMConvertible
    {
        public const uint MessageId = 5103;

        public uint MissileID { get; set; }
        public float MissileVelocity { get; set; }
        public float MissileXPos { get; set; }
        public float MissileYPos { get; set; }

        public void Import(NOM nom)
        {
            MissileID = nom.getValue("DownlinkInfo.MissileID").toUInt();
            MissileVelocity = nom.getValue("DownlinkInfo.MissileVelocity").toFloat();
            MissileXPos = nom.getValue("DownlinkInfo.MissileXPos").toFloat();
            MissileYPos = nom.getValue("DownlinkInfo.MissileYPos").toFloat();
        }
    }
}
