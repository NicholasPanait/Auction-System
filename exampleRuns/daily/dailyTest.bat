@echo off

REM Cleaning up previous runs 
DEL main.out
cd runFiles
DEL *.* /F /Q
copy "..\..\globalFiles\DailyTransactionFile.txt"
copy "..\..\globalFiles\AvailableItemsFile.txt"
copy "..\..\globalFiles\UserAccountsFile.txt"
cd ../
copy "..\..\srcFront\main.out"

call daily1.bat
timeout /t 2 /nobreak
call daily2.bat
timeout /t 2 /nobreak
call daily3.bat
timeout /t 2 /nobreak

cd ../../srcBack
python3 main.py ../exampleRuns/daily/runFiles/UserAccountsFile.txt ../exampleRuns/daily/runFiles/AvailableItemsFile.txt ../exampleRuns/daily/runFiles/DailyTransactionFile.txt
EXIT