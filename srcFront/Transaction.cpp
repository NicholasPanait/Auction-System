#include "Transaction.h"

/*
* Description: This method logs a user into the system, based on the passed in user object.
* 
* @param - user - a pointer reference to the current user object
* @return - returns true if login is successful
*/
bool Transaction::login(User *user)
{
    std::string username, password;
    std::cout << "\n***LOGIN***\nEnter Username: ";
    std::cin >> username; //get username from user
    std::cout << "\nEnter Password: ";
    std::cin >> password;
    std::cout<<"\n";
    //if the inputted user currently exists, login is successful and a welcome message is printed
    if (user->login(username.c_str(), password.c_str()))
    {
        std::cout << "Welcome " << User::getTypeName(user->getType()) << " User: " << username << "!\n";
        return true;
    }

    //if inputted username is not found, login is unsuccessful and an error message is printed
    std::cout << "Login Unsuccessful.\nUsername does not exist in the user directory or incorrect password. Please try again.\n";
    return false;
}

/*
* Description: This method logs the current user out of the system.
* 
* @param - user - a pointer reference to the current user object
* @return - returns true if user was able to successfully log out
*/
bool Transaction::logout(User *user)
{
    if (user->logout())
    {
        std::cout << "\nYou have successfully logged out.\n";
        exit(0);
        return true;
    }
    return false;
}

/*
* Description: This method allows an admin user to create a new user.
* 
* @param - user - a pointer reference to the current user object
* @return - returns true if admin user was able to successfully create a new user
*/
bool Transaction::createUser(User *user)
{
    /* overall TO DO: Get all information for new account from user, and add new user to the user accounts file. Write transaction to daily transactions file */
    UserAccountsFile userAccountsFile = UserAccountsFile(user->UserAccountsFilePath);
    std::string newUsername = "";

    //get username and user type from user
    std::cout << "\n***CREATE NEW USER***" << std::endl;
    while(newUsername == "")
    {
        std::cout << "Enter Username: ";
        std::cin >> newUsername;
        std::cout<<"Username entered: "<<newUsername<<std::endl;
        if (newUsername.length() > 15) //validate username length is < 15 characters 
        {
            std::cout << "\nThe inputted username has a length of greater than 15 characters. Please Try Again.\n";
            newUsername = "";
        }
        else if (userAccountsFile.userExistsInFile(newUsername)) // validate that username is not a current user
        {
            std::cout << "\nCreation Unsuccessful. Entered username currently exists in the user directory. Please try again.\n";
            newUsername = "";
        }
    }

    //get user type for new user
    std::string newUserType = "";
    UserType userType = UserType::NONE;

    if (user->getType() == UserType::AA){
        while (userType == UserType::NONE)
        {
            // TO DO: should probably create new test for this
            std::cout << "Enter Type of User: ";
            std::cin >> newUserType;
            userType = User::getUserType(newUserType.c_str());
            if (userType == UserType::NONE)
                std::cout << "\nThe inputted user type is invalid. Please Try Again.\n";
        }
    }
    else if (user->getType() == UserType::AM){
        while (userType == UserType::NONE || userType == UserType::AA)
        {
            // TO DO: should probably create new test for this
            std::cout << "Enter A Non Admin Type of User: ";
            std::cin >> newUserType;
            userType = User::getUserType(newUserType.c_str());
            if (userType == UserType::NONE || userType == UserType::AA)
                std::cout << "\nThe inputted user type is invalid. Please Try Again.\n";
        }
    }

    // get new password from user
    std::string newPassword = "";
    while(newPassword == "")
    {
        std::cout << "Enter new password: ";
        std::cin >> newPassword;
        std::cout<<"Password entered: "<<newPassword<<std::endl;
        if (newPassword.length() > 15) //validate password length is < 15 characters 
        {
            std::cout << "\nThe inputted password has a length of greater than 15 characters. Please Try Again.\n";
            newPassword = "";
        }
        else if (newPassword.length() < 1) //validate password length is > 0 characters 
        {
            std::cout << "\nThe inputted password has a length of less than 1 character. Please Try Again.\n";
            newPassword = "";
        }
    }

    int encrypted_password = 0;

    for (int i = 0; i < int(std::string(newPassword).length()); i++){
        encrypted_password += int(std::string(newPassword)[i]);
    }

    newPassword = std::to_string(encrypted_password);
    //TO DO: add transaction to transaction file - call file function
    TransactionFile transactionFile = TransactionFile(user->DailyTransactionFilePath, user->epochTime);
    transactionFile.appendToFile({
        .username=newUsername.c_str(),
        .password=newPassword.c_str(),
        .transactionCode=TransactionCode::CREATE,
        .userType=userType,
        .availableCredit=0.0,
    });

    // add user data to user accounts file
    // userAccountsFile.appendUserToFile({newUsername, userType, 0.0, newPassword});

    //print success message to console
    std::cout << "\nYou have successfully created a new User: " << newUsername << "!" << std::endl;

     

    //return true if able to successfully write to file.
    return false;
}

