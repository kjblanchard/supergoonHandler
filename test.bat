@echo off
powershell.exe -NoExit -Command "& {cd /d '%~dp0'; .\supergoonHandlerExe.exe}"
@echo off
start powershell.exe -NoExit -Command "cd /d '%~dp0'; .\supergoonHandlerExe.exe"

@echo off
echo Start-Process -FilePath "%~dp0\supergoonHandlerExe.exe" -Verb RunAs | powershell.exe -NoExit -Command -

@echo off
powershell.exe -NoExit -Command "Start-Process -FilePath '%~dp0\supergoonHandlerExe.exe' -Verb RunAs"



