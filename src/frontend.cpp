#include <iostream>
#include "utility/utility.h"
#include <string>
#include "appState/appState.h"
using namespace std;

int main ()
{
    cout << "Welcome to Hubble Auction House";
    while(true){
        string command;
        cout << "Please enter a command:";
        cin >> command;
        ProcessCommand(command);
    }
}