/*
* Description: This method allows an admin user to delete a specified user.
* 
* @param - user - a pointer reference to the current user object
* @return - returns true if admin user was able to successfully delete the specified user
*/
bool Transaction::deleteUser(User *user)
{
     /* Overall TO DO: traverse through user accounts file, and search for user that matches with the passed in user. 
     * delete that line from the user accounts file. Add transaction to the daily transactions file*/

    std::string userToDelete;
    std::string userType;

    //get username and user type from user
    std::cout << "\n***DELETE USER ACCOUNT***" << std::endl;
    std::cout << "Enter Username: ";
    std::cin >> userToDelete;

    // get deleted user info
    UserAccountsFile userAccountsFile = UserAccountsFile(user->UserAccountsFilePath);
    auto userInfo = userAccountsFile.getUserInfo(userToDelete);
    if (!userInfo) {
        std::cout << "Delete Unsuccessful.\nUsername does not exist in the user directory. Please try again.\n";
        return false;
    }
    if (user->getType() == UserType::AM && userInfo->userType == UserType::AA){
        std::cout << "Delete Unsuccessful.\nAccount Managers are not allowed to modify Admin accounts.\n";
        return false;
    }

    // delete entered user from user accounts file
    // userAccountsFile.deleteUserFromFile(userToDelete);

    // add transaction to transaction file
    TransactionFile transactionFile = TransactionFile(user->DailyTransactionFilePath, user->epochTime);
    transactionFile.appendToFile({
        .username=userInfo->username.c_str(),
        .password=userInfo->password.c_str(),
        .transactionCode=TransactionCode::DELETE,
        .userType=userInfo->userType,
        .availableCredit=userInfo->availableCredit,
    });

    //print success message to console.
    std::cout << "\nDeletion Confirmed. The account associated with the username: " << userToDelete << " has been deleted." << std::endl;

     

    //return true if user has been successfully deleted
    return true;
}

/*
* Description: This method allows all passed in users except of type BS to advertise/put an item up for auction. 
* 
* @param - user - a pointer reference to the current user object
* @return - returns true if user was able to successfully advertise an item
*/
bool Transaction::advertise(User *user)
{
     /* Overall TO DO: get all information from user to advertise an item, add item to available items file. Add transaction to the daily transactions file.*/
    std::string itemName = "";
    double minimumBid = 0.0;
    int numDaysToAuction = 0;

    std::cout << "\n***ADVERTISE***\n";

    //get item name from user
    std::cout << "Enter Item Name: ";
    std::cin >> itemName;
    while (itemName.length() >= 25){
        std::cout <<"Item name is greater than or equal to 25 characters. Please try again.\n";
        std::cout << "Enter Item Name: ";
        std::cin >> itemName;
    }

    //get minimum bid value from user
    std::cout << "Enter minimumBid: ";
    std::cin >> minimumBid;
    while (minimumBid > 999.99){
        std::cout << "Item price is greater than 999.99. Please try again\n";
        std::cout << "Enter minimumBid: ";
        std::cin >> minimumBid;
    }

    //get number of days until auction from user
    std::cout << "Enter Number of Days until auction ends: ";
    std::cin >> numDaysToAuction;
    while (numDaysToAuction > 99){
        std::cout << "Number of days to auction is greater than 100 days. Please try again.\n";
        std::cout << "Enter Number of Days until auction ends: ";
        std::cin >> numDaysToAuction;
    }

    //TO DO: get current user's name, and name of user with current highest bid
    // add transaction info to transaction file
    TransactionFile transactionFile = TransactionFile(user->DailyTransactionFilePath, user->epochTime);
    transactionFile.appendToFile(TransactionInfo{
        .sellerUsername=user->getUsername().c_str(),
        .transactionCode=TransactionCode::ADVERTISE,
        .itemName=itemName.c_str(),
        .numDaysToAuction=numDaysToAuction,
        .minBid=minimumBid,
    });

    //TO DO: add item info to item file
    // AvailableItemsFile availableItemsFile = AvailableItemsFile(user->AvailableItemsFilePath);
    // availableItemsFile.appendItemToFile(ItemInfo{
    //     .itemName=itemName.c_str(),
    //     .sellerUsername=user->getUsername().c_str(),
    //     .highestBidUser="",
    //     .numDaysRemaining=numDaysToAuction,
    //     .currentHighestBid=minimumBid,
    // });

    //print success message
    std::cout << "\nItem has been successfully put up for a bid!" << std::endl;
 
     

    //return true if an item has been succesfully advertised
    return false;
}

