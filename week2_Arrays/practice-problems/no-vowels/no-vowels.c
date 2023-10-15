// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replaceVowels(string word);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1; 
    }

    string converted = replaceVowels(argv[1]);
    printf("%s\n", converted);
}

string replaceVowels(string word)
{
    string output = word;
    for (int i = 0; i < strlen(output); i++)
    {
        if (output[i] == 'a')
        {
            output[i] = '6';
        }
        else if (output[i] == 'e')
        {
            output[i] = '3';
        }
        else if (output[i] == 'i')
        {
            output[i] = '1';
        }
        else if (output[i] == 'o')
        {
            output[i] = '0';
        }
    }
    return output; 
}

