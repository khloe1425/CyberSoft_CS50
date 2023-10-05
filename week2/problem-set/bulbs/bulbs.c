#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void binary_numbers(string message); 
void print_bulb(int bit);

int main(void)
{
    string message = get_string("Message: "); 
    binary_numbers(message);
}

// TODO: Turning message into binary numbers
void binary_numbers(string message)
{
    for (int i = 0; i < strlen(message); i++)
    {
        // Turning letter into numbers by ASCII
        int decimal = message[i]; 
        int binary[BITS_IN_BYTE]; 

        // Print binary 
        for (int j = BITS_IN_BYTE - 1; j >= 0; j--)
        {
            binary[j] = decimal % 2; 
            decimal /= 2; 
        }

        // From above binary, print emoji 
        for (int k = 0; k < BITS_IN_BYTE; k++)
        {
            print_bulb(binary[k]);
        }
        printf("\n");
    }
}

// TODO: Print emoji from binary numbers 
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
