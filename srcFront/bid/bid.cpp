#include "bid.h"

/**
 * Function to handle parameters and transaction code generation
 * for the bid command which will create bids on auction items
 * NOTE: Admin accounts can bid under the 5% mandatory increase per bid
 */

using namespace std;

void Bid()
{
    bool is_privilleged = AppState::getInstance().getCurrentUser().privilege_type == "AA";

    if (CheckPermission(AppState::getInstance().getCurrentUser().privilege_type, "bid"))
    {
        string item_name;
        string seller;
        cout << "Please enter the item's name:" << endl;
        cin.ignore();
        getline(cin, item_name);

        switch (ValidateItemName(item_name))
        {
        case 1:
            cout << "Please enter an item name that is less than 26 characters long!" << endl;
            return;
        case 2:
            cout << "Please enter an item name that is at least 1 character long!" << endl;
            return;
        }

        cout << "Please enter the seller's name:" << endl;
        getline(cin, seller);

        if (seller == AppState::getInstance().getCurrentUser().username){
            cout << "You can not bid on your own auction!" << endl;
            return;
        }
        
        switch (ValidateUsername(seller))
        {
        case 0:
            cout << "Please enter an existing username!" << endl;
            return;
        case 1:
            cout << "Please enter a username that is less than 16 characters long!" << endl;
            return;
        case 2:
            cout << "Please enter a username that is at least 1 character long!" << endl;
            return;
        }

        Item item = GetItem(item_name, seller);
        if (item.item_name.empty() && item.seller.empty())
        {
            cout << "Transaction Failed! Item does not exist!" << endl;
            return;
        }

        double required_bid;
        if (item.highest_bid > item.minimum_bid){
            required_bid = item.highest_bid;
        }
        else{
            required_bid = item.minimum_bid;
        }

        if (!is_privilleged){
            required_bid = required_bid * 1.05;
        }
        else{
            required_bid = required_bid + 0.01;
        }

        cout << setprecision(2)
        <<  "The current highest bid is $" << item.highest_bid 
        << " and the minimum bid is $" << item.minimum_bid
        << ", please enter your desired bid amount (must be at least $" 
        << required_bid << "):" << endl;

        string desired_bid;
        cin >> desired_bid;

        switch ((ValidateBid(desired_bid)))
        {
            case 1:
                cout << "Please enter a numeric bid!" << endl;
                return;
            case 2:
                cout << "Please enter a bid that is positive and at least $0.01!" << endl;
                return;
            case 3:
                cout << "Please enter a bid that is less than $1000!" << endl;
                return;
        }
        User currentUser = AppState::getInstance().getCurrentUser();

        if (stod(desired_bid) + currentUser.pending_credit <= currentUser.credit){

            if (stod(desired_bid) >= required_bid){

                string transaction_code = "04 ";

                transaction_code += item_name;
                for (int i = 0; i < 26-item_name.length(); i++){
                    transaction_code += ' ';
                }
                transaction_code += item.seller;
                for (int i = 0; i < 16-item.seller.length(); i++){
                    transaction_code += ' ';
                }
                transaction_code += AppState::getInstance().getCurrentUser().username;
                for (int i = 0; i < 16-AppState::getInstance().getCurrentUser().username.length(); i++){
                    transaction_code += ' ';
                }
                for (int i = 0; i < 6-desired_bid.length(); i++){
                    transaction_code += '0';
                }
                transaction_code += (desired_bid + "\n");

                AppState::getInstance().appendTransactionBuffer(transaction_code);
                /*
                BID Transaction Format: 
                XX_IIIIIIIIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUUU_PPPPPP

                XX - The 2 Digit Transaction Code 04 for bid
                IIIIIIIIIIIIIIIIIIIIIIIII - The Maximum 25 Character Item Name
                SSSSSSSSSSSSSSS - The Maximum 15 Character Seller Username
                UUUUUUUUUUUUUUU - The Maximum 15 Character Buyer Username 
                PPPPPP - The Maximum $999.99 New Bid
                _ - Represents a Space

                */

                AppState::getInstance().getCurrentUser().pending_credit += stod(desired_bid);

                cout<< "Bid placed on \'" << string(item.item_name)
                    << "\' sold by \"" << string(item.seller) << "\" for $" << desired_bid << endl;
            }
            else {
                cout << "Transaction failed! Your bid is not high enough!" << endl;
            }
        }else{
            cout << "Transaction Failed! You do not have enough credit!" << endl;
        }
    }
    else{
        cout << "Transaction Failed! You do not have permission to place bids!" << endl;
    }
}