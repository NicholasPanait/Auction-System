wsl g++ -o ../../../build/frontend.out ../../../src/sandbox.cpp
wsl ./../../../build/frontend.out < inputStream.txt > expectedOutputStream.txt