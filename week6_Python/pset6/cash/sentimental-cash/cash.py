from cs50 import get_float


def main():

    change = get_float("Change owed: \n")
    while change < 0:
        print("Try again!")
        change = get_float("Change owed: \n")

    # convert dollars input to cents
    change = int(change * 100)

    # compute change
    pay = coins_count(change)

    # print the number of coins to pe paid
    print(pay)


# count the change
def coins_count(change):

    # save the coins values in a list
    coins = [25, 10, 5, 1]

    count = 0

    # chech what's the biggest coin that fits in the change and update counter
    while change > 0:
        if change >= coins[0]:
            change = change - coins[0]
            count += 1
        elif change >= coins[1]:
            change = change - coins[1]
            count += 1
        elif change >= coins[2]:
            change = change - coins[2]
            count += 1
        elif change >= coins[3]:
            change = change - coins[3]
            count += 1

    return count


if __name__ == '__main__':
    main()
