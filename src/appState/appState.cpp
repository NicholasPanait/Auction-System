#include "appState.h"

using namespace std;

//returns the current singleton instance, grantees that there is only every one instance
AppState &AppState::getInstance(){
	static AppState INSTANCE;
	return INSTANCE;
}

//Singleton constructor, should only every be called by getInstance()
AppState::AppState(){
	this->currentUser = User();
	this->transactionBuffer = "";
}

bool AppState::isLoggedIn(){
	if (&(this->currentUser) == nullptr){
		this->currentUser = User();
		return false;
	}else if(this->currentUser.username.empty()){
		return false;
	}

	return true;
}