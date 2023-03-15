#pragma once

#include <fstream>
#include <vector>
#include <iostream>
#include <optional>

#include "User.h"
#include "Util.h"
#include "User.h"

/*
* Description: The following struct is used to manage and store all the information for each transaction that will be written to the daily 
* transactions file
*/
enum TransactionCode
{
    END_OF_SESSION = 0,
    CREATE = 1,
    DELETE = 2,
    ADVERTISE = 3,
    BID = 4,
    REFUND = 5,
    ADDCREDIT = 6,
};

struct TransactionInfo 
{
    const char* username;
    const char* sellerUsername;
    const char* buyerUsername;
    TransactionCode transactionCode;
    UserType userType;
    double availableCredit;
    double refundCredit;
    const char* itemName;
    int numDaysToAuction;
    double minBid;
    double newBId;

    bool operator==(const TransactionInfo &right)
    {
        return true;
    }
};

/*
* Description: The TransactionFile class is used to read, append, update, print the contents of a transaction file 
* and is used to verify the contents of a transaction file.
*/
class TransactionFile
{
private:
    std::fstream file;
    
public:
    TransactionFile(/* args */); //The constructor method for a TransactionFile object
    ~TransactionFile(); //The destructor method for a TransactionFile object

    //function declarations for each of the functions used to edit the Daily Transactions File
    bool appendToFile(TransactionInfo data);
    bool transactionExistsInFile(TransactionInfo data);
    std::vector<TransactionInfo> readTransactionFile();
    bool deleteLineFromFile(TransactionInfo data);
    
    static bool matchGeneral(TransactionInfo data, std::string line);
    static bool matchBid(TransactionInfo data, std::string line);
    static bool matchRefund(TransactionInfo data, std::string line);
    static bool matchAdvertise(TransactionInfo data, std::string line);
};
