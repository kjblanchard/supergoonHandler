@echo off
set "ELEVATE_CMD=%temp%\elevate_cmd.vbs"
echo Set objShell = CreateObject("Shell.Application") > "%ELEVATE_CMD%"
echo objShell.ShellExecute "cmd.exe", "/k ""%~s0""", "", "runas" >> "%ELEVATE_CMD%"
"%temp%\elevate_cmd.vbs"
del "%temp%\elevate_cmd.vbs"
exit