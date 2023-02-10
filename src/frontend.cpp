#include <iostream>
#include "utility.h"
#include <string>
using namespace std;

int main ()
{
    cout << "Welcome to Hubble Auction House";
    while(true){
        string command;
        cout << "Please enter a command:";
        cin >> command;
        processCommand(command);
    }
}