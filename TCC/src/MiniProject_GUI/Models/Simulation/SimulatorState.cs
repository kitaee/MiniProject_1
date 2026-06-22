using MiniProject_GUI.Models.Converter;
using nframework.nom;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MiniProject_GUI.Models.Simulation
{
    // TODO : add service logic into Simulation Service
    internal class SimulatorState : INOMConvertible
    {
        public ushort SimulatorID { get; set; }

        public SimulatorState() { }

        public SimulatorState(ushort simulatorID)
        {
            SimulatorID = simulatorID;
        }

        public void Import(NOM nom)
        {
            SimulatorID = nom.getValue("SimulatorID").toUShort();
        }
    }
}
