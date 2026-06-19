# Team nFramework SDK root. Dot-source: . .\tools\Get-NFrameworkRoot.ps1
function Get-NFrameworkRoot {
    $repoRoot = Split-Path $PSScriptRoot -Parent
    $pathFile = Join-Path $repoRoot 'frameworks\nFramework.path'

    if ($env:NFW_ROOT) {
        $p = $env:NFW_ROOT.Trim().TrimEnd('\')
        if (Test-Path $p) { return $p }
        Write-Warning "NFW_ROOT set but path not found: $p"
    }

    if (-not (Test-Path $pathFile)) {
        throw "Missing $pathFile — add team SDK path (e.g. C:\LIG\nFrameworkv1.8.2)"
    }

    $root = ([System.IO.File]::ReadAllText($pathFile, [System.Text.UTF8Encoding]::new($false))).Trim().TrimEnd('\')
    if (-not $root) { throw "Empty path in $pathFile" }
    return $root
}
