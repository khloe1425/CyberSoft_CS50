def print_pyramid(height):
    for line in range(height):
        print(" " * (height - line - 1), end="")
        print("#" * (line + 1))

height = int(input("Enter pyramid height (1-8): "))  # Get height with validation

# Ensure height is within the valid range (1 to 8)
if 1 <= height <= 8:
    print_pyramid(height)
else:
    print("Invalid height. Please enter a number between 1 and 8.")
