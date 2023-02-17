#include "logout.h"
#include "../appState/appState.h"
using namespace std;

void Logout()
{   
    AppState appstate = AppState::getInstance();
    fstream file;
    string file_name = "../../res/transaction_";
    
    time_t seconds;

    seconds = time(NULL);

    tm *time_structure = localtime(&seconds);

    string time_string (asctime (time_structure));

    file_name.append(time_string);
    
    file_name.append("_" + appstate.currentUser.username);

    file.open(file_name);
    string transaction_code = "00_"+appstate.currentUser.username + "_" + to_string(appstate.currentUser.credit);
    file << appstate.transactionBuffer << endl;
    file << transaction_code << endl;
    file.close();
    
    appstate.currentUser = User();
    
}