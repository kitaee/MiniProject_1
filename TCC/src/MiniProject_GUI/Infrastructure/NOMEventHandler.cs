using MiniProject_GUI.Models.Scenario;
using MiniProject_GUI.Models.Simualation;
using nframework.nom;
using NOMHandlerLib.Concrete;
using System;
using System.Windows;

namespace MiniProject_GUI.Infrastructure
{
    /// <summary>
    /// C# 내부의 송신 이벤트를 NOM 메시지로 변환하여 nFramework로 전달하는 어댑터.
    ///
    /// [역할 구분]
    /// NOMHandler     : C# WPF ↔ C++ nFramework 사이의 기술적 통로 (DLL 연결)
    /// NOMEventHandler : C# Model 이벤트를 NOM 필드로 변환하여 NOMHandler에 전달
    ///
    /// [연결 방식 — MainWindow 생성자에서 등록]
    ///   EventAggregator.Subscribe&lt;ScenarioSend&gt;(nomEventHandler.SendScenario)
    ///   EventAggregator.Subscribe&lt;SimulationStart&gt;(nomEventHandler.StartSimulation)
    ///   EventAggregator.Subscribe&lt;SimulationStop&gt;(nomEventHandler.StopSimulation)
    ///
    /// → 각 Model 이벤트가 Publish되면 해당 메서드가 자동 호출된다.
    ///
    /// [확장 가이드]
    /// 새 메시지를 추가하려면:
    ///   1. Models/에 새 Model 클래스 추가
    ///   2. 이 클래스에 새 메서드 추가 (아래 메서드들 참고)
    ///   3. MainWindow 생성자에 EventAggregator.Subscribe 등록
    ///   4. UIManager.xml에 메시지 정의 확인
    /// </summary>
    internal class NOMEventHandler
    {
        private NOMHandler nomHandler = null;

        public NOMEventHandler() { }

        public NOMEventHandler(NOMHandler nomHandler)
        {
            this.nomHandler = nomHandler;
        }

        public void SetNOMEventHandler(NOMHandler nomHandler)
        {
            this.nomHandler = nomHandler;
        }

        // ──────────────────────────────────────────────
        // 0x01 SendScenario — TCC → ATS: 시나리오 배포
        // ──────────────────────────────────────────────

