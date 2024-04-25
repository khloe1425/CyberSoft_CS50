#include <stdio.h>

int main() {
    int height;
    
    do {
        printf("height: ");
        scanf("%d", &height);
        
        if (height <= 1) {
            printf("vui long nhap so >=1 \n");
        }
    } while (height <= 1);
    
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= i; j++) {
            printf("#");
        }
        printf("\n");
    }
    
    return 0;
}

