# TODO: Delete an existing user and update the users list

def delete(username, users, items):
    acc = 0
    no_error = False
    for item in items:
        if (item.buyer == username or item.seller == username):
            # users.pop(acc)
            del users[acc]
            no_error = True
            break
        acc += 1
    if no_error == False:
        print("Error: Item does not exist in Items File!")
    acc = 0
    no_error = False
    for user in users:
        if (user.username == username):
            # users.pop(acc)
            del users[acc]
            no_error = True
            break
        acc += 1
    if no_error == False:
        print("Error: User does not exist in Users File!")
    return