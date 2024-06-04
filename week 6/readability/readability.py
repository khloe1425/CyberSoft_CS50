def calculate_index(text):
    """Calculates the Coleman-Liau index for readability."""
    letters = sum(char.isalpha() for char in text)
    words = len(text.split())
    sentences = sum(char in ".!?" for char in text)

    if words == 0:
        return 0

    avg_letters = (100.0 / words) * letters
    avg_sentences = (100.0 / words) * sentences

    return round(0.0588 * avg_letters - 0.296 * avg_sentences - 15.8)


def main():
    text = input("Text: ")
    index = calculate_index(text)

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()