/*
* Description: This method allows all passed in users except of type SS, to place a bid on an item.
* 
* @param - user - a pointer reference to the current user object
* @return - returns true if user was able to successfully place a bid on an item
*/
bool Transaction::bid(User *user)
{
     /* Overall TO DO: Get all info from user to place bid on an item of their choice, check if they have enough funds and place bid. 
     *  Add transaction to the daily transactions file.*/

    std::string itemName = "";
    std::string sellerName = "";
    double newBid = 0.0;

    std::cout << "***MAKING A BID***" << std::endl;

    //get item name
    std::cout <<"\nEnter Item Name: ";
    std::cin >> itemName;

    //get seller's username
    std::cout << "\nEnter seller's username: ";
    std::cin >> sellerName;


    //TO DO: Read through the available items file and get all the info for the required item
    AvailableItemsFile availableItemsFile = AvailableItemsFile(user->AvailableItemsFilePath);
    auto items = availableItemsFile.readItemFile();
    auto item = std::find(items.begin(), items.end(), ItemInfo{.itemName=itemName.c_str(), .sellerUsername=sellerName.c_str()});
    if (item == items.end()) {
        std::cout << "Item sold by this seller does not exist\n";
        return false;
    }

    double currentHighestBid = item->currentHighestBid; //TO DO: get current highest bid for item from file
    std::string userWithHighestBid = item->highestBidUser; //TO DO: get user with highest bid for item from file
    // int numDaysToAuction = item->numDaysRemaining; //TO DO: get num days to auction for item from file

    //print out current highest bid
    std::cout << "\nCurrent Highest Bid: " << std::to_string(currentHighestBid).substr(0, std::to_string(currentHighestBid).length()-4) << std::endl;

    //get new bid
    std::cout << "Enter New Bid: ";
    std::cin >> newBid;

    //verify that new bid is higher than the current bid
    if (user->getType() == UserType::AA){
        while (currentHighestBid > newBid){
            std::cout << "New bid amount is not higher than the current bid. Please try again." << std::endl;
            std::cout << "\nEnter New Bid: ";
            std::cin >> newBid;
        }
    }
    else{
        while (1.05 * currentHighestBid > newBid){
            std::cout << "New bid amount is not at least 5" << "% " << "greater than the current bid. Please try again." << std::endl;
            std::cout << "\nEnter New Bid: ";
            std::cin >> newBid;
        }
    }

    if (user->getAvailableCredit() < newBid){
        std::cout << "You do not have enough funds to bid on this item!" << std::endl;
        return false;
    }

    // write transaction to transaction file
    TransactionFile transactionFile = TransactionFile(user->DailyTransactionFilePath, user->epochTime);
    transactionFile.appendToFile(TransactionInfo{
        .sellerUsername=sellerName.c_str(),
        .buyerUsername=user->getUsername().c_str(),
        .transactionCode=TransactionCode::BID,
        .itemName=itemName.c_str(),
        .newBid=newBid,
    });

    // update item in items file
    // availableItemsFile.deleteItemFromFile(*item);
    // availableItemsFile.appendItemToFile(ItemInfo{
    //     .itemName=itemName.c_str(),
    //     .sellerUsername=sellerName.c_str(),
    //     .highestBidUser=user->getUsername().c_str(),
    //     .numDaysRemaining=numDaysToAuction,
    //     .currentHighestBid=newBid,
    // });

    //print success message
    std::cout << "A bid has been successfully made for this item!" << std::endl;
     

    //return true if bid has been made successfully
    return true;
}

