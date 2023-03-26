# TODO: Change the password of a user in the users list
import utility

def changepassword(username, new_password, users):
    for user in users:
        if (user.username == username):
            user.password = new_password
    return