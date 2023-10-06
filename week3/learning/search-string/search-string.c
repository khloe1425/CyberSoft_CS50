#include <cs50.h>
#include <stdio.h>
#include <string.h>

// linear search 
int main(void)
{
    string strings[] = {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};
    
    string s = get_string("String: ");
    for (int i = 0; i < 6; i++) // segmentation fault if i < 7 
    {
        // compare if strings[i] == s => strcmp from string library of cs50
        if (strcmp(strings[i], s) == 0)
        {
            printf("Found\n");
            return 0; 
        }
    }
    printf("Not found\n");
    return 1; 
}