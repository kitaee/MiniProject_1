using System;
using nframework.nom;

// This file was created by IntelliVal
// IntelliVal v1.4
// Author: Ha, Jaehee, jaehee.ha@lignex1.com

// This file was created at 2026-06-18 12:07:51

namespace nframework.intellival
{
namespace UplinkInfo
{
public class v_MessageHeader_MessageID : NUInteger{
public v_MessageHeader_MessageID(uint x):base(x){}
public v_MessageHeader_MessageID(NUInteger t):base(t.value){}}
public class v_MessageHeader_MessageLength : NUInteger{
public v_MessageHeader_MessageLength(uint x):base(x){}
public v_MessageHeader_MessageLength(NUInteger t):base(t.value){}}
public class v_UplinkInfo_AirthreatID : NUInteger{
public v_UplinkInfo_AirthreatID(uint x):base(x){}
public v_UplinkInfo_AirthreatID(NUInteger t):base(t.value){}}
public class v_UplinkInfo_AirthreatXpos : NFloat{
public v_UplinkInfo_AirthreatXpos(float x):base(x){}
public v_UplinkInfo_AirthreatXpos(NFloat t):base(t.value){}}
public class v_UplinkInfo_AirthreatYPos : NFloat{
public v_UplinkInfo_AirthreatYPos(float x):base(x){}
public v_UplinkInfo_AirthreatYPos(NFloat t):base(t.value){}}
public class v_UplinkInfo_AirthreatZPos : NFloat{
public v_UplinkInfo_AirthreatZPos(float x):base(x){}
public v_UplinkInfo_AirthreatZPos(NFloat t):base(t.value){}}
public class v_UplinkInfo_MissileID : NUInteger{
public v_UplinkInfo_MissileID(uint x):base(x){}
public v_UplinkInfo_MissileID(NUInteger t):base(t.value){}}
public class v_UplinkInfo_AirthreatVelocity : NFloat{
public v_UplinkInfo_AirthreatVelocity(float x):base(x){}
public v_UplinkInfo_AirthreatVelocity(NFloat t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageID = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageLength = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_UplinkInfo_AirthreatID = val => val.toUInt();
public static Func<nframework.nom.NValueType,float> t_UplinkInfo_AirthreatXpos = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_UplinkInfo_AirthreatYPos = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_UplinkInfo_AirthreatZPos = val => val.toFloat();
public static Func<nframework.nom.NValueType,uint> t_UplinkInfo_MissileID = val => val.toUInt();
public static Func<nframework.nom.NValueType,float> t_UplinkInfo_AirthreatVelocity = val => val.toFloat();
}

}

namespace RadarDetectionInfo
{
public class v_MessageHeader_MessageID : NUInteger{
public v_MessageHeader_MessageID(uint x):base(x){}
public v_MessageHeader_MessageID(NUInteger t):base(t.value){}}
public class v_MessageHeader_MessageLength : NUInteger{
public v_MessageHeader_MessageLength(uint x):base(x){}
public v_MessageHeader_MessageLength(NUInteger t):base(t.value){}}
public class v_RadarDetection_TargetID : NUInteger{
public v_RadarDetection_TargetID(uint x):base(x){}
public v_RadarDetection_TargetID(NUInteger t):base(t.value){}}
public class v_RadarDetection_TargetXPos : NFloat{
public v_RadarDetection_TargetXPos(float x):base(x){}
public v_RadarDetection_TargetXPos(NFloat t):base(t.value){}}
public class v_RadarDetection_TargetYPos : NFloat{
public v_RadarDetection_TargetYPos(float x):base(x){}
public v_RadarDetection_TargetYPos(NFloat t):base(t.value){}}
public class v_RadarDetection_TargetZPos : NFloat{
public v_RadarDetection_TargetZPos(float x):base(x){}
public v_RadarDetection_TargetZPos(NFloat t):base(t.value){}}
public class v_RadarDetection_DetectedFlag : NUInteger{
public v_RadarDetection_DetectedFlag(uint x):base(x){}
public v_RadarDetection_DetectedFlag(NUInteger t):base(t.value){}}
public class v_RadarDetection_TargetVelocity : NFloat{
public v_RadarDetection_TargetVelocity(float x):base(x){}
public v_RadarDetection_TargetVelocity(NFloat t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageID = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageLength = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_RadarDetection_TargetID = val => val.toUInt();
public static Func<nframework.nom.NValueType,float> t_RadarDetection_TargetXPos = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_RadarDetection_TargetYPos = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_RadarDetection_TargetZPos = val => val.toFloat();
public static Func<nframework.nom.NValueType,uint> t_RadarDetection_DetectedFlag = val => val.toUInt();
public static Func<nframework.nom.NValueType,float> t_RadarDetection_TargetVelocity = val => val.toFloat();
}

}

namespace DownlinkInfo
{
public class v_MessageHeader_MessageID : NUInteger{
public v_MessageHeader_MessageID(uint x):base(x){}
public v_MessageHeader_MessageID(NUInteger t):base(t.value){}}
public class v_MessageHeader_MessageLength : NUInteger{
public v_MessageHeader_MessageLength(uint x):base(x){}
public v_MessageHeader_MessageLength(NUInteger t):base(t.value){}}
public class v_DownlinkInfo_MissleID : NUInteger{
public v_DownlinkInfo_MissleID(uint x):base(x){}
public v_DownlinkInfo_MissleID(NUInteger t):base(t.value){}}
public class v_DownlinkInfo_MissileVelocity : NFloat{
public v_DownlinkInfo_MissileVelocity(float x):base(x){}
public v_DownlinkInfo_MissileVelocity(NFloat t):base(t.value){}}
public class v_DownlinkInfo_MissleXPos : NFloat{
public v_DownlinkInfo_MissleXPos(float x):base(x){}
public v_DownlinkInfo_MissleXPos(NFloat t):base(t.value){}}
public class v_DownlinkInfo_MissleYPos : NFloat{
public v_DownlinkInfo_MissleYPos(float x):base(x){}
public v_DownlinkInfo_MissleYPos(NFloat t):base(t.value){}}
public class v_DownlinkInfo_MissleZPos : NFloat{
public v_DownlinkInfo_MissleZPos(float x):base(x){}
public v_DownlinkInfo_MissleZPos(NFloat t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageID = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageLength = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_DownlinkInfo_MissleID = val => val.toUInt();
public static Func<nframework.nom.NValueType,float> t_DownlinkInfo_MissileVelocity = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_DownlinkInfo_MissleXPos = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_DownlinkInfo_MissleYPos = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_DownlinkInfo_MissleZPos = val => val.toFloat();
}

}

namespace DeployScenarioRequest
{
public class v_MessageHeader_MessageID : NUInteger{
public v_MessageHeader_MessageID(uint x):base(x){}
public v_MessageHeader_MessageID(NUInteger t):base(t.value){}}
public class v_MessageHeader_MessageLength : NUInteger{
public v_MessageHeader_MessageLength(uint x):base(x){}
public v_MessageHeader_MessageLength(NUInteger t):base(t.value){}}
public class v_Airthreat_AirthreatID : NUInteger{
public v_Airthreat_AirthreatID(uint x):base(x){}
public v_Airthreat_AirthreatID(NUInteger t):base(t.value){}}
public class v_Airthreat_StartLatitude : NFloat{
public v_Airthreat_StartLatitude(float x):base(x){}
public v_Airthreat_StartLatitude(NFloat t):base(t.value){}}
public class v_Airthreat_StartLongitude : NFloat{
public v_Airthreat_StartLongitude(float x):base(x){}
public v_Airthreat_StartLongitude(NFloat t):base(t.value){}}
public class v_Airthreat_EndLatitude : NFloat{
public v_Airthreat_EndLatitude(float x):base(x){}
public v_Airthreat_EndLatitude(NFloat t):base(t.value){}}
public class v_Airthreat_EndLongitude : NFloat{
public v_Airthreat_EndLongitude(float x):base(x){}
public v_Airthreat_EndLongitude(NFloat t):base(t.value){}}
public class v_RadarPositionLatitude : NFloat{
public v_RadarPositionLatitude(float x):base(x){}
public v_RadarPositionLatitude(NFloat t):base(t.value){}}
public class v_RadarPositionLongitude : NFloat{
public v_RadarPositionLongitude(float x):base(x){}
public v_RadarPositionLongitude(NFloat t):base(t.value){}}
public class v_LauncherPositionLatitude : NFloat{
public v_LauncherPositionLatitude(float x):base(x){}
public v_LauncherPositionLatitude(NFloat t):base(t.value){}}
public class v_LauncherPositionLongitude : NFloat{
public v_LauncherPositionLongitude(float x):base(x){}
public v_LauncherPositionLongitude(NFloat t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageID = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageLength = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_Airthreat_AirthreatID = val => val.toUInt();
public static Func<nframework.nom.NValueType,float> t_Airthreat_StartLatitude = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Airthreat_StartLongitude = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Airthreat_EndLatitude = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_Airthreat_EndLongitude = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_RadarPositionLatitude = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_RadarPositionLongitude = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_LauncherPositionLatitude = val => val.toFloat();
public static Func<nframework.nom.NValueType,float> t_LauncherPositionLongitude = val => val.toFloat();
}

}

namespace StartSimulationRequest
{
public class v_MessageHeader_MessageID : NUInteger{
public v_MessageHeader_MessageID(uint x):base(x){}
public v_MessageHeader_MessageID(NUInteger t):base(t.value){}}
public class v_MessageHeader_MessageLength : NUInteger{
public v_MessageHeader_MessageLength(uint x):base(x){}
public v_MessageHeader_MessageLength(NUInteger t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageID = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageLength = val => val.toUInt();
}

}

namespace StopSimulationRequest
{
public class v_MessageHeader_MessageID : NUInteger{
public v_MessageHeader_MessageID(uint x):base(x){}
public v_MessageHeader_MessageID(NUInteger t):base(t.value){}}
public class v_MessageHeader_MessageLength : NUInteger{
public v_MessageHeader_MessageLength(uint x):base(x){}
public v_MessageHeader_MessageLength(NUInteger t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageID = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageLength = val => val.toUInt();
}

}

namespace LaunchMissileRequest
{
public class v_MessageHeader_MessageID : NUInteger{
public v_MessageHeader_MessageID(uint x):base(x){}
public v_MessageHeader_MessageID(NUInteger t):base(t.value){}}
public class v_MessageHeader_MessageLength : NUInteger{
public v_MessageHeader_MessageLength(uint x):base(x){}
public v_MessageHeader_MessageLength(NUInteger t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageID = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageLength = val => val.toUInt();
}

}

namespace ScenarioACK_2101
{
public class v_MessageHeader_MessageID : NUInteger{
public v_MessageHeader_MessageID(uint x):base(x){}
public v_MessageHeader_MessageID(NUInteger t):base(t.value){}}
public class v_MessageHeader_MessageLength : NUInteger{
public v_MessageHeader_MessageLength(uint x):base(x){}
public v_MessageHeader_MessageLength(NUInteger t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageID = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageLength = val => val.toUInt();
}

}

namespace ScenarioACK_3101
{
public class v_MessageHeader_MessageID : NUInteger{
public v_MessageHeader_MessageID(uint x):base(x){}
public v_MessageHeader_MessageID(NUInteger t):base(t.value){}}
public class v_MessageHeader_MessageLength : NUInteger{
public v_MessageHeader_MessageLength(uint x):base(x){}
public v_MessageHeader_MessageLength(NUInteger t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageID = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageLength = val => val.toUInt();
}

}

namespace ScenarioACK_4101
{
public class v_MessageHeader_MessageID : NUInteger{
public v_MessageHeader_MessageID(uint x):base(x){}
public v_MessageHeader_MessageID(NUInteger t):base(t.value){}}
public class v_MessageHeader_MessageLength : NUInteger{
public v_MessageHeader_MessageLength(uint x):base(x){}
public v_MessageHeader_MessageLength(NUInteger t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageID = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageLength = val => val.toUInt();
}

}

namespace ScenarioACK_5101
{
public class v_MessageHeader_MessageID : NUInteger{
public v_MessageHeader_MessageID(uint x):base(x){}
public v_MessageHeader_MessageID(NUInteger t):base(t.value){}}
public class v_MessageHeader_MessageLength : NUInteger{
public v_MessageHeader_MessageLength(uint x):base(x){}
public v_MessageHeader_MessageLength(NUInteger t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageID = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageLength = val => val.toUInt();
}

}

namespace MissileQuantityInfo
{
public class v_MessageHeader_MessageID : NUInteger{
public v_MessageHeader_MessageID(uint x):base(x){}
public v_MessageHeader_MessageID(NUInteger t):base(t.value){}}
public class v_MessageHeader_MessageLength : NUInteger{
public v_MessageHeader_MessageLength(uint x):base(x){}
public v_MessageHeader_MessageLength(NUInteger t):base(t.value){}}
public class v_MissileQuantity : NUInteger{
public v_MissileQuantity(uint x):base(x){}
public v_MissileQuantity(NUInteger t):base(t.value){}}
public class T{
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageID = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_MessageHeader_MessageLength = val => val.toUInt();
public static Func<nframework.nom.NValueType,uint> t_MissileQuantity = val => val.toUInt();
}

}

}
