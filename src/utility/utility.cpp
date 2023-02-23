#include "utility.h"

using namespace std;

User::User(string username, string privilege_type, float credit)
{
    this->username = username;
    this->privilege_type = privilege_type;
    this->credit = credit;
}

User::User()
{
    this->username = "";
    this->privilege_type = "";
    this->credit = 0;
}

ostream &operator<<(ostream &strm, const User &user)
{
    return strm << "Username: " << user.username << ", Privilege: " << user.privilege_type << ", Credit: " << fixed << setprecision(2) << user.credit << endl;
}

Item::Item(string item_name, string seller, float winning_bid, int duration)
{
    this->item_name = item_name;
    this->seller = seller;
    this->winning_bid = winning_bid;
    this->duration = duration;
}

Item::Item()
{
    this->item_name = "";
    this->seller = "";
}

// Returns a User object with the specified user's information
// Return a user with fields (username="", privilege_type="", credit=0) if no user exists
User GetUser(string username)
{
    User user = User();
    if (!UsernameExists(username))
    {
        return user;
    }
    string line;
    ifstream input(AppState::getInstance().getUserFile());
    if (input.is_open())
    {
        while (getline(input, line))
        {
            if (username == line.substr(0, 15).erase(line.substr(0, 15).find_last_not_of(' ') + 1, std::string::npos))
            {
                user.username = line.substr(0, 15).erase(line.substr(0, 15).find_last_not_of(' ') + 1, std::string::npos);
                user.privilege_type = line.substr(16, 2);
                user.credit = stof(line.substr(19, 9));
                input.close();
                return user;
            }
        }
    }
    input.close();
    return user;
}

// TODO
// Returns an Item object with the item information
// Returns an empty object with fields (item_name="", sellers="")
Item GetItem(string item_name, string seller)
{
    return Item();
}

// Checks whether the given permission level (2 letter representation)
// is enough for the command (integer representation).
// Returns TRUE if you have the required permission, otherwise FALSE.
// NOTE: Addcredit returns TRUE if the user is an admin, otherwise FALSE.
bool CheckPermission(string permission, int command)
{
    map<string, int> privileges{{"AA", 4}, {"FS", 3}, {"BS", 2}, {"SS", 1}};

    switch (command)
    {
    // Advertise, No Buy Standard Accounts
    case 3:
        if (privileges[permission] == 2)
        {
            return false;
        }
        return true;

    // Bid, No Sell Standard Accounts
    case 4:
        if (privileges[permission] == 1)
        {
            return false;
        }
        return true;

    // Addcredit, Admin vs Normal
    case 6:
        if (privileges[permission] == 4)
        {
            return true;
        }
        return false;

    // Admin, Create, Delete, Refund,
    default:
        if (privileges[permission] < 4)
        {
            return false;
        }
        return true;
    }
}

// Returns TRUE if this is a valid permission, otherwise returns FALSE.
bool ValidatePermission(string permission)
{
    transform(permission.begin(), permission.end(), permission.begin(), ::toupper);
    map<string, int> privileges{{"AA", 4}, {"FS", 3}, {"BS", 2}, {"SS", 1}};
    if (privileges[permission] == 0)
    {
        return false;
    }
    return true;
}

// Returns TRUE if the username exists, otherwise returns FALSE.
bool UsernameExists(string username)
{
    string line;
    ifstream input(AppState::getInstance().getUserFile());
    if (input.is_open())
    {
        while (getline(input, line))
        {
            if (line == "END")
            {
                input.close();
                return false;
            }
            else
            {
                line = line.substr(0, 15).erase(line.substr(0, 15).find_last_not_of(' ') + 1, std::string::npos);
                if (username == line)
                {
                    input.close();
                    return true;
                }
            }
        }
    }
    input.close();
    return false;
}

// TODO
// Returns TRUE if the item name exists, otherwise returns FALSE.
bool ItemExists(string item_name)
{
    return false;
}

// Validates a username based on the requirements
// Returns integer based on validation:
// 0: Valid Username
// 1: Username Too Long
// 2: Username Too Short
// 3: Username Already Exists
int ValidateUsername(string username)
{
    if (username.length() > 15)
    {
        return 1;
    }
    else if (username.length() < 1)
    {
        return 2;
    }
    else if (UsernameExists(username))
    {
        return 3;
    }
    return 0;
}

// Validates an item name based on the requirements
// Returns integer based on validation:
// 0: Valid Item Name
// 1: Item Name Too Long
// 2: Item Name Too Short
int ValidateItemName(string item_name)
{
    if (item_name.length() > 25)
    {
        return 1;
    }
    else if (item_name.length() < 1)
    {
        return 2;
    }
    return 0;
}

// Validates an item name based on the requirements
// Returns integer based on validation:
// 0: Valid Bid
// 1: Bid Is Not Numeric
// 2: Bid Is Negative
// 3: Bid Is Over The Limit of $999.99
int ValidateBid(string bid)
{
    if (!isNumeric(bid))
    {
        return 1;
    }
    else if (stof(bid) < 0)
    {
        return 2;
    }
    else if (stof(bid) > 999.99)
    {
        return 3;
    }
    return 0;
}

// Returns TRUE or FALSE if a string is numeric
bool isNumeric(string input)
{
    for (int i = 0; i < input.length(); i++)
    {
        if (!isdigit(input[i]))
        {
            return false;
        }
    }
    return true;
}

string RemoveLeading(string str, char c){
    return str.erase(0, min(str.find_first_not_of(c), str.length()-1));
}

using CommandFunction = void (*)();

std::map<std::string, CommandFunction> commandMap = {
    {"login", Login},
    // {"create", Create},
    {"logout", Logout},
    // {"delete", Delete},
    // {"advertise", Advertise},
    // {"bid", Bid},
    // {"refund", Refund},
    // {"addcredit", AddCredit},
    {"listbids", ListBids},
    {"listusers", ListUsers}
};

void ProcessCommand(std::string command) {
    transform(command.begin(), command.end(), command.begin(), ::tolower);

    auto it = commandMap.find(command);
    if (it == commandMap.end()) {
        std::cout << "Invalid Command!" << std::endl;
    } else {
        bool loggedIn = AppState::getInstance().isLoggedIn();
        if (!loggedIn && it->first != "login") {
            std::cout << "Please login before using any other command!" << std::endl;
        } 
        else if (loggedIn && it->first == "login") {
            std::cout << "Transaction Failed! Please logout before trying to login again!" << std::endl;
        } 
        else {
            it->second();
        }
    }
}