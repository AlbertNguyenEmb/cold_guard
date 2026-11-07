@echo off
setlocal
if /I "%~1"=="espnow_node" goto explicit_project
call "%~dp0..\build.cmd" espnow_node %*
exit /b %errorlevel%

:explicit_project
call "%~dp0..\build.cmd" %*
exit /b %errorlevel%
