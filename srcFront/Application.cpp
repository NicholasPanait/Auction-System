#include "Application.h"

/*
 * The following method gets the user type from the user that is currently 
 * logged in and displays the appropriate menu based on user type.
 */

void Application::displayMenu()
{
	//based on user type, print out the appropriate menu to the console
	switch (this->user.getType())
	{
	case UserType::AA: //if user type is AA (admin)
		std::cout << ADMIN_MENU;
		break;
	case UserType::FS: //if user type is FS (full-standard)
		std::cout << FULL_STANDARD_MENU;
		break;
	case UserType::SS: //if user type is SS (sell-standard)
		std::cout << SELL_STANDARD_MENU;
		break;
	case UserType::BS: //if user type is BS (buy-standard)
		std::cout << BUY_STANDARD_MENU;
		break;
	case UserType::NONE: //if user type is not available (is NONE), the user should proceed to login
		std::cout << LOGIN_MENU;
		break;
	}
}

/*
 * The following method gets the user’s input for the transaction they want to do, and validates that 
 * the user’s input is one of the available transaction options. If the user’s input is incorrect 
 * (i.e. transaction code is wrong), then the appropriate error message is printed.
 *
 * @param in - the input value for the transaction code 
 */
void Application::handleInput(std::string in)
{
	std::map<std::string, std::function<bool(User *)>> res;

	switch (this->user.getType())
	{
	case UserType::AA:
		res = Transaction::getAdminMapping();  //get the menu options for an AA user
		break;
	case UserType::FS:
		res = Transaction::getFullStandardMapping(); //get the menu options for a FS user
		break;
	case UserType::BS:
		res = Transaction::getBuyStandardMapping(); //get the menu options for a SS user
		break;
	case UserType::SS:
		res = Transaction::getSellStandardMapping(); //get the menu options for a BS user
		break;
	case UserType::NONE:
		res = Transaction::getLoginMapping(); //get the menu option for login(the only option that should work if user is not logged in
		break;
	}

	/*try to find the user's inputted transaction code in the appropriate user's 
	menu. If the transaction code is not found in the menu, print an error message 
	indicating that the inputted transaction code is invalid. */
	auto feature = res.find(in);
	if (feature != res.end())
		feature->second(&this->user);
	else
		std::cout << "\nInvalid transaction code.\n";
}

/*
 * The following method starts off the program by printing the welcome 
 * message, and calling the required methods to display the appropriate 
 * menu and getting the transaction code from the user for the transaction 
 * they wish to do.
 */
void Application::start()
{
	std::cout << "Welcome to the Online Auction Sales Service!\n";
	running = true;
	std::string menuInput;

	while (running)
	{
		displayMenu();
		std::cin >> menuInput;
		handleInput(menuInput);
	}
}
