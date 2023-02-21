#include "../appState/appState.h"
#include "../utility/utility.h"

using namespace std;

// initialize the static instance pointer to nullptr
AppState* AppState::instance = nullptr;

// returns the current singleton instance, guarantees that there is only ever one instance
AppState& AppState::getInstance(){
  if(AppState::instance == nullptr){
    AppState::instance = new AppState();
  }
  return *AppState::instance;
}

// Singleton constructor, should only ever be called by getInstance()
AppState::AppState(){
  this->currentUser = nullptr;
  this->transactionBuffer = "";
}

bool AppState::isLoggedIn(){
  return (this->currentUser != nullptr);
}

User& AppState::getCurrentUser(){
  if (this->currentUser == nullptr) {
    this->currentUser = new User();
  }
  return *this->currentUser;
}

string AppState::getTransactionBuffer() const {
  return this->transactionBuffer;
}
