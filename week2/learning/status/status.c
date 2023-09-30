#include <stdio.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("missing command-line argument\n");
    }
    else 
    {
        printf("hello, %s\n", argv[1]);
    }
}