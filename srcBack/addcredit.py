# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# File Name: addcredit.py
#
# Description:
# The following file contains the function used to handle "addcredit" transactions
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

import utility

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Function Name: addcredit
#
# Description:
# The following function handles the "addcredit" transaction, it takes in a username, the recipient
# of the added credits, and the amount of credits to add, and modifies the users list to be written
# to the User File later.
#
# Parameters:
# username - The user's name
# credit - The amount of credits to add
# users - The list of Users storing the information from the Users File
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
def addcredit(username, credit, users):
    # Search the users list for the user
    for user in users:
        if (user.username == username):
            # add credits to the user
            float_cred = float(user.credit)
            float_cred += float(credit)
            str_cred = str(float_cred)

            # ensure proper formatting
            if (str_cred[-3] != "."):
                str_cred+=".00"
            str_cred = utility.pad_string(str_cred, 9)
            user.credit = str_cred
    return