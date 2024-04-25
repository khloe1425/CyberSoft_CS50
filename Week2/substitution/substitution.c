#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_LENGTH 26

// Function to check if the key is valid
bool is_valid_key(string key)
{
    // Check if the key length is 26
    if (strlen(key) != ALPHABET_LENGTH)
    {
        return false;
    }

    // Initialize an array to keep track of used characters
    bool used[ALPHABET_LENGTH] = {false};

    // Check if the key contains only alphabetic characters and each letter appears exactly once
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
        int index = tolower(key[i]) - 'a';
        if (used[index])
        {
            return false;
        }
        used[index] = true;
    }

    return true;
}

// Function to encrypt plaintext using the substitution cipher
string encrypt(string plaintext, string key)
{
    string ciphertext = plaintext;

    for (int i = 0; ciphertext[i] != '\0'; i++)
    {
        if (isalpha(ciphertext[i]))
        {
            char c = isupper(ciphertext[i]) ? 'A' : 'a';
            ciphertext[i] = isupper(plaintext[i]) ? toupper(key[plaintext[i] - c])
                                                  : tolower(key[plaintext[i] - c]);
        }
    }

    return ciphertext;
}

int main(int argc, string argv[])
{
    // Check if there is exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check if the key is valid
    if (!is_valid_key(argv[1]))
    {
        printf("Key must contain 26 unique alphabetic characters.\n");
        return 1;
    }

    // Get plaintext from user
    string plaintext = get_string("plaintext: ");

    // Encrypt plaintext using the provided key
    string ciphertext = encrypt(plaintext, argv[1]);

    // Output ciphertext
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}
