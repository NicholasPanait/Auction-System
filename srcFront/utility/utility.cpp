#include "utility.h"

// NOTE: This file contains helper functions used by at least 2 files in the front end

/**
 * The class used to store user information
 * e.g. their Username, Available Credit, and Privilege Type
 *
 * @param username          The user's username
 * @param privilege_type    The privilege type of the user
 * @param credit            The available credit of the user
 */
User::User(string username, string privilege_type, double credit, int password)
{
    this->username = username;
    this->privilege_type = privilege_type;
    this->credit = credit;
    this-> pending_credit = 0;
    this->password = password;
}

/**
 * An empty User constructor passed when bad input is given and/or
 * a user can not be found in the User File
*/
User::User()
{
    this->username = "";
    this->privilege_type = "";
    this->credit = 0;
    this->pending_credit = 0;
    this->password = -1;
}

/**
 * Operator overload for debugging with cout
 *
 * @param strm     The output stream
 * @param user     The user who's information is being outputted
 */
ostream &operator<<(ostream &strm, const User &user)
{
    return strm << "Username: " << user.username << ", Privilege: " << user.privilege_type << ", Credit: " << fixed << setprecision(2) << user.credit << endl;
}

/**
 * The class used to store item information
 * e.g. the Item Name, Seller Username, Auction Duration, Minimum Bid, and Current Highest Bid
 *
 * @param item_name     The item ame
 * @param seller        The seller's username
 * @param duration      The auction's duration in days
 * @param minimum_bid   The starting bid
 * @param highest_bid   The current highest bid
 */
Item::Item(string item_name, string seller, int duration, double minimum_bid, double highest_bid)
{
    this->item_name = item_name;
    this->seller = seller;
    this->duration = duration;
    this->minimum_bid = minimum_bid;
    this->highest_bid = highest_bid;
}

/**
 * An empty Item constructor passed when bad input is given and/or
 * a user can not be found in the User File
 */
Item::Item()
{
    this->item_name = "";
    this->seller = "";
    this->duration = 0;
    this->minimum_bid = 0.0;
    this->highest_bid = 0.0;
}

/**
 * Removes all leading specified characters
 *
 * @param str   The sttring to erase leading characters from
 * @param c     The character to remove from the string
 * @return      The new string, after the leading specified characters have been removed
*/
string RemoveLeading(string str, char c){
    return str.erase(0, min(str.find_first_not_of(c), str.length()-1));
}

/**
 * Removes all trailing specified characters
 *
 * @param str   The string to erase leading characters from
 * @param c     The character to remove from the string
 * @return      The new string, after the trailing specified characters have been removed
*/
string RemoveTrailing(string str, char c){
    return str.erase(str.find_last_not_of(c)+1, str.length());
}


/**
 * Returns a User object with the specified user's information
 * Return a user with fields (username="", privilege_type="", credit=0) if no user exists
 * 
 * @param username  The username to get from the UserFile
 * @return          A User, with parameters filled in from the UserFile
*/
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

                user.credit = stod(line.substr(19, 9));

                user.password = 0;
                string pass = RemoveTrailing(line.substr(29, 10), ' ');
                for (int i = 0; i < pass.length(); i++) {
                    user.password = user.password * 10 + (pass[i] - '0');
                }
                input.close();
                return user;
            }
        }
    }
    input.close();
    return user;
}

