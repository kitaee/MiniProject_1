## 👨‍👩‍👧‍👦 구성원
| 이름                 | 담당 모의기    |
| -------------------- | ------------ |
|  **이기태** 연구원 | `운용통제기`       |
|  **박수빈** 연구원 | `발사대 모의기` |
|  **김동민** 연구원 | `공중위협 모의기` |
|  **김우림** 연구원 | `운용통제기`       |
|  **김주성** 연구원 | `유도탄 모의기` |
|  **김도현** 연구원 | `레이다 모의기`       |

## 이해관계자 식별
<img width="782" height="421" alt="image" src="https://github.com/user-attachments/assets/032c1d51-57d4-4926-a170-82d58bbac53d" />

## 요구사항 도출 및 분석
### 인터페이스 및 시스템, 연관 관계의 정의
<img width="752" height="425" alt="image" src="https://github.com/user-attachments/assets/f54b2818-881e-4e8d-b56e-064cf45582f0" />
<img width="756" height="426" alt="image" src="https://github.com/user-attachments/assets/bdec4e75-e107-4368-bafc-7962cca90534" />

## Git Convention

본 프로젝트는 브랜치 관리는 **Git Flow**를 기반으로 하며, 커밋 메시지는 **Conventional Commits** 형식을 참고하여 작성한다.

---

## Branch Strategy

본 프로젝트는 Git Flow 기반으로 브랜치를 관리한다.

| Branch       | 설명                |
| ------------ | ----------------- |
| `main`       | 배포 가능한 안정 버전 관리   |
| `develop`    | 개발 통합 브랜치         |
| `feature/*`  | 기능 개발 브랜치         |
| `fix/*`      | 버그 수정 브랜치         |
| `refactor/*` | 코드 구조 개선 브랜치      |
| `chore/*`    | 설정, 문서, 기타 작업 브랜치 |

### Branch Naming

브랜치 이름은 아래 형식을 따른다.

```text
<type>/<description>
```

### Branch Naming 예시

```bash
feature/scenario-receive
fix/missile-inventory-count
refactor/launcher-status-manager
chore/update-readme
```

---

## Commit Message Convention

본 프로젝트는 커밋 메시지를 **Conventional Commits** 형식을 참고하여 아래 형식에 맞춰 작성한다.

```text
<type>: <message>
```

### Commit Type

| Type       | 설명                | 예시                           |
| ---------- | ----------------- | ---------------------------- |
| `feat`     | 새로운 기능 추가         | `feat: 발사 명령 처리 기능 추가`       |
| `fix`      | 버그 수정             | `fix: 유도탄 재고 차감 오류 수정`       |
| `refactor` | 기능 변경 없이 코드 구조 개선 | `refactor: 발사대 상태 관리 로직 분리`  |
| `chore`    | 빌드, 설정, 문서, 기타 작업 | `chore: README 커밋 메시지 규칙 추가` |

### 작성 예시

```bash
feat: 시나리오 수신 기능 추가
fix: 유효하지 않은 유도탄 ID 예외처리 오류 수정
refactor: 유도탄 관리 모듈 구조 개선
chore: Git ignore 파일 정리
```

### 작성 규칙

* 커밋 메시지는 한글로 작성한다.
* 메시지는 변경 내용을 간결하게 표현한다.
* 하나의 커밋에는 하나의 목적만 포함한다.
* 기능 추가, 버그 수정, 구조 개선, 기타 작업을 구분하여 작성한다.
* 커밋 타입은 `feat`, `fix`, `refactor`, `chore` 중 하나를 사용한다.

---

# SimulatorSuite

> 개발 온보딩 가이드 단독 사본: [`Guide/README.md`](Guide/README.md)

TCC / ATS / LCS / MFRS / MSS 통합 모의기 시스템 뼈대 프로젝트입니다.

상세한 nFramework 개발 절차·API·체크리스트는 [`docs/nFramework_Developer_Guide.md`](docs/nFramework_Developer_Guide.md)를 참고하세요.

---

## 처음 받은 후 (Clone / Pull)

저장소를 clone하거나 pull한 뒤, 아래 순서대로 환경을 맞추면 각 모의기 솔루션을 빌드·실행할 수 있습니다.

### 빠른 체크리스트 (팀원용)

