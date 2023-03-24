import utility
#TODO: Increase the credit of an existing user and update the users list

def addcredit(username, credit, users):
    for i in users:
        if (i.username == username):
            float_cred = float(i.credit)
            float_cred += float(credit)
            str_cred = str(float_cred)
            if (str_cred[-3] != "."):
                str_cred+="0"

            while(len(str_cred) < 9):
                str_cred = "0"+str_cred
            i.credit = str_cred