        /// <summary>
        /// SendScenario NOM 메시지를 생성하여 ATS에 송신한다.
        ///
        ///   NOM 송신 흐름:
        ///   GetNMessage("SendScenario")  → UIManager.xml 스키마 조회
        ///   createNOMInstance()           → NOM 인스턴스 생성
        ///   setValue("필드명", 값)         → C# 값을 NOM 필드에 기록
        ///   SendNOMMessage(nomInstance)   → nFConnect → UDP 송신
        ///
        /// ATS 연동 확인 용도라면 모든 좌표가 0이어도 ATS가 ACK를 응답한다.
        /// </summary>
        public void SendScenario(ScenarioSend scenarioSend)
        {
            var nomInstance = nomHandler.GetNMessage("SendScenario")?.createNOMInstance();
            if (nomInstance == null) return;

            try
            {
                nomInstance.setValue("Header.MessageID",       new NUShort(0x01));
                nomInstance.setValue("Header.MessageLength",   new NUShort(2));
                nomInstance.setValue("Scenario.OriginLat",    new NDouble(scenarioSend.OriginLat));
                nomInstance.setValue("Scenario.OriginLng",    new NDouble(scenarioSend.OriginLon));
                nomInstance.setValue("Scenario.WayPoint0_Lat", new NDouble(scenarioSend.WayPoint0_Lat));
                nomInstance.setValue("Scenario.WayPoint0_Lng", new NDouble(scenarioSend.WayPoint0_Lng));
                nomInstance.setValue("Scenario.WayPoint1_Lat", new NDouble(scenarioSend.WayPoint1_Lat));
                nomInstance.setValue("Scenario.WayPoint1_Lng", new NDouble(scenarioSend.WayPoint1_Lng));
                nomInstance.setValue("Scenario.WayPoint2_Lat", new NDouble(scenarioSend.WayPoint2_Lat));
                nomInstance.setValue("Scenario.WayPoint2_Lng", new NDouble(scenarioSend.WayPoint2_Lng));
                nomInstance.setValue("Scenario.WayPoint3_Lat", new NDouble(scenarioSend.WayPoint3_Lat));
                nomInstance.setValue("Scenario.WayPoint3_Lng", new NDouble(scenarioSend.WayPoint3_Lng));
                nomInstance.setValue("Scenario.WayPoint0_X",  new NDouble(scenarioSend.WayPoint0_X));
                nomInstance.setValue("Scenario.WayPoint0_Y",  new NDouble(scenarioSend.WayPoint0_Y));
                nomInstance.setValue("Scenario.WayPoint1_X",  new NDouble(scenarioSend.WayPoint1_X));
                nomInstance.setValue("Scenario.WayPoint1_Y",  new NDouble(scenarioSend.WayPoint1_Y));
                nomInstance.setValue("Scenario.WayPoint2_X",  new NDouble(scenarioSend.WayPoint2_X));
                nomInstance.setValue("Scenario.WayPoint2_Y",  new NDouble(scenarioSend.WayPoint2_Y));
                nomInstance.setValue("Scenario.WayPoint3_X",  new NDouble(scenarioSend.WayPoint3_X));
                nomInstance.setValue("Scenario.WayPoint3_Y",  new NDouble(scenarioSend.WayPoint3_Y));
                nomInstance.setValue("Scenario.RadarPositionX",    new NDouble(scenarioSend.RadarPositionX));
                nomInstance.setValue("Scenario.RadarPositionY",    new NDouble(scenarioSend.RadarPositionY));
                nomInstance.setValue("Scenario.LauncherPositionX", new NDouble(scenarioSend.LauncherPositionX));
                nomInstance.setValue("Scenario.LauncherPositionY", new NDouble(scenarioSend.LauncherPositionY));
                nomHandler.SendNOMMessage(nomInstance);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        // ──────────────────────────────────────────────────────
        // 0x03 StartSimulation — TCC → 모의기: 시뮬레이션 시작
        // ──────────────────────────────────────────────────────

        /// <summary>
        /// StartSimulation NOM 메시지를 생성하여 모의기들에 송신한다.
        ///
        /// [확장 가이드]
        /// SendScenario와 동일한 패턴이지만, 필드가 없는 단순 커맨드 메시지다.
        /// SimulationControl View를 추가하고 버튼 클릭 시:
        ///   SimulationService.SendStartSimulation() 호출
        ///   → EventAggregator.Publish&lt;SimulationStart&gt;()
        ///   → 이 메서드가 호출되어 NOM 송신
        /// </summary>
        public void StartSimulation(SimulationStart _)
        {
            var nomInstance = nomHandler.GetNMessage("StartSimulation")?.createNOMInstance();
            if (nomInstance == null) return;

            try
            {
                nomInstance.setValue("Header.MessageID",     new NUShort(0x03));
                nomInstance.setValue("Header.MessageLength", new NUShort(2));
                nomHandler.SendNOMMessage(nomInstance);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        // ──────────────────────────────────────────────────────
        // 0x05 StopSimulation — TCC → 모의기: 시뮬레이션 종료
        // ──────────────────────────────────────────────────────

        /// <summary>
        /// StopSimulation NOM 메시지를 생성하여 모의기들에 송신한다.
        /// StartSimulation과 동일한 구조이므로 패턴 참고용으로 유지한다.
        /// </summary>
        public void StopSimulation(SimulationStop _)
        {
            var nomInstance = nomHandler.GetNMessage("StopSimulation")?.createNOMInstance();
            if (nomInstance == null) return;

            try
            {
                nomInstance.setValue("Header.MessageID",     new NUShort(0x05));
                nomInstance.setValue("Header.MessageLength", new NUShort(2));
                nomHandler.SendNOMMessage(nomInstance);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
    }
}
