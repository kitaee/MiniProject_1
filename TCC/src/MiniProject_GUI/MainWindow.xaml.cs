using nframework.nom;
using NOMHandlerLib.Concrete;
using nframework.log4nf;
using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Interop;
using System.Threading;
using System.Windows.Threading;
using MiniProject_GUI.Infrastructure;
using MiniProject_GUI.Models.Scenario;
using MiniProject_GUI.Models.Simualation;
using MiniProject_GUI.Services;
using NOMHandlerLib.Core;

namespace MiniProject_GUI
{
    /// <summary>
    /// TCC GUI 애플리케이션의 최상위 창 — nFramework 연결의 시작점.
    ///
    /// ┌──────────────────────────────────────────────────────────────────────┐
    /// │  MainWindow의 3가지 핵심 역할                                        │
    /// │                                                                      │
    /// │  1. nFramework 초기화 (MainWindow_Loaded)                            │
    /// │     CreateNFConnect → DoPlugIn → SetWindowHandle → ExecStart      │
    /// │                                                                      │
    /// │  2. NOM 메시지 수신 → Service로 라우팅 (OnNOMMessageReceived)       │
    /// │     메시지 이름을 보고 적합한 Service의 Receive 메서드를 호출        │
    /// │                                                                      │
    /// │  3. GUI 이벤트 → NOM 송신 연결 (생성자에서 EventAggregator 구독)    │
    /// │     EventAggregator.Subscribe&lt;Model&gt;(NOMEventHandler.메서드)   │
    /// └──────────────────────────────────────────────────────────────────────┘
    ///
    /// [확장 가이드]
    /// 새 메시지를 추가하려면:
    ///   송신: EventAggregator.Subscribe&lt;새Model&gt;(nomEventHandler.새메서드) 추가
    ///   수신: OnNOMMessageReceived의 if-else 블록에 새 분기 추가
    /// </summary>


    public partial class MainWindow : Window
    {
        // NOMHandler: C# WPF와 C++ nFramework 사이의 실제 통로
        private readonly NOMHandler nomHandler = null;

        // NOMEventHandler: C# Model 이벤트를 NOM 메시지로 변환하는 어댑터
        private readonly NOMEventHandler nomEventHandler = new NOMEventHandler();

        // Object 클래스 NOM 인스턴스 관리 (Discover/Remove 처리용)
        private readonly Dictionary<string, HashSet<uint>> instanceIDByName
            = new Dictionary<string, HashSet<uint>>();
        private readonly Dictionary<uint, NOM> discoveredNOMInstance
            = new Dictionary<uint, NOM>();

        private static Mutex mutObj = new Mutex();
        private LoggableCS l = new LoggableCS("MainWindow");

        public MainWindow()
        {
            // UIManager.xml: TCC가 송수신할 NOM 메시지 스키마가 정의된 설정 파일
            List<string> nomFilePaths = new List<string>
            {
                Environment.CurrentDirectory + @"\SchemaRegistryData.xml",
                Environment.CurrentDirectory + @"\UIManager\UIManager.xml"
            };

            // NOMHandler 생성: C# WPF ↔ C++ nFConnect DLL 연결
            nomHandler = new NOMHandler(nomFilePaths);

            // NOM 메시지 수신 이벤트 구독
            // C++ 측에서 메시지가 도착하면 OnNOMMessageReceived() 호출
            nomHandler.MessageReceived += OnNOMMessageReceived;

            // NOM 메시지 송신 완료 이벤트 구독 (콘솔 로그용)
            nomHandler.MessageSent += OnNOMMessageSent;

            Loaded += MainWindow_Loaded;
            Closed += MainWindow_Closed;

            // NOMEventHandler에 NOMHandler 주입
            nomEventHandler.SetNOMEventHandler(nomHandler);

            // ──   EventAggregator 송신 이벤트 연결 ──────────
            //
            // GUI에서 이벤트가 발행(Publish)되면 NOMEventHandler의 메서드가 호출되어
            // NOM 메시지를 생성하고 nFramework로 전달한다.
            //
            // 예: ScenarioService.SendSendScenario() 호출
            //   → EventAggregator.Publish<ScenarioSend>()
            //   → nomEventHandler.SendScenario() 자동 호출
            //   → NOM 메시지 생성 → UDP 송신

            EventAggregator.Instance.Subscribe<ScenarioSend>(nomEventHandler.SendScenario);

            // [확장 가이드]
            // 시뮬레이션 시작·종료 기능을 UI에 추가하면 아래 구독을 활성화한다.
            // SimulationControl View를 만들고 버튼에서 SimulationService.SendStartSimulation() 호출.
            EventAggregator.Instance.Subscribe<SimulationStart>(nomEventHandler.StartSimulation);
            EventAggregator.Instance.Subscribe<SimulationStop>(nomEventHandler.StopSimulation);

            InitializeComponent();
        }

