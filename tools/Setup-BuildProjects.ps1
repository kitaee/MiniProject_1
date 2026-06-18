# SimulatorSuite 빌드 프로젝트 생성 스크립트
# UTF-8
$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $PSScriptRoot
$nfwSource = "c:\LIG\nFrameworkv1.8.2"
$miniProject = "c:\LIG\nFrameworkv1.8.2\examples\MiniProject_x64_vc143"

function New-GuidBrace { return "{" + [guid]::NewGuid().ToString().ToUpper() + "}" }

function Write-Utf8($path, $content) {
    $dir = Split-Path $path -Parent
    if ($dir -and -not (Test-Path $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }
    [System.IO.File]::WriteAllText($path, $content, [System.Text.UTF8Encoding]::new($false))
}

# nFramework junction (README 폴더가 있으면 _sdk 이름 사용)
$nfwLink = Join-Path $root "frameworks\nFramework_sdk"
if (-not (Test-Path (Join-Path $nfwLink "include"))) {
    New-Item -ItemType Directory -Force -Path (Split-Path $nfwLink) | Out-Null
    cmd /c mklink /J "$nfwLink" "$nfwSource" | Out-Null
}

# shared UDPCommunicationManager (MiniProject에서 복사)
$udpSrc = Join-Path $root "shared\UDPCommunicationManager"
$udpMini = Join-Path $miniProject "src\UDPCommunicationManager"
if (-not (Test-Path (Join-Path $udpSrc "UDPCommunicationManager.cpp"))) {
    New-Item -ItemType Directory -Force -Path $udpSrc | Out-Null
    Copy-Item "$udpMini\*.cpp", "$udpMini\*.h" -Destination $udpSrc -Force
}

$simulators = @{
    ats  = @{ Ini = "ATS.ini";  Main = $true;  Managers = @(
        @{ Name = "SimulationManager"; Role = "ATS 시뮬레이션 상태 관리. 시나리오 수신·Ack 송신." }
        @{ Name = "ATSModelManager";   Role = "ATS 물리/행동 모델 (위치·속도·자세 등)." }
        @{ Name = "UDPCommunicationManager"; Role = "UDP ↔ NOM 게이트웨이."; SharedUdp = $true }
    )}
    lcs  = @{ Ini = "LCS.ini";  Main = $true;  Managers = @(
        @{ Name = "SimulationManager"; Role = "LCS 시뮬레이션 상태 관리." }
        @{ Name = "LaunchManager";     Role = "요격탄 발사 제어·발사 시퀀스." }
        @{ Name = "LCSModelManager";   Role = "LCS 물리/행동 모델." }
        @{ Name = "UDPCommunicationManager"; Role = "UDP ↔ NOM 게이트웨이."; SharedUdp = $true }
    )}
    mfrs = @{ Ini = "MFRS.ini"; Main = $true;  Managers = @(
        @{ Name = "SimulationManager"; Role = "MFRS 시뮬레이션 상태 관리." }
        @{ Name = "DetectManager";     Role = "레이더 탐지·트랙 생성 처리." }
        @{ Name = "DataLinkManager";   Role = "데이터링크 송수신·링크 상태 관리." }
        @{ Name = "MFRSModelManager"; Role = "MFRS 물리/행동 모델." }
        @{ Name = "UDPCommunicationManager"; Role = "UDP ↔ NOM 게이트웨이."; SharedUdp = $true }
    )}
    mss  = @{ Ini = "MSS.ini";  Main = $true;  Managers = @(
        @{ Name = "SimulationManager"; Role = "MSS 시뮬레이션 상태 관리." }
        @{ Name = "LaunchManager";     Role = "미사일 발사 제어." }
        @{ Name = "DataLinkManager";   Role = "데이터링크 송수신·링크 상태 관리." }
        @{ Name = "MSSModelManager";   Role = "MSS 물리/행동 모델." }
        @{ Name = "DetonationManager"; Role = "요격·폭발 결과 처리." }
        @{ Name = "UDPCommunicationManager"; Role = "UDP ↔ NOM 게이트웨이."; SharedUdp = $true }
    )}
    tcc  = @{ Ini = "TCC.ini";  Main = $false; Managers = @(
        @{ Name = "UIManager";           Role = "C# WPF ↔ MEB 브릿지." }
        @{ Name = "ControlManager";      Role = "시뮬레이션 제어·발사 명령 처리." }
        @{ Name = "ScenarioManager";     Role = "시나리오 저장·배포·Ack 추적." }
        @{ Name = "StatusManager";       Role = "모의기 상태·트랙·Ack 집계." }
        @{ Name = "UDPCommunicationManager"; Role = "UDP ↔ NOM 게이트웨이."; SharedUdp = $true }
    )}
}

function Get-ManagerHeader($name, $role) {
@"

#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>

using namespace nframework;
using namespace nom;

// 역할: $role

class BASEMGRDLL_API $name : public BaseManager
{
public:
    $name();
    ~$name() override;

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

function Get-ManagerCpp($name, $role) {
@"

#include "$name.h"

// 역할: $role
// BaseManager MEC 위임만 구현. 업무 로직은 추후 reflectMsg/recvMsg/start 에 추가.

$name::$name()
{
    mec = new MECComponent;
    mec->setUser(this);
    setUserName(L"$name");
}

$name::~$name()
{
    delete mec;
    mec = nullptr;
    meb = nullptr;
}

std::shared_ptr<NOM> $name::registerMsg(std::wstring msgName) { return mec->registerMsg(msgName); }
void $name::discoverMsg(std::shared_ptr<NOM> nomMsg) { mec->discoverMsg(nomMsg); }
void $name::updateMsg(std::shared_ptr<NOM> nomMsg) { mec->updateMsg(nomMsg); }
void $name::reflectMsg(std::shared_ptr<NOM>) {}
void $name::deleteMsg(std::shared_ptr<NOM> nomMsg) { mec->deleteMsg(nomMsg); }
void $name::removeMsg(std::shared_ptr<NOM> nomMsg) { mec->removeMsg(nomMsg); }
void $name::sendMsg(std::shared_ptr<NOM> nomMsg) { mec->sendMsg(nomMsg); }
void $name::recvMsg(std::shared_ptr<NOM>) {}
void $name::setUserName(std::wstring userName) { name = userName; }
tstring $name::getUserName() { return name; }
void $name::setData(void*) {}
bool $name::start() { return true; }
bool $name::stop() { return true; }
void $name::setMEBComponent(IMEBComponent* realMEB) { meb = realMEB; mec->setMEB(meb); }

extern "C" BASEMGRDLL_API BaseManager* createObject() { return new $name; }
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) { delete mgr; }

"@
}

function Get-ManagerVcxproj($name, $guid, $sharedUdp) {
    $compileItems = if ($sharedUdp) {
@"

    <ClCompile Include="..\..\..\..\shared\UDPCommunicationManager\CommMessageHandler.cpp" />
    <ClCompile Include="..\..\..\..\shared\UDPCommunicationManager\UDPCommunicationManager.cpp" />

"@
    } else {
        "    <ClCompile Include=`"$name.cpp`" />`r`n"
    }
    $includeItems = if ($sharedUdp) {
@"

    <ClInclude Include="..\..\..\..\shared\UDPCommunicationManager\CommMessageHandler.h" />
    <ClInclude Include="..\..\..\..\shared\UDPCommunicationManager\UDPCommunicationManager.h" />
    <ClInclude Include="..\..\..\..\shared\UDPCommunicationManager\UDPCommunicationManagerIntelliVal.h" />

"@
    } else {
        "    <ClInclude Include=`"$name.h`" />`r`n"
    }
@"
<?xml version="1.0" encoding="utf-8"?>
<Project DefaultTargets="Build" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup Label="ProjectConfigurations">
    <ProjectConfiguration Include="Debug|x64"><Configuration>Debug</Configuration><Platform>x64</Platform></ProjectConfiguration>
    <ProjectConfiguration Include="Release|x64"><Configuration>Release</Configuration><Platform>x64</Platform></ProjectConfiguration>
  </ItemGroup>
  <PropertyGroup Label="Globals">
    <VCProjectVersion>17.0</VCProjectVersion>
    <ProjectGuid>$guid</ProjectGuid>
    <RootNamespace>$name</RootNamespace>
    <WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>
  </PropertyGroup>
  <Import Project="`$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
  <PropertyGroup Condition="'`$(Configuration)|`$(Platform)'=='Debug|x64'" Label="Configuration">
    <ConfigurationType>DynamicLibrary</ConfigurationType>
    <UseDebugLibraries>true</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
    <UseOfMfc>Dynamic</UseOfMfc>
  </PropertyGroup>
  <PropertyGroup Condition="'`$(Configuration)|`$(Platform)'=='Release|x64'" Label="Configuration">
    <ConfigurationType>DynamicLibrary</ConfigurationType>
    <UseDebugLibraries>false</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
    <UseOfMfc>Dynamic</UseOfMfc>
  </PropertyGroup>
  <Import Project="`$(VCTargetsPath)\Microsoft.Cpp.props" />
  <PropertyGroup Condition="'`$(Configuration)|`$(Platform)'=='Debug|x64'">
    <OutDir>`$(SolutionDir)bin\$name\</OutDir>
    <IntDir>Debug\</IntDir>
    <TargetName>${name}d</TargetName>
  </PropertyGroup>
  <PropertyGroup Condition="'`$(Configuration)|`$(Platform)'=='Release|x64'">
    <OutDir>`$(SolutionDir)bin\$name\</OutDir>
    <IntDir>Release\</IntDir>
  </PropertyGroup>
  <ItemDefinitionGroup Condition="'`$(Configuration)|`$(Platform)'=='Debug|x64'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <PreprocessorDefinitions>_DEBUG;BASEMGRDLL_EXPORTS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <LanguageStandard>stdcpp20</LanguageStandard>
      <AdditionalIncludeDirectories>`$(NFW_DIR)include;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
      <AdditionalOptions>/utf-8 %(AdditionalOptions)</AdditionalOptions>
    </ClCompile>
    <Link>
      <AdditionalLibraryDirectories>`$(NFW_DIR)lib;`$(SolutionDir)lib;%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
      <AdditionalDependencies>Log4nFd.lib;nLineStreamd.lib;nLineLogd.lib;MECd.lib;NOMd.lib;NICEd.lib;utild.lib;%(AdditionalDependencies)</AdditionalDependencies>
      <ImportLibrary>`$(SolutionDir)lib\${name}d.lib</ImportLibrary>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'`$(Configuration)|`$(Platform)'=='Release|x64'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <PreprocessorDefinitions>BASEMGRDLL_EXPORTS;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <LanguageStandard>stdcpp20</LanguageStandard>
      <AdditionalIncludeDirectories>`$(NFW_DIR)include;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
      <AdditionalOptions>/utf-8 %(AdditionalOptions)</AdditionalOptions>
    </ClCompile>
    <Link>
      <AdditionalLibraryDirectories>`$(NFW_DIR)lib;`$(SolutionDir)lib;%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
      <AdditionalDependencies>Log4nF.lib;nLineStream.lib;nLineLog.lib;MEC.lib;NOM.lib;util.lib;MEB.lib;%(AdditionalDependencies)</AdditionalDependencies>
      <ImportLibrary>`$(SolutionDir)lib\$name.lib</ImportLibrary>
    </Link>
  </ItemDefinitionGroup>
  <ItemGroup>
$compileItems  </ItemGroup>
  <ItemGroup>
$includeItems  </ItemGroup>
  <ItemGroup>
    <Xml Include="..\..\..\bin\$name\$name.xml" />
  </ItemGroup>
  <Import Project="`$(VCTargetsPath)\Microsoft.Cpp.targets" />
</Project>
"@
}

function Get-MainCpp($iniName, $exeName) {
@"

#include <nFramework/nIntegrator/nIntegrator.h>
#include <nFramework/util/util.h>
#include <nFramework/util/IniHandler.h>
#include <filesystem>
#include <Windows.h>
#include <iostream>

using namespace std::filesystem;

static const wchar_t* kIniFile = L"$iniName";

static void setWorkingDirectoryToExeDir()
{
    wchar_t exePath[MAX_PATH]{};
    if (GetModuleFileNameW(nullptr, exePath, MAX_PATH) == 0)
        return;
    current_path(std::filesystem::path(exePath).parent_path());
}

static std::wstring resolveSchemaRegistryPath(const std::wstring& binPath,
    const std::wstring& iniPath, const std::wstring& iniXml)
{
    std::filesystem::path p = iniPath.empty()
        ? std::filesystem::path(binPath) / iniXml
        : std::filesystem::path(binPath) / iniPath / iniXml;
    return std::filesystem::absolute(p).wstring();
}

int main()
{
    setWorkingDirectoryToExeDir();

    NIntegrator* nIntegrator = &(NIntegrator::getInstance());
    const std::wstring origPath = current_path().wstring();

    IniHandler iniHandler;
    iniHandler.readIni(kIniFile);

    if (iniHandler.readString(L"nLogger", L"USE") == L"true")
        nIntegrator->activateNLogger();

    if (iniHandler.readString(L"SchemaRegistryData", L"USE") == L"true")
    {
        std::wstring srPath = iniHandler.readString(L"SchemaRegistryData", L"PATH");
        std::wstring srXml = iniHandler.readString(L"SchemaRegistryData", L"XML");
        bool checkDup = iniHandler.readString(L"SchemaRegistryData", L"CheckMsgIDDuplication") == L"true";
        std::wstring srFull = resolveSchemaRegistryPath(origPath, srPath, srXml);
        if (!nIntegrator->setSchemaRegistryData(srFull, checkDup)) {
            std::wcerr << L"SchemaRegistryData load failed: " << srFull << L"\n";
            return 1;
        }
    }

    unsigned int numOfComponents = iniHandler.readUInteger(L"Components", L"Count");

    for (unsigned int cnt = 1; cnt <= numOfComponents; cnt++)
    {
        std::wstring dllIndex = L"Component_" + std::to_wstring(cnt);
        std::wstring power = iniHandler.readString(dllIndex, L"POWER");
        std::wstring dllPath = iniHandler.readString(dllIndex, L"PATH");
        std::wstring dllName = iniHandler.readString(dllIndex, L"DLL");
        std::wstring nomName = iniHandler.readString(dllIndex, L"XML");
        dllPath = dllPath.empty() ? L"" : dllPath + L"\\";
        dllPath = origPath + L"\\" + dllPath;
#ifdef _DEBUG
        dllName += L"d.dll";
#else
        dllName += L".dll";
#endif
        if (power == L"on") {
            current_path(dllPath);
            nIntegrator->plugInComponent(dllName, nomName);
            current_path(origPath);
        }
    }

    for (unsigned int cnt = 1; cnt <= numOfComponents; cnt++)
    {
        std::wstring dllIndex = L"Component_" + std::to_wstring(cnt);
        if (iniHandler.readString(dllIndex, L"POWER") == L"on") {
            auto* mgr = nIntegrator->getUserManager(iniHandler.readString(dllIndex, L"DLL"));
            if (!mgr) {
                std::wcerr << L"Manager load failed: " << iniHandler.readString(dllIndex, L"DLL") << L"\n";
                return 1;
            }
            mgr->start();
        }
    }

    std::wcout << L"$exeName ready. Press Enter to exit...\n";
    tcin.get();

    for (unsigned int cnt = 1; cnt <= numOfComponents; cnt++)
    {
        std::wstring dllIndex = L"Component_" + std::to_wstring(cnt);
        if (iniHandler.readString(dllIndex, L"POWER") == L"on") {
            nIntegrator->getUserManager(iniHandler.readString(dllIndex, L"DLL"))->stop();
        }
    }
    for (unsigned int cnt = 1; cnt <= numOfComponents; cnt++)
    {
        std::wstring dllIndex = L"Component_" + std::to_wstring(cnt);
        if (iniHandler.readString(dllIndex, L"POWER") == L"on") {
            nIntegrator->plugOutComponent(iniHandler.readString(dllIndex, L"DLL"));
        }
    }
    return 0;
}

"@
}

function Get-MainVcxproj($exeName, $guid, $iniName) {
@"
<?xml version="1.0" encoding="utf-8"?>
<Project DefaultTargets="Build" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup Label="ProjectConfigurations">
    <ProjectConfiguration Include="Debug|x64"><Configuration>Debug</Configuration><Platform>x64</Platform></ProjectConfiguration>
    <ProjectConfiguration Include="Release|x64"><Configuration>Release</Configuration><Platform>x64</Platform></ProjectConfiguration>
  </ItemGroup>
  <PropertyGroup Label="Globals">
    <VCProjectVersion>17.0</VCProjectVersion>
    <ProjectGuid>$guid</ProjectGuid>
    <RootNamespace>$exeName</RootNamespace>
    <WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>
  </PropertyGroup>
  <Import Project="`$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
  <PropertyGroup Condition="'`$(Configuration)|`$(Platform)'=='Debug|x64'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>true</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
    <UseOfMfc>Dynamic</UseOfMfc>
  </PropertyGroup>
  <PropertyGroup Condition="'`$(Configuration)|`$(Platform)'=='Release|x64'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>false</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
    <UseOfMfc>Dynamic</UseOfMfc>
  </PropertyGroup>
  <Import Project="`$(VCTargetsPath)\Microsoft.Cpp.props" />
  <PropertyGroup Condition="'`$(Configuration)|`$(Platform)'=='Debug|x64'">
    <OutDir>`$(SolutionDir)bin\</OutDir>
    <IntDir>Debug\</IntDir>
    <TargetName>${exeName}d</TargetName>
    <LocalDebuggerWorkingDirectory>`$(SolutionDir)bin\</LocalDebuggerWorkingDirectory>
    <LocalDebuggerCommand>`$(SolutionDir)bin\`$(TargetName)`$(TargetExt)</LocalDebuggerCommand>
    <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
  </PropertyGroup>
  <PropertyGroup Condition="'`$(Configuration)|`$(Platform)'=='Release|x64'">
    <OutDir>`$(SolutionDir)bin\</OutDir>
    <IntDir>Release\</IntDir>
  </PropertyGroup>
  <ItemDefinitionGroup Condition="'`$(Configuration)|`$(Platform)'=='Debug|x64'">
    <ClCompile>
      <LanguageStandard>stdcpp20</LanguageStandard>
      <AdditionalIncludeDirectories>`$(NFW_DIR)include;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
      <AdditionalOptions>/utf-8 %(AdditionalOptions)</AdditionalOptions>
    </ClCompile>
    <Link>
      <OutputFile>`$(SolutionDir)bin\${exeName}d.exe</OutputFile>
      <AdditionalLibraryDirectories>`$(NFW_DIR)lib;%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
      <AdditionalDependencies>Log4nFd.lib;nLineStreamd.lib;nLineLogd.lib;nIntegratord.lib;NOMd.lib;utild.lib;%(AdditionalDependencies)</AdditionalDependencies>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'`$(Configuration)|`$(Platform)'=='Release|x64'">
    <ClCompile>
      <LanguageStandard>stdcpp20</LanguageStandard>
      <AdditionalIncludeDirectories>`$(NFW_DIR)include;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
      <AdditionalOptions>/utf-8 %(AdditionalOptions)</AdditionalOptions>
    </ClCompile>
    <Link>
      <OutputFile>`$(SolutionDir)bin\$exeName.exe</OutputFile>
      <AdditionalLibraryDirectories>`$(NFW_DIR)lib;%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
      <AdditionalDependencies>Log4nF.lib;nLineStream.lib;nLineLog.lib;nIntegrator.lib;NOM.lib;util.lib;%(AdditionalDependencies)</AdditionalDependencies>
    </Link>
  </ItemDefinitionGroup>
  <ItemGroup>
    <ClCompile Include="SimulatorMain.cpp" />
  </ItemGroup>
  <ItemGroup>
    <None Include="..\..\..\bin\$iniName" />
  </ItemGroup>
  <Import Project="`$(VCTargetsPath)\Microsoft.Cpp.targets" />
</Project>
"@
}

foreach ($simKey in $simulators.Keys) {
    $sim = $simulators[$simKey]
    $simUpper = $simKey.ToUpper()
    $simDir = Join-Path $root $simKey
    $projects = @()
    $guids = @{}

    New-Item -ItemType Directory -Force -Path (Join-Path $simDir "lib") | Out-Null

    foreach ($mgr in $sim.Managers) {
        $name = $mgr.Name
        $role = $mgr.Role
        $sharedUdp = [bool]$mgr.SharedUdp
        $guid = New-GuidBrace
        $guids[$name] = $guid

        if (-not $sharedUdp) {
            $srcDir = Join-Path $simDir "src\Managers\$name"
            Write-Utf8 (Join-Path $srcDir "$name.h") (Get-ManagerHeader $name $role)
            Write-Utf8 (Join-Path $srcDir "$name.cpp") (Get-ManagerCpp $name $role)
            $projRel = "src\Managers\$name\$name.vcxproj"
        } else {
            $projRel = "src\Communication\$name\$name.vcxproj"
        }

        Write-Utf8 (Join-Path $simDir $projRel) (Get-ManagerVcxproj $name $guid $sharedUdp)
        $projects += @{ Name = $name; Guid = $guid; Path = $projRel; SharedUdp = $sharedUdp }
    }

    if ($sim.Main) {
        $mainGuid = New-GuidBrace
        $mainDir = Join-Path $simDir "src\Main\SimulatorMain"
        Write-Utf8 (Join-Path $mainDir "SimulatorMain.cpp") (Get-MainCpp $sim.Ini $simUpper)
        Write-Utf8 (Join-Path $mainDir "SimulatorMain.vcxproj") (Get-MainVcxproj $simUpper $mainGuid $sim.Ini)
        $projects = @(@{ Name = "SimulatorMain"; Guid = $mainGuid; Path = "src\Main\SimulatorMain\SimulatorMain.vcxproj"; SharedUdp = $false }) + $projects
    }

    # Solution
    $slnPath = Join-Path $simDir "$simUpper.sln"
    $guiGuid = $null
    if ($simKey -eq "tcc") {
        $guiGuid = New-GuidBrace
    }
    $folderMain = '{B1A1E001-7C4A-4E2B-9F10-000000000001}'
    $folderManagers = '{B1A1E002-7C4A-4E2B-9F10-000000000002}'
    $folderComm = '{B1A1E003-7C4A-4E2B-9F10-000000000003}'
    $sln = @"
Microsoft Visual Studio Solution File, Format Version 12.00
# Visual Studio Version 17
VisualStudioVersion = 17.0.31903.59
MinimumVisualStudioVersion = 10.0.40219.1
Project("{2150E333-8FDC-42A3-9474-1A3956D46DE8}") = "Main", "Main", "$folderMain"
EndProject
Project("{2150E333-8FDC-42A3-9474-1A3956D46DE8}") = "Managers", "Managers", "$folderManagers"
EndProject
Project("{2150E333-8FDC-42A3-9474-1A3956D46DE8}") = "Communication", "Communication", "$folderComm"
EndProject
"@
    if ($guiGuid) {
        $sln += "`r`nProject(`"{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}`") = `"TCC_GUI`", `"src\Main\TCC_GUI\TCC_GUI.csproj`", `"$guiGuid`"`r`nEndProject"
    }
    foreach ($p in $projects) {
        $sln += "`r`nProject(`"{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}`") = `"$($p.Name)`", `"$($p.Path)`", `"$($p.Guid)`"`r`nEndProject"
    }
    $sln += "`r`nGlobal`r`n`tGlobalSection(SolutionConfigurationPlatforms) = preSolution`r`n`t`tDebug|x64 = Debug|x64`r`n`t`tRelease|x64 = Release|x64`r`n`tEndGlobalSection`r`n`tGlobalSection(ProjectConfigurationPlatforms) = postSolution"
    if ($guiGuid) {
        $sln += "`r`n`t`t$guiGuid.Debug|x64.ActiveCfg = Debug|Any CPU`r`n`t`t$guiGuid.Debug|x64.Build.0 = Debug|Any CPU`r`n`t`t$guiGuid.Release|x64.ActiveCfg = Release|Any CPU`r`n`t`t$guiGuid.Release|x64.Build.0 = Release|Any CPU"
    }
    foreach ($p in $projects) {
        $g = $p.Guid
        $sln += "`r`n`t`t$g.Debug|x64.ActiveCfg = Debug|x64`r`n`t`t$g.Debug|x64.Build.0 = Debug|x64`r`n`t`t$g.Release|x64.ActiveCfg = Release|x64`r`n`t`t$g.Release|x64.Build.0 = Release|x64"
    }
    $sln += "`r`n`tEndGlobalSection`r`n`tGlobalSection(SolutionProperties) = preSolution`r`n`t`tHideSolutionNode = FALSE`r`n`tEndGlobalSection`r`n`tGlobalSection(NestedProjects) = preSolution"
    if ($guiGuid) {
        $sln += "`r`n`t`t$guiGuid = $folderMain"
    }
    foreach ($p in $projects) {
        $parent = if ($p.Name -eq 'SimulatorMain') { $folderMain } elseif ($p.SharedUdp) { $folderComm } else { $folderManagers }
        $sln += "`r`n`t`t$($p.Guid) = $parent"
    }
    $sln += "`r`n`tEndGlobalSection`r`nEndGlobal`r`n"
    Write-Utf8 $slnPath $sln
}

# TCC GUI minimal
$tccGuiDir = Join-Path $root "tcc\src\Main\TCC_GUI"
Write-Utf8 (Join-Path $tccGuiDir "TCC_GUI.csproj") @'
<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <OutputType>WinExe</OutputType>
    <TargetFramework>net8.0-windows</TargetFramework>
    <Nullable>enable</Nullable>
    <ImplicitUsings>enable</ImplicitUsings>
    <UseWPF>true</UseWPF>
    <RootNamespace>TCC_GUI</RootNamespace>
    <AssemblyName>TCC_GUI</AssemblyName>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)'=='Debug'">
    <OutputPath>$(SolutionDir)bin\</OutputPath>
    <AppendTargetFrameworkToOutputPath>false</AppendTargetFrameworkToOutputPath>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)'=='Release'">
    <OutputPath>$(SolutionDir)bin\</OutputPath>
    <AppendTargetFrameworkToOutputPath>false</AppendTargetFrameworkToOutputPath>
  </PropertyGroup>
  <ItemGroup>
    <Reference Include="CS_NOM.Net8">
      <HintPath Condition="'$(Configuration)'=='Debug'">$(NFW_DIR)bin\CS_NOM.Net8\Debug\net8.0\CS_NOM.Net8.dll</HintPath>
      <HintPath Condition="'$(Configuration)'=='Release'">$(NFW_DIR)bin\CS_NOM.Net8\Release\net8.0\CS_NOM.Net8.dll</HintPath>
    </Reference>
    <Reference Include="NOMHandlerLib.Net8">
      <HintPath Condition="'$(Configuration)'=='Debug'">$(NFW_DIR)bin\NOMHandlerLib.Net8\Debug\net8.0-windows\NOMHandlerLib.Net8.dll</HintPath>
      <HintPath Condition="'$(Configuration)'=='Release'">$(NFW_DIR)bin\NOMHandlerLib.Net8\Release\net8.0-windows\NOMHandlerLib.Net8.dll</HintPath>
    </Reference>
  </ItemGroup>
  <Target Name="CopyNFConnect" AfterTargets="Build">
    <Copy SourceFiles="$(NFW_DIR)bin\nFConnectd.dll" DestinationFolder="$(SolutionDir)bin\" Condition="Exists('$(NFW_DIR)bin\nFConnectd.dll')" />
    <Copy SourceFiles="$(NFW_DIR)bin\nFConnect.dll" DestinationFolder="$(SolutionDir)bin\" Condition="Exists('$(NFW_DIR)bin\nFConnect.dll')" />
  </Target>
