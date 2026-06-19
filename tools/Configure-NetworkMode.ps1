# Configure CommLinkInfo.ini for local (5 sims on one PC) or multicast 5-PC deployment.
# UTF-8 with BOM; idempotent - safe to run repeatedly.
param(    [Parameter(Mandatory = $true)]
    [ValidateSet('Local', 'Multicast5PC')]
    [string]$Mode,

    [ValidateSet('TCC', 'ATS', 'LCS', 'MFRS', 'MSS')]
    [string]$Role,

    [string]$LocalIp
)

$ErrorActionPreference = 'Stop'
$null = cmd /c 'chcp 65001 >nul'
$utf8 = New-Object System.Text.UTF8Encoding $false
[Console]::OutputEncoding = $utf8
[Console]::InputEncoding = $utf8
$OutputEncoding = $utf8
$Root = Split-Path $PSScriptRoot -Parent
$Shared = Join-Path $Root 'shared\UDPCommunicationManager'
$MulticastIp = '239.255.0.1'
$Port = 10000

$SimMap = @{
    tcc  = @{ Template = 'CommLinkInfo.sender.ini';   Label = 'TCC sender (ROLE=SEND)' }
    ats  = @{ Template = 'CommLinkInfo.receiver.ini'; Label = 'ATS (ROLE=SEND)' }
    lcs  = @{ Template = 'CommLinkInfo.receiver.ini'; Label = 'LCS (ROLE=SEND)' }
    mfrs = @{ Template = 'CommLinkInfo.receiver.ini'; Label = 'MFRS (ROLE=SEND)' }
    mss  = @{ Template = 'CommLinkInfo.receiver.ini'; Label = 'MSS (ROLE=SEND)' }
}

function Get-FirstNonLoopbackIPv4 {
    $addrs = Get-NetIPAddress -AddressFamily IPv4 -ErrorAction SilentlyContinue |
        Where-Object {
            $_.IPAddress -ne '127.0.0.1' -and
            $_.PrefixOrigin -ne 'WellKnown' -and
            $_.IPAddress -notmatch '^169\.254\.'
        } |
        Sort-Object InterfaceMetric, SkipAsSource

    if ($addrs) { return ($addrs | Select-Object -First 1).IPAddress }

    $legacy = Get-WmiObject Win32_NetworkAdapterConfiguration -ErrorAction SilentlyContinue |
        Where-Object { $_.IPEnabled -and $_.IPAddress } |
        ForEach-Object { $_.IPAddress } |
        Where-Object { $_ -match '^\d+\.\d+\.\d+\.\d+$' -and $_ -ne '127.0.0.1' -and $_ -notmatch '^169\.254\.' }

    if ($legacy) { return ($legacy | Select-Object -First 1) }
    return '0.0.0.0'
}

function Get-TemplateBody([string]$TemplatePath) {
    if (-not (Test-Path $TemplatePath)) { throw "Missing template: $TemplatePath" }
    $content = [System.IO.File]::ReadAllText($TemplatePath, [System.Text.UTF8Encoding]::new($false))
    return (($content -replace '(?m)^;.*\r?\n', '').TrimStart())
}

function Set-CommLinkInfoIni {
    param(
        [string]$Sim,
        [string]$LocalIpAddress,
        [string]$ModeLabel,
        [string]$TemplateFile
    )

    $info = $SimMap[$Sim.ToLower()]
    if (-not $info) { throw "Unknown simulator: $Sim" }

    $templateName = if ($TemplateFile) { $TemplateFile } else { $info.Template }
    $src = Join-Path $Shared $templateName
    $dst = Join-Path $Root "$Sim\bin\UDPCommunicationManager\CommLinkInfo.ini"
    $dir = Split-Path $dst -Parent
    if (-not (Test-Path $dir)) { New-Item -ItemType Directory -Force -Path $dir | Out-Null }

    $body = Get-TemplateBody $src
    if ($LocalIpAddress) {
        $body = $body -replace '(?m)^(\[LOCAL\]\r?\nIP = ).*$', "`${1}$LocalIpAddress"
    }

    $header = @"
; CommLinkInfo.ini - $($info.Label)
; Mode: $ModeLabel

"@

    if ($Mode -eq 'Local') {
        $header += "; Local 1PC: UNICAST 127.0.0.1:$Port (MiniProject TCC 로컬과 동일, 브로드캐스트 아님).`r`n`r`n"
    }
    else {
        $header += "; 5-PC multicast: MULTICAST ${MulticastIp}:${Port}, LOCAL IP=$LocalIpAddress`r`n`r`n"
    }

    [System.IO.File]::WriteAllText($dst, $header + $body, [System.Text.UTF8Encoding]::new($false))
    Write-Host "Configured CommLinkInfo.ini -> $Sim (template=$templateName)"
}

