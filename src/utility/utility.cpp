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

Item::Item(string item_name, string seller, int duration, float minimum_bid, float highest_bid)
{
    this->item_name = item_name;
    this->seller = seller;
    this->duration = duration;
    this->minimum_bid = minimum_bid;
    this->highest_bid = highest_bid;
}

Item::Item()
{
    this->item_name = "";
    this->seller = "";
    this->duration = 0;
    this->minimum_bid = 0.0;
    this->highest_bid = 0.0;
}

// TODO Format Item Text For ItemFile
// ostream &operator<<(ostream &strm, const Item &item)
// {
//     return strm 
//     << item.item_name
//     << item.seller 
//     << item.duration 
//     << item.minimum_bid 
//     << item.highest_bid 
//     << endl;
// }

// Removes all leading specified characters
string RemoveLeading(string str, char c){
    return str.erase(0, min(str.find_first_not_of(c), str.length()-1));
}

// Removes all trailing specified characters
string RemoveTrailing(string str, char c){
    return str.erase(str.find_last_not_of(c)+1, str.length());
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
            if (username == RemoveTrailing(line.substr(0, 15), ' '))
            {
                user.username = RemoveTrailing(line.substr(0, 15), ' ');
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
    Item item = Item();
    if (!ItemExists(item_name))
    {
        return item;
    }
    string line;
    ifstream input(AppState::getInstance().getItemFile());
    if (input.is_open())
    {
        while (getline(input, line))
        {
            if (item_name == RemoveTrailing(line.substr(0, 19), ' '))
            {
                item.item_name = RemoveTrailing(line.substr(0, 19), ' ');
                item.seller = RemoveTrailing(line.substr(20, 15), ' ');
                try {
                    item.duration = stoi(RemoveLeading(line.substr(52, 3), '0'));
                    if (RemoveLeading(line.substr(56, 6), '0')[0] == '.'){
                        item.minimum_bid = stof("0" + RemoveLeading(line.substr(56, 6), '0'));
                    }
                    else{
                        item.minimum_bid = stof(RemoveLeading(line.substr(56, 6), '0'));
                    }
                    if (RemoveLeading(line.substr(63, 6), '0')[0] == '.'){
                        item.highest_bid = stof("0" + RemoveLeading(line.substr(63, 6), '0'));
                    }
                    else{
                        item.highest_bid = stof(RemoveLeading(line.substr(63, 6), '0'));
                    }
                } catch(const exception &e){
                    cerr << e.what() << endl;
                    cout << "Item/Seller combination incorrect" << endl;
                    return item;
                }
                input.close();
                return item;
            }
        }
    }
    input.close();
    return item;
}

// Checks whether the given permission level (2 letter representation)
// is enough for the command (integer representation).
// Returns TRUE if you have the required permission, otherwise FALSE.
// NOTE: Addcredit returns TRUE if the user is an admin, otherwise FALSE.
bool CheckPermission(string permission, string command)
{
    map<string, int> privileges{{"AA", 4}, {"FS", 3}, {"BS", 2}, {"SS", 1}};

    // Advertise, No Buy Standard Accounts
    if (command == "advertise"){
        if (privileges[permission] == 2)
        {
            return false;
        }
        return true;
    }

    // Bid, No Sell Standard Accounts
    else if (command == "bid"){
        if (privileges[permission] == 1)
        {
            return false;
        }
        return true;
    }

    // Addcredit, Admin vs Normal
    else if (command == "addcredit"){
        if (privileges[permission] == 4)
        {
            return true;
        }
        return false;
    }

    // Admin, Create, Delete, Refund,
    else{
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
                line = RemoveTrailing(line.substr(0, 15), ' ');
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

// Returns TRUE if the item name exists, otherwise returns FALSE.
bool ItemExists(string item_name)
{
    string line;
    ifstream input(AppState::getInstance().getItemFile());
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
                line = RemoveTrailing(line.substr(0, 19), ' ');
                if (item_name == line)
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
// TODO EITHER 19 MAX or 25 MAX FOR ITEM NAME
int ValidateItemName(string item_name)
{
    if (item_name.length() > 19)
    {
        return 1;
    }
    else if (item_name.length() < 1)
    {
        return 2;
    }
    else if (ItemExists(item_name)){
        return 3;
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

// Processes commands and bad input
using CommandFunction = void (*)();

std::map<std::string, CommandFunction> commandMap = {
    {"login", Login},
    // {"create", Create},
    {"logout", Logout},
    // {"delete", Delete},
    // {"advertise", Advertise},
    {"bid", Bid},
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