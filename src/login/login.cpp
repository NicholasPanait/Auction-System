#include "login.h"

/**
 * Function to handle parameters and appState updates for the login command
 * NOTE: Only usable when not logged in
 */

void Login()
{
	string username;
	string password;
	int pass_total = 0;

	cout << "Please enter a username:" << endl;
    cin.ignore();
    getline(cin, username);

	User user = GetUser(username);

	if (user.username.empty())
	{
		cout << "Transaction Failed! User does not exist!" << endl;
		return;
	}

	cout << "Please enter the password:" << endl;
    getline(cin, password);
	for (int i = 0; i < password.length();i++){
		pass_total += int(password[i]);
	}
	if (pass_total != user.password){
		user = User();
		
		cout << "Transaction Failed! Incorrect Password!" << endl;
		return;
	}

	AppState::getInstance().setCurrentUser(user);

	cout << "Welcome " << user.username << ", your current balance is $" << fixed << setprecision(2) << user.credit << endl;
}
