#include "logout.h"
#include "../appState/appState.h"
using namespace std;

void Logout()
{   
    fstream file;
    string file_name = AppState::getInstance().getOutputDirectory();
    
    time_t seconds;

    seconds = time(NULL);

    tm *time_structure = localtime(&seconds);

    string time_string (asctime (time_structure));

    file_name.append(time_string);
    
    file_name.append("_" + AppState::getInstance().getCurrentUser().username);

    file.open(file_name);
    string transaction_code = "00_"+AppState::getInstance().getCurrentUser().username + "_" + to_string(AppState::getInstance().getCurrentUser().credit);
    file << AppState::getInstance().getTransactionBuffer() << endl;
    file << transaction_code << endl;
    file.close();
    
    AppState::getInstance().resetCurrentUser();
    cout << "Session terminated, transaction saved" << endl;
}