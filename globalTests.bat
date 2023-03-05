@echo off

forfiles /p tests\ /s /m *.bat /c "cmd /c @path"
PAUSE
EXIT