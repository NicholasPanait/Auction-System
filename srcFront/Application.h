#pragma once
#include "User.h"
#include "Transaction.h"
#include "Util.h"

/*
 * The application class is responsible for starting the program and running it in 
 * the console. It welcomes the user, prints the appropriate menu based on user 
 * type, and gets the input code for the transaction that they wish to conduct.
 */
class Application
{
private:
	User user;
	bool running = false;

	void displayMenu(); //displays the appropriate menu based on user type
	void handleInput(std::string in); //handles the transaction code input from user

public:
	Application(){}; //constructor of Application class
	~Application(){}; //destructor for application class
	void start(char **argv); //start function that starts the program
};
