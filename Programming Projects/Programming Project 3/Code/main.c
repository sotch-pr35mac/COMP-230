/*
*  File: main.c
*  Author: Preston Stosur-Bassett
*  Date: 13.5.15
*  Description: This is the main driver function that will handle input from the user and parse it into binary.
*  Usage: TODO: write this
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LabelTable.h"
#include "pass1.h"
#include "getToken.h"
#include "assemble.h"

/*
*  TODO: write function spec
*/
int main(int argc, char *argv[]) {
  int EQUAL = 0;
  char buffer[BUFSIZ];
  FILE* fptr;   /* file pointer */
  int lineNum = 0;
  int length;

  /* Was a file passed in a parameter? */
  if(argc == 2) {
    /* Open the file for reading */
    if((fptr = fopen (argv[1], "r")) == NULL) {
      fprintf(stderr, "Error: Cannot open file %s.\n", argv[1]);
      return 1;
    }
  }
  else {
      /* No file passed in; use the standard input */
      fptr = stdin;
  }

  /* Start First Pass */
  LabelTable tableOfLabels = pass1(fptr);

  /* Start Second Pass */
  char * superTokenBegin; /* beginToken for getToken calls before parsing instruction */
  char * superTokenEnd; /* endToken for getToken calls before parsing instruction */
  int PC = 0; /* Start the program counter at 0. */
  char inst[BUFSIZ]; /* holds the instruction */
  char* operation;

  /* create a small table of labels to start off */
  if((fptr = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Error: Cannot open file %s.\n", argv[1]);
  }

  /* Continuously read next line of input until End Of File is reached. */
  for(PC = 0; fgets(inst, BUFSIZ, fptr); PC += 4) {
    /* Remove the comments */
    if(*inst == '#') continue;
    (void) strok (inst, '#');

    /* point the token to the first non-white space character. */
    superTokenBegin = inst;
    getToken(&superTokenBegin, &superTokenEnd);

    /* skip over labels */
    if(*(superTokenEnd) == ':') {
      superTokenBegin = superTokenEnd + 1;
      getToken(&superTokenBegin, &superTokenEnd);
    }

    /* Get operation */
    *superTokenEnd = '\0';
    operation = superTokenBegin;

    /* Get operation format */
    char * opCode = getOpCode(operation);
    int format = getFormat(opCode);

    /* Parse the instruction */
    if(format == 0) {
      /* Handle R format instructions */
      parseR(inst, opCode, operation, &superTokenBegin, &superTokenEnd, lineNum);
    }
    else if(format == 1) {
      /* Handle I type instructions */
      parseI(inst, opCode, &superTokenBegin, &superTokenEnd, lineNum, tableOfLabels);
    }
    else if(format == 2) {
      /* Handle J type instructions */
      parseJ(inst, opCode, &superTokenBegin, &superTokenEnd, lineNum, tableOfLabels);
    }

    lineNum++;
  }
}
