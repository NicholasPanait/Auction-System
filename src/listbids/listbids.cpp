#include "listbids.h"

using namespace std;
// TODO: implement listBids function so that it displays all items and the information assosiated with them

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
    cout << output << endl;
    input.close();
}

/*
Item Name           Seller          Days Left   Min Bid     Highest Bid
BulkNails (5000pcs) WarehouserJane  009         $50.00      None
This Website        MasterAdmin     021         $500.00     $921.30
RussianSuperYaught  NoBuyOlivia     003         $20.00      $32.44
Washers (5pcs)      WarehouserJane  002         $2.00       $4.00
*/