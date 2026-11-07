@echo off
setlocal
if /I "%~1"=="main_controller" goto explicit_project
call "%~dp0..\build.cmd" main_controller %*
exit /b %errorlevel%

:explicit_project
call "%~dp0..\build.cmd" %*
exit /b %errorlevel%