| # | 작업 | 확인 방법 |
|---|------|-----------|
| 1 | nFramework SDK junction | `frameworks\nFramework_sdk\include` 폴더가 보임 |
| 2 | 솔루션 빌드 **Debug \| x64** | `<sim>\bin\` 아래 `*d.exe`, Manager `*d.dll` 생성 |
| 3 | 런타임 DLL 복사 | `Copy-NFrameworkBin.ps1` 실행 후 `bin\nFConnectd.dll` 존재 |
| 4 | 실행 | `bin\`에서 exe 실행 또는 VS에서 **SimulatorMain** F5 |
| 5 | 성공 메시지 | headless: `MSS ready. Press Enter to exit...` 등 콘솔 출력 |

> **pull만 한 경우:** 3번(DLL 복사)은 `bin\`을 지우지 않았다면 생략 가능. **clone 직후** 또는 `bin\` 정리 후에는 2→3→4 순서 필수.

### 1. 사전 요구 사항

| 항목 | 용도 |
|------|------|
| **Visual Studio 2022** | C++ Manager DLL, headless 실행기 빌드 |
| **v143 toolset** (MSVC 14.3) | 모든 `.vcxproj`가 vc143 기준 |
| **MFC** (VS 설치 구성 요소) | nFramework C++ Manager 빌드 |
| **.NET 8 SDK** | TCC WPF (`tcc/src/Main/TCC_GUI`) 전용 |

> ATS / LCS / MFRS / MSS는 C++만으로 빌드됩니다. TCC만 C# WPF 프로젝트가 포함됩니다.

### 2. nFramework SDK junction (1회 설정)

SDK는 Git에 포함되지 않습니다. 로컬 nFramework 설치 경로를 junction으로 연결합니다.

```bat
cd <SimulatorSuite 루트>
mklink /J frameworks\nFramework_sdk c:\LIG\nFrameworkv1.8.2
```

SDK가 다른 경로에 있으면 오른쪽 경로만 본인 환경에 맞게 바꿉니다. 연결 후 `frameworks\nFramework_sdk\include`, `lib`, `bin`이 보이면 성공입니다. 자세한 설명은 [`frameworks/nFramework/README.md`](frameworks/nFramework/README.md)를 참고하세요.

### 3. (선택) vcxproj 재생성

`.sln` / `.vcxproj`가 없거나 스크립트를 수정한 경우:

```powershell
powershell -ExecutionPolicy Bypass -File tools\Setup-BuildProjects.ps1
```

이 스크립트는 junction 생성, 공유 UDP 소스 복사, 모의기별 빌드 프로젝트 생성을 함께 수행할 수 있습니다.

### 4. 빌드

**TCC만** NuGet 복원이 필요합니다 (최초 1회):

```powershell
dotnet restore tcc\src\Main\TCC_GUI\TCC_GUI.csproj
```

1. Visual Studio 2022에서 담당 모의기 솔루션을 엽니다. (예: `ats/ATS.sln`)
2. 구성을 **Debug \| x64**로 선택합니다.
3. 솔루션 빌드(F7)를 실행합니다.

| 모의기 | 솔루션 |
|--------|--------|
| TCC | `tcc/TCC.sln` |
| ATS | `ats/ATS.sln` |
| LCS | `lcs/LCS.sln` |
| MFRS | `mfrs/MFRS.sln` |
| MSS | `mss/MSS.sln` |

### 5. 실행 전 — nFramework 런타임 DLL 복사

Manager DLL과 실행기만 빌드해도, nFramework 런타임 DLL(`nFConnectd.dll`, `nLoggerd.dll` 등)은 SDK `bin`에서 `bin/`으로 복사해야 합니다.

**권장 (스크립트):**

```powershell
powershell -ExecutionPolicy Bypass -File tools\Copy-NFrameworkBin.ps1 -Simulator ats
```

`-Simulator` 값: `tcc`, `ats`, `lcs`, `mfrs`, `mss`

**수동 복사:**

```
frameworks\nFramework_sdk\bin\*.dll  →  <sim>\bin\
```

Debug 빌드에서는 Manager DLL·실행 파일 이름에 `d` 접미사가 붙습니다 (`ATSd.exe`, `SimulationManagerd.dll`).

### 6. 실행

실행 파일의 **작업 디렉터리는 반드시 `<sim>/bin/`** 입니다. INI·XML의 상대 경로가 모두 `bin/` 기준입니다.

| 유형 | 실행 파일 | 비고 |
|------|-----------|------|
| **Headless** (ATS, LCS, MFRS, MSS) | `<sim>/bin/<SIM>d.exe` | 예: `ats/bin/ATSd.exe` |
| **전체** | `BuildAndRun_All.bat` | 메뉴: [1] 전체 빌드, [2~6] 개별 실행, [7] 전체 실행 |
| **TCC (GUI)** | `tcc/bin/TCC_GUI.exe` | `nFConnect.ini`, `TCC.ini`가 같은 `bin/`에 있어야 함 |

**탐색기 / 배치 파일 (권장):**

```text
BuildAndRun_All.bat        # 루트: 메뉴에서 빌드/개별·전체 실행 선택
```

**Visual Studio 로컬 디버거 (F5):**

1. 시작 프로젝트 = **`SimulatorMain`** (Manager DLL이 아님)
2. 구성 = **Debug \| x64**
3. `SimulatorMain` 우클릭 → **다시 빌드**
4. 프로젝트 속성 → **디버깅** 확인:
   - **명령:** `$(SolutionDir)bin\<SIM>d.exe` (예: `MSSd.exe`)
   - **작업 디렉터리:** `$(SolutionDir)bin\`
5. F5 실행 → 콘솔에 `ready. Press Enter...` 표시되면 정상

> Manager DLL(`SimulationManager` 등)은 exe가 아니라 **단독 F5 불가**. DLL 디버깅 시에도 시작 프로젝트는 `SimulatorMain`으로 두고, DLL 프로젝트에 브레이크포인트를 걸면 로드 시 멈춥니다.

**자주 나는 오류:**

| 증상 | 원인 | 조치 |
|------|------|------|
| `nFConnectd.dll` 없음 | 런타임 DLL 미복사 | `Copy-NFrameworkBin.ps1 -Simulator <sim>` |
| `MessageHeaderStruct` undefined | SchemaRegistry 경로 | 최신 `SimulatorMain.cpp` pull 후 재빌드 |
| `mfc140ud.dll` / `MECd.dll` 0xC0000005 | 예전 exe, 잘못된 cwd, NOM 파싱 실패 | SimulatorMain 재빌드, `bin\`에서 실행 |
| VS에서만 예외 팝업 | nFramework C++ 예외 first-chance | **계속(Continue)** 또는 예외 설정에서 첫째 기회 중단 해제 |

TCC는 WPF가 `nFConnect.dll`로 MEB에 연결됩니다. C# 쪽 메시지 헬퍼는 IntelliVal로 생성한 뒤 `TCC_GUI` 프로젝트에 포함합니다.

---

## UDP / CommLinkInfo.ini (모의기별)

모의기 **간** 연동( wire )은 각 솔루션의 `UDPCommunicationManager`가 담당합니다. 설정 파일은 모두 아래 경로에 있습니다.

```text
<sim>/bin/UDPCommunicationManager/CommLinkInfo.ini
```

템플릿 원본: `shared/UDPCommunicationManager/CommLinkInfo.ini` (스크립트/수동으로 각 `bin/`에 동기화)

### 통합 연동 기본값 (전 모의기 동일)

한 PC 또는 LAN에서 **TCC + ATS + LCS + MFRS + MSS를 동시에** 붙일 때는 **멀티캐스트 IP·포트를 전원 동일**하게 맞춥니다.

| 항목 | 기본값 | 설명 |
|------|--------|------|
| **CAST** | `MULTICAST` | 다수 모의기가 같은 그룹 수신 |
| **MULTICAST IP** | `239.255.0.1` | 통합 연동용 멀티캐스트 주소 |
| **MULTICAST PORT** | `10000` | wire UDP 포트 |
| **LOCAL IP** | `127.0.0.1` | 단일 PC 루프백 테스트 |
| **LOCAL PORT** | `10000` | 로컬 소켓 바인드 |
| **REMOTE IP** | `127.0.0.1` | (멀티캐스트 시 보조) |
| **REMOTE PORT** | `20000` | (멀티캐스트 시 보조) |
| **PROTOCOL** | `UDP` | |
| **ROLE** | `SENDRECEIVE` | 송수신 |
| **HEADER SIZE** | `8` | ICD `MessageHeaderStruct`: MessageID(uint) + MessageLength(uint) |
| **ID_POS / ID_SIZE** | `0` / `4` | 메시지 ID (uint, big-endian on wire) |
| **LEN_POS / LEN_SIZE** | `4` / `4` | 메시지 길이 (uint) |

### 모의기별 설정 파일 위치

| 모의기 | CommLinkInfo.ini | UDP Manager XML | 비고 |
|--------|------------------|-----------------|------|
| **TCC** | `tcc/bin/UDPCommunicationManager/CommLinkInfo.ini` | `.../UDPCommunicationManager.xml` | GUI + MEB, `nFConnect.ini`도 `tcc/bin/` |
| **ATS** | `ats/bin/UDPCommunicationManager/CommLinkInfo.ini` | 동일 | `ATSd.exe` |
| **LCS** | `lcs/bin/UDPCommunicationManager/CommLinkInfo.ini` | 동일 | `LCSd.exe` |
| **MFRS** | `mfrs/bin/UDPCommunicationManager/CommLinkInfo.ini` | 동일 | `MFRSd.exe` |
| **MSS** | `mss/bin/UDPCommunicationManager/CommLinkInfo.ini` | 동일 | `MSSd.exe` |

현재 저장소 기본값은 **위 표의 통합 연동 값으로 5개 모의기가 동일**합니다. 팀에서 IP/포트를 바꿀 때는 **전원 합의 후 한꺼번에** 맞추세요.

### 설정 변경 시나리오

**① 단일 PC 통합 테스트 (기본)**  
- 5개 `CommLinkInfo.ini` 모두 `MULTICAST` = `239.255.0.1:10000`, `ROLE` = `SENDRECEIVE` 유지  
- 각 모의기 `bin/`에서 exe 실행 (또는 VS에서 `SimulatorMain` F5)  
- Wireshark: `udp.port == 10000`

**② 두 모의기만 1:1 (UNICAST)**  
- [`docs/nFramework_Developer_Guide.md`](docs/nFramework_Developer_Guide.md) **7.4절** 참고  
- A측 `LOCAL` ↔ B측 `REMOTE` IP/PORT를 **교차** 설정, `CAST` = `UNICAST`, `ROLE` = `SEND` / `RECEIVE` 분리

**③ 개발 PC에서 포트 충돌**  
- 다른 프로그램이 `10000`을 쓰면 `MULTICAST PORT`와 `LOCAL PORT`를 팀 합의 값(예: `10010`)으로 **5개 ini 동시 변경**

**④ 다중 PC (LAN)**  
- `LOCAL IP`를 각 PC의 실제 NIC IP로 변경 (예: `192.168.x.x`)  
- `MULTICAST IP`는 사설 대역 허용 주소 유지 (`239.255.x.x` 또는 `224.0.0.x`, 팀 합의)  
- 방화벽에서 UDP 포트 인바운드 허용

### UDP 관련 같이 맞출 파일

| 파일 | 역할 |
|------|------|
| `CommLinkInfo.ini` | IP, PORT, ROLE, HEADER 바이트 레이아웃 |
| `UDPCommunicationManager.xml` | wire 메시지 ID·타입 (ICD 기준) |
| `common/SchemaRegistryData.xml` → `<sim>/bin/` | 공통 struct (`MessageHeaderStruct` 등) |
| `<sim>.ini` | `UDPCommunicationManager` 컴포넌트 `POWER = on` |

`MSS.ini` 등 각 모의기 INI에서 `UDPCommunicationManager`가 `POWER = on`이어야 UDP가 기동합니다.

---

## 모의기별 담당 가이드

팀별로 담당 Manager DLL과 첫 구현 과제를 정리했습니다. 각 Manager는 `src/Managers/<이름>/`에 `.h`/`.cpp` 껍데기가 있고, `bin/<이름>/`에 ICD용 `.xml` 스텁이 있습니다. headless 모의기 실행기는 `src/Main/SimulatorMain/`, TCC WPF는 `src/Main/TCC_GUI/`, UDP 게이트웨이는 `src/Communication/UDPCommunicationManager/`에 있습니다.

| 모의기 | 솔루션 | 실행 파일 | 담당 Manager | 첫 작업 |
|--------|--------|-----------|--------------|---------|
| **TCC** | `tcc/TCC.sln` | `TCC_GUI.exe` | UIManager, ControlManager, ScenarioManager, StatusManager, UDPCommunicationManager | ICD→XML, WPF + NOMHandler |
| **ATS** | `ats/ATS.sln` | `ATSd.exe` | SimulationManager, ATSModelManager, UDPCommunicationManager | ICD→XML, `reflectMsg` / `recvMsg` |
| **LCS** | `lcs/LCS.sln` | `LCSd.exe` | SimulationManager, LaunchManager, LCSModelManager | 동일 패턴 |
| **MFRS** | `mfrs/MFRS.sln` | `MFRSd.exe` | SimulationManager, DetectManager, DataLinkManager, MFRSModelManager | 동일 패턴 |
| **MSS** | `mss/MSS.sln` | `MSSd.exe` | SimulationManager, LaunchManager, DataLinkManager, MSSModelManager, DetonationManager | 동일 패턴 |

**Headless 모의기 공통 흐름:** `SimulationManager`가 시뮬레이션 루프·상태를 담당하고, 역할별 Manager(기동·탐지·모델 등)가 `reflectMsg` / `recvMsg`로 MEB 메시지를 주고받습니다. 모의기 간 연동은 `UDPCommunicationManager`가 담당합니다.

**TCC:** C# WPF가 UI이고, `UIManager`가 C#↔MEB 브릿지입니다. `ControlManager` XML·sharing 설정과 `NOMHandler` 생성 코드를 맞추는 것이 첫 마일스톤입니다.

MiniProject `FooManager` 템플릿을 참고해 **BaseManager를 상속한 DLL**을 구현합니다. `FooManager`·`BarManager`는 학습용이므로 설계도의 Manager 이름으로 새로 만듭니다.

---

## 공통 작업 (전원)

모의기 팀이 나눠져도, 아래 작업은 저장소·런타임 관점에서 공통입니다.

1. **ICD → XML**
   - 공통 타입: `common/SchemaRegistryData.xml`
   - Manager별 메시지: `<sim>/bin/<Manager>/<Manager>.xml`
   - UDP wire 메시지: `<sim>/bin/UDPCommunicationManager/UDPCommunicationManager.xml`
   - 원본 ICD 엑셀은 `ICD/`에 배치·참조 (엑셀 자체는 팀 정책에 따름)

2. **IntelliVal → `*IntelliVal.h` (또는 C# 출력)**
   - Manager XML을 기준으로 메시지 직렬화 헬퍼를 생성합니다.
   - C++ Manager는 `*IntelliVal.h`, TCC는 `--outext=cs` 등으로 C# 헬퍼를 생성합니다.
   - 명령 예시는 개발 가이드 8장을 참고하세요.

3. **UDP — `CommLinkInfo.ini`**
   - 경로: `<sim>/bin/UDPCommunicationManager/CommLinkInfo.ini`
   - **통합 연동:** 전 모의기 `MULTICAST` `239.255.0.1:10000` (기본값, [UDP 절](#udp--commlinkinfoini-모의기별) 참고)
   - IP/PORT 변경 시 5개 모의기 ini를 **동시에** 맞출 것

4. **내부 통신 — MEB**
   - 같은 프로세스 안 Manager 간 메시지는 Manager XML의 **sharing** 정의로 라우팅됩니다.
   - 송신 측 XML에 메시지가 있고, 수신 측 XML에도 동일 name/id/구조가 있어야 합니다.

5. **외부 통신 — UDPCommunicationManager**
   - 소스는 `shared/UDPCommunicationManager/` 한 벌을 각 모의기 프로젝트에서 참조합니다.
   - wire 포맷은 UDP Manager XML + `SchemaRegistryData.xml`과 일치해야 합니다.

---

## 폴더별 역할

```
SimulatorSuite/
├── Guide/          # 개발 온보딩 가이드 (루트 README.md 하단과 동일)
├── docs/           # nFramework 개발 가이드 (본 README보다 상세)
├── design/         # 모의기별 모듈·시퀀스 설계 문서
├── ICD/            # ICD 엑셀·메시지 목록 참조
├── common/         # 전 모의기 공통 SchemaRegistryData.xml, NOM.xsd
├── shared/         # 공유 C++ 소스 (UDPCommunicationManager 등)
├── frameworks/
│   ├── nFramework/       # SDK 연결 안내 (README)
│   └── nFramework_sdk/   # junction → 로컬 nFramework SDK (Git 미포함)
├── tools/          # Setup-BuildProjects.ps1, Copy-NFrameworkBin.ps1
├── tcc/            # TCC 솔루션 (WPF + Manager DLL)
├── ats/            # ATS 솔루션 (headless)
├── lcs/
├── mfrs/
└── mss/
```

각 `<sim>/` 아래는 동일 패턴입니다.

- `src/Main/` — headless `SimulatorMain` (TCC는 `TCC_GUI` WPF)
- `src/Managers/` — 역할별 Manager DLL 프로젝트
- `src/Communication/` — `UDPCommunicationManager` (공유 소스 참조)
- `bin/` — 실행 배포 루트: `*.ini`, `SchemaRegistryData.xml`, Manager별 하위 폴더
- `<SIM>.sln` — Visual Studio 솔루션 (솔루션 폴더: Main / Managers / Communication)

---

## Git 주의사항

저장소에는 **설정·스키마·소스**를 두고, **빌드 산출물·SDK**는 두지 않습니다.

| 경로·대상 | 커밋 | 비고 |
|-----------|------|------|
| `<sim>/bin/*.ini`, `*.xml` | ✅ | 런타임 설정·NOM 정의 |
| `<sim>/bin/*.dll`, `*.exe` | ❌ | 빌드·복사 산출물 (`.gitignore`) |
| `lib/` (프로젝트별 중간 산출물) | ❌ | 링크·빌드 캐시 |
| `frameworks/nFramework_sdk/` | ❌ | 로컬 junction, clone마다 재생성 |
| `src/**/Debug/`, `Release/` | ❌ | VS 중간 폴더 |

clone 직후 `bin/`에 DLL이 없는 것은 정상입니다. 빌드 후 Manager DLL을 만들고, `Copy-NFrameworkBin.ps1`로 nFramework 런타임을 채웁니다.

---

## 빌드 방법 (요약)

위 [처음 받은 후](#처음-받은-후-clone--pull) 절을 따르면 됩니다. **팀원 온보딩 한 줄 요약:**

```powershell
# 1) junction (최초 1회, 관리자 CMD)
cd <SimulatorSuite 루트>
mklink /J frameworks\nFramework_sdk c:\LIG\nFrameworkv1.8.2

