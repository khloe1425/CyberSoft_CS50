#include <stdio.h>
#include <cs50.h>

const int N = 4; 

float average(int length, int numbers[]);

int main(void)
{
    // Scores
    int scores[N];
    for (int i = 0; i < N; i++)
    {
        scores[i] = get_int("Score %i: ", i+1);
    }

    // Print average
    printf("Average: %f\n", average(N, scores));
}

float average(int length, int array[])
{
    int sum = 0; 
    for (int i = 0; i < length; i++)
    {
        sum = sum + array[i];
    }
    return sum / (float) length; 
}