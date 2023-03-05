#include "create.h"

/**
 * Function to handle parameters and transaction code generation
 * for the create command which is responsible for creating new
 * users in the system
 * NOTE: Only usable by Admins
 */

void Create()
{
    if (CheckPermission(AppState::getInstance().getCurrentUser().privilege_type, "create"))
    {
        string username;
        string permission;
        string password;
        int password_encrypted = 0;

        cout << "Please enter new user’s username:" << endl;
        cin.ignore();
        getline(cin, username);

        switch (ValidateUsername(username))
        {
        case 1:
            cout << "Please enter a username that is less than 16 characters long" << endl;
            return;
        case 2:
            cout << "Please enter a username that is at least 1 character long" << endl;
            return;
        case 3:
            cout << "Transaction Failed! Username already exists!" << endl;
            return;
        }

        cout << "Please enter the account type:" << endl;
        getline(cin, permission);

        if (!ValidatePermission(permission))
        {
            cout << "Please enter a valid account type (AA,FS,BS,SS)" << endl;
            return;
        }

        cout << "Please enter the password for the account (must be less than 15 characters long):" << endl;
        getline(cin, password);

        for (int i = 0; i < password.size(); i++){
            password_encrypted += int(password[i]);
        }

        // TODO Still need to implement the code to create the account

        string transaction_code = "01 ";

        transaction_code += username;
        for (int i = 0; i < 16 - username.length(); i++)
        {
            transaction_code += ' ';
        }
        transaction_code += permission + " ";
        transaction_code += "000000.00 ";

        transaction_code +=  to_string(password_encrypted);
        transaction_code += "\n";

        AppState::getInstance().appendTransactionBuffer(transaction_code);
        /*
        CREATE Transaction Format: 

        XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC_PPPPPPPPPP
        XX - The 2 Digit Transaction Code
        UUUUUUUUUUUUUUU - The Maximum 15 Character Username
        TT - The 2 Digit Account Type Code of the User
        CCCCCCCCC - The Available Credit of the Account
        PPPPPPPPPP - the password for the account
        _ - Represents a Space

        */
        map<string, string> privileges{{"AA", "Admin"}, {"FS", "Full Standard"}, {"BS", "Buy Standard"}, {"SS", "Sell Standard"}};

               cout << "User \"" << username << "\" will be created upon logout with permission type " 
                    << privileges[permission] << " and a balance of $0 credits." << endl;
    }
    else
    {
        cout << "Transaction Failed! You do not have permission to create new accounts!" << endl;
    }
}