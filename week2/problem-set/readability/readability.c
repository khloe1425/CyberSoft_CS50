#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int result_index(int letters, int words, int sentences);

int main(void) 
{
    string text = get_string("Text: ");
 
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    int index = result_index(letters, words, sentences);

    printf("%i letters\n", letters);
    printf("%i words\n", words);
    printf("%i sentences\n", sentences);

    // Print reading level 
    if (index < 1)
    {
        printf("Before Grade 1");
    }
    else if (index > 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %i", index);
    }
    printf("\n");
}

// TODO: Function to count the number of letters
int count_letters(string text)
{
    int count = 0; 
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count; 
}

// TODO: Function to count the number of words 
int count_words(string text)
{
    int count = 1; 
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            count++; 
        }
    }
    return count; 
}

// TODO: Function to count the number of sentences 
int count_sentences(string text)
{
    int count = 0; 
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            count++; 
        }
    }
    return count; 
}

// TODO: Calculate index from 3 above counts 
int result_index(int letters, int words, int sentences)
{
    double L = letters / (float) words * 100; 
    double S = sentences / (float) words * 100; 
    
    int index = round(0.0588 * L - 0.296 * S - 15.8); 
    return index; 
}