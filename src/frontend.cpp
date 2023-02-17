#include <iostream>
#include "utility/utility.h"
#include <string>
using namespace std;

User current_user = User();
bool logged_in = false;

int main ()
{
    cout << "Welcome to Hubble Auction House";
    while(true){
        string command;
        cout << "Please enter a command:";
        cin >> command;
        ProcessCommand(command, current_user, logged_in);
    }
}