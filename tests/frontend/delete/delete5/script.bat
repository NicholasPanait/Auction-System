@echo off
copy ..\..\globalTestItems.txt .\localTestItems.txt
copy ..\..\globalTestUsers.txt .\localTestUsers.txt
copy .\..\..\..\..\build\frontend.exe .\frontend.exe
frontend.exe ./localTestUsers.txt ./localTestItems.txt ./ < ./inputStream.txt > ./output.txt

fc output.txt expectedOutputStream.txt
if errorlevel 1 goto different

color 02
echo TEST PASSED
PAUSE
EXIT

:different
color 04
echo TEST FAILED
PAUSE
EXIT