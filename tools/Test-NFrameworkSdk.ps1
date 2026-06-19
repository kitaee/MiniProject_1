# Verify team nFramework SDK at C:\LIG\nFrameworkv1.8.2 (or frameworks/nFramework.path).
$ErrorActionPreference = 'Stop'
[Console]::OutputEncoding = [Text.UTF8Encoding]::UTF8
. (Join-Path $PSScriptRoot 'Get-NFrameworkRoot.ps1')

$nfw = Get-NFrameworkRoot
Write-Host "nFramework SDK: $nfw"
Write-Host ''

$checks = @(
    @{ Label = 'include'; Path = Join-Path $nfw 'include' }
    @{ Label = 'lib'; Path = Join-Path $nfw 'lib' }
    @{ Label = 'bin'; Path = Join-Path $nfw 'bin' }
    @{ Label = 'NOMHandlerLib.Net8 (Debug)'; Path = Join-Path $nfw 'bin\NOMHandlerLib.Net8\Debug\net8.0-windows\NOMHandlerLib.Net8.dll' }
    @{ Label = 'CS_NOM.Net8 (Debug)'; Path = Join-Path $nfw 'bin\CS_NOM.Net8\Debug\net8.0\CS_NOM.Net8.dll' }
    @{ Label = 'nFConnectd.dll'; Path = Join-Path $nfw 'bin\nFConnectd.dll' }
)

$ok = $true
foreach ($c in $checks) {
    if (Test-Path $c.Path) {
        Write-Host "  [OK]   $($c.Label)" -ForegroundColor Green
    } else {
        Write-Host "  [FAIL] $($c.Label) — $($c.Path)" -ForegroundColor Red
        $ok = $false
    }
}

Write-Host ''
if ($ok) {
    Write-Host 'SDK ready. Next: build in VS, then Copy-NFrameworkBin.ps1 per sim.' -ForegroundColor Green
    exit 0
}

Write-Host 'Install nFramework v1.8.2 to C:\LIG\nFrameworkv1.8.2 (team standard).' -ForegroundColor Yellow
Write-Host 'Or edit frameworks\nFramework.path / set NFW_ROOT for this machine only.'
exit 1
