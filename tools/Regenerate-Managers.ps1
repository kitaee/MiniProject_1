# Manager ICD XML 재생성 — ICD/1팀 ICD.xlsx msgID(10진수) 기준
$ErrorActionPreference = 'Stop'
$Root = 'C:\Users\User\Desktop\SimulatorSuite'
$Utf8 = New-Object System.Text.UTF8Encoding $false

function Write-Utf8([string]$Path, [string]$Text) {
    $dir = Split-Path -Parent $Path
    if ($dir -and -not (Test-Path $dir)) { New-Item -ItemType Directory -Path $dir -Force | Out-Null }
    [System.IO.File]::WriteAllText($Path, $Text.Replace("`r`n", "`n"), $Utf8)
}

function NomField([string]$Name, [string]$DataType, [string]$Size = $null) {
    [PSCustomObject]@{ Name = $Name; DataType = $DataType; Size = $Size }
}

# Kind: interaction(비주기) | object(주기)
$WireMessages = @(
    @{ Id='1001'; Name='DeployScenarioRequest'; Kind='interaction'; Sem='통합통제기→모의기 시나리오 배포'; Fields=@(
        (NomField MessageHeader MessageHeaderStruct),
        (NomField Airthreat AirthreatStruct),
        (NomField RadarPositionLatitude float),
        (NomField RadarPositionLongitude float),
        (NomField LauncherPositionLatitude float),
        (NomField LauncherPositionLongitude float)) }
    @{ Id='1002'; Name='StartSimulationRequest'; Kind='interaction'; Sem='통합통제기→모의기 시뮬레이션 시작'; Fields=@(
        (NomField MessageHeader MessageHeaderStruct)) }
    @{ Id='1003'; Name='StopSimulationRequest'; Kind='interaction'; Sem='통합통제기→모의기 시뮬레이션 정지'; Fields=@(
        (NomField MessageHeader MessageHeaderStruct)) }
    @{ Id='1401'; Name='LaunchMissileRequest'; Kind='interaction'; Sem='통합통제기→발사대 모의기 발사 명령'; Fields=@(
        (NomField MessageHeader MessageHeaderStruct)) }
    @{ Id='1501'; Name='UplinkInfo'; Kind='object'; Sem='통합통제기→레이더 모의기 업링크(주기)'; Fields=@(
        (NomField MessageHeader MessageHeaderStruct),
        (NomField UplinkInfo UplinkInfoStruct)) }
    @{ Id='2101'; Name='ScenarioACK'; Kind='interaction'; Sem='ATS→통합통제기 시나리오 ACK'; Fields=@(
        (NomField MessageHeader MessageHeaderStruct)) }
    @{ Id='2501'; Name='ATInfo'; Kind='object'; Sem='공중위협→레이더 공중위협 객체 정보(주기)'; Fields=@(
        (NomField MessageHeader MessageHeaderStruct),
        (NomField AirthreatID uint),
        (NomField AirthreatXPos float),
        (NomField AirthreatYPos float),
        (NomField AirthreatZPos float),
        (NomField AirthreatVelocity float)) }
    @{ Id='3101'; Name='ScenarioACK'; Kind='interaction'; Sem='유도탄→통합통제기 시나리오 ACK'; Fields=@(
        (NomField MessageHeader MessageHeaderStruct)) }
    @{ Id='3201'; Name='DetonationInfo'; Kind='interaction'; Sem='유도탄→공중위협 요격 결과'; Fields=@(
        (NomField MessageHeader MessageHeaderStruct),
        (NomField MissleID uint),
        (NomField TargetID uint)) }
    @{ Id='3501'; Name='DownlinkInfo'; Kind='object'; Sem='유도탄→레이더 유도탄 좌표(주기)'; Fields=@(
        (NomField MessageHeader MessageHeaderStruct),
        (NomField DownlinkInfo DownlinkInfoStruct)) }
    @{ Id='4101'; Name='ScenarioACK'; Kind='interaction'; Sem='발사대→통합통제기 시나리오 ACK'; Fields=@(
        (NomField MessageHeader MessageHeaderStruct)) }
    @{ Id='4102'; Name='MissileQuantityInfo'; Kind='interaction'; Sem='발사대→통합통제기 유도탄 재고'; Fields=@(
        (NomField MessageHeader MessageHeaderStruct),
        (NomField MissileQuantity uint)) }
    @{ Id='4301'; Name='LaunchMissile'; Kind='interaction'; Sem='발사대→유도탄 발사 정보'; Fields=@(
        (NomField MessageHeader MessageHeaderStruct),
        (NomField AirthreatID uint),
        (NomField AirthreatXpos float),
        (NomField AirthreatYPos float),
        (NomField AirthreatZPos float),
        (NomField MissleID uint),
        (NomField LCSXpos float),
        (NomField LCSYPos float),
        (NomField LCSZPos float)) }
    @{ Id='5101'; Name='ScenarioACK'; Kind='interaction'; Sem='레이더→통합통제기 시나리오 ACK'; Fields=@(
        (NomField MessageHeader MessageHeaderStruct)) }
    @{ Id='5102'; Name='RadarDetectionInfo'; Kind='object'; Sem='레이더→통합통제기 탐지 결과(주기)'; Fields=@(
        (NomField MessageHeader MessageHeaderStruct),
        (NomField RadarDetection DetectedTargetStruct)) }
    @{ Id='5103'; Name='DownlinkInfo'; Kind='object'; Sem='레이더→통합통제기 유도탄 좌표(주기)'; Fields=@(
        (NomField MessageHeader MessageHeaderStruct),
        (NomField DownlinkInfo DownlinkInfoStruct)) }
    @{ Id='5301'; Name='UplinkInfo'; Kind='object'; Sem='레이더→유도탄 업링크(주기)'; Fields=@(
        (NomField MessageHeader MessageHeaderStruct),
        (NomField UplinkInfo UplinkInfoStruct)) }
)

