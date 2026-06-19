@echo off
chcp 65001 >nul
cd /d "%~dp0.."
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0Configure-NetworkMode.ps1" -Mode Multicast5PC
exit /b %ERRORLEVEL%
