#include <cs50.h>
#include <stdio.h>

void left_pyramid(int num);

int main(void) 
{
    int height; 
    do
    {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);
    
    left_pyramid(height);
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