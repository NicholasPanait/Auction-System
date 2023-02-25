#include "login.h"

/**
 * Function to handle parameters and appState updates for the login command
 * NOTE: Only usable when not logged in
 */

void Login()
{
	string username;

	cout << "Please enter a username:" << endl;
    cin.ignore();
    getline(cin, username);

	User user = GetUser(username);

	if (user.username.empty())
	{
		cout << "Transaction Failed! User does not exist!" << endl;
		return;
	}

	AppState::getInstance().setCurrentUser(user);

	cout << "Welcome " << user.username << ", your current balance is $" << fixed << setprecision(2) << user.credit << endl;
}