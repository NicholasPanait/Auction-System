# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# File Name: changepassword.py
#
# Description:
# The following file contains the function used to handle "changepassword" transactions
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Function Name: advertise
#
# Description:
# The following function handles the "changepassword" transaction, it takes in a username and the new password.
# Using these parameters, the function modifies the users list to be written to the Users File later.
#
# Parameters:
# username - The user's name
# new_password - The new password which will replace the current password
# users - The list of Users storing the information from the Users File
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
def changepassword(username, new_password, users):
    # find the user in the users list
    for user in users:
        if (user.username == username):
            # Update their password
            user.password = new_password
    return