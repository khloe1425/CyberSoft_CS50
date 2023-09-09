#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string s = get_string("Text: ");

    int letterNumber = count_letters(s);

    int wordNumber = count_words(s);

    int sentenceNumber = count_sentences(s);

    float L = letterNumber / ((float) wordNumber / 100);

    float S = sentenceNumber / ((float) wordNumber / 100);

    float index = 0.0588 * L - 0.296 * S - 15.8;

    int grade = round(index);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 1 && grade < 16)
    {
        printf("Grade %i\n", grade);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int count_letters(string text)
{
    int count = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        char c = text[i];
        if (isalpha(c))
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    int words = 1;
    char c;

    for (int i = 0; i < strlen(text); i++)
    {
        c = text[i];
        if (c == ' ')
        {
            words++;
        }
    }

    return words;
}

int count_sentences(string text)
{
    int sentence = 0;
    char c;

    for (int i = 0; i < strlen(text); i++)
    {
        c = text[i];
        if (c == '.' || c == '?' || c == '!')
        {
            sentence++;
        }
    }

    return sentence;
}