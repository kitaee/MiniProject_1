# SimulatorSuite - Build & Run menu (UTF-8)
# Called from BuildAndRun_All.bat at repo root
$ErrorActionPreference = 'Stop'
[Console]::OutputEncoding = [Text.UTF8Encoding]::UTF8

$Root = if ($PSScriptRoot) { Split-Path $PSScriptRoot -Parent } else { Get-Location }
$Mark = Join-Path $Root '_build_tmp'

function Find-MSBuild {
    $vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (Test-Path $vswhere) {
        $p = & $vswhere -latest -requires Microsoft.Component.MSBuild -find 'MSBuild\**\Bin\MSBuild.exe' | Select-Object -First 1
        if ($p) { return $p }
    }
    foreach ($edition in @('Professional', 'Community', 'Enterprise')) {
        $p = "${env:ProgramFiles}\Microsoft Visual Studio\2022\$edition\MSBuild\Current\Bin\MSBuild.exe"
        if (Test-Path $p) { return $p }
    }
    return $null
}

function Copy-RuntimeDlls([string]$Sim) {
    & (Join-Path $Root 'tools\Copy-NFrameworkBin.ps1') -Simulator $Sim
}

function Launch-Sim([string]$Sim, [string]$Exe) {
    $bin = Join-Path $Root "$Sim\bin"
    $path = Join-Path $bin $Exe
    if (-not (Test-Path $path)) {
        Write-Host "[WARN] $Sim - $Exe 없음. 먼저 [1] 전체 빌드를 실행하세요." -ForegroundColor Yellow
        return
    }
    Start-Process cmd -ArgumentList '/k', "title $Sim Simulator && cd /d `"$bin`" && $Exe" -WorkingDirectory $bin
    Write-Host "  Started $Sim ($Exe)"
}

function Build-One([string]$Sim, [string]$Sln, [string]$Msbuild) {
    $script = @"
@echo off
call "$Msbuild" "$Root\$Sim\$Sln" /p:Configuration=Debug /p:Platform=x64 /m /v:minimal /nologo
if errorlevel 1 (echo fail>"$Mark\$Sim.result") else (echo ok>"$Mark\$Sim.result")
echo done>"$Mark\$Sim.done"
"@
    $scriptPath = Join-Path $Mark "build_$Sim.cmd"
    Set-Content -Path $scriptPath -Value $script -Encoding ASCII
    $p = Start-Process cmd -ArgumentList '/c', $scriptPath -PassThru -WindowStyle Minimized
    return $p
}

function Wait-Builds {
    $deadline = (Get-Date).AddMinutes(20)
    while ((Get-Date) -lt $deadline) {
        $pending = @('mss','ats','lcs','mfrs','tcc') | Where-Object { -not (Test-Path (Join-Path $Mark "$_.done")) }
        if (-not $pending) { return $true }
        Start-Sleep -Seconds 2
    }
    Write-Host '[ERROR] Build timeout (20 min)' -ForegroundColor Red
    return $false
}

function Test-BuildResult([string]$Sim, [string]$ExePath) {
    $resultFile = Join-Path $Mark "$Sim.result"
    $result = if (Test-Path $resultFile) { Get-Content $resultFile -Raw } else { 'fail' }
    if ($result.Trim() -eq 'ok') {
        Write-Host "  [OK]   $Sim"
        return $true
    }
    if (Test-Path $ExePath) {
        Write-Host "  [OK]   $Sim (exe present, marker=$result)"
        return $true
    }
    Write-Host "  [FAIL] $Sim (marker=$result, missing $ExePath)" -ForegroundColor Red
    return $false
}

function Do-BuildAll([string]$Msbuild) {
    Write-Host ''
    Write-Host '========================================'
    Write-Host ' [1] 전체 빌드 (Debug|x64)'
    Write-Host '========================================'
    if (Test-Path $Mark) { Remove-Item $Mark -Recurse -Force }
    New-Item -ItemType Directory -Path $Mark | Out-Null

    $slns = @{ mss='MSS.sln'; ats='ATS.sln'; lcs='LCS.sln'; mfrs='MFRS.sln'; tcc='TCC.sln' }
    foreach ($kv in $slns.GetEnumerator()) { Build-One $kv.Key $kv.Value $Msbuild | Out-Null }

    if (-not (Wait-Builds)) { return $false }

    $ok = $true
    $exes = @{
        mss = Join-Path $Root 'mss\bin\MSSd.exe'
        ats = Join-Path $Root 'ats\bin\ATSd.exe'
        lcs = Join-Path $Root 'lcs\bin\LCSd.exe'
        mfrs = Join-Path $Root 'mfrs\bin\MFRSd.exe'
        tcc = Join-Path $Root 'tcc\bin\TCC_GUI.exe'
    }
    foreach ($kv in $exes.GetEnumerator()) {
        if (-not (Test-BuildResult $kv.Key $kv.Value)) { $ok = $false }
    }
    if (-not $ok) {
        Write-Host ''
        Write-Host "빌드 실패. 로그: $Mark\build_*.cmd 실행 결과 확인" -ForegroundColor Red
        return $false
    }

    Write-Host ''
    Write-Host 'DLL 복사 중...'
    foreach ($s in @('mss','ats','lcs','mfrs','tcc')) { Copy-RuntimeDlls $s }
    Write-Host '전체 빌드 완료.'
    Remove-Item $Mark -Recurse -Force -ErrorAction SilentlyContinue
    return $true
}

function Do-RunOne([string]$Sim, [string]$Exe) {
    Write-Host ''
    Write-Host "========================================"
    Write-Host " [$Sim] 실행 준비"
    Write-Host '========================================'
    Copy-RuntimeDlls $Sim
    Launch-Sim $Sim $Exe
}

function Do-RunAll {
    Write-Host ''
    Write-Host '========================================'
    Write-Host ' [7] 전체 실행'
    Write-Host '========================================'
    foreach ($s in @('mss','ats','lcs','mfrs','tcc')) { Copy-RuntimeDlls $s }
    Launch-Sim 'mss' 'MSSd.exe'
    Launch-Sim 'ats' 'ATSd.exe'
    Launch-Sim 'lcs' 'LCSd.exe'
    Launch-Sim 'mfrs' 'MFRSd.exe'
    Launch-Sim 'tcc' 'TCC_GUI.exe'
    Write-Host ''
    Write-Host '5개 모의기 창을 띄웠습니다. 각 창을 닫으면 해당 모의기가 종료됩니다.'
}

$msbuild = Find-MSBuild
if (-not $msbuild) {
    Write-Host '[ERROR] MSBuild not found. Install Visual Studio 2022 with C++ workload.' -ForegroundColor Red
    Read-Host 'Press Enter'
    exit 1
}

if (-not (Test-Path (Join-Path $Root 'frameworks\nFramework_sdk\include'))) {
    Write-Host '[WARN] nFramework SDK junction missing.'
    Write-Host '       mklink /J frameworks\nFramework_sdk c:\LIG\nFrameworkv1.8.2'
    Write-Host ''
}

do {
    Clear-Host
    Write-Host '========================================'
    Write-Host ' SimulatorSuite - Build & Run'
    Write-Host '========================================'
    Write-Host " MSBuild: $msbuild"
    Write-Host ''
    Write-Host '  1. 전체 빌드        (Debug|x64, 5개 병렬)'
    Write-Host '  2. MSS 실행         (MSSd.exe)'
    Write-Host '  3. ATS 실행         (ATSd.exe)'
    Write-Host '  4. LCS 실행         (LCSd.exe)'
    Write-Host '  5. MFRS 실행        (MFRSd.exe)'
    Write-Host '  6. TCC 실행         (TCC_GUI.exe)'
    Write-Host '  7. 전체 실행        (5개 동시)'
    Write-Host '  0. 종료'
    Write-Host ''
    $choice = Read-Host '선택 (0-7)'

    switch ($choice) {
        '0' { break }
        '1' { [void](Do-BuildAll $msbuild) }
        '2' { Do-RunOne 'mss' 'MSSd.exe' }
        '3' { Do-RunOne 'ats' 'ATSd.exe' }
        '4' { Do-RunOne 'lcs' 'LCSd.exe' }
        '5' { Do-RunOne 'mfrs' 'MFRSd.exe' }
        '6' { Do-RunOne 'tcc' 'TCC_GUI.exe' }
        '7' { Do-RunAll }
        default {
            Write-Host ''
            Write-Host '[ERROR] 잘못된 입력입니다. 0~7 중에서 선택하세요.' -ForegroundColor Red
            Start-Sleep -Seconds 2
            continue
        }
    }

    if ($choice -ne '0') {
        Write-Host ''
        Read-Host 'Press Enter to continue'
    }
} while ($choice -ne '0')
