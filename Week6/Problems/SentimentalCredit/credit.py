def main():

    number = input("Number: ")

    calculate_checksum(number)
    check_card_length(number)

    print_issuing_company(number)


def calculate_checksum(card):
    """Calculates whether a card number is valid or not based on Luhn's Algorithm. Returns 'True' if valid, 'False' if not."""

    card_sum = 0

    for digit in reversed(range(0, len(card), 2)):
        multiplied_digit = int(card[digit]) * 2

        if len(str(multiplied_digit)) != 2:
            card_sum += multiplied_digit
        else:
            multiplied_digit = str(multiplied_digit)
            first, second = multiplied_digit[0], multiplied_digit[1]

            card_sum += int(first) + int(second)

    for digit in reversed(range(1, len(card), 2)):
        card_sum += int(card[digit])

    if card_sum % 10 == 0:
        return True
    else:
        return False


def check_card_length(card):
    """Checks for the length of the card number to be either 13, 15 or 16. Prints out 'INVALID' if it's not."""

    if len(card) != [13, 15, 16]:
        print("INVALID")


def print_issuing_company(card):
    """Prints out the name of the company that issued the card based on the first digit/digits. Prints out 'INVALID' if none matches."""

    if card.startswith("4"):
        print("VISA")
    elif card.startswith(("51", "52", "53", "54", "55")):
        print("MASTERCARD")
    elif card.startswith(("34", "37")):
        print("AMEX")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
