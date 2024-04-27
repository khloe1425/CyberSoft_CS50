#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    int count_letter = 0;
    int count_word = 1;
    int count_sentence = 0;
    char text[1000];
    printf("Text: ");
    fgets(text, sizeof(text), stdin);

    int text_length = strlen(text);
    int i;
    for (i = 0; i < text_length; i++)
    {
        if (isalpha(text[i]))
        {
            count_letter++;
        }
    }

    for (i = 0; i < text_length; i++)
    {
        if (isspace(text[i]))
        {
            count_word++;
        }
    }

    for (i = 0; i < text_length; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            count_sentence++;
        }
    }

    float calculation = (0.0588 * count_letter / count_word * 100) - (0.296 * count_sentence / count_word * 100) - 15.8;
    int index = round(calculation);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