$MsgById = @{}
foreach ($m in $WireMessages) { $MsgById[$m.Id] = $m }

function Format-Field($Field, [string]$Tag) {
    if ($Field.Size) {
        return "      <$Tag name=`"$($Field.Name)`" semantics=`"$($Field.Name)`" dataType=`"$($Field.DataType)`" size=`"$($Field.Size)`"/>"
    }
    return "      <$Tag name=`"$($Field.Name)`" semantics=`"$($Field.Name)`" dataType=`"$($Field.DataType)`"/>"
}

function Format-Message([hashtable]$m, [string]$Sharing, [string]$NomName) {
    $open = if ($m.Kind -eq 'object') {
        "    <NOM:object name=`"$NomName`" id=`"$($m.Id)`" semantics=`"$($m.Sem)`" sharing=`"$Sharing`" orderType=`"Receive`" alignment=`"false`">"
    } else {
        "    <NOM:interaction name=`"$NomName`" id=`"$($m.Id)`" semantics=`"$($m.Sem)`" sharing=`"$Sharing`" orderType=`"Receive`" alignment=`"false`">"
    }
    $tag = if ($m.Kind -eq 'object') { 'NOM:attribute' } else { 'NOM:parameter' }
    $parts = [System.Collections.Generic.List[string]]::new()
    $parts.Add($open)
    foreach ($f in @($m.Fields)) { $parts.Add((Format-Field $f $tag)) }
    $parts.Add($(if ($m.Kind -eq 'object') { '    </NOM:object>' } else { '    </NOM:interaction>' }))
    return ($parts -join "`n")
}

function Get-NomNameMap([string[]]$Ids) {
    $unique = @($Ids | Select-Object -Unique)
    $counts = @{}
    foreach ($id in $unique) {
        $n = $MsgById[$id].Name
        if (-not $counts.ContainsKey($n)) { $counts[$n] = 0 }
        $counts[$n]++
    }
    $map = @{}
    foreach ($id in $unique) {
        $m = $MsgById[$id]
        $map[$id] = if ($counts[$m.Name] -gt 1) { "{0}_{1}" -f $m.Name, $m.Id } else { $m.Name }
    }
    return $map
}

function Get-ManagerXml([string]$Name, [hashtable]$Spec) {
    $objs = [System.Collections.Generic.List[string]]::new()
    $ixs = [System.Collections.Generic.List[string]]::new()
    $allIds = @($Spec.pub) + @($Spec.sub) + @($Spec.both) | Select-Object -Unique
    $nameMap = Get-NomNameMap $allIds
    foreach ($id in $allIds) {
        $m = $MsgById[$id]
        $sharing = if ($Spec.pub -contains $id) { 'Publish' } elseif ($Spec.sub -contains $id) { 'Subscribe' } else { 'PublishSubscribe' }
        $fmt = Format-Message $m $sharing $nameMap[$id]
        if ($m.Kind -eq 'object') { $objs.Add($fmt) } else { $ixs.Add($fmt) }
    }
    $objBlock = if ($objs.Count) { ($objs -join "`n") + "`n" } else { '' }
    $ixBlock = if ($ixs.Count) { ($ixs -join "`n") + "`n" } else { '' }
    return @"
<?xml version="1.0" encoding="UTF-8"?>
<NOM:Nex1ObjectModel xmlns:NOM="lignex1.sw.nframework.NOM" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="lignex1.sw.nframework.NOM NOM.xsd" version="0.1" name="$Name" date="2026-06-18" author="SimulatorSuite">
  <NOM:objects>
$objBlock  </NOM:objects>
  <NOM:interactions>
$ixBlock  </NOM:interactions>
  <NOM:dataTypes>
    <NOM:basicTypes/>
    <NOM:enumerationTypes/>
    <NOM:complexTypes/>
  </NOM:dataTypes>
  <NOM:notes>
  </NOM:notes>
</NOM:Nex1ObjectModel>
"@
}

function Get-UdpXml {
    $objs = [System.Collections.Generic.List[string]]::new()
    $ixs = [System.Collections.Generic.List[string]]::new()
    $allIds = @($WireMessages | ForEach-Object { $_.Id })
    $nameMap = Get-NomNameMap $allIds
    foreach ($m in $WireMessages) {
        $fmt = Format-Message $m 'PublishSubscribe' $nameMap[$m.Id]
        if ($m.Kind -eq 'object') { $objs.Add($fmt) } else { $ixs.Add($fmt) }
    }
    $objBlock = if ($objs.Count) { ($objs -join "`n") + "`n" } else { '' }
    $ixBlock = if ($ixs.Count) { ($ixs -join "`n") + "`n" } else { '' }
    return @"
<?xml version="1.0" encoding="UTF-8"?>
<NOM:Nex1ObjectModel xmlns:NOM="lignex1.sw.nframework.NOM" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="lignex1.sw.nframework.NOM NOM.xsd" version="0.1" name="UDPCommunicationManager" date="2026-06-18" author="SimulatorSuite">
  <NOM:objects>
$objBlock  </NOM:objects>
  <NOM:interactions>
$ixBlock  </NOM:interactions>
  <NOM:dataTypes>
    <NOM:basicTypes/>
    <NOM:enumerationTypes/>
    <NOM:complexTypes/>
  </NOM:dataTypes>
  <NOM:notes>
  </NOM:notes>
</NOM:Nex1ObjectModel>
"@
}

function Get-ManagerH([string]$Name, [string]$Role) {
    return @"
#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>

using namespace nframework;
using namespace nom;

// 역할: $Role

class BASEMGRDLL_API ${Name} : public BaseManager
{
public:
    ${Name}();
    ~${Name}() override;

    std::shared_ptr<NOM> registerMsg(std::wstring) override;
    void discoverMsg(std::shared_ptr<NOM>) override;
    void updateMsg(std::shared_ptr<NOM>) override;
    void reflectMsg(std::shared_ptr<NOM>) override;
    void deleteMsg(std::shared_ptr<NOM>) override;
    void removeMsg(std::shared_ptr<NOM>) override;
    void sendMsg(std::shared_ptr<NOM>) override;
    void recvMsg(std::shared_ptr<NOM>) override;
    void setUserName(std::wstring) override;
    tstring getUserName() override;
    void setData(void*) override;
    bool start() override;
    bool stop() override;
    void setMEBComponent(IMEBComponent*) override;

private:
    IMEBComponent* meb{ nullptr };
    MECComponent* mec{ nullptr };
    tstring name;
};
"@
}

function Get-ManagerCpp([string]$Name, [string]$Role) {
    return @"
#include "$Name.h"

// 역할: $Role
// BaseManager MEC 위임만 구현. 업무 로직은 추후 reflectMsg/recvMsg/start 에 추가.

${Name}::${Name}()
{
    mec = new MECComponent;
    mec->setUser(this);
    setUserName(L"$Name");
}

${Name}::~${Name}()
{
    delete mec;
    mec = nullptr;
    meb = nullptr;
}

std::shared_ptr<NOM> ${Name}::registerMsg(std::wstring msgName) { return mec->registerMsg(msgName); }
void ${Name}::discoverMsg(std::shared_ptr<NOM> nomMsg) { mec->discoverMsg(nomMsg); }
void ${Name}::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void ${Name}::reflectMsg(std::shared_ptr<NOM>) {}
void ${Name}::deleteMsg(std::shared_ptr<NOM> nomMsg) { mec->deleteMsg(nomMsg); }
void ${Name}::removeMsg(std::shared_ptr<NOM> nomMsg) { mec->removeMsg(nomMsg); }
void ${Name}::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }
void ${Name}::recvMsg(std::shared_ptr<NOM>) {}
void ${Name}::setUserName(std::wstring userName) { name = userName; }
tstring ${Name}::getUserName() { return name; }
void ${Name}::setData(void*) {}
bool ${Name}::start() { return true; }
bool ${Name}::stop() { return true; }
void ${Name}::setMEBComponent(IMEBComponent* realMEB) { meb = realMEB; mec->setMEB(meb); }

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new ${Name}; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }
"@
}

