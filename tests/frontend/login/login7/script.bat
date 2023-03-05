@echo off
copy ..\..\globalTestItems.txt .\localTestItems.txt
copy ..\..\globalTestUsers.txt .\localTestUsers.txt
copy .\..\..\..\..\build\frontend.exe .\frontend.exe
frontend.exe ./localTestUsers.txt ./localTestItems.txt ./ < ./inputStream.txt > ./output.txt

fc output.txt expectedOutputStream.txt
if errorlevel 1 goto different

echo %cd% [92mTEST PASSED[0m
EXIT

:different
echo %cd% [91mTEST FAILED[0m
PAUSE
EXIT