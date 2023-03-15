#include "TransactionFile.h"

/* The constructor method for a TransactionFile object.
*/
TransactionFile::TransactionFile()
{
    this->file.open(TRANSACTION_FILE, std::ios::app | std::ios::in);
}

/* The destructor method for a TransactionFile object.
*/
TransactionFile::~TransactionFile()
{
    this->file.close();
}

/*
* Description: This method appends the information for the specified transaction to the daily transactions file, 
* and returns true if successfully appended to the file.
*
* @param - data - A TransactionInfo struct that contains the information for the transaction to be written to file
* @return - returns true if transaction information is successfully appended to the file
*/
bool TransactionFile::appendToFile(TransactionInfo data)
{
    /* TO DO: take the information from the data struct and convert it into a string. Append the string to file */
    char transaction[63];
    switch(data.transactionCode){
        case(CREATE):
        case(DELETE):
        case(END_OF_SESSION):
        case(ADDCREDIT):
            //append username_userType_availableCredit
            std::snprintf(transaction, 63, "%02d %-15s %s %09.2f", data.transactionCode, data.username, User::getTypeCode(data.userType).c_str(), data.availableCredit);
            break;
        
        case(ADVERTISE):
            //append itemName_sellerName_daysToAuction_minBid
            std::snprintf(transaction, 63, "%02d %-19s %-15s %03d %06.2f", data.transactionCode, data.itemName, data.sellerUsername, data.numDaysToAuction, data.minBid);
            break;
        
        case(REFUND):
            //append username_sellername_refundCredit
            std::snprintf(transaction, 63, "%02d %-15s %-15s %09.2f", data.transactionCode, data.buyerUsername, data.sellerUsername, data.refundCredit);
            break;
        
        case(BID):
            //append item_seller_buyer_newBid
            std::snprintf(transaction, 63, "%02d %-19s %-15s %-15s %06.2f", data.transactionCode, data.itemName, data.sellerUsername, data.buyerUsername, data.newBId);
            break;
        
    }

    //Try writing the transaciton to the file
    try{
        //std::cout<<"Wrote to transaction file";
        file<<transaction<<'\n';
        return true;
    }catch(...){
        std::cout << "An error occured while writing to the transaction file\n";
    }
    
    return false;
}

/*
* Description: This method verifies if the specified transaction’s information 
* currently exists in the daily transactions file and returns true if the 
* transaction’s information is found in the file.
* 
* @param - data - A TransactionInfo struct that contains the information for the transaction to be verified
* @return - returns true if the transaction's information is found in the file
*/
bool TransactionFile::transactionExistsInFile(TransactionInfo data)
{
    /* TO DO: traverse through file, read each line get each transaction. Compare each transaction from file to the data struct until a match is found */
    //Read in all transactions into vector
    auto transactions = this->readTransactionFile();
    //Return true if TransactionInfo structure matches data
    return std::find(transactions.begin(), transactions.end(), data) != transactions.end();
    
}

/*
* Description: This method reads in all the contents of the daily transactions file, and returns a 
* vector with all the information. The information for each transaction is stored as a TransactionInfo struct 
* in the vector.
*
* @return  - a vector containing TransactionInfo structs
*/
std::vector<TransactionInfo> TransactionFile::readTransactionFile()
{
    /* TO DO:  traverse through daily transactions file, read each line, and convert it into a TransactionInfo struct. Add the struct to the vector.*/
    std::vector<TransactionInfo> allTransactions;
    std::string line;
    int transactionCode;
    while (std::getline(this->file, line))
    {   
        //Find what type of transaciton is being read
        transactionCode = stoi(line.substr(1,1));

        //Create and populate a TransactionInfo structure based on the type 
        switch(transactionCode)
        {
            //Populate username, usertype, availableCredit
            case(CREATE):
            case(DELETE):
            case(END_OF_SESSION):
            case(ADDCREDIT):
                allTransactions.emplace_back(TransactionInfo{
                    .username=Util::trim(line.substr(3,15)).c_str(),//Username
                    .transactionCode=static_cast<TransactionCode>(transactionCode),//Transaction code
                    .userType=User::getUserType(line.substr(20,2).c_str()),//User type
                    .availableCredit=atof(line.substr(23,9).c_str()),//available credit
                });
                break;

            //Populate itemName, sellerName, daysToAuction, minBid
            case(ADVERTISE):
                allTransactions.emplace_back(TransactionInfo{
                    .sellerUsername=Util::trim(line.substr(23,15)).c_str(),//Seller name
                    .transactionCode=static_cast<TransactionCode>(transactionCode),//Transaction code
                    .itemName=line.substr(3,19).c_str(),//Item name
                    .numDaysToAuction=atoi(line.substr(39,3).c_str()),//Days to auction
                    .minBid=atof(line.substr(43, 6).c_str()),
                });
                break;

            //Populate username, sellername, refundCredit
            case(REFUND):
                allTransactions.emplace_back(TransactionInfo{
                    .username=Util::trim(line.substr(3,15)).c_str(),//Username
                    .sellerUsername=Util::trim(line.substr(19,15)).c_str(),//Seller name
                    .transactionCode=static_cast<TransactionCode>(transactionCode),//Transaction code
                    .userType=UserType::NONE,//User type
                    .refundCredit=atof(line.substr(35,9).c_str()),//Refund credit
                });

                break;
            
            //Populate item, seller, buyer, newBid
            case(BID):
                allTransactions.emplace_back(TransactionInfo{
                    .sellerUsername=Util::trim(line.substr(23,15)).c_str(),//Seller name
                    .buyerUsername=Util::trim(line.substr(39,15)).c_str(),//Buyer name
                    .transactionCode=static_cast<TransactionCode>(transactionCode),//Transaction code
                    .userType=UserType::NONE,//User type
                    .itemName=line.substr(3,19).c_str(),//Item name
                    .newBId=atof(line.substr(56,6).c_str())//New bid
                });
                break;


        }
        
        
    }
    // reset file pointer
    this->file.clear();
    this->file.seekg(0);
    return allTransactions;
}

