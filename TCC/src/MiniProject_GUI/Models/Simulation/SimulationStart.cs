namespace MiniProject_GUI.Models.Simualation
{
    /// <summary>
    /// TCC → 모의기: 시뮬레이션 시작 요청 메시지 (NOM ID: 0x03)
    ///
    /// [확장 가이드]
    /// 시뮬레이션 시작 기능을 추가하려면:
    /// 1. 버튼 클릭 핸들러에서 SimulationService.SendStartSimulation() 호출
    /// 2. NOMEventHandler.StartSimulation()이 NOM 메시지를 생성·송신
    /// 3. 각 모의기가 StartSimulationAck로 응답
    ///
    /// 이 모델은 데이터 필드가 없는 단순 커맨드 메시지다.
    /// (Header만 있어도 충분히 동작한다)
    /// </summary>
    internal class SimulationStart
    {
        public SimulationStart() { }
    }
}
