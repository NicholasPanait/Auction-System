#include "setpassword.h"

void SetPassword(){

    string password;
    int password_encrypted = 0;
    string transaction = "07 ";
    User user = AppState::getInstance().getCurrentUser();
    cin.ignore();
    cout << "please enter a new password (less than 15 characters)" << endl;

    getline(cin, password);
    if (password.length() > 15){
        cout << "password must be less than 16 characters long" << endl;
        return;
    } else if (password.length() < 1){
        cout <<  "password must be at least 1 character long" << endl;
        return;
    }

    for (int i = 0; i < password.size(); i++){
        password_encrypted += int(password[i]);
    }

    transaction += user.username;
    for (int i = 0; i < 16 - user.username.length(); i++)
    {
        transaction += ' ';
    }
    transaction += user.privilege_type + " ";

    transaction += to_string(password_encrypted);
    cout << "password set, new password will be in use tomorrow." << endl;
    AppState::getInstance().appendTransactionBuffer(transaction);
    
}