/*
* Description: This method deletes the information for the specified transaction from the daily
* transaction file and returns true if the information is successfully deleted.
* 
* @param - data - A TransactionInfo struct that contains the information for the transaction to be deleted
* @return - returns true if the transaction's information is deleted from the file
*/
bool TransactionFile::deleteLineFromFile(TransactionInfo data)
{
    /* TO DO: travserse through the file, and read each line and try to find the line containing the same transaction info as the data struct. 
    * Delete that line from the file*/
    
    std::string line;
    std::ofstream tempFile;
    int transactionCode;
    const char* tempFileName = "tempTransactions.txt";
    tempFile.open(tempFileName);

    while(getline(file, line))
    {  
        //Check if the transaction code matches
        transactionCode = stoi(line.substr(1,1));
        if (data.transactionCode == transactionCode){

            //Check if remaining info matches
            switch(transactionCode){
                case(CREATE):
                case(DELETE):
                case(END_OF_SESSION):
                case(ADDCREDIT):
                    if(TransactionFile::matchGeneral(data,line))
                        continue;
                    break;
                
                case(ADVERTISE):
                    if(TransactionFile::matchAdvertise(data,line))
                        continue;
                    break;
                
                case(REFUND):
                    if(TransactionFile::matchRefund(data,line))
                        continue;
                    break;

                case(BID):
                    if(TransactionFile::matchBid(data,line))
                        continue;
                    break;
            }
        }
        tempFile << line << '\n';
    }

    tempFile.close();
    file.close();
    remove(TRANSACTION_FILE);//CHANGE
    rename(tempFileName, TRANSACTION_FILE);//CHANGEEEE
    this->file.open(TRANSACTION_FILE, std::ios::app | std::ios::in);

    return true;

}

bool TransactionFile::matchBid(TransactionInfo data, std::string line){
    return data.itemName==line.substr(3,19).c_str() &&
        data.sellerUsername == Util::trim(line.substr(23,15)).c_str() &&
        data.buyerUsername == Util::trim(line.substr(39,15)).c_str() &&
        data.newBId == atof(line.substr(56,6).c_str());
           
}
bool TransactionFile::matchRefund(TransactionInfo data, std::string line){
    return data.username == line.substr(3,15).c_str() &&
        data.sellerUsername == Util::trim(line.substr(19,15)).c_str() &&
        data.refundCredit == atof(line.substr(35,9).c_str());
}
bool TransactionFile::matchAdvertise(TransactionInfo data, std::string line){
    return data.sellerUsername==line.substr(23,15).c_str() &&
        data.itemName == line.substr(3,19).c_str() &&
        data.numDaysToAuction == atoi(line.substr(39,3).c_str());
}

bool TransactionFile::matchGeneral(TransactionInfo data, std::string line){
    return data.username==line.substr(3,15).c_str() &&
        data.userType == User::getUserType(line.substr(20,2).c_str()) &&
        data.availableCredit == atof(line.substr(23,6).c_str());
}