</Project>
'@
Write-Utf8 (Join-Path $tccGuiDir "App.xaml") @'
<Application x:Class="TCC_GUI.App"
             xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
             xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
             StartupUri="MainWindow.xaml">
</Application>
'@
Write-Utf8 (Join-Path $tccGuiDir "App.xaml.cs") @'
namespace TCC_GUI;

public partial class App : System.Windows.Application
{
}
'@
Write-Utf8 (Join-Path $tccGuiDir "MainWindow.xaml") @'
<Window x:Class="TCC_GUI.MainWindow"
        xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
        xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
        Title="TCC" Height="360" Width="640">
    <Grid>
        <TextBlock Text="TCC GUI — NOMHandler 연동 예정" HorizontalAlignment="Center" VerticalAlignment="Center" FontSize="16"/>
    </Grid>
</Window>
'@
Write-Utf8 (Join-Path $tccGuiDir "MainWindow.xaml.cs") @'
namespace TCC_GUI;

public partial class MainWindow : System.Windows.Window
{
    public MainWindow() => InitializeComponent();
}
'@

# Copy nFramework runtime DLLs helper script
Write-Utf8 (Join-Path $root "tools\Copy-NFrameworkBin.ps1") @'
param([string]$Simulator = "ats")
$root = Split-Path -Parent $PSScriptRoot
$nfw = Join-Path $root "frameworks\nFramework_sdk\bin"
$dest = Join-Path $root "$Simulator\bin"
if (-not (Test-Path $nfw)) { Write-Error "nFramework bin not found: $nfw"; exit 1 }
Copy-Item "$nfw\*.dll" $dest -Force -ErrorAction SilentlyContinue
Write-Host "Copied runtime DLLs to $dest"
'@

Write-Host "Build projects generated."
