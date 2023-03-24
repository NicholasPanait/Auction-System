# CSCI3060U_Project

# IMPORTANT NOTE
# System Requirements
For use, please either:
1. Be on Linux and have `g++` and `make` available

# How to Run
This project requires linux style build tools, primarily `g++` and `make`. As long a there requirement are fulfilled, it should be buildable and runnable on any operating system.

To build the frontend program

`cd srcFront`
`make`

The resulting executable will appear in this folder as `main`

## To test frontend program

`cd tests/frontend`
`./run_tests.sh`

This shell script will auto build the program, test results will be shown on screen

## To test the backend program
Requires Python, Pip, and PyTest
Install pytest via `pip install -U pytest`
In the root of the project, or in srcBack run `pytest`