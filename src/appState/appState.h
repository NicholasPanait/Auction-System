#ifndef APPSTATE_H
#define APPSTATE_H

#include "../utility/utility.h"
#include <string>
using namespace std;

// forward declaration
class User;

// Singleton class that contains all the current state information for the app
class AppState
{
public:
    static AppState &getInstance(); // make this return a reference

    bool isLoggedIn();
    User &getCurrentUser();              // return a reference to User
    string getTransactionBuffer() const; // make this method const
    string getUserFile() const;          // make this method const
    string getItemFile() const;          // make this method const
    string getOutputDirectory() const;   // make this method const
    void setCurrentUser(User user);
    void resetCurrentUser();
    void appendTransactionBuffer(string transaction);
    void setUserFile(string file);
    void setItemFile(string file);
    void setOutputDirectory(string directory);

private:
    AppState(); // make the constructor private

    User *currentUser;
    string transactionBuffer;
    string itemFile;
    string userFile;
    string outputDirectory;
};

#endif