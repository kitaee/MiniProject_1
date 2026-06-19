param([string]$Simulator = "ats")
$ErrorActionPreference = 'Stop'
. (Join-Path $PSScriptRoot 'Get-NFrameworkRoot.ps1')
$root = Split-Path $PSScriptRoot -Parent
$nfwBin = Join-Path (Get-NFrameworkRoot) 'bin'
$dest = Join-Path $root "$Simulator\bin"
if (-not (Test-Path $nfwBin)) { Write-Error "nFramework bin not found: $nfwBin"; exit 1 }
Copy-Item "$nfwBin\*.dll" $dest -Force -ErrorAction SilentlyContinue
$log4nf = Join-Path $nfwBin "Log4nF.ini"
if (Test-Path $log4nf) {
    Copy-Item $log4nf (Join-Path $dest "Log4nF.ini") -Force
}
$commonSr = Join-Path $root "common\SchemaRegistryData.xml"
if (Test-Path $commonSr) {
    Copy-Item $commonSr (Join-Path $dest "SchemaRegistryData.xml") -Force
    Get-ChildItem $dest -Directory | ForEach-Object {
        Copy-Item $commonSr (Join-Path $_.FullName "SchemaRegistryData.xml") -Force
    }
}
Get-ChildItem $dest -Directory | ForEach-Object {
    Copy-Item "$nfwBin\*.dll" $_.FullName -Force -ErrorAction SilentlyContinue
}
Write-Host "Copied runtime DLLs from $nfwBin to $dest and manager subfolders"
