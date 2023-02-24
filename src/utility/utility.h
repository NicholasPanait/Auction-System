
/*
This header file contains utility functions that
are used by files for at least 2 commands
*/

#ifndef UTILITY_H // include guard
#define UTILITY_H

#include "../login/login.h"
#include "../logout/logout.h"
#include "../bid/bid.h"
#include "../addcredit/addcredit.h"
#include "../listusers/listusers.h"
#include "../listbids/listbids.h"
#include "../appState/appState.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <fstream>
#include <string>

using namespace std;

class User{
    public:
        string username;
        string privilege_type;
        float credit;
        User(string username, string privilege_type, float credit);
        User();
        friend ostream &operator<<(ostream &strm, const User &user);
};

class Item {
    public:
        string item_name;
        string seller;
        float highest_bid;
        int duration;
        float minimum_bid;
        Item(string item_name, string seller, int duration, float minimum_bid, float highest_bid);
        Item();
};

// Removes all leading specified characters
string RemoveLeading(string str, char c);

// Removes all trailing specified characters
string RemoveTrailing(string str, char c);

// Returns a User object with the specified user's information
// Return a user with fields (username="", privilege_type="", credit=0) if no user exists
User GetUser(string username);

// TODO 
// Returns an Item object with the item information
// Returns an empty object with fields (item_name="", sellers="")
Item GetItem(string item_name, string seller);

// Returns TRUE if the given permission is enough for the command
bool CheckPermission(string permission, string command);

// Returns TRUE if this is a valid permission, otherwise returns FALSE.
bool ValidatePermission(string permission);


// Returns TRUE if the username exists, otherwise returns FALSE.
bool UsernameExists(string username);

// TODO
// Returns TRUE if the item name exists, otherwise returns FALSE.
bool ItemExists(string item_name);

// Validates a username based on the requirements
// Returns integer based on validation:
// 0: Valid Username
// 1: Username Too Long
// 2: Username Too Short
// 3: Username Already Exists
int ValidateUsername(string username);

// Validates an item name based on the requirements
// Returns integer based on validation:
// 0: Valid Item Name
// 1: Item Name Too Long
// 2: Item Name Too Short
int ValidateItemName(string item_name);

// Validates an item name based on the requirements
// Returns integer based on validation:
// 0: Valid Bid
// 1: Bid Is Not Numeric
// 2: Bid Is Negative
// 3: Bid Is Over The Limit of $999.99
int ValidateBid(string bid);

// Returns TRUE or FALSE if a string is numeric
bool isNumeric(string input);

// Calls respective commands and handles invalid commands
void ProcessCommand(string command);
#endif