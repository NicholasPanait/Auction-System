import utility

# Creates a new user and adds them to the users list
def create(username, account_type, credit, password, users):
    user = utility.User(username, account_type, credit, password)
    users.append(user)