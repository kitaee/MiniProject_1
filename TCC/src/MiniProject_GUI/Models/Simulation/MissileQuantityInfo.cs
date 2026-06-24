using MiniProject_GUI.Models.Converter;
using nframework.nom;

namespace MiniProject_GUI.Models.Simulation
{
    internal class MissileQuantityInfo : INOMConvertible
    {
        public const uint MessageId = 4102;

        public uint MissileQuantity { get; set; }

        public void Import(NOM nom)
        {
            MissileQuantity = nom.getValue("MissileQuantity").toUInt();
        }
    }
}