/*
* Description: This method allows an admin user to refund the credit amount to the specified user.
* 
* @param - user - a pointer reference to the current user object
* @return - returns true if the admin user was able to complete a refund successfully
*/
bool Transaction::refund(User *user)
{
     /* Overall TO DO: decrease the specified credit amount from a seller's account to the buyer's account for an item. 
     *  Add transaction to the daily transactions file.*/

    std::string buyerName = "";
    std::string sellerName = "";
    double creditToTransfer = 0.0;
    UserAccountsFile userAccountsFile = UserAccountsFile(user->UserAccountsFilePath);

    std::cout << "***Issue a Refund***" << std::endl;

    std::cout << "Enter buyer's username: ";
    std::cin >> buyerName;
    auto buyerInfo = userAccountsFile.getUserInfo(buyerName);
    if (buyerInfo == std::nullopt)
    {
        std::cout << "User could not be found\n";
        return false;
    }

    std::cout << "\nEnter seller's username: ";
    std::cin >> sellerName;
    auto sellerInfo = userAccountsFile.getUserInfo(sellerName);
    if (sellerInfo == std::nullopt)
    {
        std::cout << "User could not be found\n";
        return false;
    }

    std::cout << "\nEnter the amount of credit to transfer: ";
    std::cin >> creditToTransfer;

    // completed the fund transfer (subtract the credit amount from buyer, add to seller)
    sellerInfo->availableCredit -= creditToTransfer;
    buyerInfo->availableCredit += creditToTransfer;

    // update the credit amounts for the seller and the buyer in the user accounts file
    // userAccountsFile.deleteUserFromFile(sellerInfo->username);
    // userAccountsFile.deleteUserFromFile(buyerInfo->username);
    // userAccountsFile.appendUserToFile(*sellerInfo);
    // userAccountsFile.appendUserToFile(*buyerInfo);

    //TO DO: write transaction to transaction file
    TransactionFile transactionFile = TransactionFile(user->DailyTransactionFilePath, user->epochTime);
    transactionFile.appendToFile({
        .sellerUsername=sellerName.c_str(),
        .buyerUsername=buyerName.c_str(),
        .transactionCode=TransactionCode::REFUND,
        .refundCredit=creditToTransfer,
    });

    //print success message
    std::cout << "The refund has been successfully completed!" << std::endl;

     

    //return true if refund is successfully completed
    return true;
}

/*
* Description: This method allows users to add a credit amount to a specified user’s account.
* 
* @param - user - a pointer reference to the current user object
* @return - returns true if user was able to add a credit amount successfully
*/
bool Transaction::addcredit(User *user)
{
     /*Overall TO DO: Get credit amount to add from user, update credit amount attribute for user. Add transaction to the daily transactions file.*/
    std::string userToAddCreditTo;
    double creditAmountToAdd;

    std::cout << "***Add Credit***" << std::endl;

    if (user->getType() == UserType::AA || user->getType() == UserType::AM) 
    {
        std::cout << "\nEnter username of account to add credit to: ";
        std::cin >> userToAddCreditTo;
    }
    else
    {
        userToAddCreditTo = user->getUsername();
    }
    

    // verify that user current exists and get their information (current credit amount)
    //if user is found, print success message
    UserAccountsFile userAccountsFile = UserAccountsFile(user->UserAccountsFilePath);
    auto userInfo = userAccountsFile.getUserInfo(userToAddCreditTo);
    while (!userInfo)
    { // else print failure message
        std::cout << "User not found. Please try again.\n";
        std::cout << "Enter username of account to add credit to: ";
        std::cin >> userToAddCreditTo;
        userInfo = userAccountsFile.getUserInfo(userToAddCreditTo);
    }
    std::cout << "User Found! Please proceed to add a credit amount.\n";

    //get credit amount to add
    std::cout << "Enter the amount of credit to add: ";
    std::cin >> creditAmountToAdd;

    //ensure the credit amount is <= 1000
    while (creditAmountToAdd > 1000) { 
        std::cout << "Credit Amount to be added is greater than 1000. Please try again.\n";
        std::cout << "\nEnter the amount of credit to add: ";
        std::cin >> creditAmountToAdd;
    }

    while (creditAmountToAdd + user->addedCredit > 1000) { 
        std::cout << "Credit Amount to be added this sesson is greater than 1000. Please try again.\n";
        if (1000-(user->addedCredit) == 0){
            std::cout << "This session cannot add any more credits." << std::endl;
        }
        else{
            std::cout << "This session can only add " << 1000-(user->addedCredit) << " more credits." << std::endl;
        }
        std::cout << "\nEnter the amount of credit to add: ";
        std::cin >> creditAmountToAdd;
    }

    // add credit amount to specified user's account
    userInfo->availableCredit += creditAmountToAdd;
    user->addedCredit += creditAmountToAdd;
    // userAccountsFile.deleteUserFromFile(userInfo->username);
    // userAccountsFile.appendUserToFile(*userInfo);

    TransactionFile transactionFile = TransactionFile(user->DailyTransactionFilePath, user->epochTime);
    transactionFile.appendToFile({
        .username=userToAddCreditTo.c_str(),
        .transactionCode=TransactionCode::ADDCREDIT,
        .userType=userInfo->userType,
        .availableCredit=userInfo->availableCredit,
    });

    //print success message
    std::cout << "\n\nThe specified credit has been successfully add to the indicated account!" << std::endl;

     

    //returns true if the credit amount was succesfully added
    return true;
}

