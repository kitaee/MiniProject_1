# src/ 레이아웃: Main, Managers, Communication + 솔루션 폴더
$ErrorActionPreference = 'Stop'
$Root = 'C:\Users\User\Desktop\SimulatorSuite'
$Utf8 = New-Object System.Text.UTF8Encoding $false

function Write-Utf8([string]$Path, [string]$Text) {
    $dir = Split-Path -Parent $Path
    if ($dir -and -not (Test-Path $dir)) { New-Item -ItemType Directory -Path $dir -Force | Out-Null }
    [System.IO.File]::WriteAllText($Path, $Text.Replace("`r`n", "`n"), $Utf8)
}

$FolderMain = '{B1A1E001-7C4A-4E2B-9F10-000000000001}'
$FolderManagers = '{B1A1E002-7C4A-4E2B-9F10-000000000002}'
$FolderCommunication = '{B1A1E003-7C4A-4E2B-9F10-000000000003}'

$SimConfig = @{
    tcc  = @{ HasMain = $false; HasGui = $true; Managers = @('UIManager','ControlManager','ScenarioManager','StatusManager') }
    ats  = @{ HasMain = $true;  HasGui = $false; Managers = @('SimulationManager','ATSModelManager') }
    lcs  = @{ HasMain = $true;  HasGui = $false; Managers = @('SimulationManager','LaunchManager','LCSModelManager') }
    mfrs = @{ HasMain = $true;  HasGui = $false; Managers = @('SimulationManager','DetectManager','DataLinkManager','MFRSModelManager') }
    mss  = @{ HasMain = $true;  HasGui = $false; Managers = @('SimulationManager','LaunchManager','DataLinkManager','MSSModelManager','DetonationManager') }
}

function Get-ProjGuid([string]$VcxprojPath) {
    if (-not (Test-Path $VcxprojPath)) { return $null }
    $xml = [xml](Get-Content -LiteralPath $VcxprojPath -Raw -Encoding UTF8)
    $ns = $xml.Project.PropertyGroup | Where-Object { $_.ProjectGuid }
    return $ns.ProjectGuid
}

function Move-IfExists([string]$From, [string]$To) {
    if (-not (Test-Path -LiteralPath $From)) { return }
    if (Test-Path -LiteralPath $To) { Remove-Item -LiteralPath $To -Recurse -Force }
    $parent = Split-Path -Parent $To
    if (-not (Test-Path $parent)) { New-Item -ItemType Directory -Path $parent -Force | Out-Null }
    Move-Item -LiteralPath $From -Destination $To
}

