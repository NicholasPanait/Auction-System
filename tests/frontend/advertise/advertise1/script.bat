@echo off
REM copy ..\..\globalTestItems.txt .\localTestItems.txt
REM copy ..\..\globalTestUsers.txt .\localTestUsers.txt
copy .\..\..\..\..\build\frontend.exe .\frontend.exe
del dailyTransactionFile.txt
frontend.exe ./localTestUsers.txt ./localTestItems.txt ./ < ./inputStream.txt > ./output.txt

fc output.txt expectedOutputStream.txt
if errorlevel 1 goto different
fc transactionFile.txt expectedTransactionFile.txt
if errorlevel 1 goto different

echo %cd% [92mTEST PASSED[0m
EXIT

:different
echo %cd% [91mTEST FAILED[0m
PAUSE
EXIT