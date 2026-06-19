# Quick UDP receive test: start ATS, send DeployScenarioRequest-like packet to multicast.
# Confirms processRecvMessage -> SimulationManager::recvMsg path.
param([string]$Sim = 'ats')
$ErrorActionPreference = 'Stop'
$root = Split-Path $PSScriptRoot -Parent
$bin = Join-Path $root "$Sim\bin"
$exe = Join-Path $bin "${Sim}d.exe"
if ($Sim -eq 'tcc') { throw 'Use headless sim (ats/lcs/mfrs/mss)' }
if (-not (Test-Path $exe)) { throw "Missing $exe — build first." }

& (Join-Path $PSScriptRoot 'Configure-NetworkMode.ps1') -Mode Local | Out-Null

$body = [byte[]](0x01,0x00,0x00,0x00,0x00,0x00,0x16,0x42,0x00,0x00,0xfe,0x42,0x66,0x66,0x16,0x42,0x33,0x33,0xfe,0x42,0x33,0x33,0x16,0x42,0x9a,0x19,0xfe,0x42,0x7b,0x14,0x16,0x42,0x3d,0x0a,0xfe,0x42)
# Little-endian header: id=1001 (e9 03 00 00), len=44 — matches sendCommMsg / NOM serialize
$packet = [byte[]](0xe9,0x03,0x00,0x00,0x2c,0x00,0x00,0x00) + $body

$out = Join-Path $env:TEMP "udp_test_${Sim}.txt"
Remove-Item $out -ErrorAction SilentlyContinue
$p = Start-Process -FilePath $exe -WorkingDirectory $bin -RedirectStandardOutput $out -PassThru -WindowStyle Hidden
Start-Sleep 8
$udp = New-Object System.Net.Sockets.UdpClient
$ep = New-Object System.Net.IPEndPoint([System.Net.IPAddress]::Parse('127.0.0.1'), 10000)
[void]$udp.Send($packet, $packet.Length, $ep)
$udp.Close()
Start-Sleep 3
if (-not $p.HasExited) { Stop-Process -Id $p.Id -Force }

$ok = $false
$tracePath = Join-Path $bin 'udp_trace.log'
if (Test-Path $out) {
    $ok = (Select-String -Path $out -Pattern 'DeployScenarioRequest received' -Quiet)
    Get-Content $out | Select-String 'DeployScenario|recvMsg|undefined'
}
if (-not $ok -and (Test-Path $tracePath)) {
    $ok = (Select-String -Path $tracePath -Pattern 'interaction sendMsg: DeployScenarioRequest' -Quiet)
    Get-Content $tracePath
}
if ($ok) { Write-Host "[OK] $Sim received DeployScenarioRequest" -ForegroundColor Green }
else { Write-Host "[FAIL] $Sim did not log DeployScenarioRequest receive" -ForegroundColor Red; exit 1 }
