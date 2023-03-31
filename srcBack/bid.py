# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# File Name: bid.py
#
# Description:
# The following file contains the function used to handle "bid" transactions
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

import utility

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Function Name: advertise
#
# Description:
# The following function handles the "bid" transaction, it will take in the item's name, seller's
# username, new bidder's username, new bid amount, the users list storing all our changes to
# the User File, and our items list storing all our changes to our Items File. It will modify
# the item's entry in the items list so it can be written to the new Items File later.
#
# Parameters:
# item_name - The item's name
# seller_name - The username of the seller
# buyer_name - The username of the buyer
# bid - The amount of credits to bid on the item
# users - The list of Users storing the information from the Users File
# items - The list of Items storing the information from the Items File
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
def bid(item_name, seller_name, buyer_name, bid, users, items):
    Admin = False
    if (seller_name == buyer_name):
        print("Error: you can\'t bid on your own item")
        return

    if (float(bid) < 0.01):
        print("Error: Bid value too low")
        return
    
    # find the buyer in the items list
    old_buyer = ""
    old_credits = 0
    iacc = -1
    for item in items:
        iacc += 1
        if (item.item_name == item_name and item.seller == seller_name):
            old_buyer = item.buyer
            old_credits = item.winning_bid
            break

    
    # find the buyer in the users list
    oacc = -1
    uacc = -1
    buyer_set = False
    old_set = False
    for user in users:
        if buyer_set == False:
            uacc += 1
        if  not old_set:
            oacc +=1
        if (user.username == buyer_name and buyer_set == False):
            buyer_set = True
            if (user.privilege_type == "AA"):
                Admin = True
        elif (user.username == old_buyer):
            old_set=True

    if((float(bid) < float(old_credits)*1.05) and not Admin):
        print("Error: bid does not exceed 5% of the previous bid")
        return        
    else:
        users[oacc].credit = utility.pad_number(str(float(users[oacc].credit) + float(old_credits))+"0",9)
    
    # place the bid on the item
    if (float(bid) <= float(users[uacc].credit)):
        for item in items:
            if (item.item_name == item_name and item.seller == seller_name):
                item.winning_bid = bid
                item.buyer = buyer_name
                users[uacc].credit = utility.pad_number(str(float(users[uacc].credit) - float(bid)) + "0", 9)
                items[iacc].buyer = buyer_name

    return