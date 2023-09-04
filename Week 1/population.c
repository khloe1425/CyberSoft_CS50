#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size

    int nStart;
    do
    {
      nStart = get_int("Positive Integer: ");
    }
    while (nStart < 9);

    // TODO: Prompt for end size
    int nEnd;
    do
    {
      nEnd = get_int("Positive Integer: ");
    }
    while (nEnd < nStart);

    // TODO: Calculate number of years until we reach threshold
    int nYear = 0;
    while (nStart < nEnd){
        nStart = nStart + (nStart/3) - (nStart/4);
        nYear++;
    }

    // TODO: Print number of years
    printf("The number of year is %i\n", nYear);
}
