# Two-hop UDP verification (hop2 wire path on headless sims)
# Uses network-byte-order 8-byte header (id=1001, len=44) per CommLinkInfo ID_SIZE=4.
param(
    [ValidateSet('unicast', 'multicast')]
    [string]$Delivery = 'unicast'
)
$ErrorActionPreference = 'Stop'

$root = 'C:\Users\User\Desktop\SimulatorSuite'
$body = [byte[]](
    0x01,0x00,0x00,0x00,0x00,0x00,0x16,0x42,0x00,0x00,0xfe,0x42,0x66,0x66,0x16,0x42,
    0x33,0x33,0xfe,0x42,0x33,0x33,0x16,0x42,0x9a,0x19,0xfe,0x42,0x7b,0x14,0x16,0x42,
    0x3d,0x0a,0xfe,0x42
)
$payload = [byte[]](0x00,0x00,0x03,0xe9,0x00,0x00,0x00,0x2c) + $body

& (Join-Path $root 'tools\Configure-NetworkMode.ps1') -Mode Local | Out-Null

$sims = @(
    @{ Name = 'ats'; Exe = 'ATSd.exe' }
    @{ Name = 'lcs'; Exe = 'LCSd.exe' }
    @{ Name = 'mfrs'; Exe = 'MFRSd.exe' }
    @{ Name = 'mss'; Exe = 'MSSd.exe' }
)
$procs = @()

foreach ($sim in $sims) {
    $bin = Join-Path $root "$($sim.Name)\bin"
    & (Join-Path $root 'tools\Copy-NFrameworkBin.ps1') -Simulator $sim.Name | Out-Null
    Remove-Item (Join-Path $bin 'udp_trace.log') -ErrorAction SilentlyContinue
    $out = Join-Path $env:TEMP "udp2hop_$($sim.Name)_out.txt"
    $err = Join-Path $env:TEMP "udp2hop_$($sim.Name)_err.txt"
    Remove-Item $out,$err -ErrorAction SilentlyContinue
    $procs += [PSCustomObject]@{
        Sim = $sim.Name
        Bin = $bin
        Out = $out
        Err = $err
        P = Start-Process -FilePath (Join-Path $bin $sim.Exe) -WorkingDirectory $bin -PassThru `
            -RedirectStandardOutput $out -RedirectStandardError $err -WindowStyle Hidden
    }
}

Start-Sleep -Seconds 10

$udp = New-Object System.Net.Sockets.UdpClient
if ($Delivery -eq 'multicast') {
    $udp.JoinMulticastGroup([System.Net.IPAddress]::Parse('239.255.0.1'))
    $endpoint = New-Object System.Net.IPEndPoint([System.Net.IPAddress]::Parse('239.255.0.1'), 10000)
}
else {
    $endpoint = New-Object System.Net.IPEndPoint([System.Net.IPAddress]::Parse('127.0.0.1'), 10000)
}
[void]$udp.Send($payload, $payload.Length, $endpoint)
$udp.Close()

Start-Sleep -Seconds 4

$results = @()
foreach ($item in $procs) {
    if (-not $item.P.HasExited) { Stop-Process -Id $item.P.Id -Force -ErrorAction SilentlyContinue }
    $text = @()
    if (Test-Path $item.Out) { $text += Get-Content $item.Out -Raw -ErrorAction SilentlyContinue }
    if (Test-Path $item.Err) { $text += Get-Content $item.Err -Raw -ErrorAction SilentlyContinue }
    $combined = ($text -join "`n")
    $trace = if (Test-Path (Join-Path $item.Bin 'udp_trace.log')) { Get-Content (Join-Path $item.Bin 'udp_trace.log') -Raw } else { '' }
    $hop2 = ($combined -match 'DeployScenarioRequest received|recvMsg: DeployScenarioRequest') -or
            ($trace -match 'interaction sendMsg: DeployScenarioRequest')
    $results += [PSCustomObject]@{
        Sim = $item.Sim
        Hop2 = $(if ($hop2) { 'OK' } else { 'FAIL' })
        Trace = (($trace.Trim() -split "`r?`n" | Select-Object -Last 4) -join ' | ')
    }
}

Write-Host "Delivery mode: $Delivery"
$results | Format-Table -Wrap -AutoSize
$results | ConvertTo-Json | Out-File (Join-Path $env:TEMP 'udp2hop_results.json')
if ($results.Hop2 -contains 'FAIL') { exit 1 }
