import utility

def create(username, account_type, credit, password, users):
    user = utility.User(username, account_type, credit, password)
    users.append(user)