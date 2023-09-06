#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("N: ");
    }
    while(n < 1 || n > 8);

    for (int i = 1; i <= n; i++)
    {
        // Print leading spaces
        for (int j = 1; j <= n - i; j++)
        {
            printf(" ");
        }

        // Print '#' characters
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }

        // Move to the next line
        printf("\n");
    }
}