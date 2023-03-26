# TODO: Modify the winning bid on an existing item and update the items list 
# TODO: Compare with item highest bid in items list and update the items
# TODO: Decide on how to check enough credit for bid

def bid(item_name, seller_name, buyer_name, bid, items):
    total_bid = bid
    for item in items:
        if (item.buyer == buyer_name):
            total_bid += float(item.winning_bid)

    for item in items:
        if (item.item_name == item_name):
            item.winning_bid = bid
            item.buyer = buyer_name
    
    return