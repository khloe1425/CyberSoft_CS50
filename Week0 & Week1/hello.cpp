#include <stdio.h>

int main() {
    while (1) {
        char name[256];

        printf("What's your name? ");
        scanf("%s", name);

        printf("hello, %s\n", name);
    }

    return 0;
}

