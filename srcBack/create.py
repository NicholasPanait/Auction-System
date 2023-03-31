# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# File Name: create.py
#
# Description:
# The following file contains the function used to handle "create" transactions
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

import utility

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Function Name: advertise
#
# Description:
# The following function handles the "create" transaction, it takes in the new user's username
# the account type, starting credit, encrypted password, and the users list storing the information
# from the Users file. It will add this new user's information to the users list to be written
# to the Users file later.
#
# Parameters:
# username - The name of the new account
# account_type - The privilege of the new account
# credit - The credits that the new account will have
# password - The password of the new account
# users - The list of Users storing the information from the Users File
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
def create(username, account_type, credit, password, users):
    # Creates a new user and adds them to the users list
    acc = 0
    no_error = True
    for user in users:
        if (user.username == username):
            no_error = False
        acc += 1
    if no_error == False:
        print('Error: User already exists in Users File!')
        return
    user = utility.User(username, account_type, credit, password)
    users.append(user)