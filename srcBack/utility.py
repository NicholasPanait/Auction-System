# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# File Name: utility.py
#
# Description:
# The following file contains utility functions used throughout the backend program
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

import create
import delete
import advertise
import addcredit
import changepassword
import bid
import refund
import re

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Class Name: Class
#
# Description:
# The following class stores all the related information for a User.
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
class User:

    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    # Function Name: __init__
    #
    # Description:
    # The constructor for the User class
    #
    # Parameters:
    # username - The username of the user
    # privilege_type - The privilege type of the user
    # credit - The available credit of the user
    # password - The encrypted password of the user
    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    def __init__(self, username, privilege_type, credit, password):
        self.username = username
        self.privilege_type = privilege_type
        self.credit = credit
        self.password = password

    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    # Function Name: __str__
    #
    # Description:
    # The following function handles the string conversion of the user
    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    def __str__(self):
        return pad_string(self.username, 16) + pad_string(self.privilege_type, 3) + pad_string(self.credit, 10) + self.password


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Class Name: Item
#
# Description:
# The following class stores all the related information for an Item.
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
class Item:

    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    # Function Name: __init__
    #
    # Description:
    # The constructor for the Item class
    #
    # Parameters:
    # item_name - The item's name
    # seller - The username of the item's seller's
    # buyer = The username of the user with the current highest bid
    # duration - The remaining duration of the auction
    # min_bid - The minimum bid any new bidder will need to make for the item
    # winning_bid - The current winning bid on the item
    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    def __init__(self, item_name, seller, buyer, duration, min_bid, winning_bid):
        self.item_name = item_name
        self.seller = seller
        self.buyer = buyer
        self.duration = duration
        self.min_bid = min_bid
        self.winning_bid = winning_bid

    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    # Function Name: __str__
    #
    # Description:
    # The following function handles the string conversion of the Item
    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    def __str__(self):
        return pad_string(self.item_name, 26) + pad_string(self.seller, 16) + pad_string(self.buyer, 16) + pad_number(self.duration, 2) + " " + pad_number(self.min_bid, 6) + " " + pad_number(self.winning_bid, 6)

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Function Name: pad_string
#
# Parameters:
# string - The input string
# length - The desired length to pad to
#
# Description:
# The following function takes in an input string and the desired length for it to be padded
# to. The function will return the left aligned string padded with spaces up to the desired
# length.
#
# Return:
# The string padded with spaces up to the desired length
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
def pad_string(string, length):
    result = string
    for i in range(length-len(string)):
        result += " "
    return result

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Function Name: pad_number
#
# Parameters:
# number - The input number
# length - The desired length to pad to
#
# Description:
# The following function takes in an input number and the desired length for it to be padded
# to. The function will return the right aligned number padded with zeros up to the desired
# length.
#
# Return:
# The number padded with zeros up to the desired length
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
def pad_number(number, length):
    zeros = ''
    for i in range(length-len(number)):
        zeros += '0'
    return zeros + number

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Function Name: process_transaction
#
# Parameters:
# transaction - The line from the Daily Transaction File
# users - The list of Users that contains the information from the Users file
# items - The list of Items that contains the information from the Items file
#
# Description:
# The following function will handle processing each transaction from the Daily Transaction File
# by calling the appropriate function.
#
# Return:
# The modified users and items list
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
def process_transaction(transaction, users, items):
    transactions = re.split("\s+", transaction)
    if len(transactions) > 5:
        print("Fatal Error: Incorrect Number of Arguments in Daily Transaction File!")

    # validate if the transaction are correct and formatted correctly
    if (validate_transaction(transaction) == False):
        return users, items

    if transactions[0] == "00":
        # print("END OF SESSION")
        return users, items
    elif transactions[0] == "01":
        if len(transactions) < 5: transactions += "temp"
        create.create(transactions[1], transactions[2], transactions[3], transactions[4], users)
        # print("CREATE")
    elif transactions[0] == "02":
        delete.delete(transactions[1], users, items)
        # print("DELETE")
    elif transactions[0] == "03":
        advertise.advertise(transactions[1], transactions[2], transactions[3], transactions[4], items,users)
        # print("ADVERTISE")
    elif transactions[0] == "04":
        bid.bid(transactions[1], transactions[2], transactions[3], transactions[4], users, items)
        # print("BID")
    elif transactions[0] == "05":
        refund.refund(transactions[1], transactions[2], transactions[3], users)
        # print("REFUND")
    elif transactions[0] == "06":
        addcredit.addcredit(transactions[1], transactions[3], users)
        # print("ADDCREDIT")
    elif transactions[0] == "07":
        changepassword.changepassword(transactions[1], transactions[2], users)
        # print("CHANGEPASSWORD")
    else:
        print('Fatal Error: Incorrect Transaction Code in Daily Transaction File!')
    return users, items

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Function Name: validate_transaction
#
# Parameters:
# transaction - The line from the Daily Transaction File
#
# Description:
# The following function will validate formatting of a transaction from the Daily Transaction File
#
# Return:
# 1. If the transaction is improperly formatted it will return False
# 2. If the transaction is properly formatted it will return True
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
def validate_transaction(transaction):
    transaction_code = transaction[:2]
    # End of Session and add credit
    if transaction_code == "00" or transaction_code == "06":
        if re.match("^(00|06) (\\S)(.){14} (AA|FS|SS|BS|AM) (\\d){6}\.(\\d){2}", transaction):
            return True
        else:
            if transaction_code == "00":
                print('Error: Incorrect formatting for End of Session in Daily Transaction File')
            else:
                print('Error: Incorrect formatting for Add Credit in Daily Transaction File')
            
    # Create and Delete
    elif transaction_code == "01" or transaction_code == "02":
        if re.match("^(01|02) (\\S)(.){14} (AA|FS|SS|BS|AM) (\\d){6}\.(\\d){2} (\\d){1,4}", transaction):
            return True
        else:
            if transaction_code == "01":
                print("Error: Incorrect formatting for Create in Daily Transaction File")
            else:
                print("Error: Incorrect formatting for Delete in Daily Transaction File")

    # Advertise
    elif transaction_code == "03":
        if re.match("^(03) (\\S)(.){24} (\\S)(.){14} (\\d){2} (\\d){3}\\.(\\d){2}", transaction):
            return True
        else:
            print("Error: Incorrect formatting for Advertise in Daily Transaction File")
            
    # Bid
    elif transaction_code == "04":
        if re.match("^(04) (\\S)(.){24} (\\S)(.){14} (\\S)(.){14} (\\d){3}\\.(\\d){2}", transaction):
            return True
        else:
            print("Error: Incorrect formatting for Bid in Daily Transaction File")   
        
    # Refund
    elif transaction_code == "05":
        if re.match("^(05) (\\S)(.){14} (\\S)(.){14} (\\d){6}\\.(\\d){2}", transaction):
            return True
        else:
            print("Error: Incorrect formatting for Refund in Daily Transaction File")     
        
    # Changepassword
    elif transaction_code == "07":
        if re.match("^(03) (\\S)(.){14} (\\d){1,4}", transaction):
            return True
        else:
            print("Error: Incorrect formatting for Changepassword in Daily Transaction File")     
    return False

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Function Name: validate_user
#
# Parameters:
# user - The line from the User File
#
# Description:
# The following function will validate formatting of a user from the User File
#
# Return:
# 1. If the transaction is improperly formatted it will return False
# 2. If the transaction is properly formatted it will return True
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
def validate_user(user):
    if re.match("^\\S(.){14} (AA|SS|BS|FS|AM) \\d{6}.\d{2} \\d{1,4}", user):
        return True
    return False

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Function Name: validate_item
#
# Parameters:
# item - The line from the Item File
#
# Description:
# The following function will validate formatting of a item from the Items File
#
# Return:
# 1. If the transaction is improperly formatted it will return False
# 2. If the transaction is properly formatted it will return True
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
def validate_item(item):
    if re.match("^\\S(.){24} \\S(.){14} [\\S, ]{15} \\d{2} \\d{3}.\\d{2} \\d{3}.\\d{2}", item):
        return True
    return False