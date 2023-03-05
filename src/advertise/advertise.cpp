#include "advertise.h"

/**
 * This function handles parameters and transaction code generation for
 * the advertise command responsible for creating new auctions
 */
// NOTE: Buy Standard accounts can not use this command

void Advertise()
{
    bool is_privilleged = AppState::getInstance().getCurrentUser().privilege_type == "AA";
    if (CheckPermission(AppState::getInstance().getCurrentUser().privilege_type, "advertise"))
    {
        string item_name;
        string min_bid_input;
        string duration_input;
        int duration;
        cout << "Please enter your item name:" << endl;
        cin.ignore();
        getline(cin, item_name, '\n');

        switch (ValidateItemName(item_name))
        {
        case 1:
            cout << "Please enter an item name that is less than 26 characters long" << endl;
            return;
        case 2:
            cout << "Please enter an item name that is at least 1 character long" << endl;
            return;
        }

        cout << "Please enter your item's minimum bid in dollars:" << endl;
        cin >> min_bid_input;
        
        switch ((ValidateBid(min_bid_input)))
        {
            case 1:
                cout << "Please enter a minimum bid that is numeric" << endl;
                return;
            case 2:
                cout << "Please enter a minimum bid that is positive and at least $0.01" << endl;
                return;
            case 3:
                cout << "Please enter a minimum bid that is less than $1000" << endl;
                return;
        }
        stringstream stream;
        stream << fixed << setprecision(2) << stod(min_bid_input);
        min_bid_input = stream.str();

        cout << "Please enter your item's auction duration in days:" << endl;
        cin >> duration_input;

        try
        {
            if (!isNumeric(duration_input))
            {
                cout << "Please enter an integer value" << endl;
                return;
            }
            duration = stoi(duration_input);
            if (duration < 1)
            {
                cout << "Please enter a duration that is at least 1 day" << endl;
                return;
            }
            else if (duration > 99)
            {
                cout << "Please enter a duration that is less than 100 days" << endl;
                return;
            }
            if (duration_input.length() > 2){
                cout << "Invalid Input!" << endl;
                return;
            }
        }
        catch (exception e)
        {
            cout << "Please enter an integer value" << endl;
            return;
        }

        string transaction_code = "03 ";

        transaction_code += item_name;
        for (int i = 0; i < 26 - item_name.length(); i++)
        {
            transaction_code += ' ';
        }
        transaction_code += AppState::getInstance().getCurrentUser().username;
        for (int i = 0; i < 16 - AppState::getInstance().getCurrentUser().username.length(); i++)
        {
            transaction_code += ' ';
        }
        for (int i = 0; i < 3 - duration_input.length(); i++)
        {
            transaction_code += '0';
        }
        transaction_code += duration_input + " ";
        for (int i = 0; i < 6 - min_bid_input.length(); i++)
        {
            transaction_code += '0';
        }
        transaction_code += min_bid_input + "\n";

        AppState::getInstance().appendTransactionBuffer(transaction_code);
        /*

        ADVERTISE Transaction Format
        XX_IIIIIIIIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_DDD_PPPPPP
        XX - The 2 Digit Transaction Code 03 that represents advertise
        IIIIIIIIIIIIIIIIIIIIIIIII - The Maximum 25 Character Item Name
        SSSSSSSSSSSSSSS - The Maximum 15 Character Seller Username
        DDD - The Maximum 100 Day Duration of the Auction
        PPPPPP - The Maximum $999.99 Starting Bid
        _ - Represents a Space

        */

        string s = "";
        if (duration != 1) s = "s";

        cout << "Your auction of " << item_name << " will be put up for auction at the end of the day"
             << " with a minimum bid of $" << min_bid_input << " for " << duration << " day(s)" << s << endl;
    }
    else
    {
        cout << "Transaction Failed! You do not have permission to place bids!" << endl;
    }
}