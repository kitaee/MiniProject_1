@echo off
chcp 65001 >nul
cd /d "%~dp0.."
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0Test-NFrameworkSdk.ps1"
pause
exit /b %ERRORLEVEL%