/**
 * Returns an Item object with the item information
 * Returns an empty object with fields (item_name="", sellers="")
 * 
 * @param item_name     The item name to get from the ItemFile
 * @param seller        The seller of the item
 * @return              An Item, with parameters filled in from the ItemFile
*/
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
            if (item_name == RemoveTrailing(line.substr(0, 25), ' ') && seller == RemoveTrailing(line.substr(26, 15), ' '))
            {
                item.item_name = RemoveTrailing(line.substr(0, 25), ' ');
                item.seller = RemoveTrailing(line.substr(26, 15), ' ');
                try {
                    item.duration = stoi(RemoveLeading(line.substr(58, 3), '0'));
                    if (RemoveLeading(line.substr(58, 6), '0')[0] == '.'){
                        item.minimum_bid = stod("0" + RemoveLeading(line.substr(62, 6), '0'));
                    }
                    else{
                        item.minimum_bid = stod(RemoveLeading(line.substr(62, 6), '0'));
                    }
                    if (RemoveLeading(line.substr(69, 6), '0')[0] == '.'){
                        item.highest_bid = stod("0" + RemoveLeading(line.substr(69, 6), '0'));
                    }
                    else{
                        item.highest_bid = stod(RemoveLeading(line.substr(69, 6), '0'));
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

/**
 * Checks whether the given permission level (2 letter representation)
 * is enough for the command (integer representation).
 * Returns TRUE if you have the required permission, otherwise FALSE.
 * 
 * @param permission    Account Type (2 characters)
 * @param command       The command to verify
 * @return              Returns true if the command is allowed for the account type
*/
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

/**
 * This function checks if the account type exists (AA,FS,BS,SS)
 * 
 * @param permission    Account Type (2 characters)
 * @return              Returns TRUE if this is a valid permission, otherwise returns FALSE.
*/
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

/**
 * This function checks if the Username exists in the UserFile
 * 
 * @param username      The username to check
 * @return              Returns TRUE if the username exists, otherwise returns FALSE.
*/
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
/**
 * @brief tests if the string can be parsed into a float
 * 
 * @param myString 
 * @return true 
 * @return false 
 */
bool isFloat(string myString)
{
    std::istringstream iss(myString);
    float f;
    iss >> noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

/**
 * This function checks if the Item exists in the ItemFile
 * 
 * @param Item_name     The item to check
 * @return              Returns TRUE if the item name exists, otherwise returns FALSE.
*/
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
                line = RemoveTrailing(line.substr(0, 25), ' ');
                item_name = RemoveTrailing(line.substr(0, 25), ' ');
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


/**
 * Validates a username based on the requirements
 * 
 * @param username      The username to check
 * @return              Integer based on validation:
 *                          0: Valid Username
 *                          1: Username Too Long
 *                          2: Username Too Short
 *                          3: Username Already Exists
*/
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

/**
 * Validates an item name based on the requirements
 * 
 * @param item_name     The item to check
 * @return              Integer based on validation:
 *                          0: Valid Item Name
 *                          1: Item Name Too Long
 *                          2: Item Name Too Short
*/
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
    else if (ItemExists(item_name)){
        return 3;
    }
    return 0;
}

/**
 * Validates an item name based on the requirements
 * 
 * @param bid   The bid to check
 * @return      Integer based on validation:
 *                  0: Valid Bid
 *                  1: Bid Is Not Numeric
 *                  2: Bid Is Negative
 *                  3: Bid Is Over The Limit of $999.99
*/
int ValidateBid(string bid)
{
    try {
        if (!isFloat(bid)){
            return 1;
        }
        if (stod(bid) < 0.01)
        {
            return 2;
        }
        else if (stod(bid) > 999.99)
        {
            return 3;
        }
    } catch(exception e){
        return 1;
    }
    return 0;
}

/**
 * This function checks if a given input can become a number
 * 
 * @param input     The input to check
 * @return          Returns TRUE or FALSE depending if a string is numeric
*/
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

// This map stores the functions to call, used in ProcessCommand below
map<string, CommandFunction> commandMap = {
    {"login", Login},
    {"create", Create},
    {"logout", Logout},
    {"delete", Delete},
    {"advertise", Advertise},
    {"bid", Bid},
    {"refund", Refund},
    {"addcredit", AddCredit},
    {"listbids", ListBids},
    {"listusers", ListUsers},
    {"setpassword", SetPassword}
};

/**
 * This function is called from the while loop within frontend.cpp
 * The purpose of this function is run the function for a specified command
 * If a user enters the command login, the login function will be called for example
 * If a user tries to login while they are already logged in, they will be alerted, and the command will not go thorugh
 * Similarly if a user tries to log out while they are not logged in, they will be alerted, and the command will not go through
 * 
 * @param command   The command to run
*/
void ProcessCommand(string command) {
    transform(command.begin(), command.end(), command.begin(), ::tolower);

    auto it = commandMap.find(command);
    if (it == commandMap.end()) {
        cout << "Invalid Command!" << std::endl;
    } else {
        bool loggedIn = AppState::getInstance().isLoggedIn();
        if (!loggedIn && it->first != "login") {
            cout << "Please login before using any other command!" << std::endl;
        } 
        else if (loggedIn && it->first == "login") {
            cout << "Transaction Failed! Please logout before trying to login again!" << std::endl;
        } 
        else {
            it->second();
        }
    }
}