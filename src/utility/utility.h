#include <iostream>
#include <algorithm>
#include <map>
#include <fstream>

using namespace std;

/*
This header file contains utility functions that
are used by files for at least 2 commands
*/

#ifndef UTILITY_H // include guard
#define UTILITY_H

class User {
    public:
        string username;
        string privilege_type;
        float credit;
        User(string username, string privilege_type, float credit){
            this->username = username;
            this->privilege_type = privilege_type;
            this->credit = credit;
        }
        User(){
            this->username = "";
            this->privilege_type = "";
            this->credit = 0;
        }
    
    friend ostream &operator<<(ostream &strm, const User &user){
        return strm << 
        "Username: " << user.username << 
        ", Privilege: " << user.privilege_type << 
        ", Credit: " << fixed << setprecision(2) << user.credit << endl;
    }
};

// Returns a User object with the specified user's information
// Return NULL if no user exists
User GetUser(string username){
    User user = User();
    if (!UsernameExists(username)){
        return user;
    }
    string line;
    ifstream input ("../../res/UserFile.txt");
    if (input.is_open()){
        while (getline(input, line))
        {
            if (username == line.substr(0, 15).erase(line.substr(0, 15).find_last_not_of(' ') + 1, std::string::npos)){
                user.username = line.substr(0, 15).erase(line.substr(0, 15).find_last_not_of(' ') + 1, std::string::npos);
                user.privilege_type = line.substr(16,2);
                user.credit = stof(line.substr(19,9));
                input.close();
                return user;
            }
            
        }
    }
    input.close();
    return user;
}

// Checks whether the given permission level (2 letter representation)
// is enough for the command (integer representation).
// Returns TRUE if you have the required permission, otherwise FALSE.
// NOTE: Addcredit returns TRUE if the user is an admin, otherwise FALSE.
bool CheckPermission(string permission, int command){
    map<string, int> privileges {{"AA",4},{"FS",3},{"BS",2},{"SS",1}};

    switch (command)
    {
    // Advertise
    case 3
        if (privileges[permission] == 2){
            return false;
        }
        return true;
    
    // Bid
    case 4
        if (privileges[permission] == 1){
            return false;
        }
        return true;
    
    // Addcredit, Admin vs Normal
    case 6
        if (privileges[permission] == 4){
            return true;
        }
        return false;

    // Admin, Create, Delete, Refund, 
    default:
        if (privileges[permission] < 4){
            return false;
        }
        return true;
    }
}

// Returns TRUE if this is a valid permission, otherwise returns FALSE.
bool ValidatePermission(string permission){
    map<string, int> privileges {{"AA",4},{"FS",3},{"BS",2},{"SS",1}};
    if (privieges[toupper(permission)] == 0){
        return false;
    }
    return true;

}


// Returns TRUE if the username exists, otherwise returns FALSE.
bool UsernameExists(string username){
    string line;
    ifstream input ("../../res/UserFile.txt");
    if (input.is_open()){
        while (getline(input, line))
        {
            if (line == "END"){
                input.close();
                return false;
            }
            else{
                line = line.substr(0, 15).erase(line.substr(0, 15).find_last_not_of(' ') + 1, std::string::npos);
                if (username == line){
                    input.close();
                    return true;
                }
            }
        }
    }
    input.close();
    return false;
}

// Returns integer based on validation:
// 0: Valid Username
// 1: Username Too Long
// 2: Username Too Short
// 3: Username Already Exists
int ValidateUsername(string username){
    if (username.length() > 15){
        return 1;
    }
    else if(username.length() < 1){
        return 2;
    } 
    else if(UsernameExists(username)){
        return 3;
    }
    return 0;
}

// Calls respective commands and handles invalid commands
void ProcessCommand(string command, User current_user, bool logged_in){
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
        cout << "Invalid Command!" << endl;
    }
}

#endif