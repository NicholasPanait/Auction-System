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

call day1.bat
timeout /t 1 /nobreak
call runBackend.bat
timeout /t 2 /nobreak

call day2.bat
timeout /t 1 /nobreak
call runBackend.bat
timeout /t 2 /nobreak

call day3.bat
timeout /t 1 /nobreak
call runBackend.bat
timeout /t 2 /nobreak

call day4.bat
timeout /t 1 /nobreak
call runBackend.bat
timeout /t 2 /nobreak

call day5.bat
timeout /t 1 /nobreak
call runBackend.bat
timeout /t 2 /nobreak

PAUSE
EXIT