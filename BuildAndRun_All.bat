@echo off
chcp 65001 >nul
cd /d "%~dp0"
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0tools\BuildAndRun_All.ps1"
exit /b %ERRORLEVEL%
