namespace MiniProject_GUI.Models.Scenario
{
    /// <summary>
    /// TCC → ATS: 시나리오 배포 요청 메시지 모델 (NOM ID: 0x01)
    ///
    ///  
    /// 이 클래스는 NOM 메시지의 데이터를 C# 타입으로 표현한 Model이다.
    /// NOMEventHandler.SendScenario()가 이 클래스의 필드를 읽어 NOM 값을 기록한다.
    ///
    /// [ATS 연동 확인 시 사용법]
    /// new ScenarioSend() → 모든 좌표가 0으로 초기화된다.
    /// ATS는 좌표와 관계없이 SendScenario를 받으면 SendScenarioAck를 응답한다.
    ///
    /// [확장 가이드]
    /// 실제 시나리오를 배포하려면 WayPoint, Radar, Launcher 위경도 좌표를
    /// 각 필드에 설정한 뒤 ScenarioService.SendSendScenario(scenarioSend) 호출.
    /// </summary>
    internal class ScenarioSend
    {
        // 공중위협 경로점 위경도 (지도 좌표 — 사람이 읽기 좋은 형식)
        public double WayPoint0_Lat { get; set; }
        public double WayPoint0_Lng { get; set; }
        public double WayPoint1_Lat { get; set; }
        public double WayPoint1_Lng { get; set; }
        public double WayPoint2_Lat { get; set; }
        public double WayPoint2_Lng { get; set; }
        public double WayPoint3_Lat { get; set; }
        public double WayPoint3_Lng { get; set; }

        // 원점 좌표
        public double OriginLat { get; set; }
        public double OriginLon { get; set; }

        // 공중위협 경로점 NE 좌표 (North/East 평면 좌표 — 시뮬레이터가 사용하는 형식)
        public double WayPoint0_X { get; set; }
        public double WayPoint0_Y { get; set; }
        public double WayPoint1_X { get; set; }
        public double WayPoint1_Y { get; set; }
        public double WayPoint2_X { get; set; }
        public double WayPoint2_Y { get; set; }
        public double WayPoint3_X { get; set; }
        public double WayPoint3_Y { get; set; }

        // 레이다 및 발사대 위치 NE 좌표
        public double RadarPositionX    { get; set; }
        public double RadarPositionY    { get; set; }
        public double LauncherPositionX { get; set; }
        public double LauncherPositionY { get; set; }

        /// <summary>
        /// 기본 생성자: 모든 좌표가 0으로 초기화된다.
        /// ATS 연동 확인(연동 상태 점검)에는 이 생성자를 사용한다.
        /// </summary>
        public ScenarioSend() { }
    }
}
