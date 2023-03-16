import create
import delete
import advertise

class User:
    def __init__(self, username, privilege_type, credit, password):
        self.username = username
        self.privilege_type = privilege_type
        self.credit = credit
        self.password = password

    def __str__(self):
        user = self.username + (16 - len(self.username))*" "
        return user + self.privilege_type + self.credit + self.password
    
class Item:
    def __init__(self, item_name, seller, buyer, duration, min_bid, winning_bid):
        self.item_name = item_name
        self.seller = seller
        self.buyer = buyer
        self.duration = duration
        self.min_bid = min_bid
        self.winning_bid = winning_bid

    def __str__(self):
        item_name = self.item_name + (20 - len(self.item_name))*" "
        seller_name = self.seller + (16 - len(self.seller))*" "
        buyer_name = self.buyer + (16 - len(self.buyer))*" "
        return item_name + seller_name + buyer_name + self.duration + self.min_bid + self.winning_bid

# Takes a line of the transaction file and calls the appropriate function
def process_transaction(transaction, users, items):
    if transaction[:2] == "00":
        print("END OF SESSION")
    elif transaction[:2] == "01":
        if len(transaction) < 32: transaction += "temp"
        create.create(transaction[3:19], transaction[3:21], transaction[22:31], transaction[32:], users)
        print("CREATE")
    elif transaction[:2] == "02":
        print("DELETE")
    elif transaction[:2] == "03":
        print("ADVERTISE")
    elif transaction[:2] == "04":
        print("BID")
    elif transaction[:2] == "05":
        print("REFUND")
    elif transaction[:2] == "06":
        print("ADDCREDIT")
    elif transaction[:2] == "07":
        print("CHANGEPASSWORD")
    return users, items