#pragma once
#include <functional>

#include "TransactionFile.h"
#include "UserAccountsFile.h"
#include "AvailableItemsFile.h"
#include "User.h"

/* Description: The transaction class is used to manage and carry out all the 
* transactions that can be done by a user.
*/
class Transaction
{
public:
	//function declarations for each of the transactions
	static bool login(User *user);
	static bool logout(User *user);
	static bool createUser(User *user);
	static bool deleteUser(User *user);
	static bool advertise(User *user);
	static bool bid(User *user);
	static bool refund(User *user);
	static bool addcredit(User *user);
	static bool listitems(User *user);
	static bool outputAllActiveAccounts(User *user);

	//function declaration for the transaction options that are available for each user type
	static std::map<std::string, std::function<bool(User *)>> getAdminMapping();
	static std::map<std::string, std::function<bool(User *)>> getFullStandardMapping();
	static std::map<std::string, std::function<bool(User *)>> getSellStandardMapping();
	static std::map<std::string, std::function<bool(User *)>> getBuyStandardMapping();
	
	//function declaration for the options that are available to the user at the start of the program(only login is available)
	static std::map<std::string, std::function<bool(User *)>> getLoginMapping();
};
