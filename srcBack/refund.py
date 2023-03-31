# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# File Name: refund.py
#
# Description:
# The following file contains the function used to handle "refund" transactions
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

import utility

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Function Name: advertise
#
# Description:
# The following function handles the "refund" transaction, it takes in a buyer, the recipient
# of the refund, and the seller, the person paying, and modifies the users list to be written
# to the User File later.
#
# Parameters:
# buyer_name - The username of the buyer
# seller_name - The username of the seller
# credit - The amount of credits to bid on the item
# users - The list of Users storing the information from the Users File
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
def refund(buyer_name, seller_name, credit, users):
    bacc = 0
    sacc = 0
    for user in users:
        if (buyer_name == user.username):
            break
        bacc += 1
    for user in users:
        if (seller_name == user.username):
            break
        sacc += 1
    if (sacc >= len(users)):
        print("Error: Seller does not exist")
        return
    if (bacc >= len(users)):
        print("Error: Buyer does not exist")
        return
    if (float(users[bacc].credit) + float(credit) > 999999.0):
        print("Error: Buyer credit would exceed $999,999 if refund was processed")
        return
    if float(users[sacc].credit) >= float(credit):
        users[bacc].credit = utility.pad_number(str(float(users[bacc].credit) + float(credit)) + '0', 9)
        users[sacc].credit = utility.pad_number(str(float(users[sacc].credit) - float(credit)) + '0', 9)
    else:
        print("Error: Seller does not have enough money for a refund")

    return
