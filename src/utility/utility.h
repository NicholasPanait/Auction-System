#include <iostream>
#include <algorithm>
using namespace std;

#ifndef UTILITY_H // include guard
#define UTILITY_H

void processCommand(string command, User current_user, bool logged_in){
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
    else if (command == "listbids"){
        
    }
    else if (command == "listusers"){
        
    }
    else{
        cout << "Invalid Command!";
    }
}

#endif