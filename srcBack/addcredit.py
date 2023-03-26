import utility
#TODO: Increase the credit of an existing user and update the users list

def addcredit(username, credit, users):
    for user in users:
        if (user.username == username):
            float_cred = float(user.credit)
            float_cred += float(credit)
            str_cred = str(float_cred)
            if (str_cred[-3] != "."):
                str_cred+=".00"
            str_cred = utility.pad_string(str_cred, 9)
            user.credit = str_cred