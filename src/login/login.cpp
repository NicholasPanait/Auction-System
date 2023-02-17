#include "login.h"
using namespace std;
void Login()
{
	string username;
	cout << "Please enter a username:";
	cin >> username;

	User user = GetUser(username);

	if (user.username.empty())
	{
		cout << "Transaction Failed !User does not exist !" << endl;
		return;
	}

	cout << "Welcome " << user.username << ", your current balance is $" << fixed << setprecision(2) << user.credit << endl;
}