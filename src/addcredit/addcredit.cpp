#include "addcredit.h"

/**
 * This function handles the input and transaction code generation for
 * the addcredit command responsible for adding credit to accounts
 */
// NOTE: If used by an Admin account, credit can be added to accounts other than your own

void AddCredit()
{
    bool is_privilleged = CheckPermission(AppState::getInstance().getCurrentUser().privilege_type, "addcredit");
    string username = AppState::getInstance().getCurrentUser().username;
    string amount;
    cout << "Please select an amount of credits to add (max of $1000):" << endl;
    cin >> amount;

    switch (ValidateBid(amount))
    {
    case 1:
        cout << "Please enter a credit amount that is numeric!" << endl;
        return;
    case 2:
        cout << "Please enter a credit amount that is positive!" << endl;
        return;
    case 3:
        if (amount != "1000"){
            cout << "Please enter a credit amount that is less than $1000 credits!" << endl;
            return;
        }
    }

    if (is_privilleged)
    {
        cout << "Please select a user to add credits to:" << endl;
        cin.ignore();
        getline(cin, username);
    }

    switch (ValidateUsername(username))
    {
    case 1:
        cout << "Please enter a username that is less than 16 characters long!" << endl;
        return;
    case 2:
        cout << "Please enter a username that is at least 1 character long!" << endl;
        return;
    }
    if (!(UsernameExists(username)))
    {
        cout << "Transaction Failed! User does not exist!" << endl;
        return;
    }

    if (is_privilleged){
        if (stod(amount) + GetUser(username).credit > 999999.99){
            cout << "Transaction Failed! A User cannot exceed $999999.99!" << endl;
            return;
        }
    }
    else{
        if (stod(amount) + AppState::getInstance().getCurrentUser().credit > 999999.99){
            cout << "Transaction Failed! A User cannot exceed $999999.99!" << endl;
            return;
        }
    }
    double addedCredit = AppState::getInstance().getAddedCredit();
    if (stod(amount) + addedCredit > 1000){
        cout << "Transaction Failed! You may not add more than $1000 in a session!" << endl;
        return;
    }
    AppState::getInstance().addCredit(stod(amount));

    string transaction_code = "06 ";

    transaction_code += username;
    for (int i = 0; i < 16 - username.length(); i++)
    {
        transaction_code += ' ';
    }
    if (is_privilleged){
        transaction_code += GetUser(username).privilege_type + ' ';
    }
    else{
        transaction_code += AppState::getInstance().getCurrentUser().privilege_type + ' ';
    }

    stringstream stream;
    if (is_privilleged){
        stream << fixed << setprecision(2) << GetUser(username).credit + stod(amount);
    }
    else{
        stream << fixed << setprecision(2) << AppState::getInstance().getCurrentUser().credit + stod(amount);
    }
    string new_amount = stream.str();

    for (int i = 0; i < (9 - new_amount.length()); i++)
    {
        transaction_code += '0';
    }
    transaction_code += (new_amount + "\n");
    AppState::getInstance().appendTransactionBuffer(transaction_code);

    cout << "$" << amount << " credits have been successfully added to: \"" << username << "\"" << endl;
}