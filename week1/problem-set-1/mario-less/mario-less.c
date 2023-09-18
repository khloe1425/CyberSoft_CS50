#include <cs50.h>
#include <stdio.h>

void left_pyramid(int num);
void right_pyramid(int num);

int main(void) 
{
    int height; 
    do
    {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);
    
    left_pyramid(height);
    right_pyramid(height);
}

// TODO: Build a left-aligned pyramid
void left_pyramid(int num)
{
    for (int i = 1; i <= num; i++)
    {
        for (int j = 1; j <= i; j++) 
        {
            printf("#");
        }
        printf("\n");
    }
}

// TODO: Build a right-aligned pyramid with dots 
void right_pyramid(int num)
{
    int height = num; 
    for (int i = 0; i <= num - 1; i++)
    {
        for (int j = 0; j <= num - 1; j++)
        {
            if (((height - 1) - j) > i)
            {
                printf(".");
            }
            else 
            {
                printf("#");
            }
        }
        printf("\n");
    }
}