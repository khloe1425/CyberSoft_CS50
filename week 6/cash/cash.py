def main():
    cents = get_positive_input("Change owed: ")
    coins = calculate_coins(cents)
    print(f"You can make change with {coins} coins.")


def get_positive_input(prompt):
    while True:
        try:
            value = float(input(prompt))
            if value > 0:
                return int(value * 100)  # Convert to cents and return as integer
            else:
                print("Invalid amount: Please enter a positive number.")
        except ValueError:
            print("Invalid input: Please enter a number.")


def calculate_coins(cents):
    coins = 0
    for coin in [25, 10, 5, 1]:
        coins += cents // coin  # Efficient integer division for coins
        cents %= coin  # Update remaining cents after each coin calculation
    return coins


if __name__ == "__main__":
    main()
