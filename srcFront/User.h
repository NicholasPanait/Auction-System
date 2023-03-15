#pragma once
#include <iostream>
#include <map>
#include <string.h>

/* An enum for all the user types */
enum UserType
{
	AA,
	FS,
	BS,
	SS,
	NONE,
};

/* Description: The User class is used to construct each user object, and 
*  manage its current status to determine whether or not it is currently logged in.
*/
class User
{
private:
	//member attributes of the User class
	UserType userType;
	std::string username;
	double availableCredit;
	bool loggedIn;

public:
	User(); //The constructor method for a user object
	~User(); //The destructor method for a user object

	bool login(const char* username, const char* password);
	bool logout();
	UserType getType() { return userType; } //gets and returns the user type for the current user
	std::string getUsername() { return username; }

	static std::string getTypeName(UserType userType);
	static std::string getTypeCode(UserType userType);
	static UserType getUserType(const char* typeCode);
};