        // ────────────────────────────────────────────────────────────────────
        // nFramework 초기화 및 정리
        // ────────────────────────────────────────────────────────────────────

        /// <summary>
        /// 창이 표시된 직후 nFramework를 초기화한다.
        /// HWND(윈도우 핸들)는 창이 완전히 생성된 이후에만 사용 가능하므로
        /// 생성자가 아닌 Loaded 이벤트에서 초기화한다.
        ///
        ///   초기화 순서 (순서 변경 불가):
        ///   ① AddHook        : C++ UIManager가 WM_COPYDATA로 NOM을 보낼 콜백 등록
        ///   ② CreateNFConnect: C++ nFConnect 객체 생성
        ///   ③ DoPlugIn       : MiniProject.ini 파일을 읽어 컴포넌트 DLL 로드
        ///   ④ SetWindowHandle: C++ 측에 WPF 창의 HWND 전달
        ///   ⑤ ExecStart      : 모든 컴포넌트 시작 (UDPCommunicationManager가 소켓 오픈)
        /// </summary>
        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            (PresentationSource.FromVisual(this) as HwndSource)?.AddHook(nomHandler.WndProcCallback); // ①

            if (nomHandler.CreateNFConnect()) // ②
            {
                nomHandler.DoPlugIn();                                             // ③
                nomHandler.SetWindowHandle(new WindowInteropHelper(this).Handle); // ④
                nomHandler.ExecStart();                                            // ⑤
            }
            else
            {
                MessageBox.Show("C++ NFConnect 객체를 생성하지 못하였습니다.\n" +
                                "MiniProject.ini 및 nFramework DLL 경로를 확인하세요.");
            }

            l.Warn("Main Window is loaded.");
        }

        /// <summary>
        /// 창이 닫힐 때 nFramework 연결을 정리한다.
        /// </summary>
        private void MainWindow_Closed(object sender, EventArgs e)
        {
            nomHandler.ExecStop();
            nomHandler.DoPlugOut();
            nomHandler.DestroyNFConnect();

            System.Diagnostics.Process.GetCurrentProcess().Kill();
            Application.Current.Shutdown();
            Environment.Exit(0);
        }

        // ────────────────────────────────────────────────────────────────────
        // NOM 메시지 처리
        // ────────────────────────────────────────────────────────────────────

        private void OnNOMMessageSent(NOM nomInstance, EMessageOperation operation)
        {
            if (operation == EMessageOperation.Send)
                Console.WriteLine("[OnNOMMessageSent()] C# send {" + nomInstance.name + "}.");
        }

