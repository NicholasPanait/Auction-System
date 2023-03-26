#
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

import utility
import sys
import re

# The main method is used to start running the program in the command line by reading
# the user, items, and transaction files, making changes to those files, and saving them

# Lists storing the user, item, and daily transaction file data
users = []
items = []
transactions = []

# Path location for the user, item, and daily transaction file
user_file_path = ""
item_file_path = ""
transaction_file_path = ""

# Reads in the user, item, and transaction files
# Stores the data from these files into users, items, and transactions lists
def read_files():
    # opens the files in read only mode
    userFile = open(user_file_path, "r")
    itemFile = open(item_file_path, "r")
    transactionFile = open(transaction_file_path, "r")

    # Reads in the user file, stores the users as User objects in the users list
    Lines = userFile.readlines()
    for line in Lines:
        if (len(line) != 1):
            line = re.split("\s+", line[:-1])
            user = utility.User(line[0], line[1], line[2], line[3])
            #user = utility.User(line[:16], line[16:19], line[19:28], line[28:-1])
            users.append(user)

    # Reads in the item file, stores the items as Item objects in the items list
    Lines = itemFile.readlines()
    for line in Lines:
        line = re.split("\s+", line[:-1])
        if len(line) == 5:
            item = utility.Item(line[0], line[1], '                ', line[2], line[3], line[4])
        else:
            item = utility.Item(line[0], line[1], line[2], line[3], line[4], line[5])
        #item = utility.Item(line[:26], line[26:42], line[42:58], line[58:62], line[62:69], line[69:-1])
        items.append(item)
        # ['BulkNails(5000pcs)', 'testAAUser', '009050.00', '00.00', '']

        # BulkNails(5000pcs) testAAUser                             02 009050.00 00.00

    # Reads in the daily transaction file, stores the transactions in the transactions list
    Lines = transactionFile.readlines()
    for line in Lines:
        transactions.append(line[0:-1])

    # Closes the three files
    userFile.close()
    itemFile.close()
    transactionFile.close()

# Writes to the user, item, and transaction files
# Clears all three files, stores new data in the userFile and itemFile
def write_files():
    userFile = open(user_file_path, "w")
    itemFile = open(item_file_path, "w")
    #! removing the next two comments will make it so that running the backend clears the daily transaction file
    #transactionFile = open(transaction_file_path, "w")
    #transactionFile.close()

    # appends each user and item in their lists to the userFile and itemFile respectively
    for user in users:
        userFile.write(str(user) + '\n')

    for item in items:
        itemFile.write(str(item) + '\n')

    # Closes the userFile and itemFile
    userFile.close()
    itemFile.close()

#! Use the following command to run the python script directly
# python3 main.py ../srcFront/UserAccountsFile.txt ../srcFront/AvailableItemsFile.txt ../srcFront/DailyTransactionFile.txt
if __name__ == "__main__":
    # sets the file paths for the three files
    user_file_path = sys.argv[1]
    item_file_path = sys.argv[2]
    transaction_file_path = sys.argv[3]

    # reads in the data from the three files
    read_files()

    # Edits the users and items lists based on the transaction codes
    for transaction in transactions:
        users, items = utility.process_transaction(transaction, users, items)
    
    # Replaces the old user and item files with the data in users and items lists
    write_files()