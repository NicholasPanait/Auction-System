#pragma once

#include <vector>
#include <fstream>
#include <optional>

#include "User.h"
#include "Util.h"

/*
* Description: The following struct is used to manage and store all the information for each user that will be written to the user
* accounts file
*/
struct UserInfo 
{
    std::string username;
    UserType userType;
    double availableCredit;
    std::string password;

    bool operator==(const UserInfo &r)
    {
        return username == r.username && password == r.password;
    }
    bool operator==(const std::string &r)
    {
        return username == r;
    }
};

/*
* Description: The UserAccountsFile class is used to read, append, update, 
* print the contents of a UserAccountsFile and is used to verify the contents 
* of a UserAccounts file.
*/
class UserAccountsFile
{
private:
    std::fstream file;

public:
    UserAccountsFile(/* args */); //The constructor method for a UserAccountsFile object.
    ~UserAccountsFile(); // The destructor method for a UserAccountsFile object.

    //function declarations for each of the functions used to edit the User Accounts File
    std::optional<UserInfo> getUserInfo(std::string username);
    bool appendUserToFile(UserInfo data);
    bool userExistsInFile(std::string username);
    std::vector<UserInfo> readUserFile();
    bool deleteUserFromFile(std::string username);
};
