#pragma once
#include <regex>
#include <string>

//The menu to be printed for admin users
#define ADMIN_MENU "\n***MENU***\nlogout - Logout\n"         \
				   "delete - Delete User Account\n"          \
				   "create - Create New Account\n"           \
				   "advertise - Put up item for Auction\n"   \
				   "bid - Make a bid on an available item\n" \
				   "refund - Issue a refund\n"               \
				   "addcredit - Add Credit\n"                \
				   "accounts - Display all active accounts\n"  \
				   "listitems - List Items Up For Auction\n"   \
                   "changepassword - Change Your Password\n"

//The menu to be printed for Full Standard users
#define FULL_STANDARD_MENU "\n***MENU***\nlogout - Logout\n"         \
						   "advertise - Put up item for Auction\n"   \
						   "bid - Make a bid on an available item\n" \
						   "addcredit - Add Credit\n"                \
				   		   "accounts - Display all active accounts\n"  \
						   "listitems - List Items Up For Auction\n" \
                             "changepassword - Change Your Password\n"

//The menu to be printed for Sell Standard users
#define SELL_STANDARD_MENU "\n***MENU***\nlogout - Logout\n"       \
						   "advertise - Put up item for Auction\n" \
						   "addcredit - Add Credit\n"              \
						   "listitems - List Items Up For Auction\n" \
                             "changepassword - Change Your Password\n"

//The menu to be printed for Buy Standard users
#define BUY_STANDARD_MENU "\n***MENU***\nlogout - Logout\n"         \
						  "bid - Make a bid on an available item\n" \
						  "addcredit - Add Credit\n"                \
						  "listitems - List Items Up For Auction\n" \
                             "changepassword - Change Your Password\n"

#define ACCOUNT_MANAGER_MENU "\n***MENU***\nlogout - Logout\n"         \
				   			 "delete - Delete User Account\n"          \
				   			 "create - Create New Account\n"           \
				   			 "refund - Issue a refund\n"               \
				   			 "addcredit - Add Credit\n"                \
				   			 "accounts - Display all active accounts\n"  \
				   			 "listitems - List Items Up For Auction\n"   \
                             "changepassword - Change Your Password\n"

//The menu to be printed for when program starts
#define LOGIN_MENU "\nPlease enter login to Login.\nlogin - Login\n"

// #define USER_ACCOUNTS_FILE "UserAccountsFile.txt"
// #define AVAILABLE_ITEMS_FILE "AvailableItemsFile.txt"
// #define TRANSACTION_FILE "DailyTransactionFile.txt"
namespace Util
{
	static inline std::string trim(std::string s)
	{
		return std::regex_replace(s, std::regex("^\\s+|\\s+$"), std::string(""));
	}
}
