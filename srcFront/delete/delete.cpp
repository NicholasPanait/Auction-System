#include "delete.h"

/**
 * Function to handle parameters and transaction code generation
 * for the delete command which is responsible for deleting users
 * in the system
 * NOTE: Only usable by Admins
 */

void Delete()
{
    if (CheckPermission(AppState::getInstance().getCurrentUser().privilege_type, "delete"))
    {
        string username;
        cout << "Please enter the user to delete:" << endl;
        cin.ignore();
        getline(cin, username);

        switch (ValidateUsername(username))
        {
        case 0:
            cout << "Transaction Failed! The user \"" << username << "\" does not exist!" << endl;
            return;
        case 1:
            cout << "Please enter a username that is less than 16 characters long!" << endl;
            return;
        case 2:
            cout << "Please enter a username that is at least 1 character long!" << endl;
            return;
        }

        if (username == AppState::getInstance().getCurrentUser().username){
            cout << "Transaction Failed! You can not delete yourself!" << endl;
            return;
        }

        // TODO Still need to implement the code to create the account

        string transaction_code = "02 ";

        transaction_code += username;
        for (int i = 0; i < 16 - username.length(); i++)
        {
            transaction_code += ' ';
        }
        transaction_code += GetUser(username).privilege_type + " ";
        
        stringstream stream;
        stream << fixed << setprecision(2) << GetUser(username).credit;
        string credit = stream.str();

        for (int i = 0; i < (9 - credit.length()); i++)
        {
            transaction_code += '0';
        }
        transaction_code += credit + "\n";

        AppState::getInstance().appendTransactionBuffer(transaction_code);
        /*
        DELETE Transaction Format:

        XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC
        XX - The 2 Digit Transaction Code
        UUUUUUUUUUUUUUU - The Maximum 15 Character Username
        TT - The 2 Digit Account Type Code of the User
        CCCCCCCCC - The Available Credit of the Account
        _ - Represents a Space
        */

        cout << "User \"" << username << "\" will be deleted upon logout" << endl;
    }
    else
    {
        cout << "Transaction Failed! You do not have permission to delete accounts!" << endl;
    }
}