/*
* Description: This method allows users to list all items up for auction in the console.
* 
* @param - user - a pointer reference to the current user object
* @return - returns true if user was able to list all the items up for auction successfully
*/
bool Transaction::listitems(User *user)
{
     /* TO DO: get all the items from the readItemFile function. Traverse through them and print all items to console.
      * Add transaction to the daily transactions file.*/

    std::cout << "\n***Items Up For Auction***" << std::endl;
    std::printf("|---------------------------|-------------|------------------|---------------|\n");
    std::printf("| Item name                 | Current Bid | Seller           | Days Remaning |\n");
    std::printf("|---------------------------|-------------|------------------|---------------|\n");

    AvailableItemsFile availableItemsFile = AvailableItemsFile(user->AvailableItemsFilePath);
    for (const auto &item : availableItemsFile.readItemFile())
    {
        std::printf("| %-25s | %-9.2f   | %-16s | %-13d |\n", item.itemName.c_str(), item.currentHighestBid, item.sellerUsername.c_str(), item.numDaysRemaining);
    }    
    std::printf("|---------------------------|-------------|------------------|---------------|\n");

    //returns true if all the items up for auction were successfully listed
    return false;
}

/*
* Description: This method allows admin users to output to console all active accounts.
* 
* @param - user - a pointer reference to the current user object
* @return - returns true if admin user was able to output all active accounts successfully
*/
bool Transaction::outputAllActiveAccounts(User *user)
{
    /* TO DO: Traverse through the user accounts file, and print out all the active users.*/

    std::cout << "\n***Output All Active Accounts***" << std::endl;
    std::printf("|-----------------|-------------|-----------|\n");
    std::printf("| Username        | User Type   | Credit    |\n");
    std::printf("|-----------------|-------------|-----------|\n");

    UserAccountsFile userAccountsFile = UserAccountsFile(user->UserAccountsFilePath);
    for (const auto &user : userAccountsFile.readUserFile())
    {
        std::printf("| %-15s | %s          | %-9.2f |\n", user.username.c_str(), User::getTypeCode(user.userType).c_str(), user.availableCredit);
    }
    std::printf("|-----------------|-------------|-----------|\n");

    //return true if all active accounts have been successfully printed
    return false;
}

