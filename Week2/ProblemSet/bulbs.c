#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string s = get_string("Message: ");
    // Iterate over each character in the message
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // Get the ASCII value of the character
        int ascii_value = (int) s[i];

        // Convert the ASCII value to binary
        for (int j = BITS_IN_BYTE - 1; j >= 0; j--)
        {
            int bit = (ascii_value >> j) & 1;
            print_bulb(bit);
        }

        // Print a newline after each 8-bit "byte"
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
