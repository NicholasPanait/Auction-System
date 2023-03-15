#include "UserAccountsFile.h"

/*The constructor method for a UserAccountsFile object.
*/
UserAccountsFile::UserAccountsFile()
{
    this->file.open(USER_ACCOUNTS_FILE, std::ios::app | std::ios::in);
}

/*The destructor method for a UserAccountsFile object.
*/
UserAccountsFile::~UserAccountsFile()
{
    this->file.close();
}

std::optional<UserInfo> UserAccountsFile::getUserInfo(std::string username)
{
    auto users = this->readUserFile();
    auto res = std::find(users.begin(), users.end(), Util::trim(username));
    return (res == users.end()) ? std::nullopt : std::optional<UserInfo>{*res};
}

/*
* Description: This method appends the information for the specified user to the user accounts file, 
* and returns true if successfully appended to the file.
*
* @param - data - A UserInfo struct that contains the information for the user to be written to file
* @return - returns true if user's information is successfully appended to the file
*/
bool UserAccountsFile::appendUserToFile(UserInfo data)
{
    /* TO DO: take the information from the data struct and convert it into a string. Append the string to file */
    // format: UUUUUUUUUUUUUUU_TT_CCCCCCCCC_PPPPPPPPPPPP

    char username[30];
    std::snprintf(username, 30, "%-15s %s %09.2f ", data.username.c_str(), User::getTypeCode(data.userType).c_str(), data.availableCredit);
    file << username << data.password << '\n';
    return false;
}

/*
* Description: This method verifies if the specified user’s information 
* currently exists in the user accounts file and returns true if the 
* user’s information is found in the file.
* 
* @param - data - A UserInfo struct that contains the information for the user to be verified
* @return - returns true if the user's information is found in the file
*/
bool UserAccountsFile::userExistsInFile(std::string username)
{
    /* TO DO: traverse through file, read each line get each user's info. Compare each user from file to the data struct until a match is found */
    auto users = this->readUserFile();
    return std::find(users.begin(), users.end(), Util::trim(username)) != users.end();
}

/*
* Description: This method reads in all the contents of the user accounts file, and returns a 
* vector with all the information. The information for each user is stored as a UserInfo struct 
* in the vector.
*
* @return  - a vector containing UserInfo structs
*/
std::vector<UserInfo> UserAccountsFile::readUserFile()
{
    /* TO DO:  traverse through user accounts file, read each line, and convert it into a UserInfo struct. Add the struct to the vector.*/
    // format: UUUUUUUUUUUUUUU_TT_CCCCCCCCC_PPPPPPPPPPPP
    std::vector<UserInfo> userInfo;
    std::string line;
    while (std::getline(this->file, line))
    {
        userInfo.emplace_back(UserInfo{
            Util::trim(line.substr(0,15)), 
            User::getUserType(line.substr(16,2).c_str()), 
            atof(line.substr(20,9).c_str()), 
            line.substr(29)
        });
    }
    // reset file pointer
    this->file.clear();
    this->file.seekg(0);

    return userInfo;
}

/*
* Description: This method deletes the information for the specified user from the user
* accounts file and returns true if the information is successfully deleted.
* 
* @param - data - A UserInfo struct that contains the information for the user to be deleted
* @return - returns true if the user's information is deleted from the file
*/
bool UserAccountsFile::deleteUserFromFile(std::string username)
{
    /* TO DO: travserse through the file, and read each line and try to find the line containing the same user info as the data struct. 
    *  Delete that line from the file*/

    std::string line;
    std::ofstream tempFile;
    const char* tempFileName = "temp.txt";
    tempFile.open(tempFileName);

    while(getline(file, line))
    {
        if (Util::trim(line.substr(0,15)) == Util::trim(username))
            continue;
        tempFile << line << '\n';
    }

    tempFile.close();
    file.close();
    remove(USER_ACCOUNTS_FILE);
    rename(tempFileName, USER_ACCOUNTS_FILE);
    this->file.open(USER_ACCOUNTS_FILE, std::ios::app | std::ios::in);

    return true;
}
