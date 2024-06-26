# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# File Name: advertise.py
#
# Description:
# The following file contains the function used to handle "advertise" transactions
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

import utility

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Function Name: advertise
#
# Description:
# The following function handles the "advertise" transaction, it takes in a item name,
# seller name, duration, and min bid. Using these parameters, the function modifies the items list to be written
# to the Item File later.
#
# Parameters:
# item_name - The item's name
# seller_name - The username of the seller
# duration - The remaining duration of the auction
# min_bid - The starting bid of the auction
# items - The list of Items storing the information from the Items File
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
def advertise(item_name, seller_name, duration, min_bid, users, items, new_items):
    # Create a new Item and append it to the items list
    for user in users:
        if user.username == seller_name:
            if user.privilege_type[0] == 'B' or user.privilege_type == 'AM':
                print('ERROR: User does not have permission to advertise.')
                return
            
    if float(min_bid) < 0.01:
        print('ERROR: Advertise min bid below 0.01')
        return
    
    if int(duration) < 1:
        print('ERROR: Advertise duration below 1 day')
        return

    new_item = utility.Item(item_name, seller_name, "               ", duration, min_bid, "00.00")
    items.append(new_item)
    new_items.append(new_item)
    return