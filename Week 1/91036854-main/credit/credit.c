#include <cs50.h>
#include <stdio.h>

int main(void)
{
       long long creditCardNumber;

    // Nhập số thẻ tín dụng từ người dùng
    do {
        creditCardNumber = get_long("Nhap so the tin dung: ");
    } while (creditCardNumber <= 0);

    // Tính tổng các chữ số đã nhân 2
    int sumDoubled = 0;
    long long tempNumber = creditCardNumber;
    int count = 0;

    while (tempNumber > 0) {
        int digit = tempNumber % 10;
        if (count % 2 == 1) {
            int doubled = digit * 2;
            while (doubled > 0) {
                sumDoubled += doubled % 10;
                doubled /= 10;
            }
        } else {
            sumDoubled += digit;
        }
        tempNumber /= 10;
        count++;
    }

    // Kiểm tra hợp lệ và loại thẻ
    if (sumDoubled % 10 == 0) {
        if ((creditCardNumber >= 340000000000000 && creditCardNumber < 350000000000000) ||
            (creditCardNumber >= 370000000000000 && creditCardNumber < 380000000000000)) {
            printf("AMEX\n");
        } else if (creditCardNumber >= 5100000000000000 && creditCardNumber < 5600000000000000) {
            printf("MASTERCARD\n");
        } else if ((creditCardNumber >= 4000000000000 && creditCardNumber < 5000000000000) ||
                   (creditCardNumber >= 4000000000000000 && creditCardNumber < 5000000000000000)) {
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
    } else {
        printf("INVALID\n");
    }

    return 0;
}