#include <stdio.h>

int main(void)
{
     char name[100];

    // Nhập tên từ người dùng
    printf("Nhap ten cua ban: ");
    fgets(name, sizeof(name), stdin);

    // Loại bỏ ký tự xuống dòng '\n' ở cuối tên nếu có
    name[strcspn(name, "\n")] = '\0';

    // Nếu người dùng không nhập tên, in ra "Hello, World!"
    if (strlen(name) == 0) {
        printf("Hello, World!\n");
    } else {
        printf("Hello, %s!\n", name);
    }

    return 0;
}  