        /// <summary>
        /// NOM 메시지 수신 핸들러 — 메시지를 해당 Service로 라우팅한다.
        ///
        ///  
        /// 이 메서드는 "교환원" 역할을 한다.
        ///   수신 메시지 이름 → 해당 Service.Receive메서드() 호출
        ///   → Service가 NOM을 C# Model로 변환
        ///   → EventAggregator.Publish로 ViewModel에 전달
        ///   → ViewModel이 상태 변경 → INotifyPropertyChanged → WPF Binding → UI 갱신
        ///
        /// [Dispatcher.BeginInvoke가 필요한 이유]
        /// NOM 수신 콜백은 C++ 스레드에서 발생한다.
        /// WPF에서 UI 관련 작업은 반드시 UI Thread에서 수행해야 하므로
        /// Dispatcher를 통해 UI Thread의 실행 큐로 전달한다.
        ///
        /// [확장 가이드]
        /// 새 메시지를 수신하려면 아래 if-else 블록에 분기를 추가한다.
        ///   else if (innerNom.name == "새메시지이름")
        ///       새Service.Receive새메시지(innerNom);
        /// UIManager.xml에도 해당 메시지가 Subscribe로 정의되어 있어야 한다.
        /// </summary>
        private void OnNOMMessageReceived(NOM nomInstance, EMessageOperation operation)
        {
            Dispatcher.BeginInvoke(DispatcherPriority.Send, new Action(delegate
            {
                mutObj.WaitOne();
                try
                {
                    switch (operation)
                    {
                        case EMessageOperation.Receive:
                        {
                            NOM innerNom = nomInstance.clone();
                            Console.WriteLine("[OnNOMMessageReceived()] C# receive {" + innerNom.name + "}.");

                            // ── 수신 메시지 라우팅 ─────────────────────────────────

                            if (ScenarioSendAck.IsScenarioAckMessage(Convert.ToUInt32(innerNom.msgID)))
                            {
                                // ATS → TCC: 시나리오 배포 ACK
                                // → ScenarioService → EventAggregator.Publish<ScenarioSendAck>
                                // → AckStatusViewModel.OnScenarioSendAck() → 표시등 초록색
                                ScenarioService.ReceiveSendScenarioAck(innerNom);
                            }
                            else if (innerNom.name == "SimulatorState")
                            {
                                // 모의기 → TCC: 1초 주기 하트비트
                                // → SimulationService → EventAggregator.Publish<SimulatorState>
                                // → StatusViewModel → 연결 상태 표시등 갱신
                                SimulationService.ReceiveSimulatorState(innerNom);
                            }
                            else if (innerNom.name == "StartSimulationAck")
                            {
                                // [확장 가이드]
                                // 시뮬레이션 시작 ACK 처리. SimulationViewModel을 추가하여
                                // IsSimulationRunning 등의 상태를 관리할 수 있다.
                                SimulationService.ReceiveStartSimulationAck(innerNom);
                            }
                            else if (innerNom.name == "StopSimulationAck")
                            {
                                SimulationService.ReceiveStopSimulationAck(innerNom);
                            }

                            break;
                        }

                        case EMessageOperation.Discover:
                        {
                            if (!discoveredNOMInstance.ContainsKey(nomInstance.instanceID))
                            {
                                discoveredNOMInstance[nomInstance.instanceID] = nomInstance;
                                NOM innerNom = discoveredNOMInstance[nomInstance.instanceID];

                                Console.WriteLine("[OnNOMMessageReceived()] C# discover {" + innerNom.name + "}.");

                                if (!instanceIDByName.ContainsKey(innerNom.name))
                                    instanceIDByName.Add(innerNom.name, new HashSet<uint>() { innerNom.instanceID });
                                else
                                    instanceIDByName[innerNom.name].Add(innerNom.instanceID);
                            }
                            break;
                        }

                        case EMessageOperation.Remove:
                        {
                            if (discoveredNOMInstance.TryGetValue(nomInstance.instanceID, out NOM innerNom))
                            {
                                Console.WriteLine("[OnNOMMessageReceived()] C# remove {" + innerNom.name + "}.");

                                if (instanceIDByName.ContainsKey(innerNom.name))
                                    instanceIDByName[innerNom.name].Remove(innerNom.instanceID);

                                discoveredNOMInstance.Remove(nomInstance.instanceID);
                            }
                            break;
                        }
                    }
                }
                finally
                {
                    mutObj.ReleaseMutex();
                }
            }));
        }
    }
}
