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
            MessageId = GetMessageId(nom);
            SimulatorID = GetSimulatorId(MessageId);
        }

        public static uint GetMessageId(NOM nom)
        {
            try
            {
                return Convert.ToUInt32(nom.getValue("MessageHeader.MessageID").toUInt());
            }
            catch
            {
                return Convert.ToUInt32(nom.msgID);
            }
        }

        public static bool IsScenarioAckMessage(uint messageId)
        {
            return messageId == AtsMessageId ||
                   messageId == MssMessageId ||
                   messageId == LcsMessageId ||
                   messageId == MfrsMessageId;
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

    }
}
