#include <stdio.h>

int main() {
  int change_owed;
  int dollars;
  int quarters;
  int dimes;
  int nickels;
  int pennies;
  printf("Nhap so tien can tra: ");
  scanf("%d", &change_owed);

  dollars = change_owed / 100;
  change_owed %= 100;
  quarters = change_owed / 25;
  change_owed %= 25;
  dimes = change_owed / 10;
  change_owed %= 10;
  nickels = change_owed / 5;
  change_owed %= 5;
  pennies = change_owed;
  printf("\nSo tien can tra:\n");
  printf("%d to 1 do la\n", dollars);
  printf("%d xu 25 xu\n", quarters);
  printf("%d xu 10 xu\n", dimes);
  printf("%d xu 5 xu\n", nickels);
  printf("%d xu 1 xu\n", pennies);
  return 0;
}

