/*
*  File: decToBin.c
*  Author: Preston Stosur-Bassett
*  Date: 13.5.15
*  Description: TODO: write the desciprtion for this file
*  Usage: TODO: write the documentation for this file
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "decToBin.h"

/*
* TODO: write the function spec for this function
*/
char * decToBin(int dec, int len) {
  char * bin;

  int i = 0;
  while(i < len) {
    if(dec >= (pow(2, len-k))) {
      (void)strcat(bin, "1");
      dec -= pow(2, len-k);
    }
    else {
        (void)strcat(bin, "0");
    }

    i++;
  }

  return bin;
}

/*
*   TODO: write the function spec for this program
*/
char * decToBin(char * charDec, int len) {
  int dec = atoi(charDec);
  return decToBin(dec, len);
}
