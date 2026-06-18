# SimulatorSuite — IntelliVal 일괄 실행
$ErrorActionPreference = 'Stop'
$Root = 'C:\Users\User\Desktop\SimulatorSuite'
$IvExe = 'c:\LIG\nFrameworkv1.8.2\examples\MiniProject_x64_vc143\IntelliVal\IntelliVal.exe'
$IvDir = Split-Path $IvExe -Parent

if (-not (Test-Path $IvExe)) { throw "IntelliVal not found: $IvExe" }

function Get-RelPath([string]$AbsPath) {
    $uriBase = New-Object System.Uri((Join-Path $IvDir '.'))
    $uriTarget = New-Object System.Uri($AbsPath)
    $rel = $uriBase.MakeRelativeUri($uriTarget).ToString().Replace('/', '\')
    if ($rel -notmatch '\\') { return ".\$rel" }
    return $rel
}

function Invoke-IntelliVal([string]$Sim, [string]$Mgr, [string]$OutExt = 'h', [string]$CsProj = $null, [string]$SrcSub = 'Managers') {
    $binAbs = Join-Path $Root "$Sim\bin"
    $srcAbs = Join-Path $Root "$Sim\src\$SrcSub"
    $bin = Get-RelPath $binAbs
    $src = Get-RelPath $srcAbs
    $args = @(
        "--bin=$bin", "--src=$src",
        "--mgr=$Mgr", "--nom=$Mgr.xml",
        "--outext=$OutExt",
        '--schreg=y', '--srpath=SchemaRegistryData.xml',
        '--tdspc=y'
    )
    if ($OutExt -eq 'cs' -and $CsProj) { $args += "--csproj=$CsProj" }

    $psi = New-Object System.Diagnostics.ProcessStartInfo
    $psi.FileName = $IvExe
    $psi.WorkingDirectory = $IvDir
    $psi.Arguments = ($args -join ' ')
    $psi.UseShellExecute = $false
    $psi.RedirectStandardOutput = $true
    $psi.RedirectStandardError = $true
    $psi.CreateNoWindow = $true
    $p = [System.Diagnostics.Process]::Start($psi)
    $stdout = $p.StandardOutput.ReadToEnd()
    $stderr = $p.StandardError.ReadToEnd()
    $p.WaitForExit()
  return [PSCustomObject]@{
        Sim = $Sim; Manager = $Mgr; OutExt = $OutExt
        ExitCode = $p.ExitCode; Output = $stdout; Error = $stderr
    }
}

$SimManagers = @{
    tcc  = @('UIManager','ControlManager','ScenarioManager','StatusManager','UDPCommunicationManager')
    ats  = @('SimulationManager','ATSModelManager','UDPCommunicationManager')
    lcs  = @('SimulationManager','LaunchManager','LCSModelManager','UDPCommunicationManager')
    mfrs = @('SimulationManager','DetectManager','DataLinkManager','MFRSModelManager','UDPCommunicationManager')
    mss  = @('SimulationManager','LaunchManager','DataLinkManager','MSSModelManager','DetonationManager','UDPCommunicationManager')
}

$results = [System.Collections.Generic.List[object]]::new()
foreach ($sim in $SimManagers.Keys) {
    foreach ($mgr in $SimManagers[$sim]) {
        if ($mgr -eq 'UDPCommunicationManager') { continue }
        $results.Add((Invoke-IntelliVal $sim $mgr 'h'))
    }
}

# UDP: shared 소스, wire XML은 tcc/bin 기준 (전 sim 동일)
$udpBin = Get-RelPath (Join-Path $Root 'tcc\bin')
$udpSrc = Get-RelPath (Join-Path $Root 'shared')
$udpArgs = @(
    "--bin=$udpBin", "--src=$udpSrc",
    '--mgr=UDPCommunicationManager', '--nom=UDPCommunicationManager.xml',
    '--outext=h', '--schreg=y', '--srpath=SchemaRegistryData.xml', '--tdspc=y'
)
$psi = New-Object System.Diagnostics.ProcessStartInfo
$psi.FileName = $IvExe
$psi.WorkingDirectory = $IvDir
$psi.Arguments = ($udpArgs -join ' ')
$psi.UseShellExecute = $false
$psi.RedirectStandardOutput = $true
$psi.RedirectStandardError = $true
$psi.CreateNoWindow = $true
$p = [System.Diagnostics.Process]::Start($psi)
$udpOut = $p.StandardOutput.ReadToEnd()
$udpErr = $p.StandardError.ReadToEnd()
$p.WaitForExit()
$results.Add([PSCustomObject]@{ Sim='shared'; Manager='UDPCommunicationManager'; OutExt='h'; ExitCode=$p.ExitCode; Output=$udpOut; Error=$udpErr })

$results.Add((Invoke-IntelliVal 'tcc' 'UIManager' 'cs' 'src\Main\TCC_GUI\TCC_GUI.csproj'))

$ok = @($results | Where-Object { $_.ExitCode -eq 0 })
$fail = @($results | Where-Object { $_.ExitCode -ne 0 })

Write-Host "IntelliVal OK: $($ok.Count) / $($results.Count)"
foreach ($f in $fail) {
    Write-Host "FAIL $($f.Sim)/$($f.Manager): exit $($f.ExitCode)"
    if ($f.Output) { Write-Host $f.Output }
    if ($f.Error) { Write-Host $f.Error }
}
if ($fail.Count) { exit 1 }
