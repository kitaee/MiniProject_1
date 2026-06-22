using MiniProject_GUI.Models.Converter;
using nframework.nom;
using System;
using Simulator = MiniProject_GUI.Models.Enum.SimulatorID;

namespace MiniProject_GUI.Models.Scenario
{
    internal class ScenarioSendAck : INOMConvertible
    {
        public const uint AtsMessageId = 2101;
        public const uint MssMessageId = 3101;
        public const uint LcsMessageId = 4101;
        public const uint MfrsMessageId = 5101;

        public uint MessageId { get; set; }
        public ushort SimulatorID { get; set; }

        public ScenarioSendAck() { }

        public ScenarioSendAck(ushort simulatorID)
        {
            SimulatorID = simulatorID;
        }

        public void Import(NOM nom)
        {
            MessageId = Convert.ToUInt32(nom.msgID);
            SimulatorID = GetSimulatorId(MessageId);
            if (SimulatorID == 0)
                SimulatorID = GetSimulatorId(nom.name);
        }

        public static bool IsScenarioAckMessage(uint messageId)
        {
            return messageId == AtsMessageId ||
                   messageId == MssMessageId ||
                   messageId == LcsMessageId ||
                   messageId == MfrsMessageId;
        }

        public static bool IsScenarioAckName(string messageName)
        {
            return GetSimulatorId(messageName) != 0;
        }

        private static ushort GetSimulatorId(uint messageId)
        {
            switch (messageId)
            {
                case AtsMessageId:
                    return (ushort)Simulator.ATS;
                case MssMessageId:
                    return (ushort)Simulator.MSS;
                case LcsMessageId:
                    return (ushort)Simulator.LCS;
                case MfrsMessageId:
                    return (ushort)Simulator.MFRS;
                default:
                    return 0;
            }
        }

        private static ushort GetSimulatorId(string messageName)
        {
            switch (messageName)
            {
                case "ScenarioACK_ATS":
                    return (ushort)Simulator.ATS;
                case "ScenarioACK_MSS":
                    return (ushort)Simulator.MSS;
                case "ScenarioACK_LCS":
                    return (ushort)Simulator.LCS;
                case "ScenarioACK_MFRS":
                    return (ushort)Simulator.MFRS;
                default:
                    return 0;
            }
        }
    }
}
