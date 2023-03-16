import utility
import sys

users = []
items = []
transactions = []

user_file_path = ""
item_file_path = ""
transaction_file_path = ""

def read_files():
    userFile = open(user_file_path, "r")
    itemFile = open(item_file_path, "r")
    transactionFile = open(transaction_file_path, "r")

    print("users:")
    Lines = userFile.readlines()
    for line in Lines:
        username = line[:16]
        user = utility.User(line[:16], line[16:19], line[19:28], line[28:-1])
        users.append(user)

    for user in users:
        print(str(user))

    # TODO: Check if items are 19 characters long or 25 characters
    print("items:")
    Lines = itemFile.readlines()
    for line in Lines:
        item = utility.Item(line[:26], line[26:42], line[42:58], line[58:62], line[62:69], line[69:-1])
        items.append(item)

#Washers (5pcs)      testAAUser      testAAUser      002 002.00 004.00

    for item in items:
        print(str(item))

    print("transactions:")
    Lines = transactionFile.readlines()
    for line in Lines:
        transactions.append(line[0:-1])

    for transaction in transactions:
        print(transaction)


    userFile.close()
    itemFile.close()
    transactionFile.close()

def write_files():
    userFile = open(user_file_path, "w")
    itemFile = open(item_file_path, "w")
    #transactionFile = open(transaction_file_path, "w")
    #transactionFile.close()

    for user in users:
        userFile.write(str(user) + '\n')

    for item in items:
        itemFile.write(str(item) + '\n')

    userFile.close()
    itemFile.close()

# python3 main.py ../srcFront/UserAccountsFile.txt ../srcFront/AvailableItemsFile.txt ../srcFront/DailyTransactionFile.txt
if __name__ == "__main__":
    user_file_path = sys.argv[1]
    item_file_path = sys.argv[2]
    transaction_file_path = sys.argv[3]
    read_files()

    for transaction in transactions:
        users, items = utility.process_transaction(transaction, users, items)
    
    write_files()