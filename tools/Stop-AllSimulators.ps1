# Stop all SimulatorSuite processes (TCC + headless sims).
$ErrorActionPreference = 'Continue'
[Console]::OutputEncoding = [Text.UTF8Encoding]::UTF8

$ProcessNames = @(
    'TCC_GUI',
    'ATSd',
    'ATS',
    'LCSd',
    'LCS',
    'MFRSd',
    'MFRS',
    'MSSd',
    'MSS'
)

function Stop-SimulatorProcess {
    param([System.Diagnostics.Process]$Proc)

    $name = $Proc.ProcessName
    try {
        if (-not $Proc.HasExited) {
            $Proc.CloseMainWindow() | Out-Null
            if (-not $Proc.WaitForExit(3000)) {
                Stop-Process -Id $Proc.Id -Force -ErrorAction Stop
                Write-Host "  Force stopped $name (PID $($Proc.Id))"
                return
            }
            Write-Host "  Stopped $name (PID $($Proc.Id))"
        }
    }
    catch {
        try {
            Stop-Process -Id $Proc.Id -Force -ErrorAction Stop
            Write-Host "  Force stopped $name (PID $($Proc.Id))"
        }
        catch {
            Write-Host "  [WARN] Could not stop $name (PID $($Proc.Id)): $_" -ForegroundColor Yellow
        }
    }
}

Write-Host ''
Write-Host '========================================'
Write-Host ' 전체 모의기 종료'
Write-Host '========================================'

$found = @()
foreach ($procName in $ProcessNames) {
    $found += Get-Process -Name $procName -ErrorAction SilentlyContinue
}

$found = $found | Sort-Object Id -Unique

if (-not $found) {
    Write-Host '실행 중인 모의기 프로세스가 없습니다.'
    exit 0
}

Write-Host "Stopping $($found.Count) process(es)..."
foreach ($proc in $found) {
    Stop-SimulatorProcess -Proc $proc
}

Start-Sleep -Milliseconds 500
$remaining = @()
foreach ($procName in $ProcessNames) {
    $remaining += Get-Process -Name $procName -ErrorAction SilentlyContinue
}
$remaining = $remaining | Sort-Object Id -Unique

if ($remaining) {
    Write-Host ''
    Write-Host "[WARN] $($remaining.Count) process(es) still running:" -ForegroundColor Yellow
    foreach ($proc in $remaining) {
        Write-Host "  $($proc.ProcessName) (PID $($proc.Id))"
    }
    exit 1
}

Write-Host ''
Write-Host '모든 모의기가 종료되었습니다.'
exit 0
