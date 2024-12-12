def main():
    dollars = get_input()
    amount = get_coins(dollars)

    print(amount)


def get_input():
    while True:
        try:
            dollars = float(input("Change owed: "))

            if dollars > 0:
                return int(dollars * 100)

        except ValueError as error:
            print(error)


def get_coins(dollars):
    counter = 0

    # Loop
    for coin in [25, 10, 5, 1]:
        amount = int(dollars / coin)
        dollars -= amount * coin
        counter += amount

        # Break out of the loop .
        if dollars == 0:
            break

    return counter


if __name__ == "__main__":
    main()
