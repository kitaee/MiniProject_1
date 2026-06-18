# nFramework 개발 가이드

> **대상 독자:** nFramework를 처음 사용하는 개발자  
> **적용 시스템:** TCC / ATS / LCS / MFRS / MSS 모의기  
> **통신 설계:** 모의기 **내부** = nFramework(MEB), 모의기 **간** = UDP  
> **참고 예제:** MiniProject_x64_vc143 (본 저장소)

---

## 목차

1. [한눈에 보는 아키텍처](#1-한눈에-보는-아키텍처)
2. [핵심 개념](#2-핵심-개념)
3. [권장 저장소·폴더 구조](#3-권장-저장소폴더-구조)
4. [모의기별 bin 폴더 구성](#4-모의기별-bin-폴더-구성)
5. [새 Manager 만들기](#5-새-manager-만들기)
6. [새 메시지(NOM) 추가하기](#6-새-메시지nom-추가하기)
7. [모의기 간 UDP 통신 설정](#7-모의기-간-udp-통신-설정)
8. [TCC C# 프론트엔드 연동](#8-tcc-c-프론트엔드-연동)
9. [개발 진행 순서 (체크리스트)](#9-개발-진행-순서-체크리스트)
10. [자주 하는 실수 & 문제 해결](#10-자주-하는-실수--문제-해결)
11. [MiniProject 예제 매핑표](#11-miniproject-예제-매핑표)

---

## 1. 한눈에 보는 아키텍처

### 1.1 시스템 전체

```
┌─────────────────────────────────────────────────────────────────────────┐
│  TCC 프로세스                                                            │
│  ┌──────────────┐    nFConnect/MEB     ┌─────────────────────────────┐  │
│  │ WPF (C#)     │◄────────────────────►│ ControlManager              │  │
│  │ NOMHandler   │                      │ ScenarioManager             │  │
│  └──────────────┘                      │ StatusManager               │  │
│                                        │ UDPCommunicationManager ────┼──┼──► UDP
└────────────────────────────────────────┴─────────────────────────────┴──┘
                                                    │
                    ═══════════ UDP (ICD) ══════════╪══════════════════════
                                                    │
┌───────────────────────────────────────────────────┼──────────────────────┐
│  ATS 프로세스                                      ▼                      │
│  SimulationManager ◄── MEB ──► ATSModelManager                           │
│                              UDPCommunicationManager ──► UDP             │
└─────────────────────────────────────────────────────────────────────────┘
        (LCS / MFRS / MSS도 동일 패턴)
```

### 1.2 한 프로세스 내부


| 계층           | 구성요소                                           | 역할                        |
| ------------ | ---------------------------------------------- | ------------------------- |
| **실행기**      | `MiniProjectMain.exe` 또는 `MiniProject_GUI.exe` | INI 읽고 Manager DLL 로드     |
| **메시지 버스**   | MEB (`NIntegrator`)                            | Manager 간 NOM 메시지 라우팅     |
| **Manager**  | `BaseManager` 상속 DLL                           | 업무 로직 + MEC 콜백 구현         |
| **MEC**      | `MECComponent`                                 | 큐·스레드, MEB와 Manager 사이 중개 |
| **외부 게이트웨이** | `UDPCommunicationManager`                      | UDP ↔ NOM 변환              |


### 1.3 통신 규칙 (팀 설계 기준)


| 범위                           | 사용 기술                       | 담당 모듈                              |
| ---------------------------- | --------------------------- | ---------------------------------- |
| **모의기 내부** Manager ↔ Manager | nFramework MEB              | SimulationManager, LaunchManager 등 |
| **모의기 간** ATS ↔ LCS ↔ MFRS … | UDP ICD                     | 각 프로세스의 `UDPCommunicationManager`  |
| **TCC UI ↔ TCC 내부 Manager**  | nFConnect + NOMHandler (C#) | WPF + UIManager/NewRoleManager     |


> **중요:** `CommunicationManager`는 설계도상 **역할 이름**입니다.  
> 구현체는 `UDPCommunicationManager` 하나면 됩니다. 별도 `CommunicationManager.dll`은 만들지 않습니다.

---

## 2. 핵심 개념

### 2.1 BaseManager — 모든 Manager의 공통 계약

프레임워크 헤더: `include/nFramework/BaseManager.h`

모든 Manager DLL은 아래 **13개 함수**를 구현해야 합니다.

#### Object (상태) 메시지


| 함수            | 방향      | 설명                           |
| ------------- | ------- | ---------------------------- |
| `registerMsg` | 송신 측 등록 | 내가 소유·발행할 object 등록          |
| `discoverMsg` | 수신 측 발견 | 다른 Manager가 등록한 object 구독 시작 |
| `updateMsg`   | 송신      | object 값 변경 → MEB 전파         |
| `reflectMsg`  | 수신      | 다른 Manager의 object 갱신 수신     |
| `deleteMsg`   | 송신 측 삭제 | 내 object 제거                  |
| `removeMsg`   | 수신 측 해제 | 구독하던 object 사라짐              |


#### Interaction (이벤트) 메시지


| 함수        | 방향  | 설명         |
| --------- | --- | ---------- |
| `sendMsg` | 송신  | 1회성 이벤트 발행 |
| `recvMsg` | 수신  | 1회성 이벤트 수신 |


#### 생명주기


| 함수                            | 설명                    |
| ----------------------------- | --------------------- |
| `setUserName` / `getUserName` | Manager 이름 (MEB 식별자)  |
| `setMEBComponent`             | MEB 연결 (프레임워크가 호출)    |
| `start` / `stop`              | 기동·종료                 |
| `setData`                     | 확장용 (예: C# 윈도우 핸들 전달) |


#### 표준 구현 패턴

```cpp
// 생성자
mec = new MECComponent;
mec->setUser(this);       // MEC → 이 Manager 콜백
setUserName(L"MyManager");

// setMEBComponent
meb = realMEB;
mec->setMEB(meb);

// 메시지 API — 대부분 mec->xxx() 위임 + 로컬 map 관리
// 업무 로직 — reflectMsg, recvMsg, start 에 작성
```

### 2.2 NOM / XML / sharing

- **NOM (Nex1 Object Model):** 메시지 스키마. XML로 정의.
- **SchemaRegistryData.xml:** 공통 타입(struct, enum) 정의. 전 모의기 공유.
- **Manager별 XML:** 해당 Manager가 다루는 메시지 + `sharing` 속성.

#### sharing 값


| sharing            | 의미      | Publisher | Subscriber |
| ------------------ | ------- | --------- | ---------- |
| `Publish`          | 송신만     | ✓         |            |
| `Subscribe`        | 수신만     |           | ✓          |
| `PublishSubscribe` | 양방향     | ✓         | ✓          |
| `Neither`          | MEB 미사용 |           |            |


MEB가 `sharing`과 XML 정의를 보고 **어느 Manager에게 deliver할지** 결정합니다.

### 2.3 Object vs Interaction


|        | Object               | Interaction              |
| ------ | -------------------- | ------------------------ |
| 예      | 항공기 위치, CFCS_Status  | CFCS_Connect, WeaponFire |
| 송신 API | `updateMsg`          | `sendMsg`                |
| 수신 콜백  | `reflectMsg`         | `recvMsg`                |
| 생명주기   | register → update 반복 | 1회 send                  |


### 2.4 IntelliVal — 타입 헬퍼 자동 생성

XML 수정 후 `IntelliVal/RunIntelliVal.bat` 실행 → `*IntelliVal.h`(C++) 또는 `*IntelliVal.cs`(C#) 생성.

```cpp
// C++ 예
#include "SimulationManagerIntelliVal.h"
using namespace nframework::intellival::CFCS_Status;
nomMsg->setValue(L"CFCSOperationalCondition", ...);
auto val = t_CFCSOperationalCondition(nomMsg->getValue(L"CFCSOperationalCondition"));
```

---

## 3. 권장 저장소·폴더 구조

팀 전체 저장소를 **모의기별 + 공통**으로 나누는 것을 권장합니다.

```
SimulatorSuite/                          # 루트 솔루션
├── docs/
│   └── nFramework_Developer_Guide.md    # 본 문서
├── common/
│   ├── SchemaRegistryData.xml           # ★ 전 모의기 공통 ICD 타입
│   └── nom/
│       └── NOM.xsd
├── frameworks/
│   └── nFramework/                      # nFramework SDK (include, lib, bin)
├── tcc/
│   ├── src/
│   │   ├── Main/
│   │   │   └── TCC_GUI/                 # C# WPF
│   │   ├── Managers/
│   │   │   ├── UIManager/               # C#↔MEB 브릿지 (C++)
│   │   │   ├── ControlManager/
│   │   │   ├── ScenarioManager/
│   │   │   └── StatusManager/
│   │   └── Communication/
│   │       └── UDPCommunicationManager/ # shared 소스 참조
│   ├── bin/                             # TCC 실행 배포 폴더
│   │   ├── TCC.ini                      # (MiniProject.ini 와 동일 역할)
│   │   ├── nFConnect.ini                # C# GUI용
│   │   ├── SchemaRegistryData.xml
│   │   ├── UIManager/
│   │   ├── ControlManager/
│   │   └── UDPCommunicationManager/
│   └── TCC.sln                          # 솔루션 폴더: Main / Managers / Communication
├── ats/
│   ├── src/
│   │   ├── Main/
│   │   │   └── SimulatorMain/           # headless 실행기
│   │   ├── Managers/
│   │   │   ├── SimulationManager/
│   │   │   └── ATSModelManager/
│   │   └── Communication/
│   │       └── UDPCommunicationManager/
│   ├── bin/
│   │   ├── ATS.ini
│   │   └── ...
│   └── ATS.sln
├── lcs/   ... (동일 패턴: Main / Managers / Communication)
├── mfrs/  ...
├── mss/   ...
└── shared/
    └── UDPCommunicationManager/         # 선택: UDP Manager 소스 1벌 공유
```

### 3.1 MiniProject / TCC 예제와의 대응


| MiniProject (교육용)                          | TCC 팀 예제                                   | 실제 모의기에서 만들 것                      |
| ------------------------------------------ | ------------------------------------------ | ---------------------------------- |
| `MiniProject.ini`                          | `bin/MiniProject.ini`, `bin/nFConnect.ini` | `TCC.ini`, `ATS.ini` …             |
| `FooManager` / `BarManager`                | (POWER=off, 학습용 잔존)                        | **사용하지 않음** — 역할별 Manager를 새로 구현   |
| `StateManager`                             | TCC 콘솔 테스트용                                | `StatusManager` 등 (BaseManager 상속) |
| `UIManager`                                | TCC WPF↔MEB 브릿지                            | TCC `UIManager` (BaseManager 상속)   |
| `UDPCommunicationManager`                  | TCC UDP 게이트웨이 (POWER=on)                   | **모든 모의기 공통** 패턴                   |
| `MiniProject_GUI` / `MiniProject_GUI.Net8` | TCC WPF (`MiniProject_GUI`)                | TCC 프론트엔드                          |
| `MiniProjectMain`                          | 동일                                         | ATS/LCS 등 headless 기동              |


> **주의:** `FooManager`·`BarManager`는 nFramework 학습용 샘플입니다.  
> 실제 TCC/ATS/LCS 개발 시 **설계도의 Manager 이름으로 BaseManager를 상속한 DLL을 새로 만듭니다.**

---

## 4. 모의기별 bin 폴더 구성

실행 파일의 **작업 디렉터리 = bin/** 입니다. 모든 상대 경로는 여기 기준입니다.

```
bin/
├── ATS.exe                    # 또는 MiniProjectMain.exe
├── ATS.ini                    # Manager 목록
├── SchemaRegistryData.xml     # 공통 타입
├── nLogger.ini                # (선택) 로그 설정
│
├── SimulationManager/
│   ├── SimulationManager.dll
│   ├── SimulationManager.xml  # ★ 이 Manager의 NOM 정의
│   ├── SimulationManager.ini  # (선택) Manager 전용 설정
│   └── NOM.xsd
│
├── ATSModelManager/
│   ├── ATSModelManager.dll
│   └── ATSModelManager.xml
│
└── UDPCommunicationManager/
    ├── UDPCommunicationManager.dll
    ├── UDPCommunicationManager.xml   # ★ UDP wire 메시지 정의
    ├── CommLinkInfo.ini              # ★ IP/PORT/ROLE
    └── NOM.xsd
```

### 4.1 INI 파일 (Manager 로드)

`MiniProject.ini` 형식을 그대로 사용합니다.

```ini
[SchemaRegistryData]
USE = true
XML = SchemaRegistryData.xml
CheckMsgIDDuplication = true

[Components]
Count = 4

[Component_1]
PATH = SimulationManager
DLL = SimulationManager
XML = SimulationManager.xml
POWER = on

[Component_2]
PATH = ATSModelManager
DLL = ATSModelManager
XML = ATSModelManager.xml
POWER = on

[Component_3]
PATH = UDPCommunicationManager
DLL = UDPCommunicationManager
XML = UDPCommunicationManager.xml
POWER = on

; CommandManager / 디버그용 — 필요 시
[Component_4]
PATH = CommandManager
DLL = CommandManager
XML = CommandManager.xml
POWER = off
```

**로드 순서:** Communication Manager는 **업무 Manager 다음**에 두는 것을 권장 (MiniProject 주석 참고).

---

## 5. 새 Manager 만들기

### 5.1 절차 요약

1. Visual Studio에서 **Dynamic-Link Library** 프로젝트 생성
2. `FooManager` 또는 `BarManager` 프로젝트를 **템플릿으로 복사**
3. 클래스명·DLL export 함수 rename
4. `bin/<ManagerName>/` 폴더 + XML + INI 등록
5. IntelliVal 실행
6. `reflectMsg` / `recvMsg` / `start`에 업무 로직 작성

### 5.2 필수 파일

```
src/Managers/SimulationManager/
├── SimulationManager.h
├── SimulationManager.cpp
├── SimulationManager.vcxproj
└── SimulationManagerIntelliVal.h   ← IntelliVal 자동 생성

bin/SimulationManager/
├── SimulationManager.xml
├── SimulationManager.ini           ← 선택
└── NOM.xsd                         ← bin/UDPCommunicationManager/NOM.xsd 복사
```

### 5.3 DLL Export (반드시 필요)

```cpp
extern "C" BASEMGRDLL_API
BaseManager* createObject()
{
    return new SimulationManager;
}

extern "C" BASEMGRDLL_API
void deleteObject(BaseManager* userManager)
{
    delete userManager;
}
```

### 5.4 업무 로직을 넣는 위치


| 콜백                 | 넣을 내용                            |
| ------------------ | -------------------------------- |
| `start()`          | INI 읽기, 타이머 시작, 초기 registerMsg   |
| `reflectMsg()`     | **다른 Manager/UDP에서 온 object** 처리 |
| `recvMsg()`        | **interaction 이벤트** 처리           |
| `updateMsg()` 호출 전 | setValue 후 mec->updateMsg (송신)   |


---

## 6. 새 메시지(NOM) 추가하기

### 6.1 작업 순서

```
① SchemaRegistryData.xml — 새 struct/enum (필요 시)
② 송신 측 Manager XML — sharing=Publish 또는 PublishSubscribe
③ 수신 측 Manager XML — 같은 name, id, 구조, sharing=Subscribe 또는 PublishSubscribe
④ UDPCommunicationManager.xml — 외부 wire 메시지 (id = ICD msgID)
⑤ IntelliVal 실행 (C++ / C# 각각)
⑥ 코드에서 registerMsg → setValue → updateMsg / sendMsg
```

### 6.2 예: CFCS_Status (ATS → LCS)

**SchemaRegistryData.xml** — `MessageHeaderStruct`, `OperationalConditionEnum8` (이미 존재)

**ATS UDPCommunicationManager.xml**

```xml
<NOM:object name="CFCS_Status" id="104" sharing="PublishSubscribe" ...>
  <NOM:attribute name="MessageHeader" dataType="MessageHeaderStruct"/>
  <NOM:attribute name="CFCSOperationalCondition" dataType="OperationalConditionEnum8"/>
  ...
</NOM:object>
```

**ATS SimulationManager.xml** — 동일 메시지 (내부에서 생성·갱신)

**LCS SimulationManager.xml** — 동일 메시지 (수신·처리)

**LCS UDPCommunicationManager.xml** — ATS와 동일 ICD 메시지 정의

### 6.3 메시지별 XML 작성 규칙


| 항목                  | 규칙                          |
| ------------------- | --------------------------- |
| `name`              | 전 Manager·전 모의기에서 **동일**    |
| `id`                | ICD msgID와 **동일**           |
| attribute/parameter | 구조 **동일**                   |
| `sharing`           | Publisher/Subscriber 역할에 맞게 |


---

## 7. 모의기 간 UDP 통신 설정

> **참고 구현:** TCC 팀 예제 (`TCC/bin`, `TCC/src`) — 멀티캐스트 UDP + Interaction ICD + C# WPF 연동

### 7.1 역할 분담 (모든 Manager는 BaseManager 상속)


| Manager 종류                         | BaseManager 구현  | UDP 관련 역할                               |
| ---------------------------------- | --------------- | --------------------------------------- |
| **UDPCommunicationManager**        | ✓ (프레임워크 제공 패턴) | UDP 패킷 ↔ NOM 변환, **외부 통신 전담**           |
| **SimulationManager** 등 업무 Manager | ✓ (팀이 구현)       | `sendMsg`/`recvMsg`/`reflectMsg`로 업무 처리 |
| **UIManager** (TCC만)               | ✓               | C# WPF ↔ MEB 브릿지                        |
| **StateManager / StatusManager**   | ✓               | 주기 상태 보고 등 내부 로직                        |


**원칙:** 업무 Manager는 UDP 소켓을 직접 다루지 않습니다. MEB를 통해 `UDPCommunicationManager`와 연결됩니다.

### 7.2 UDPCommunicationManager 핵심 콜백

```cpp
// 내부 → 외부 (Interaction 송신) — TCC에서 주로 사용
void UDPCommunicationManager::recvMsg(shared_ptr<NOM> nomMsg)
{
    commInterface->sendCommMsg(nomMsg);   // MEB가 deliver → UDP wire 송신
}

// 내부 → 외부 (Object 갱신 송신)
void UDPCommunicationManager::reflectMsg(shared_ptr<NOM> nomMsg)
{
    commInterface->updateCommMsg(nomMsg);
}

// 외부 → 내부 (UDP 수신)
void UDPCommunicationManager::processRecvMessage(unsigned char* data, int size)
{
    // msgID 추출 → deserialize
    // object  → updateMsg()
    // interaction → clone → sendMsg()  → MEB → 업무 Manager.recvMsg()
}
```


| 메시지 타입          | 내부에서 UDP로 나갈 때                                             | UDP에서 내부로 들어올 때                                                 |
| --------------- | ---------------------------------------------------------- | --------------------------------------------------------------- |
| **Interaction** | 업무 Manager `sendMsg()` → MEB → UDP `recvMsg()` → wire      | wire → `processRecvMessage` → `sendMsg()` → 업무 `recvMsg()`      |
| **Object**      | 업무 Manager `updateMsg()` → MEB → UDP `reflectMsg()` → wire | wire → `processRecvMessage` → `updateMsg()` → 업무 `reflectMsg()` |


TCC 팀 ICD는 **Interaction 위주** (`SendScenario`, `StartSimulation`, `SimulatorState` 등)입니다.

---

### 7.3 XML sharing 설계 (TCC 팀 패턴)

모의기마다 **업무 Manager XML**과 **UDPCommunicationManager XML**을 둘 다 작성합니다.  
메시지 **name·id·구조는 ICD와 동일**해야 하고, **sharing은 역할별로 다르게** 잡습니다.

#### TCC UIManager.xml (UI ↔ MEB)

```xml
<!-- TCC가 보내는 메시지: Publish -->
<NOM:interaction name="SendScenario" id="0x01" sharing="Publish" .../>
<NOM:interaction name="StartSimulation" id="0x03" sharing="Publish" .../>

<!-- TCC가 받는 메시지: Subscribe -->
<NOM:interaction name="SendScenarioAck" id="0x02" sharing="Subscribe" .../>
<NOM:interaction name="SimulatorState" id="0x0b" sharing="Subscribe" .../>
```

#### UDPCommunicationManager.xml (MEB ↔ wire)

```xml
<!-- wire 전체: PublishSubscribe (브릿지) -->
<NOM:interaction name="SendScenario" id="0x01" sharing="PublishSubscribe" .../>
<NOM:interaction name="SendScenarioAck" id="0x02" sharing="PublishSubscribe" .../>
<NOM:interaction name="SimulatorState" id="0x0b" sharing="PublishSubscribe" .../>
```

#### ATS SimulationManager.xml (예)

```xml
<!-- ATS는 시나리오 수신: Subscribe -->
<NOM:interaction name="SendScenario" id="0x01" sharing="Subscribe" .../>

<!-- ATS는 Ack 송신: Publish -->
<NOM:interaction name="SendScenarioAck" id="0x02" sharing="Publish" .../>
```


| Manager                 | 송신 메시지 sharing                  | 수신 메시지 sharing           |
| ----------------------- | ------------------------------- | ------------------------ |
| TCC UIManager           | `Publish`                       | `Subscribe`              |
| ATS SimulationManager   | `Publish` (Ack 등)               | `Subscribe` (Scenario 등) |
| UDPCommunicationManager | `PublishSubscribe` (전 wire 메시지) | 동일                       |


---

### 7.4 CommLinkInfo.ini — UNICAST vs MULTICAST

#### (A) 1:1 UNICAST (ATS ↔ LCS point-to-point)

**ATS**

```ini
[LOCAL]
IP = 192.168.1.10
PORT = 10010

[REMOTE]
IP = 192.168.1.20
PORT = 10020

[SERVICE]
PROTOCOL = UDP
ROLE = SEND
CAST = UNICAST

[HEADER]
SIZE = 4
ID_POS = 0
ID_SIZE = 2
LEN_POS = 2
LEN_SIZE = 2
```

**LCS** — LOCAL/REMOTE 교차, `ROLE = RECEIVE`

#### (B) MULTICAST (TCC 팀 예제 — 다수 모의기 동시 수신)

TCC `bin/UDPCommunicationManager/CommLinkInfo.ini`:

```ini
[LOCAL]
IP = 169.254.152.49
PORT = 10000

[REMOTE]
IP = 224.0.0.100
PORT = 10000

[MULTICAST]
IP = 224.0.0.100
PORT = 10000

[SERVICE]
PROTOCOL = UDP
ROLE = SEND
CAST = MULTICAST

[HEADER]
SIZE = 4
ID_POS = 0
ID_SIZE = 2
LEN_POS = 2
LEN_SIZE = 2
```


| CAST        | 용도                              | 설정                              |
| ----------- | ------------------------------- | ------------------------------- |
| `UNICAST`   | 두 모의기 1:1                       | LOCAL/REMOTE IP·PORT 쌍          |
| `MULTICAST` | TCC + ATS + LCS + MFRS + MSS 동시 | `[MULTICAST]` IP/PORT, 전원 같은 그룹 |
| `BROADCAST` | LAN 전체                          | `[BROADCAST]` 섹션                |


**HEADER** 값은 ICD 헤더 크기에 맞춥니다. TCC는 4바이트, MiniProject CFCS 예제는 12바이트입니다. ICD 문서와 반드시 대조하세요.

---

### 7.5 INI — UDPCommunicationManager 켜기

#### TCC GUI (`nFConnect.ini` — C# exe가 사용)

```ini
[ComponentsOnNFConnect]
Count = 1

[ComponentOnNFConnect_1]
PATH = UIManager
MANAGER = UIManager
XML = UIManager.xml

[Components]
Count = 8

[Component_1]
PATH = UIManager
DLL = UIManager
XML = UIManager.xml
POWER = on

[Component_7]
PATH = UDPCommunicationManager
DLL = UDPCommunicationManager
XML = UDPCommunicationManager.xml
POWER = on
```

#### ATS headless (`ATS.ini` — MiniProjectMain.exe)

```ini
[Components]
Count = 3

[Component_1]
PATH = SimulationManager
DLL = SimulationManager
XML = SimulationManager.xml
POWER = on

[Component_2]
PATH = ATSModelManager
DLL = ATSModelManager
XML = ATSModelManager.xml
POWER = on

[Component_3]
PATH = UDPCommunicationManager
DLL = UDPCommunicationManager
XML = UDPCommunicationManager.xml
POWER = on
```

DDS / TCP / RTI CommunicationManager는 `POWER = off`.

---

### 7.6 End-to-End 흐름

#### (1) TCC → ATS: 시나리오 전송 (Interaction)

```
[WPF] ScenarioControl → EventAggregator
  → NOMEventHandler.SendScenario()
  → nomHandler.SendNOMMessage(SendScenario)     // Header.MessageID = 0x01
  → MEB
  → UDPCommunicationManager.recvMsg()
  → commInterface->sendCommMsg()                // UDP MULTICAST 송신

[ATS] UDP 수신
  → processRecvMessage() → deserialize
  → sendMsg(clone)
  → MEB
  → SimulationManager.recvMsg(SendScenario)     // 시나리오 저장·모델 세팅
  → SimulationManager.sendMsg(SendScenarioAck)  // Ack 송신
  → … → UDP → TCC UIManager → C# Receive
```

#### (2) ATS → TCC: SimulatorState 주기 보고

```
[ATS] SimulationManager (또는 StateManager)
  → sendMsg(SimulatorState)                     // id=0x0b
  → MEB → UDPCommunicationManager.recvMsg() → UDP

[TCC] UDP → processRecvMessage → sendMsg
  → MEB → UIManager.recvMsg()
  → WM_SEND_DATA → C# OnNOMMessageReceived(Receive)
  → SimulationService.ReceiveSimulatorState()
```

#### (3) Object 갱신 (해당 ICD에 object가 있을 때)

```
SimulationManager.updateMsg(trackObject)
  → MEB → UDPCommunicationManager.reflectMsg()
  → wire → 상대 processRecvMessage → updateMsg()
  → 상대 SimulationManager.reflectMsg()
```

---

### 7.7 업무 Manager 코드 패턴 (BaseManager 상속)

#### 송신 (ATS SimulationManager)

```cpp
void SimulationManager::recvMsg(std::shared_ptr<NOM> nomMsg)
{
    if (nomMsg->getName() == L"SendScenario")
    {
        // 1. 시나리오 파싱·저장
        // 2. Ack 송신
        auto ack = meb->getNOMInstance(name, L"SendScenarioAck");
        ack->setValue(L"SimulatorID", &NUShort(atsSimulatorId));
        sendMsg(ack);
    }
}

void SimulationManager::sendPeriodicStatus()
{
    auto nom = meb->getNOMInstance(name, L"SimulatorState");
    nom->setValue(L"SimulatorID", &NUShort(atsSimulatorId));
    sendMsg(nom);
}
```

#### C# 송신 (TCC — TCC 팀 NOMEventHandler.cs)

```csharp
var nom = nomHandler.GetNMessage("SendScenario")?.createNOMInstance();
nom.setValue("Header.MessageID", new NUShort(0x01));
nom.setValue("Header.MessageLength", new NUShort(...));
nom.setValue("Scenario.OriginLat", new NDouble(scenarioSend.OriginLat));
// ...
nomHandler.SendNOMMessage(nom);
```

---

### 7.8 모의기별 UDP 체크리스트


| #   | 항목                                         | TCC            | ATS               | LCS | …       |
| --- | ------------------------------------------ | -------------- | ----------------- | --- | ------- |
| 1   | `UDPCommunicationManager` POWER=on         | ✓              | ✓                 | ✓   |         |
| 2   | `UDPCommunicationManager.xml` (전 wire 메시지) | ✓              | ✓                 | ✓   | 공통 가능   |
| 3   | 업무 Manager XML (Subscribe/Publish 역할)      | UIManager      | SimulationManager | …   | 모의기별    |
| 4   | `CommLinkInfo.ini` (MULTICAST/UNICAST)     | ✓              | ✓                 | ✓   | IP/PORT |
| 5   | `SchemaRegistryData.xml` 공통 타입             | ✓              | ✓                 | ✓   | 1벌 공유   |
| 6   | IntelliVal (C++ / C#)                      | ✓              | ✓                 | —   |         |
| 7   | `recvMsg` / `sendMsg` 업무 로직                | C# + UIManager | SimulationManager | …   |         |


---

### 7.9 object 수신 시 주의

`UDPCommunicationManager.updateMsg()`는 **registerMsg된 object 인스턴스**가 있어야 합니다.  
Interaction-only ICD(TCC 팀)는 `sendMsg`/`recvMsg` 경로만 쓰면 되어 상대적으로 단순합니다.

Object가 ICD에 포함되면:

- 송신 측: `registerMsg` → `updateMsg`
- 수신 측: `start()`에서 Publish/PublishSubscribe 메시지 자동 register 또는 수동 `registerMsg`

---

### 7.10 디버깅 순서

1. **MEB 내부만** — UDP off, 두 Manager 간 sendMsg/recvMsg 확인
2. **UDP loopback** — 같은 PC, UNICAST 127.0.0.1, 프로세스 2개
3. **MULTICAST** — TCC + ATS 동시 기동, Wireshark `udp.port == 10000`
4. 로그 — `undefined message` → XML id / CommLinkInfo HEADER 불일치
5. `oid error` → object register 누락

---

## 8. TCC C# 프론트엔드 연동

TCC는 **C# WPF + C++ BaseManager(UIManager) + UDPCommunicationManager** 혼합 구조입니다.  
**1차 참고:** TCC 팀 예제 `MiniProject_GUI` / `UIManager` / `NOMEventHandler.cs`  
**2차 참고:** 본 저장소 `MiniProject_GUI.Net8`

### 8.1 연동 아키텍처

```
┌─────────────────────────────────────────────────────────┐
│  MiniProject_GUI.exe (C# WPF)                           │
│                                                         │
│  MainViewModel                                          │
│    └── NOMHandler (NOMHandlerLib.Net8)                  │
│          ├── CreateNFConnect()  → nFConnect.dll         │
│          ├── DoPlugIn()         → nFConnect.ini 기반   │
│          ├── RegisterNOMMessage / SendNOMMessage          │
│          └── MessageReceived 이벤트                      │
│                                                         │
│  HwndSource.AddHook(WndProcCallback)  ← Win32 메시지    │
└───────────────────────────┬─────────────────────────────┘
                            │ nFConnect / MEB
┌───────────────────────────▼─────────────────────────────┐
│  UIManager.dll / NewRoleManager.dll (C++)               │
│    setData(HWND) — C# 창 핸들                           │
│    discoverMsg / reflectMsg → SendMessage(WM_*_DATA)    │
└─────────────────────────────────────────────────────────┘
```

### 8.2 필요 DLL / 패키지 (C#)


| 파일                                 | 출처             |
| ---------------------------------- | -------------- |
| `nFConnect.dll` / `nFConnectd.dll` | nFramework bin |
| `NOMHandlerLib.Net8.dll`           | nFramework bin |
| `CS_NOM.Net8.dll`                  | nFramework bin |
| `CS_Log4nF.Net8.dll`               | nFramework bin |


C# 프로젝트 출력 경로를 `**bin/**` 으로 맞춥니다 (`MiniProject_GUI.Net8.csproj` 참고).

### 8.3 nFConnect.ini (C# ↔ C++ Manager 연결)

**TCC 팀 예제** (UIManager만 plug-in, UDPCommunicationManager는 Components에서 POWER=on):

```ini
[ComponentsOnNFConnect]
Count = 1

[ComponentOnNFConnect_1]
PATH = UIManager
MANAGER = UIManager
XML = UIManager.xml

[Components]
Count = 8

[Component_1]
PATH = UIManager
DLL = UIManager
XML = UIManager.xml
POWER = on

[Component_7]
PATH = UDPCommunicationManager
DLL = UDPCommunicationManager
XML = UDPCommunicationManager.xml
POWER = on
```

확장 시 (ControlManager 등 C++ Manager 추가):

```ini
[ComponentsOnNFConnect]
Count = 2

[ComponentOnNFConnect_1]
PATH = UIManager
MANAGER = UIManager
XML = UIManager.xml

[ComponentOnNFConnect_2]
PATH = ControlManager
MANAGER = ControlManager
XML = ControlManager.xml
```

C# `NOMHandler` 생성 시 **plug-in되는 Manager XML 경로**를 반드시 포함:

```csharp
// TCC 팀 예제
new NOMHandler(new List<string> {
    Environment.CurrentDirectory + @"\UIManager\UIManager.xml"
});
```

### 8.4 C# 초기화 코드 (MiniProject_GUI.Net8 패턴)

```csharp
// 1. NOMHandler 생성 — XML 경로 목록
var nomHandler = new NOMHandler(new List<string> {
    Environment.CurrentDirectory + @"\UIManager\UIManager.xml",
    Environment.CurrentDirectory + @"\ControlManager\ControlManager.xml"
});

nomHandler.MessageReceived += OnNOMMessageReceived;

// 2. MainWindow Loaded
IntPtr hwnd = new WindowInteropHelper(this).Handle;
HwndSource.FromHwnd(hwnd)?.AddHook(nomHandler.WndProcCallback);

nomHandler.CreateNFConnect();
nomHandler.DoPlugIn();
nomHandler.SetWindowHandle(hwnd);   // C++ Manager setData(HWND) 로 전달
nomHandler.ExecStart();
```

### 8.5 C#에서 메시지 수신 처리

```csharp
private void OnNOMMessageReceived(NOM nom, EMessageOperation op)
{
    Application.Current.Dispatcher.InvokeAsync(() =>
    {
        switch (op)
        {
            case EMessageOperation.Reflect:   // object 갱신
                // UI 바인딩 갱신
                break;
            case EMessageOperation.Receive:   // interaction
                break;
            case EMessageOperation.Discover:  // object 최초 발견
                break;
            case EMessageOperation.Remove:
                break;
        }
    });
}
```

### 8.6 C#에서 메시지 송신

```csharp
// Object update
var nom = nomHandler.GetRegisteredNOMInstance(instanceId);
nom.setValue("WorldLocation.X", new v_WorldLocation_X(100.0));
nomHandler.SendNOMMessage(nom);

// Interaction send
var evt = nomHandler.GetNMessage("StartResume")?.createNOMInstance();
evt.setValue("RequestIdentifier", new NUInteger(1));
nomHandler.SendNOMMessage(evt);
```

### 8.7 C++ Manager ↔ C# Win32 메시지 (선택적·레거시)

`NewRoleManager`는 `setData(HWND)`로 C# 창 핸들을 받아 `SendMessage`로 NOM 바이트를 전달합니다.


| 메시지                      | 의미              |
| ------------------------ | --------------- |
| `WM_DISCOVERED_MSG_DATA` | object discover |
| `WM_SEND_DATA`           | reflect / recv  |
| `WM_REMOVED_MSG_DATA`    | remove          |


**권장:** 새 TCC 개발은 **NOMHandler 이벤트(`MessageReceived`)** 위주로 구현하고, Win32 `SendMessage`는 MiniProject 호환·고성능 경로가 필요할 때만 사용.

### 8.8 TCC C# IntelliVal

`RunIntelliVal.bat`에서 C# 출력 예:

```bat
IntelliVal.exe --bin=../bin --src=../src --mgr=UIManager --nom=UIManager.xml --outext=cs --csproj=TCC_GUI --schreg=y --srpath=SchemaRegistryData.xml --tdspc=y
```

→ `TCC_GUI/UIManagerIntelliVal.cs` 생성 → ViewModel에서 `nframework.intellival.*` 사용.

### 8.9 TCC INI 전체 예

```ini
; TCC.ini — C++ Manager (MiniProject.ini 형식)
[Components]
Count = 5

[Component_1]
PATH = UIManager
DLL = UIManager
XML = UIManager.xml
POWER = on

[Component_2]
PATH = ControlManager
...
POWER = on

[Component_5]
PATH = UDPCommunicationManager
...
POWER = on
```

C# GUI는 **별도 exe**이며 `nFConnect.ini`로 UIManager 등에 plug-in 합니다.  
C++ Manager만 있는 ATS/LCS 등은 `MiniProjectMain` + `ATS.ini`만 있으면 됩니다.

---

## 9. 개발 진행 순서 (체크리스트)

### Phase 0 — 환경

- [ ] nFramework SDK 경로 (`NFW_DIR`) 설정
- [ ] MiniProject 빌드·실행 확인
- [ ] IntelliVal 실행 확인

### Phase 1 — 공통 ICD

- [ ] `SchemaRegistryData.xml`에 공통 타입 정의
- [ ] 모의기 간 UDP 메시지 목록 (name, id, struct) 문서화
- [ ] msgID 중복 검사 (`CheckMsgIDDuplication = true`)

### Phase 2 — 모의기 1개 scaffold (예: ATS)

- [ ] 솔루션·폴더 구조 생성
- [ ] SimulationManager 템플릿 (FooManager 복사)
- [ ] UDPCommunicationManager (MiniProject 복사)
- [ ] ATS.ini + bin 배치
- [ ] CommLinkInfo.ini

### Phase 3 — 내부 통신

- [ ] Manager XML에 메시지 + sharing 정의
- [ ] IntelliVal → C++ 헬퍼
- [ ] registerMsg / updateMsg / reflectMsg 동작 테스트 (UDP 없이)

### Phase 4 — UDP 연동

- [ ] UDPCommunicationManager.xml에 wire 메시지
- [ ] 양쪽 모의기 CommLinkInfo
- [ ] processRecvMessage / reflectMsg 경로 테스트

### Phase 5 — TCC

- [ ] WPF + NOMHandler + nFConnect.ini
- [ ] UIManager / ControlManager XML을 C# NOMHandler 경로에 등록
- [ ] IntelliVal C# 출력
- [ ] UI ↔ ControlManager 메시지 연동

### Phase 6 — 나머지 모의기

- [ ] LCS, MFRS, MSS — ATS와 동일 패턴 복제
- [ ] 모의기별 CommLinkInfo·메시지 subset만 변경

---

## 10. 자주 하는 실수 & 문제 해결


| 증상                      | 원인                  | 해결                                     |
| ----------------------- | ------------------- | -------------------------------------- |
| Manager DLL 로드 실패       | bin 경로·이름 불일치       | INI의 PATH/DLL/XML 확인, Debug는 `*d.dll`  |
| 메시지가 다른 Manager에 안 감    | 수신 측 XML에 메시지 없음    | name/id/구조 동일하게 추가                     |
| UDP `undefined message` | msgID 테이블 없음        | UDP XML id ↔ CommLinkInfo HEADER       |
| UDP `oid error`         | object 미등록          | registerMsg / start() 자동등록 확인          |
| C# NFConnect 생성 실패      | nFConnect.dll 없음·권한 | bin에 DLL, nFConnect_ACL.ps1            |
| C# 메시지 목록 비음            | XML 경로 오류           | CurrentDirectory = bin 인지 확인           |
| deserialize 깨짐          | endian/struct 불일치   | SchemaRegistryData `ushortBE` 등 ICD 대조 |
| GUI reflect 안 옴         | sharing / plug-in   | nFConnect.ini MANAGER·XML, sharing     |


---

## 11. BaseManager 상속 Manager 분류 (실제 개발 기준)

**모든 모의기 내부 모듈은 `BaseManager`를 상속한 DLL로 구현합니다.**  
MiniProject의 `FooManager`·`BarManager`는 **프레임워크 학습용**이며, 실제 TCC/ATS/LCS 코드에 그대로 매핑하지 않습니다.

### 11.1 Manager 역할별 분류


| 역할               | 설계도 이름                                        | BaseManager | 주요 API                               | 예시 (TCC 팀)                      |
| ---------------- | --------------------------------------------- | ----------- | ------------------------------------ | ------------------------------- |
| **UI 브릿지**       | UIManager                                     | ✓           | `recvMsg`→C#, C#→`sendMsg`           | `UIManager`                     |
| **시나리오/제어**      | ScenarioManager, ControlManager               | ✓           | `recvMsg`, `sendMsg`                 | (TCC는 C# `NOMEventHandler`가 대체) |
| **상태/시뮬레이션**     | SimulationManager, StateManager               | ✓           | `recvMsg`, `sendMsg`, `start`        | `StateManager`                  |
| **기동/발사/탐지**     | ManeuverManager, LaunchManager, DetectManager | ✓           | `reflectMsg`, `recvMsg`              | (팀 구현)                          |
| **모델**           | ATSModelManager, LCSModelManager …            | ✓           | `reflectMsg`, `updateMsg`            | (팀 구현)                          |
| **외부 UDP 게이트웨이** | CommunicationManager (설계명)                    | ✓           | `recvMsg`→wire, `processRecvMessage` | `UDPCommunicationManager`       |
| **디버그/테스트**      | CommandManager                                | ✓           | CLI register/update                  | `CommandManager` (POWER=off 권장) |


### 11.2 BaseManager 구현 필수 요소 (공통)

모든 Manager DLL은 아래를 **동일 패턴**으로 포함합니다.

```
MyManager.h / .cpp
  ├── class MyManager : public BaseManager
  ├── MECComponent* mec + IMEBComponent* meb
  ├── registeredMsgMap / discoveredMsgMap
  ├── 13개 virtual 함수 override
  └── createObject() / deleteObject() export

bin/MyManager/
  ├── MyManager.dll
  ├── MyManager.xml          ← 이 Manager가 다루는 NOM + sharing
  ├── MyManager.ini          ← (선택)
  └── NOM.xsd
```

**업무 로직 위치:** `reflectMsg`, `recvMsg`, `start` — 나머지는 `mec->xxx()` 위임이 일반적.

### 11.3 모의기별 Manager 구성 (설계도 기준)


| 모의기      | BaseManager 상속 Manager                                                                                         | UDP       |
| -------- | -------------------------------------------------------------------------------------------------------------- | --------- |
| **TCC**  | UIManager, ControlManager, ScenarioManager, StatusManager, UDPCommunicationManager                             | MULTICAST |
| **ATS**  | SimulationManager, ATSModelManager, UDPCommunicationManager                                   | MULTICAST |
| **LCS**  | SimulationManager, LaunchManager, LCSModelManager, UDPCommunicationManager                                     | MULTICAST |
| **MFRS** | SimulationManager, DetectManager, DataLinkManager, MFRSModelManager, UDPCommunicationManager                   | MULTICAST |
| **MSS**  | SimulationManager, LaunchManager, DataLinkManager, MSSModelManager, DetonationManager, UDPCommunicationManager | MULTICAST |


각 프로세스 INI에 위 Manager를 `POWER = on`으로 등록합니다.

### 11.4 MiniProject 교육용 vs 실제 사용


| MiniProject 프로젝트                   | 실제 사용 여부     | 대신 할 것                      |
| ---------------------------------- | ------------ | --------------------------- |
| `FooManager`                       | ✗ 학습용        | `SimulationManager` 등 신규 구현 |
| `BarManager`                       | ✗ 학습용        | `ManeuverManager` 등 신규 구현   |
| `NewRoleManager`                   | △ UI 패턴 참고   | TCC `UIManager`             |
| `StateManager`                     | △ TCC 팀 테스트  | `StatusManager`             |
| `UDPCommunicationManager`          | ✓ **그대로 사용** | CommLinkInfo·XML만 ICD에 맞게   |
| `CommandManager`                   | △ 디버그용       | 개발 중에만 POWER=on             |
| `DDS/TCP/RTI CommunicationManager` | ✗            | POWER=off                   |


### 11.5 TCC 팀 예제 파일 매핑 (참고)


| TCC 팀 파일                                                  | 설명                                               |
| --------------------------------------------------------- | ------------------------------------------------ |
| `src/Managers/UIManager/`                                 | BaseManager — C#↔MEB, `recvMsg`에서 `WM_SEND_DATA` |
| `src/Managers/StatusManager/`                             | BaseManager — `sendSimulatorState()` 주기 송신       |
| `src/Communication/UDPCommunicationManager/`              | BaseManager — UDP 브릿지                            |
| `src/Main/TCC_GUI/`                                       | C# WPF 프론트엔드                                    |
| `bin/UIManager/UIManager.xml`                             | UI용 sharing (Publish/Subscribe)                  |
| `bin/UDPCommunicationManager/UDPCommunicationManager.xml` | wire 전체 (PublishSubscribe)                       |
| `bin/UDPCommunicationManager/CommLinkInfo.ini`            | MULTICAST 224.0.0.100:10000                      |
| `bin/nFConnect.ini`                                       | C# GUI — UIManager + UDPCommunicationManager     |
| `MiniProject_GUI/Infrastructure/NOMEventHandler.cs`       | C#에서 SendScenario 등 송신                           |
| `MiniProject_GUI/MainWindow.xaml.cs`                      | C# 수신 dispatch (SimulatorState, Ack …)           |


### 11.6 새 Manager 추가 시 복사 템플릿

1. **복사 원본:** `StateManager` (TCC) 또는 `FooManager` (최소 골격)
2. rename → `SimulationManager`
3. XML 작성 → IntelliVal
4. INI `[Component_N]` 등록
5. `reflectMsg` / `recvMsg`에 ICD 처리 코드

---

## 부록 A — Manager 간 메시지 흐름 (ATS 내부)

```
ATSModelManager                    SimulationManager
     │                                    │
     │  updateMsg("ATInfo")               │
     └──────────────► MEB ───────────────►│ reflectMsg()
                                          │  (로직 처리)
```

## 부록 B — TCC → ATS UDP (TCC 팀 Interaction ICD)

```
TCC C# NOMEventHandler.SendScenario()
  → nomHandler.SendNOMMessage(SendScenario)
  → MEB → UDPCommunicationManager.recvMsg() → UDP MULTICAST

ATS UDPCommunicationManager.processRecvMessage()
  → sendMsg(SendScenario)
  → ATS SimulationManager.recvMsg()  → 시나리오 처리
  → sendMsg(SendScenarioAck)
  → … → TCC C# OnNOMMessageReceived(Receive)
```

## 부록 C — TCC UI → ControlManager (C#)

```
WPF Button → nomHandler.SendNOMMessage(nom)
  → nFConnect → MEB → ControlManager.recvMsg() / reflectMsg()
```

---

**문서 버전:** 1.1  
**기준 예제:** MiniProject_x64_vc143 / TCC 팀 예제 / nFramework v1.8.2  
**작성 목적:** 다모의기 UDP + TCC C# 연동 개발 온보딩