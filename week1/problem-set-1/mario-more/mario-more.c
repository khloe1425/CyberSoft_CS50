#include <stdio.h>
#include <cs50.h>

void pyramid(int n);

int main(void)
{
    int height; 
    do
    {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);

    pyramid(height);
}

// TODO: Using 3 loops to print # or space with condition
void pyramid(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            if ((n - 1) - j > i)
            {
                printf(" ");
            }
            else if (j == n)
            {
                printf("  ");
            }
            else 
            {
                printf("#");
            }
        }
        for (int z = 0; z <= i; z++)
        {
            printf("#"); 
        }
        printf("\n");
    }
}