function Invoke-LocalMode {
  Write-Host ''
  Write-Host '========================================'
  Write-Host ' CommLinkInfo - 로컬 1PC (UNICAST)'
  Write-Host '========================================'
  Write-Host ' CAST = UNICAST, REMOTE = 127.0.0.1:10000'
  Write-Host ' (MiniProject TCC 로컬 예제와 동일, 멀티캐스트/브로드캐스트 아님)'
  Write-Host ''
  Write-Host ' [참고] Windows UDP: 127.0.0.1:10000 으로 보낸 1패킷은'
  Write-Host '        같은 포트에 붙은 프로세스 중 보통 1개만 수신합니다.'
  Write-Host '        로컬에서 4모의기 동시 수신 확인은 어려울 수 있습니다.'
  Write-Host '        (실장비 5대는 메뉴 [9] 멀티캐스트 사용)'
  Write-Host ''

  Set-CommLinkInfoIni -Sim 'tcc' -LocalIpAddress $null -ModeLabel 'Local 1PC (UNICAST)' -TemplateFile 'CommLinkInfo.local-tcc.ini'
  foreach ($sim in @('ats', 'lcs', 'mfrs', 'mss')) {
    Set-CommLinkInfoIni -Sim $sim -LocalIpAddress $null -ModeLabel 'Local 1PC (UNICAST)' -TemplateFile 'CommLinkInfo.local-receiver.ini'
  }

  Write-Host ''
  Write-Host 'Done. [K] 종료 후 [7] 전체 실행 → TCC Deploy (NUdp send_to 오류 없어야 함).'
}

function Invoke-Multicast5PCMode {
    param([string]$SelectedRole, [string]$SelectedLocalIp)

    if (-not $SelectedRole) {
        Write-Host ''
        Write-Host '이 PC에서 실행할 모의기 역할을 선택하세요:'
        Write-Host '  T  TCC  (sender)'
        Write-Host '  A  ATS  (receiver)'
        Write-Host '  L  LCS  (receiver)'
        Write-Host '  F  MFRS (receiver)'
        Write-Host '  M  MSS  (receiver)'
        $inputRole = (Read-Host '역할 (T/A/L/F/M)').Trim().ToUpper()
        $SelectedRole = switch ($inputRole) {
            'T' { 'TCC' }
            'A' { 'ATS' }
            'L' { 'LCS' }
            'F' { 'MFRS' }
            'M' { 'MSS' }
            'TCC' { 'TCC' }
            'ATS' { 'ATS' }
            'LCS' { 'LCS' }
            'MFRS' { 'MFRS' }
            'MSS' { 'MSS' }
            default { throw "Invalid role: $inputRole" }
        }
    }

    if (-not $SelectedLocalIp) {
        $detected = Get-FirstNonLoopbackIPv4
        Write-Host ''
        Write-Host "Detected LOCAL IP: $detected"
        $answer = (Read-Host "LOCAL IP [Enter=$detected, 0=0.0.0.0]").Trim()
        $SelectedLocalIp = if ($answer -eq '') { $detected }
            elseif ($answer -eq '0' -or $answer -eq '0.0.0.0') { '0.0.0.0' }
            else { $answer }
    }

    $sim = $SelectedRole.ToLower()
    Write-Host ''
    Write-Host '========================================'
    Write-Host " CommLinkInfo - 5대 PC 멀티캐스트 ($SelectedRole)"
    Write-Host '========================================'
    Write-Host " MULTICAST ${MulticastIp}:${Port}"
    Write-Host " LOCAL IP = $SelectedLocalIp"
    Write-Host ''

    Set-CommLinkInfoIni -Sim $sim -LocalIpAddress $SelectedLocalIp -ModeLabel "Multicast5PC ($SelectedRole on this PC)"

    Write-Host ''
    Write-Host "Done. On this PC run only [$SelectedRole] from the menu."
}

switch ($Mode) {
    'Local' { Invoke-LocalMode }
    'Multicast5PC' { Invoke-Multicast5PCMode -SelectedRole $Role -SelectedLocalIp $LocalIp }
}
