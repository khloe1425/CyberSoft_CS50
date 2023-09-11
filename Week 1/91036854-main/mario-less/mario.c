#include <stdio.h>
#include <cs50.h>
#include <cs50.c>

int main(void)
{
     int height;

    // Nhập chiều cao từ người dùng
    do {
        printf("Nhap chieu cao (khong qua 8): ");
        scanf("%d", &height);
    } while (height <= 0 || height > 8);

    // Tạo kim tự tháp
    for (int i = 1; i <= height; i++) {
        // In khoảng trắng
        for (int j = 0; j < height - i; j++) {
            printf(" ");
        }

        // In ký tự #
        for (int j = 0; j < i; j++) {
            printf("#");
        }

        printf("\n");
    } 

    return 0;
}