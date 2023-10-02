def main():
    dollars = get_input()
    amount = get_coins(dollars)

    print(amount)


def get_input():
    """Prompts user for a positive float. Returns that amount times 100 as an integer."""

    while True:
        try:
            dollars = float(input("Change owed: "))

            if dollars > 0:
                return int(dollars * 100)

        except ValueError as error:
            print(error)


def get_coins(dollars):
    """Returns the smallest number of coins that can be given for the change owed."""

    counter = 0

    for coin in [25, 10, 5, 1]:
        amount = int(dollars / coin)
        dollars -= amount * coin
        counter += amount

        if dollars == 0:
            break

    return counter


if __name__ == "__main__":
    main()
