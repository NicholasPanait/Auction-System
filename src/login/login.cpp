#include "login.h"
#include "../appState/appState.h"
using namespace std;
//TODO: finish login command
void Login()
{
	AppState appState = AppState::getInstance();
	string username;
	
	cout << "Please enter a username:" << endl;
	cin >> username;

	User user = GetUser(username);

	if (user.username.empty())
	{
		cout << "Transaction Failed !User does not exist!" << endl;
		return;
	}

	appState.getCurrentUser() = user;

	cout << "Welcome " << user.username << ", your current balance is $" << fixed << setprecision(2) << user.credit << endl;
}