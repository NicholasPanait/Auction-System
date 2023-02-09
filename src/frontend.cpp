#include <iostream>
#include <algorithm>
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

void processCommand(string command){
    transform(command.begin(), command.end(), command.begin(), ::tolower);
    if (command == "login"){

    }
    else if (command == "create"){
        
    }
    else if (command == "logout"){
        
    }
    else if (command == "delete"){
        
    }
    else if (command == "advertise"){
        
    }
    else if (command == "bid"){
        
    }
    else if (command == "refund"){
        
    }
    else if (command == "addcredit"){
        
    }
    else if (command == "listall"){
        
    }
    else{
        cout << "Invalid Command!";
    }
}