# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# File Name: delete.py
#
# Description:
# The following file contains the function used to handle "delete" transactions
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

import utility

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Function Name: advertise
#
# Description:
# The following function handles the "delete" transaction, which takes in a username to delete.
# The function then removes the user from the user list, and removes all items that they adverised.
# Then the function modifies the items and users lists to be written to the Item/User File later.
#
# Parameters:
# username - The user's name
# users - The list of Users storing the information from the Users File
# items - The list of Items storing the information from the Items File
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
def delete(username, users, items):
    buyers_to_refund = []
    amount_to_refund = []

    # Searches the items list for any instance where the deleted user is buying/selling an item
    acc = 0
    for item in items:
        # Deleted user is selling an item, refund the highest bidder
        if (item.seller == username):
            if item.buyer != '                ':
                buyers_to_refund.append(item.buyer)
                amount_to_refund.append(float(item.winning_bid))
            del items[acc]

        # Deleted user is buying an item, remove the item from sale
        if (item.buyer == username):
            del items[acc]
        acc += 1

    # Go though the list of highest bidders in need of a refund, refund them
    acc = 0
    for buyer in buyers_to_refund:
        for user in users:
            if (buyer == user.username):
                user.credit = utility.pad_number(str(float(user.credit) + float(amount_to_refund[acc])) + '0', 9)
        acc += 1

    # Delete the deleted user from the users list
    acc = 0
    no_error = False
    for user in users:
        if (user.username == username):
            del users[acc]
            no_error = True
            break
        acc += 1
    if no_error == False:
        print('Error: User does not exist in Users File!')
        return
    return