# 2) 빌드 — VS에서 <sim>\<SIM>.sln → Debug|x64 → F7

# 3) 런타임 DLL (clone 직후 또는 bin 비었을 때)
powershell -ExecutionPolicy Bypass -File tools\Copy-NFrameworkBin.ps1 -Simulator mss

# 4) 실행 — <sim>\bin\<SIM>d.exe 또는 Run_<SIM>.bat
```

| 단계 | 내용 |
|------|------|
| 1 | `frameworks\nFramework_sdk` junction 확인 |
| 2 | `<sim>/<SIM>.sln` → **Debug \| x64** 빌드, 시작 프로젝트 **SimulatorMain** |
| 3 | `tools\Copy-NFrameworkBin.ps1 -Simulator <sim>` |
| 4 | 작업 디렉터리 = `<sim>/bin` 에서 실행 (또는 VS F5) |
| 5 | UDP 연동 시 [CommLinkInfo.ini](#통합-연동-기본값-전-모의기-동일) 전 모의기 값 일치 확인 |

---

## 다음 단계

1. [`docs/nFramework_Developer_Guide.md`](docs/nFramework_Developer_Guide.md) 9장 체크리스트(Phase 0~6) 순서로 진행
2. `ICD/` 엑셀을 반영해 `SchemaRegistryData.xml` 및 담당 Manager XML 작성
3. MiniProject `FooManager`·`UDPCommunicationManager` 예제를 참고해 BaseManager 상속 DLL 구현
4. MEB 내부 메시지 검증 후 `CommLinkInfo.ini`로 모의기 간 UDP 연동
