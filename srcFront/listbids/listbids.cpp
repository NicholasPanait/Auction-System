#include "listbids.h"

/**
 * Function to handle parameters and transaction code generation
 * for the listbids command which will list all the current running
 * auctions and their bids
 */

void ListBids()
{
    string output = "Item Name\t    Seller\t    Days Left\tMin Bid \tHighest Bid";
    string line;
    ifstream input(AppState::getInstance().getItemFile());
    if (input.is_open())
    {
        while (getline(input, line))
        {
            if (line == "END")
            {
                input.close();
            }
            else
            {
                output.append("\n");
                output.append(line.substr(0, 36)); // item name and seller
                output.append(RemoveLeading(line.substr(51, 3), '0') + "\t\t"); // days left
                output.append("$" + RemoveLeading(line.substr(55, 6), '0') + "\t\t"); // min bid
                if (line.substr(62, 6) == "000.00") { // highest bid
                    output.append("None");
                }
                else
                {
                    output.append("$" + RemoveLeading(line.substr(62, 6), '0'));
                }
            }
        }
    }
    input.close();
    if (output == "Item Name\t    Seller\t    Days Left\tMin Bid \tHighest Bid"){
        cout << "There are currently no items up for sale right now!" << endl;
        return;
    }
    else{
        cout << output << endl;
    }
}

/*
Item Name           Seller          Days Left   Min Bid     Highest Bid
BulkNails (5000pcs) WarehouserJane  009         $50.00      None
This Website        MasterAdmin     021         $500.00     $921.30
RussianSuperYaught  NoBuyOlivia     003         $20.00      $32.44
Washers (5pcs)      WarehouserJane  002         $2.00       $4.00
*/