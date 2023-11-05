# TODO

def main():
    dollars = get_input()
    amount = get_coins(dollars)

    print(amount)


def get_input():
    # Prompt user for a positive number

    while True:
        try:
            dollars = float(input("Change owed: "))

            if dollars > 0:
                return int(dollars * 100)

        except ValueError as error:
            print(error)


def get_coins(dollars):
    # Return the smallest number of coins

    counter = 0

    # Loop through a list that contains all coins available.
    for coin in [25, 10, 5, 1]:
        # Divide the dollars by each coin and store integer result in a temporary variable.
        amount = int(dollars / coin)
        # Substract from dollars that result multiplied by the coin.
        dollars -= amount * coin
        # Add to counter the result of the division.
        counter += amount

        # Break out of the loop when dollars reach 0.
        if dollars == 0:
            break

    return counter


if __name__ == "__main__":
    main()
