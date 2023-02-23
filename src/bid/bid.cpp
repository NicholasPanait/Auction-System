#include "bid.h"
using namespace std;
//TODO: implement the bid function so that it can be used to bid on an item
void Bid(){
    bool is_privilleged = AppState::getInstance().getCurrentUser().privilege_type == "AA";
    if (CheckPermission(AppState::getInstance().getCurrentUser().privilege_type, "bid")){
        string item_name;
        string seller;
        cout << "Please enter the item's name:" << endl;
        cin >> item_name;
        cout << "Please enter the seller's name:" << endl;
        cin >> seller;
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