#include "bid.h"
using namespace std;
// TODO: implement the bid function so that it can be used to bid on an item
void Bid()
{
    bool is_privilleged = AppState::getInstance().getCurrentUser().privilege_type == "AA";
    if (CheckPermission(AppState::getInstance().getCurrentUser().privilege_type, "bid"))
    {
        string item_name;
        string seller;
        cout << "Please enter the item's name:" << endl;
        cin >> item_name; // TODO change so that it reads the entire line

        switch (ValidateItemName(item_name))
        {
        case 1:
            cout << "Please enter an item name that is less than 20 characters long" << endl;
            return;
        case 2:
            cout << "Please enter an item name that is at least 1 character long" << endl;
            return;
        }

        cout << "Please enter the seller's name:" << endl;
        cin >> seller;  // TODO change so that it reads the entire line
        
        switch (ValidateUsername(seller))
        {
        case 1:
            cout << "Please enter a username that is less than 16 characters long" << endl;
            return;
        case 2:
            cout << "Please enter a username that is at least 1 character long" << endl;
            return;
        }

        Item item = GetItem(item_name, seller);
        if (to_string(item.minimum_bid).empty())
        {
            cout << "Transaction Failed! Item does not exist!" << endl;
            return;
        }

        float required_bid = item.minimum_bid;
        if (item.highest_bid == 0 && !is_privilleged) required_bid = item.highest_bid * 1.05;

        cout << setprecision(2)
        <<  "The current highest bid is $" << item.highest_bid 
        << " and the minimum bid is $" << item.minimum_bid
        << ", please enter your desired bid amount: (must be at least $" 
        << required_bid << ")" << endl;

        string desired_bid;
        cin >> desired_bid;

        if (stof(desired_bid) >= required_bid){
            // Still need to implement the code to place the bid

            string transaction_code = "04 ";

            // TODO EITHER 19 MAX or 25 MAX FOR ITEM NAME
            transaction_code += item_name;
            for (int i = 0; i < 20-item_name.length(); i++){
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
            XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUUU_PPPPPP

            XX - The 2 Digit Transaction Code 04 for bid
            IIIIIIIIIIIIIIIIIII - The Maximum 19 Character Item Name
            SSSSSSSSSSSSSSS - The Maximum 15 Character Seller Username
            UUUUUUUUUUUUUUU - The Maximum 15 Character Buyer Username 
            PPPPPP - The Maximum $999.99 New Bid
            _ - Represents a Space

            */

            cout << "Bid placed on " << string(item.item_name) 
            << " sold by " << string(item.seller) << " for $" << desired_bid << endl;
        }
        else {
            cout << "Transaction failed! Your bid is not high enough!" << endl;
        }
    }
    else{
        cout << "Transaction Failed! You do not have permission to place bids!";
    }
}