function Fix-VcxprojPaths([string]$Path, [switch]$IsUdp, [switch]$IsMain) {
    if (-not (Test-Path $Path)) { return }
    $c = [IO.File]::ReadAllText($Path, $Utf8)
    if ($IsUdp) {
        $c = $c.Replace('..\..\..\shared\', '..\..\..\..\shared\')
        $c = $c.Replace('..\..\bin\', '..\..\..\bin\')
    } elseif ($IsMain) {
        $c = $c.Replace('..\..\bin\', '..\..\..\bin\')
    } else {
        $c = $c.Replace('..\..\bin\', '..\..\..\bin\')
    }
    [IO.File]::WriteAllText($Path, $c, $Utf8)
}

function New-SimSln([string]$SimKey, [hashtable]$Cfg, [string]$SimUpper) {
    $simDir = Join-Path $Root $SimKey
    $projects = [System.Collections.Generic.List[hashtable]]::new()

    if ($Cfg.HasGui) {
        $guiPath = Join-Path $simDir 'src\Main\TCC_GUI\TCC_GUI.csproj'
        $projects.Add(@{ Name = 'TCC_GUI'; Path = 'src\Main\TCC_GUI\TCC_GUI.csproj'; Guid = '{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}'; Kind = 'cs'; Folder = $FolderMain })
    }
    if ($Cfg.HasMain) {
        $mainVcx = Join-Path $simDir 'src\Main\SimulatorMain\SimulatorMain.vcxproj'
        $g = Get-ProjGuid $mainVcx
        if ($g) { $projects.Add(@{ Name = 'SimulatorMain'; Path = 'src\Main\SimulatorMain\SimulatorMain.vcxproj'; Guid = $g; Kind = 'vcx'; Folder = $FolderMain }) }
    }
    foreach ($m in $Cfg.Managers) {
        $vcx = Join-Path $simDir "src\Managers\$m\$m.vcxproj"
        $g = Get-ProjGuid $vcx
        if ($g) { $projects.Add(@{ Name = $m; Path = "src\Managers\$m\$m.vcxproj"; Guid = $g; Kind = 'vcx'; Folder = $FolderManagers }) }
    }
    $udpVcx = Join-Path $simDir 'src\Communication\UDPCommunicationManager\UDPCommunicationManager.vcxproj'
    $ug = Get-ProjGuid $udpVcx
    if ($ug) { $projects.Add(@{ Name = 'UDPCommunicationManager'; Path = 'src\Communication\UDPCommunicationManager\UDPCommunicationManager.vcxproj'; Guid = $ug; Kind = 'vcx'; Folder = $FolderCommunication }) }

    $sln = @"
Microsoft Visual Studio Solution File, Format Version 12.00
# Visual Studio Version 17
VisualStudioVersion = 17.0.31903.59
MinimumVisualStudioVersion = 10.0.40219.1
Project("{2150E333-8FDC-42A3-9474-1A3956D46DE8}") = "Main", "Main", "$FolderMain"
EndProject
Project("{2150E333-8FDC-42A3-9474-1A3956D46DE8}") = "Managers", "Managers", "$FolderManagers"
EndProject
Project("{2150E333-8FDC-42A3-9474-1A3956D46DE8}") = "Communication", "Communication", "$FolderCommunication"
EndProject
"@
    foreach ($p in $projects) {
        $type = if ($p.Kind -eq 'cs') { '{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}' } else { '{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}' }
        $sln += "`r`nProject(`"$type`") = `"$($p.Name)`", `"$($p.Path)`", `"$($p.Guid)`"`r`nEndProject"
    }
    $sln += "`r`nGlobal`r`n`tGlobalSection(SolutionConfigurationPlatforms) = preSolution`r`n`t`tDebug|x64 = Debug|x64`r`n`t`tRelease|x64 = Release|x64`r`n`tEndGlobalSection`r`n`tGlobalSection(ProjectConfigurationPlatforms) = postSolution"
    foreach ($p in $projects) {
        $g = $p.Guid
        if ($p.Kind -eq 'cs') {
            $sln += "`r`n`t`t$g.Debug|x64.ActiveCfg = Debug|Any CPU`r`n`t`t$g.Debug|x64.Build.0 = Debug|Any CPU`r`n`t`t$g.Release|x64.ActiveCfg = Release|Any CPU`r`n`t`t$g.Release|x64.Build.0 = Release|Any CPU"
        } else {
            $sln += "`r`n`t`t$g.Debug|x64.ActiveCfg = Debug|x64`r`n`t`t$g.Debug|x64.Build.0 = Debug|x64`r`n`t`t$g.Release|x64.ActiveCfg = Release|x64`r`n`t`t$g.Release|x64.Build.0 = Release|x64"
        }
    }
    $sln += "`r`n`tEndGlobalSection`r`n`tGlobalSection(SolutionProperties) = preSolution`r`n`t`tHideSolutionNode = FALSE`r`n`tEndGlobalSection`r`n`tGlobalSection(NestedProjects) = preSolution"
    foreach ($p in $projects) {
        $sln += "`r`n`t`t$($p.Guid) = $($p.Folder)"
    }
    $sln += "`r`n`tEndGlobalSection`r`nEndGlobal`r`n"
    Write-Utf8 (Join-Path $simDir "$SimUpper.sln") $sln
}

foreach ($sim in $SimConfig.Keys) {
    $src = Join-Path $Root "$sim\src"
    foreach ($d in @('Main','Managers','Communication')) {
        New-Item -ItemType Directory -Path (Join-Path $src $d) -Force | Out-Null
    }

    Move-IfExists (Join-Path $src 'SimulatorMain') (Join-Path $src 'Main\SimulatorMain')
    Move-IfExists (Join-Path $src 'TCC_GUI') (Join-Path $src 'Main\TCC_GUI')

    foreach ($m in $SimConfig[$sim].Managers) {
        Move-IfExists (Join-Path $src $m) (Join-Path $src "Managers\$m")
    }
    Move-IfExists (Join-Path $src 'UDPCommunicationManager') (Join-Path $src 'Communication\UDPCommunicationManager')

    $mainVcx = Join-Path $src 'Main\SimulatorMain\SimulatorMain.vcxproj'
    Fix-VcxprojPaths $mainVcx -IsMain
    foreach ($m in $SimConfig[$sim].Managers) {
        Fix-VcxprojPaths (Join-Path $src "Managers\$m\$m.vcxproj")
    }
    Fix-VcxprojPaths (Join-Path $src 'Communication\UDPCommunicationManager\UDPCommunicationManager.vcxproj') -IsUdp

    New-SimSln $sim $SimConfig[$sim] ($sim.ToUpper())
    Write-Host "OK $sim"
}

Write-Host 'Done: src/Main, src/Managers, src/Communication'
