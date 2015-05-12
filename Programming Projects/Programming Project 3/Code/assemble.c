/*
*  File: assemble.c
*  Author: Preston Stosur-Bassett
*  Date: 13.5.15
*  Description: TODO: Write description
*  Usage: TODO: write the usage documentation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assemble.h"
#include "LabelTable.h"

/*
*  TODO: write the function spec for this function
*/
char * getOpCode(char * operation) {
    int EQUAL = 0;

    /* Create a static array of MIPS operation names, where the index corresponds to an array with the correct opcode. */
    static char * operationNames[] = [
      "add",
      "addu",
      "sub",
      "subu",
      "addi",
      "addiu",
      "and",
      "or",
      "nor",
      "andi",
      "ori",
      "sll",
      "srl",
      "lw",
      "sw",
      "lui",
      "beq",
      "bne",
      "slt",
      "sltu",
      "slti",
      "sltiu",
      "j",
      "jr",
      "jal"
    ];

    /* Create a static array of operation Codes where the index is respective to the array of MIPS operation names */
    static char * opCodes[] = [
      "000000",
      "000000",
      "000000",
      "000000",
      "001000",
      "001001",
      "000000",
      "000000",
      "000000",
      "001100",
      "001101",
      "000000",
      "000000",
      "100011",
      "101011",
      "001111",
      "000100",
      "000101",
      "000000",
      "000000",
      "001010",
      "001011",
      "000010",
      "000000",
      "000011"
    ];

    /* Ensure that the lists are the same size */
    int opCodeListLength = sizeof(opCodes);
    int operationNamesListLength = sizeof(operationNames);

    if(opCodeListLength != operationnamesListLength) {
      fprintf(stderr, "Error: Check the opCode list length, not respective. The output will not be correct. Moving on...");
    }

    int i = 0;
    while(i < operationNamesListLength) {
      if(strcmp(operation, operationNames[i]) == EQUAL) {
        return opCodes[i];
      }
      i++;
    }

    return "Error";
}

/*
* TODO: write the function spec for this function
*/
int getFormat(char * opCode) {
  int EQUAL = 0;

  if(strcmp(opCode, "000000") == EQUAL) {
    /* If the opCode is 000000 then return 0, which stands for R type format instruction */
    return 0;
  }

  /* Create a static array of operation Codes where the index is respective to the array of MIPS format instruction */
  static char * opCodes[] = [
    "001000",
    "001001",
    "001100",
    "001101",
    "100011",
    "101011",
    "001111",
    "000100",
    "000101",
    "001010",
    "001011",
    "000010",
    "000011"
  ];

  /* Create a static array of format codes (0 = R, 1 = I, 2 = J) where the index is respective to the opCodes */
  static int respectiveFormat[] = [
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    2,
    2
  ];

  int opCodeListLength = sizeof(opCode);
  int respectiveFormatListLength = sizeof(respectiveFormat);

  if(opCodeListLength != respectiveFormatListLength) {
    fprintf(stderr, "Error: Check the opCode list length, not respective. The output will not be correct. Moving on...");
  }

  int i = 0;
  while(i < opCodeListLength) {
    if(strcmp(opCode, opCodes[i]) == EQUAL) {
      return respectiveFormat[i];
    }
    i++;
  }

  return -1;
}
