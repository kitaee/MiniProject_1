# Sync CommLinkInfo.ini from shared templates to each simulator bin folder.
# Default: Local mode (5 sims on one PC). Use Configure-NetworkMode.ps1 for Multicast5PC.
param(
    [ValidateSet('Local', 'Multicast5PC')]
    [string]$Mode = 'Local',

    [ValidateSet('TCC', 'ATS', 'LCS', 'MFRS', 'MSS')]
    [string]$Role,

    [string]$LocalIp
)

$cfg = Join-Path $PSScriptRoot 'Configure-NetworkMode.ps1'
if ($Role) {
    & $cfg -Mode $Mode -Role $Role -LocalIp $LocalIp
}
elseif ($LocalIp) {
    & $cfg -Mode $Mode -LocalIp $LocalIp
}
else {
    & $cfg -Mode $Mode
}
