#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // operator 1
    printf("Sum\n");
    int x = get_int("x: ");
    int y = get_int("y: ");

    printf("sum: %i\n", x + y);

    // operator 2 
    printf("Division\n");
    long a = get_long("a: ");
    long b = get_long("b: ");

    printf("division: %li\n", a / b);

    // operator 3
    printf("Division with float\n");
    long n = get_long("n: ");
    long m = get_long("m: ");

    float l = (float) n / (float) m; 
    printf("result 1: %f\n", l);

    // operator 4 => floating-point imprecision 
    printf("Division with double\n");
    long a1 = get_long("a1: ");
    long b1 = get_long("b1: ");

    // "double" is at least more precise than using "float"
    double c = (double) a1 / (double) b1; 
    printf("result 2: %.20f\n", c);
}