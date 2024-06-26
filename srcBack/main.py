# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# CSCI 3060 - Phase 5: Backend Implementation With Testing
# Authors: Nicholas Panait, Alden Chan, Alexander Naylor, Ryan De Sousa
#
# Group Name: Team Hubble
#
# Submission Date: March 31, 2023
# Version: 1.0
#  
# Description:
# The following program is a full implementation of the backend responsible for handling the
# Daily Transaction File and modifying the Accounts and Items File at the end of the day
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

import utility
import sys
import re

# The main method is used to start running the program in the command line by reading
# the user, items, and transaction files, making changes to those files, and saving them

# Lists storing the user, item, and daily transaction file data
users = []
items = []
transactions = []
new_items = []   # A list for items that were added today

# Path location for the user, item, and daily transaction file
user_file_path = ""
item_file_path = ""
transaction_file_path = ""

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Function Name: read_files
#
# Description:
# The following function handles reading in the current User, Items and Daily Transaction File
# then each line in a list that we will manipulate throughout or backend program as we process
# transactions before we write it back to their respective files after all our processing
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
def read_files():
    
    # opens the files in read only mode
    userFile = open(user_file_path, "r")
    itemFile = open(item_file_path, "r")
    transactionFile = open(transaction_file_path, "r")

    # Reads in the user file, stores the users as User objects in the users list
    Lines = userFile.readlines()
    for line in Lines:
        if (len(line) != 1):
            if (utility.validate_user(line[:-1])):
                line = re.split("\s+", line[:-1])
                user = utility.User(line[0], line[1], line[2], line[3])
            else:
                raise Exception('Format Error: User in user file not properly formatted')
            #user = utility.User(line[:16testBSUser], line[16:19], line[19:28], line[28:-1])
            users.append(user)

    # Reads in the item file, stores the items as Item objects in the items list
    Lines = itemFile.readlines()
    for line in Lines:
        if len(re.split("\s+", line[:-1])) == 5:
            if (utility.validate_item(line[:-1])):
                line = re.split("\s+", line[:-1])
                item = utility.Item(line[0], line[1], '                ', line[2], line[3], line[4])
            else:
                raise Exception('Format Error: Item in item file not properly formatted')
            #(item_name, seller, buyer, duration, min_bid, winning_bid):
        else:
            if (utility.validate_item(line[:-1])):
                line = re.split("\s+", line[:-1])
                item = utility.Item(line[0], line[1], line[2], line[3], line[4], line[5])
            else:
                raise Exception('Format Error: Item in item file not properly formatted')
        items.append(item)

    # Reads in the daily transaction file, stores the transactions in the transactions list
    Lines = transactionFile.readlines()
    acc = -1
    for line in Lines:
        acc += 1
        transactions.append(line[0:-1])

    # Closes the three files
    userFile.close()
    itemFile.close()
    transactionFile.close()

    if transactions[-1][:2] != "00" or not utility.validate_transaction(transactions[-1]):
        raise Exception('Format Error: Transaction file does not end in logout!')
        

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Function Name: write_files
#
# Description:
# The following function handles writing our modifications to the users and items lists back
# to their respective files
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
def write_files():
    userFile = open(user_file_path, "w")
    itemFile = open(item_file_path, "w")
    transactionFile = open(transaction_file_path, "w")
    #! removing the next two comments will make it so that running the backend clears the daily transaction file
    #transactionFile = open(transaction_file_path, "w")
    #transactionFile.close()

    for item in items:
        if (int(item.duration) > 1):
            if (new_items.__contains__(item)):
                item.duration = str(int(item.duration))
            else:
                item.duration = str(int(item.duration)-1)
            itemFile.write(str(item) + '\n')
        else:
            for user in users:
                if (user.username == item.seller):
                    credit_string = str(float(user.credit) + float(item.winning_bid))
                    if (credit_string[-2] == "."):
                        credit_string += "0"
                    credit_string = credit_string.zfill(9)
                    user.credit = credit_string
                    break

    # appends each user and item in their lists to the userFile and itemFile respectively
    for user in users:
        userFile.write(str(user) + '\n')

    transactionFile.write("")

    # Closes the userFile and itemFile
    userFile.close()
    itemFile.close()
    transactionFile.close()


def main():
    global users, items, transactions
    users,items,transactions = [],[],[]
    if (user_file_path[-4:] != ".txt"):
        raise Exception('Invalid file type for users file: ' + user_file_path)
    if (item_file_path[-4:] != ".txt"):
        raise Exception('Invalid file type for items file: ' + item_file_path)
    if (transaction_file_path[-4:] != ".txt"):
        raise Exception('Invalid file type for transaction file:' + transaction_file_path)
    # reads in the data from the three files
    read_files()
    

    # Edits the users and items lists based on the transaction codes
    for transaction in transactions:
        users, items = utility.process_transaction(transaction, users, items, new_items)

    # Replaces the old user and item files with the data in users and items lists
    write_files()

def arg_main(user_path, item_path, transaction_path):
    # a more convienient way to run the program from the tests
    global transaction_file_path
    transaction_file_path = transaction_path
    global item_file_path
    item_file_path = item_path
    global user_file_path
    user_file_path = user_path
    main()

#! Use the following command to run the python script directly
#* python3 main.py ../srcFront/UserAccountsFile.txt ../srcFront/AvailableItemsFile.txt ../srcFront/DailyTransactionFile.txt

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Function Name: main
#
# Description:
# The following function is run on startup, it will handle invalid input files and call the 
# appropriate functions to run our backend program
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
if __name__ == "__main__":
    # sets the file paths for the three files
    user_file_path = sys.argv[1]
    item_file_path = sys.argv[2]
    transaction_file_path = sys.argv[3]
    main()

