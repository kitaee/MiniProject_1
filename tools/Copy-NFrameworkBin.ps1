param([string]$Simulator = "ats")
$root = Split-Path -Parent $PSScriptRoot
$nfw = Join-Path $root "frameworks\nFramework_sdk\bin"
$dest = Join-Path $root "$Simulator\bin"
if (-not (Test-Path $nfw)) { Write-Error "nFramework bin not found: $nfw"; exit 1 }
Copy-Item "$nfw\*.dll" $dest -Force -ErrorAction SilentlyContinue
$log4nf = Join-Path $nfw "Log4nF.ini"
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
    Copy-Item "$nfw\*.dll" $_.FullName -Force -ErrorAction SilentlyContinue
}
Write-Host "Copied runtime DLLs to $dest and manager subfolders"
