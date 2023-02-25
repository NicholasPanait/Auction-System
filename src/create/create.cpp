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
            cout << "Username already exists" << endl;
            return;
        }

        cout << "Please enter the account type:" << endl;
        getline(cin, permission);

        if (!ValidatePermission(permission))
        {
            cout << "Please enter a valid account type (AA,FS,BS,SS)" << endl;
            return;
        }

        // TODO Still need to implement the code to create the account

        string transaction_code = "01 ";

        transaction_code += username;
        for (int i = 0; i < 16 - username.length(); i++)
        {
            transaction_code += ' ';
        }
        transaction_code += permission + " ";
        transaction_code += "000000.00\n";

        AppState::getInstance().appendTransactionBuffer(transaction_code);
        /*
        CREATE Transaction Format: 

        XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC
        XX - The 2 Digit Transaction Code
        UUUUUUUUUUUUUUU - The Maximum 15 Character Username
        TT - The 2 Digit Account Type Code of the User
        CCCCCCCCC - The Available Credit of the Account
        _ - Represents a Space

        */
        map<string, string> privileges{{"AA", "Admin"}, {"FS", "Full Standard"}, {"BS", "Buy Standard"}, {"SS", "Sell Standard"}};

               cout << "User " << username << " will be created upon logout with permission type " 
                    << privileges[permission] << " and a balance of $0 credits." << endl;
    }
    else
    {
        cout << "Transaction Failed! You do not have permission to create new accounts!";
    }
}