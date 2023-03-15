#pragma once

#include <fstream>
#include <vector>
#include "TransactionFile.h"
#include "UserAccountsFile.h"
#include "AvailableItemsFile.h"
#include "User.h"

/*The following struct is used to manage the all the information for an item that will be written to the available items file*/
struct ItemInfo 
{
    std::string itemName;
    std::string sellerUsername;
    std::string highestBidUser;
    int numDaysRemaining;
    double currentHighestBid;

    bool operator==(const ItemInfo &r)
    {
        if (std::string(r.itemName) == std::string(itemName) && std::string(r.sellerUsername) == std::string(sellerUsername))
            return true;
        return false;
    }
};

/* 
The AvailableItemsFile class is used to read, append, update, print the contents of an 
available items file and is used to verify the contents of an available items file.
*/
class AvailableItemsFile
{
private:
    std::fstream file;

public:
    AvailableItemsFile(/* args */); //The constructor method for an AvailableItemsFile object.
    ~AvailableItemsFile(); // The destructor method for an AvailableItemsFile object.

    //function declarations for each of the functions used to edit the Available Items File
    bool appendItemToFile(ItemInfo data);
    bool itemExistsInFile(ItemInfo data);
    std::vector<ItemInfo> readItemFile();
    bool deleteItemFromFile(ItemInfo data);
};
