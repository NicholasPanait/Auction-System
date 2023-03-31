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
def advertise(item_name, seller_name, duration, min_bid, items,users):
    # Create a new Item and append it to the items list
    for user in users:
        if user.username == seller_name:
            if user.privilege_type[0] == 'B' or user.privilege_type == 'AM':
                raise Exception('ERROR: User does not have permission to advertise.')
            
    if float(min_bid) < 0.01:
        raise Exception('ERROR: Advertise min bid below 0.01')
    
    if int(duration) < 1:
        raise Exception('ERROR: Advertise duration below 1 day')

    new_item = utility.Item(item_name, seller_name, "               ", duration, min_bid, "00.00")
    items.append(new_item)
    return