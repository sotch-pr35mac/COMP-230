/*
*  File: decToBin.c
*  Author: Preston Stosur-Bassett
*  Date: 13.5.15
*  Description: TODO: write the desciprtion for this file
*  Usage: TODO: write the documentation for this file
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "decToBin.h"

/*
* Description: TODO: write the description for this function
* Pre-Condition: TODO: write the precondition for this function
* Post-Condition: TODO: write the postconditions for this function
* @param TODO: add the parameters for this function
* @param TODO: add the parameters for this function
* @return TODO: add the return for this function
*/
char * decToBinInt(int dec, int len) {
  char * bin[15];
  bin[0] = '\0';
  int k = 0;

  int i = 0;
  while(i < len) {
    if(dec >= (pow(2, len-k))) {
      (void)strcat("1", (char *)bin);
      dec -= pow(2, len-k);
    }
    else {
        (void)strcat("0", (char *)bin);
    }

    i++;
  }

  return (char*) bin;
}

/*
*   Description: TODO: write the description for this function
*   Pre-Condition: TODO: write the precondition for this function
*   Post-Condition: TODO: write the postcondition for this function
*   @param TODO: add the parameters for this function
*   @param TODO: add the parameters for this function
*   @return TODO: add the return for this function
*/
char * decToBin(char ** charDec, int len) {
  int dec = (int) charDec - '0';
  return decToBinInt(dec, len);
}
