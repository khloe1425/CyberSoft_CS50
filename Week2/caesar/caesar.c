#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    // Check if there is exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check if the command-line argument contains only digits
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert the command-line argument to an integer
    int k = atoi(argv[1]);

    // Get plaintext from user
    string plaintext = get_string("plaintext: ");

    // Encrypt plaintext
    printf("ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        if (isupper(plaintext[i]))
        {
            printf("%c", 'A' + (plaintext[i] - 'A' + k) % 26);
        }
        else if (islower(plaintext[i]))
        {
            printf("%c", 'a' + (plaintext[i] - 'a' + k) % 26);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");

    return 0;
}
