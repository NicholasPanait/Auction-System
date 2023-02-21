#ifndef APPSTATE_H
#define APPSTATE_H

#include "../utility/utility.h"
#include <string>
using namespace std;

// forward declaration
class User;

// Singleton class that contains all the current state information for the app
class AppState {
public:
  static AppState& getInstance(); // make this return a reference

  bool isLoggedIn();
  User& getCurrentUser(); // return a reference to User
  string getTransactionBuffer() const; // make this method const

private:
  static AppState* instance;
  AppState(); // make the constructor private

  User* currentUser;
  string transactionBuffer;
  string itemFile;
  string accountFile;
  string outputDirectory;
};

#endif