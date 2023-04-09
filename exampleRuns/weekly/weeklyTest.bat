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