@echo off
wsl g++ -o ../../../../build/frontend.out ../../../../src/frontend.cpp
wsl ./../../../../build/frontend.out < inputStream.txt > output.txt
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