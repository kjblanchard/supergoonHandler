@echo off
for %%I in ("%~dp0") do start cmd /k "cd /d %%~fI && supergoonHandlerExe.exe"



