#include "AvailableItemsFile.h"

/*
* Description: The constructor method for an AvailableItemsFile object
*/
AvailableItemsFile::AvailableItemsFile()
{
    /* TO DO: create constructor */
    this->file.open(AVAILABLE_ITEMS_FILE, std::ios::app | std::ios::in);
}

/*
* Description: The destructor method for an AvailableItemsFile object.
*/
AvailableItemsFile::~AvailableItemsFile()
{
   this->file.close();
}

/*
* Description: This method appends the information for the specified item to the available items file, 
* and returns true if successfully appended to the file.
*
* @param - data - An ItemInfo struct that contains the information for the item to be written to file
* @return - returns true if item information is successfully appended to the file
*/
bool AvailableItemsFile::appendItemToFile(ItemInfo data)
{
    /* TO DO: take the information from the data struct and convert it into a string. Append the string to file */
    //Format: IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUU_DDD_PPPPPP
    char item[63];
    std::snprintf(item, 63, "%-19s %-15s %-15s %03d %06.2f", data.itemName.c_str(), data.sellerUsername.c_str(), data.highestBidUser.c_str(), data.numDaysRemaining, data.currentHighestBid);

    try{
        file<<item<<'\n';
        return true;
    }catch(...){
        std::cout << "Ane error occured wihle writing to the Item file\n";
    }
    return false;
}

/*
* Description: This method verifies if the specified item’s information 
* currently exists in the available items file and returns true if the 
* item’s information is found in the file.
* 
* @param - data - An ItemInfo struct that contains the information for the item to be verified
* @return - returns true if the item's information is found in the file
*/
bool AvailableItemsFile::itemExistsInFile(ItemInfo data)
{
    /* TO DO: traverse through file, read each line get the name of each item. compare each item from file to the data struct until a match is found */
    auto items = this->readItemFile();
    return std::find(items.begin(), items.end(), data) != items.end();
   
}

/*
* Description: This method reads in all the contents of the available items file, and returns a 
vector with all the information. The information for each item is stored as an ItemInfo struct 
in the vector.
*
* @return  - a vector containing ItemInfo structs
*/
std::vector<ItemInfo> AvailableItemsFile::readItemFile()
{
    /* TO DO:  traverse through available items file, read each line, and convert it into a ItemInfo struct. Add the struct to the vector.*/
    std::vector<ItemInfo> items;
    std::string line;
    while (std::getline(this->file, line))
    {
        items.emplace_back(ItemInfo{
            Util::trim(line.substr(0,19)),
            Util::trim(line.substr(20,15)),
            Util::trim(line.substr(36,15)),
            stoi(line.substr(52,3)),
            atof(line.substr(56,6).c_str())
        });
    }
    // reset file pointer
    this->file.clear();
    this->file.seekg(0);

    return items;
}

/*
* Description: This method deletes the information for the specified item from the available 
items file and returns true if the information is successfully deleted.
* 
* @param - data - An ItemInfo struct that contains the information for the item to be deleted
* @return - returns true if the item's information is deleted from the file
*/
bool AvailableItemsFile::deleteItemFromFile(ItemInfo data)
{
    /* TO DO: travserse through the file, and read each line and try to find the line containing the same item name as the data struct. 
    * Delete that line from the file*/
   std::string line;
    std::ofstream tempFile;
    const char* tempFileName = "tempItems.txt";
    tempFile.open(tempFileName);

    while(getline(file, line))
    {
        if (Util::trim(data.itemName) == Util::trim(line.substr(0,19)) &&
            Util::trim(data.sellerUsername) == Util::trim(line.substr(20,15)) &&
            Util::trim(data.highestBidUser) == Util::trim(line.substr(36,15)) &&
            data.numDaysRemaining == stoi(line.substr(52,3)) &&
            data.currentHighestBid == atof(line.substr(56,6).c_str())
        )
        {
            continue;
        }
          
        tempFile << line << '\n';
    }

    tempFile.close();
    file.close();
    remove(AVAILABLE_ITEMS_FILE);
    rename(tempFileName, AVAILABLE_ITEMS_FILE);
    this->file.open(AVAILABLE_ITEMS_FILE, std::ios::app | std::ios::in);

    return false;
}
