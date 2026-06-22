using MiniProject_GUI.Models.Converter;
using nframework.nom;

namespace MiniProject_GUI.Models.Simualation
{
    /// <summary>
    /// 모의기 → TCC: 시뮬레이션 종료 ACK 메시지 (NOM ID: 0x06)
    /// </summary>
    internal class SimulationStopAck : INOMConvertible
    {
        /// <summary>ACK를 보낸 시뮬레이터 ID</summary>
        public ushort SimulatorID { get; set; }

        public SimulationStopAck() { }

        public void Import(NOM nom)
        {
            SimulatorID = nom.getValue("SimulatorID").toUShort();
        }
    }
}
