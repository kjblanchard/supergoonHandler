@echo off
powershell.exe -NoExit -Command "& {Start-Process -FilePath './supergoonHandlerExe.exe' -Verb RunAs}"

@echo off
powershell.exe -NoExit -Command "Set-Location -Path '%~dp0'; Start-Process -FilePath 'supergoonHandlerExe.exe' -Verb RunAs"