/*
* Description: This method allows an admin user to change the password of a user.
* 
* @param - user - a pointer reference to the current user object
* @return - returns true if admin user was able to successfully change the user's password
*/
bool Transaction::changepassword(User *user)
{
    /* overall TO DO: Get all information for new account from user, and add new user to the user accounts file. Write transaction to daily transactions file */
    UserAccountsFile userAccountsFile = UserAccountsFile(user->UserAccountsFilePath);
    std::string userToChangePassword = "";

    //get username and user type from user
    std::cout << "\n***CHANGE PASSWORD***" << std::endl;

    userToChangePassword = user->getUsername();

    std::string newPassword = "";

    // get new password from user
    while(newPassword == "")
    {
        std::cout << "Enter new password: ";
        std::cin >> newPassword;
        std::cout<<"Password entered: "<<newPassword<<std::endl;
        if (newPassword.length() > 15) //validate password length is < 15 characters 
        {
            std::cout << "\nThe inputted password has a length of greater than 15 characters. Please Try Again.\n";
            newPassword = "";
        }
        else if (newPassword.length() < 1) //validate password length is > 0 characters 
        {
            std::cout << "\nThe inputted password has a length of less than 1 character. Please Try Again.\n";
            newPassword = "";
        }
    }

    int encrypted_password = 0;

    for (int i = 0; i < int(std::string(newPassword).length()); i++){
        encrypted_password += int(std::string(newPassword)[i]);
    }

    newPassword = std::to_string(encrypted_password);
    //TO DO: add transaction to transaction file - call file function
    TransactionFile transactionFile = TransactionFile(user->DailyTransactionFilePath, user->epochTime);
    transactionFile.appendToFile({
        .username=userToChangePassword.c_str(),
        .password=newPassword.c_str(),
        .transactionCode=TransactionCode::CHANGEPASSWORD,
    });

    // add user data to user accounts file
    // userAccountsFile.appendUserToFile({newUsername, userType, 0.0, newPassword});

    //print success message to console
    std::cout << "\nYou have successfully changed your password!" << std::endl;

     

    //return true if able to successfully write to file.
    return false;
}

/*
* Description: This method is used to return the appropriate menu options available for 
* an admin user.
* 
* @return - a map of all the transactions codes that are available to the admin user
*/
std::map<std::string, std::function<bool(User *)>> Transaction::getAdminMapping()
{
    return {
        {"logout", &logout},
        {"delete", &deleteUser},
        {"create", &createUser},
        {"advertise", &advertise},
        {"bid", &bid},
        {"refund", &refund},
        {"addcredit", &addcredit},
        {"listitems", &listitems},
        {"accounts", &outputAllActiveAccounts},
        {"changepassword", &changepassword}
    };
}

/*
* Description: This method is used to return the appropriate menu options available for 
* a full standard user.
* 
* @return - a map of all the transactions codes that are available to the full standard user
*/
std::map<std::string, std::function<bool(User *)>> Transaction::getFullStandardMapping()
{
    return {
        {"logout", &logout},
        {"create", &createUser},
        {"advertise", &advertise},
        {"bid", &bid},
        {"addcredit", &addcredit},
        {"listitems", &listitems},
        {"accounts", &outputAllActiveAccounts},
        {"changepassword", &changepassword}
    };
}

/*
* Description: This method is used to return the appropriate menu options available for 
* a sell standard user.
* 
* @return - a map of all the transactions codes that are available to the sell standard user
*/
std::map<std::string, std::function<bool(User *)>> Transaction::getSellStandardMapping()
{
    return {
        {"logout", &logout},
        {"advertise", &advertise},
        {"addcredit", &addcredit},
        {"listitems", &listitems},
        {"changepassword", &changepassword}
    };
}

/*
* Description: This method is used to return the appropriate menu options available for 
* a buy standard user.
* 
* @return - a map of all the transactions codes that are available to the buy standard user
*/
std::map<std::string, std::function<bool(User *)>> Transaction::getBuyStandardMapping()
{
    return {
        {"logout", &logout},
        {"bid", &bid},
        {"addcredit", &addcredit},
        {"listitems", &listitems},
        {"changepassword", &changepassword}
    };
}

/*
* Description: This method is used to return the appropriate menu options available for 
* an admin user.
* 
* @return - a map of all the transactions codes that are available to the admin user
*/
std::map<std::string, std::function<bool(User *)>> Transaction::getAccountManagerMapping()
{
    return {
        {"logout", &logout},
        {"delete", &deleteUser},
        {"create", &createUser},
        {"refund", &refund},
        {"addcredit", &addcredit},
        {"listitems", &listitems},
        {"accounts", &outputAllActiveAccounts},
        {"changepassword", &changepassword}
    };
}

/*
* Description: This method is used to return the appropriate menu option that is 
* available to the user at the start of the program(only login is available).
* 
* @return - a map of all the transactions codes that are available to the 
* user at the beginning of the program
*/
std::map<std::string, std::function<bool(User *)>> Transaction::getLoginMapping()
{
    return {
        {"login", &login}};
}