$AckAll = @('2101','3101','4101','5101')

$ManagerMsgs = @{
    UIManager = @{
        role = 'C# WPF ↔ MEB 브릿지'
        pub = @('1001','1002','1003','1401','1501')
        sub = $AckAll + @('4102','5102','5103')
    }
    ScenarioManager = @{
        role = '시나리오 저장·배포'
        pub = @('1001')
        sub = $AckAll
    }
    ControlManager = @{
        role = '시뮬레이션 제어·발사 명령'
        pub = @('1002','1003','1401')
    }
    StatusManager = @{
        role = '모의기 상태·트랙·Ack 집계'
        sub = $AckAll + @('4102','5102','5103')
    }
    SimulationManager = @{
        role = '시뮬레이션 상태·시나리오·Ack'
        pub = @()   # sim별 ACK id는 SimManagerAck에서 지정
        sub = @('1001','1002','1003')
    }
    ATSModelManager = @{ role = 'ATS 물리/행동 모델'; pub = @('2501') }
    LaunchManager = @{
        role = '발사 제어'
        sub = @('1401')
        pub = @('4301')
    }
    LCSModelManager = @{ role = 'LCS 물리/행동 모델'; pub = @('4102') }
    DetectManager = @{ role = '레이더 탐지'; pub = @('5102') }
    DataLinkManager = @{
        role = '데이터링크'
        pub = @('5301','5103')
        sub = @('1501','2501','3501')
    }
    MFRSModelManager = @{ role = 'MFRS 물리/행동 모델'; pub = @() }
    MSSModelManager = @{ role = 'MSS 물리/행동 모델'; pub = @() }
    DetonationManager = @{ role = '요격·폭발 결과'; pub = @('3201') }
}

