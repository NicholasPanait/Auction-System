#ifndef APPSTATE_H
#define APPSTATE_H

#include "../utility/utility.h";
#include <string>
using namespace std;

//Singleton class that contains all the current state information for the app
class AppState{
	public:
	static AppState getInstance();
	
	bool isLoggedIn();
	User currentUser;
	string transactionBuffer;

	private:
	static AppState instance;
	AppState();
};

#endif