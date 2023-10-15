#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Loop 1
    int i = 3; 
    while (i > 0)
    {
        printf("meow\n");
        i--;
    }

    // Loop 2
    for (int i = 0; i < 3; i++)
    {
        printf("meow meow\n");
    }

    // Loop 3
    int j = 0;
    while (j < 3)
    {
        printf("meow meow meow\n");
        j++;
    }
}