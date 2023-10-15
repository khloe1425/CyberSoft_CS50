#include <stdio.h>
#include <cs50.h>

/**
 * 3 functions:
 *  - main
 *  - get_size
 *  - print_grid 
 *  => we abstracted away the essential problems within our program -> main is very short 
*/

int get_size(void);
void print_grid(int size);

int main(void)
{
    // Get size of grid
    int n = get_size();

    // Print grid of bricks 
    print_grid(n);
}

// Customize your function here 
int get_size(void)
{
    int n; 
    do
    {
        n = get_int("Size: "); 
    }
    while (n < 1);
    return n; 
}

void print_grid(int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}