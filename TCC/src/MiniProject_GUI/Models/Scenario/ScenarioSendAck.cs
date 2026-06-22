using MiniProject_GUI.Models.Converter;
using nframework.nom;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MiniProject_GUI.Models.Scenario
{
    internal class ScenarioSendAck : INOMConvertible
    {
        public ushort SimulatorID { get; set; }
        public ScenarioSendAck() { }

        public ScenarioSendAck(ushort simulatorID)
        {
            SimulatorID = simulatorID;
        }

        public void Import(NOM nom)
        {
            SimulatorID = nom.getValue("SimulatorID").toUShort();
        }
    }
}
