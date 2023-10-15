#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // TODO: Prompt user for name 
    string name = get_string("What's is your name ? "); 
    printf("hello, world!\n");
    printf("hello, %s!\n", name);
}