import utility
# TODO: Create a new auction and append it to the items list

def advertise(item_name, seller_name, duration, min_bid, items):
    new_item = utility.Item(item_name, seller_name, "               ", duration, min_bid, "00.00")
    items.append(new_item)