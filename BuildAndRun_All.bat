@echo off
cd /d "%~dp0"
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0tools\BuildAndRun_All.ps1"
exit /b %ERRORLEVEL%
