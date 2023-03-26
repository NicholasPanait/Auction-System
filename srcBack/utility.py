import create
import delete
import advertise
import addcredit
import re

# Class used to store user information: Username, Privilege Type, Available Credit, and Password
class User:
    def __init__(self, username, privilege_type, credit, password):
        self.username = username
        self.privilege_type = privilege_type
        self.credit = credit
        self.password = password

    def __str__(self):
        return pad_string(self.username, 16) + pad_string(self.privilege_type, 3) + pad_string(self.credit, 10) + self.password

# Class used to store item information: Item Name, Seller, Buyer, Duration, Minimum Bid, Winning Bid
class Item:
    def __init__(self, item_name, seller, buyer, duration, min_bid, winning_bid):
        self.item_name = item_name
        self.seller = seller
        self.buyer = buyer
        self.duration = duration
        self.min_bid = min_bid
        self.winning_bid = winning_bid

    def __str__(self):
        return pad_string(self.item_name, 25) + pad_string(self.seller, 16) + pad_string(self.buyer, 16) + pad_number(self.duration, 2) + " " + pad_number(self.min_bid, 6) + " " + pad_number(self.winning_bid, 6)

def pad_string(string, length):
    result = string
    for i in range(length-len(string)):
        result += " "
    return result

def pad_number(number, length):
    zeros = ''
    for i in range(length-len(number)):
        zeros += '0'
    return zeros + number

# Takes a line of the transaction file and calls the appropriate function
def process_transaction(transaction, users, items):
    transactions = re.split("\s+", transaction)
    if transactions[0] == "00":
        print("END OF SESSION")
    elif transactions[0] == "01":
        if len(transactions) < 5: transactions += "temp"
        create.create(transactions[1], transactions[2], transactions[3], transactions[4], users)
        print("CREATE")
    elif transactions[0] == "02":
        # TODO
        print("DELETE")
    elif transactions[0] == "03":
        # TODO
        print("ADVERTISE")
    elif transactions[0] == "04":
        # TODO
        print("BID")
    elif transactions[0] == "05":
        # TODO
        print("REFUND")
    elif transactions[0] == "06":
        # TODO
        addcredit.addcredit(transaction[1],transaction[2],users)
        print("ADDCREDIT")
    elif transactions[0] == "07":
        # TODO
        
        print("CHANGEPASSWORD")
    return users, items

# bounds 32 - 126, diff is 94

def encrypt(input):
    password = ""
    ascii_values = list(input.encode("ascii"))
    for value in ascii_values:
        if value >= 123:
            password += chr(value-90)
        else:
            password += chr(value+4)
    return password

def decrypt(input):
    password = ''
    for letter in input:
        # abcd
        # [97, 98, 99, 100]
        nums = list(letter.encode("ascii"))
        for number in nums:
            if number <= 35:
                password += chr(number+90)
            else:
                password += chr(number-4)

    for i in password:
        print(i)
    return password