#include "refund.h"

//TODO: implement refund so it takes money from one account and transfers it to another
void Refund(){
    if (CheckPermission(AppState::getInstance().getCurrentUser().privilege_type, "refund"))
    {
        string buyer;
        string seller;
        string refund_amount;
        cout << "Please enter the buyer's username:" << endl;
        cin >> buyer; // TODO change so that it reads the entire line

        switch (ValidateUsername(buyer))
        {
        case 0:
            cout << "Please enter an existing username" << endl;
            return;
        case 1:
            cout << "Please enter a username that is less than 16 characters long" << endl;
            return;
        case 2:
            cout << "Please enter a username that is at least 1 character long" << endl;
            return;
        }

        cout << "Please enter the seller's username:" << endl;
        cin >> seller; // TODO change so that it reads the entire line

        switch (ValidateUsername(seller))
        {
        case 0:
            cout << "Please enter an existing username" << endl;
            return;
        case 1:
            cout << "Please enter a username that is less than 16 characters long" << endl;
            return;
        case 2:
            cout << "Please enter a username that is at least 1 character long" << endl;
            return;
        }

        cout << "Please enter the refund amount:" << endl;
        cin >> refund_amount; // TODO change so that it reads the entire line
        
        float refund;
        try{
            refund = stof(refund_amount);
            if (refund <= 0){
                cout << "Transaction Failed! Refund amount must be more than 0 credits!" << endl;
                return;
            }
            if (GetUser(seller).credit < refund){
                cout << GetUser(seller).username << " does not have enough credit to refund" << endl;
                return;
            }
            else if ((GetUser(buyer).credit + refund) > 999999.00){
                cout << "Refund cancelled, this refund would put " << GetUser(buyer).username << " over the credit limit" << endl;
                return;
            }
        } catch(exception e){
            cout << "Please enter a numeric amount" << endl;
            return;
        }

        stringstream stream;
        stream << fixed << setprecision(2) << stof(refund);
        refund_amount = stream.str();

        // TODO Still need to implement the code to refund
        
        string transaction_code = "05 ";

        transaction_code += buyer;
        for (int i = 0; i < 16 - buyer.length(); i++)
        {
            transaction_code += ' ';
        }
        transaction_code += seller;
        for (int i = 0; i < 16 - seller.length(); i++)
        {
            transaction_code += ' ';
        }
        for (int i = 0; i < 9 - refund_amount.length(); i++)
        {
            transaction_code += '0';
        }
        transaction_code += refund_amount + "\n";
        

        AppState::getInstance().appendTransactionBuffer(transaction_code);
        /*
        REFUND Transaction Format: 

        XX_UUUUUUUUUUUUUUU_SSSSSSSSSSSSSSS_CCCCCCCCC
        XX - The 2 Digit Transaction Code 05 that represents refund
        UUUUUUUUUUUUUUU - The Maximum 15 Character Username
        SSSSSSSSSSSSSSS - The Maximum 15 Character Seller Username
        CCCCCCCCC - The Refund Credit
        */

        cout << "Refund will be issued from " << buyer << " to " << seller 
        << " for $" << refund_amount << " upon logout" << endl;
    }
    else
    {
        cout << "Transaction Failed! You do not have permission to refund accounts!";
    }
}

/*
Please enter the buyer's username:
Please enter the seller's username:
Please enter the refund amount:
Refund issued from CheapKent to SuperMod for $100
 */