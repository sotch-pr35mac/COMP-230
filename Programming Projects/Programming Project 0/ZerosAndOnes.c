/*
  Author: Preston Stosur-Bassett
  Date: 1.4.15
  Description: This is no better than a hello world.
*/

#include<stdio.h>

main() {
  int zeroCounter = 0;
  int oneCounter = 0;
  int i = 0;
  char currentChar;

  printf("Please enter 32 0/1 digits: ");
  while(i < 32) {
    scanf("%c", &currentChar);

    if(currentChar == '0') {
      zeroCounter++;
    }
    else if(currentChar == '1') {
      oneCounter++;
    }

    i++;
  }

  printf("You had %i 0's and %i 1's.\n", zeroCounter, oneCounter);

  printf("Program Complete.\n");
}