$SimManagerAck = @{
    ats  = '2101'
    mss  = '3101'
    lcs  = '4101'
    mfrs = '5101'
}

$SimManagers = @{
    tcc  = @('UIManager','ControlManager','ScenarioManager','StatusManager')
    ats  = @('SimulationManager','ATSModelManager')
    lcs  = @('SimulationManager','LaunchManager','LCSModelManager')
    mfrs = @('SimulationManager','DetectManager','DataLinkManager','MFRSModelManager')
    mss  = @('SimulationManager','LaunchManager','DataLinkManager','MSSModelManager','DetonationManager')
}

foreach ($sim in $SimManagers.Keys) {
    foreach ($mgr in $SimManagers[$sim]) {
        $spec = @{
            role = $ManagerMsgs[$mgr].role
            pub  = @($ManagerMsgs[$mgr].pub)
            sub  = @($ManagerMsgs[$mgr].sub)
            both = @($ManagerMsgs[$mgr].both)
        }
        if (-not $spec.pub)  { $spec.pub  = @() }
        if (-not $spec.sub)  { $spec.sub  = @() }
        if (-not $spec.both) { $spec.both = @() }

        if ($mgr -eq 'SimulationManager' -and $SimManagerAck.ContainsKey($sim)) {
            $spec.pub += $SimManagerAck[$sim]
        }
        if ($mgr -eq 'SimulationManager' -and $sim -eq 'lcs') {
            $spec.sub += '1401'
        }
        if ($mgr -eq 'SimulationManager' -and $sim -eq 'ats') {
            $spec.sub += '3201'
        }
        if ($mgr -eq 'LaunchManager' -and $sim -eq 'mss') {
            $spec.pub = @('3501')
            $spec.sub = @('4301')
        }
        if ($mgr -eq 'DataLinkManager' -and $sim -eq 'mss') {
            $spec.pub = @('3501')
            $spec.sub = @('5301')
        }

        $src = Join-Path $Root "$sim\src\Managers\$mgr"
        Write-Utf8 (Join-Path $src "$mgr.h") (Get-ManagerH $mgr $spec.role)
        Write-Utf8 (Join-Path $src "$mgr.cpp") (Get-ManagerCpp $mgr $spec.role)
        Write-Utf8 (Join-Path $Root "$sim\bin\$mgr\$mgr.xml") (Get-ManagerXml $mgr $spec)
    }
    Write-Utf8 (Join-Path $Root "$sim\bin\UDPCommunicationManager\UDPCommunicationManager.xml") (Get-UdpXml)
}

Write-Host 'Done: ICD Excel msgID (decimal) applied'
