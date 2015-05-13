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
#include "decToBin.h"

/*
*  TODO: write the function spec for this function
*/
char * getOpCode(char * operation) {
    static int EQUAL = 0;

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
      fprintf(stderr, "Error: Check the opCode list length, not respective. The output will not be correct. Moving on...\n");
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
  static int EQUAL = 0;

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
    fprintf(stderr, "Error: Check the opCode list length, not respective. The output will not be correct. Moving on...\n");
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


/*
* TODO: write the function spec for this function
*/
char * getFunctCode(char * operation) {
  static int EQUAL = 0;

  /* A list of the function names for R type instructions that has a repsective index for functCodes array */
  static char * functionNames[] = [
    "add",
    "addu",
    "sub",
    "subu",
    "and",
    "or",
    "nor",
    "sll",
    "srl",
    "slt",
    "sltu",
    "jr"
  ];

  /* A list of functcodes that has repsective indexes for functinon names array */
  static char * functCodes[] = [
    "100000",
    "100001",
    "100010",
    "100011",
    "100100",
    "100101",
    "100111",
    "000000",
    "000010",
    "101010",
    "101011",
    "001000"
  ];

  /* Ensure the lists are the same size */
  int functionNamesListLength = sizeof(functionNames);
  int functCodesListLength = sizeof(functCodes);

  if(functionNamesListLength != functCodesListLength) {
    fprintf(stderr, "Error: Function code and function names list's are not the same length. Moving on...\n");
  }

  int i = 0;
  while(i < functionNamesListLength) {
    if(strcmp(operation, functionNames[i]) == EQUAL) {
      return functionNames[i];
    }

    i++;
  }

  return "ERROR";

}

/*
* TODO: write the function spec for this function
*/
char * parseReg(char * regName) {
  static int EQUAL = 0;

  /* An array of register names with respective indexes for the binary value*/
  static char * regNames[] = [
    "$zero",
    "$at",
    "$v0",
    "$v1",
    "$a0",
    "$a1",
    "$a2",
    "$a3",
    "$t0",
    "$t1",
    "$t2",
    "$t3",
    "$t4",
    "$t5",
    "$t6",
    "$t7",
    "$s0",
    "$s1",
    "$s2",
    "$s3",
    "$s4",
    "$s5",
    "$s6",
    "$s7",
    "$t8",
    "$t9",
    "$k0",
    "$k1",
    "$gp",
    "$sp",
    "$fp",
    "$ra"
  ];

  /* An array of register binary values with respetive indexes to the register names array */
  static char * regBin[] = [
    "00000",
    "00001",
    "00010",
    "00011",
    "00100",
    "00101",
    "00110",
    "00111",
    "01000",
    "01001",
    "01010",
    "01011",
    "01100",
    "01101",
    "01110",
    "01111",
    "10000",
    "10001",
    "10010",
    "10011",
    "10100",
    "10101",
    "10110",
    "10111",
    "11000",
    "11001",
    "11010",
    "11011",
    "11100",
    "11101",
    "11110",
    "11111"
  ];

  /* Ensure the size of the lists are the same */
  int regNamesListLength = sizeof(regNames);
  int regBinListLength = sizeof(regBin);

  if(regNamesListLength != regBinListLength) {
    fprintf(stderr, "Error: the lendth of the two register lists is not the same. Moving on...\n");
  }

  int i = 0;
  while(i < regNamesListLength) {
    if(strcmp(regName, regNames[i]) == EQUAL) {
      return regBin[i];
    }

    i++;
  }

  return "ERROR"
}

/*
* TODO: write the function spec for this function
*/
void parseR(char * instruction, char * opCode, char * operation, char * superTokenBegin, char * superTokenEnd, lineNum) {
  static int EQUAL = 0;
  char * functCode = getFunctCode(operation);

  if(strcmp(functCode, "001000") == EQUAL) {
    /* Handle jr instructions here */
    /* Get the binary of the register */
    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);

    char * rd = parseReg(superTokenBegin);

    /* Print the statement to the console. */
    printf("%i. %s%s000000000000000%s", lineNum, opCode, rd, functCode);
  }
  else if(strcmp(functCode, "000000") == EQUAL || strcmp(functCode, "000010") == EQUAL) {
    /* Handle shirt instructions here */
    /* Get the binary for the registers */
    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);
    char * rs = parseReg(superTokenBegin);

    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);
    char * rd = parseReg(superTokenBegin);

    /* Convert the decimal value to binary */
    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);
    char * shift = decToBin(superTokenBegin, 5);

    /* Print the statement to the console. */
    printf("%i. %s00000%s%s%s%s\n", lineNum, opCode, rd, rs, shift, functCode);
  }
  else {
    /* Handle standard R format instructions here */
  }
}

/*
* TODO: write the function spec for this function
*/
void parseI(char * instruction, char * opCode) {

}

/*
* TODO: write the function spec for this function
*/
void parseJ(char * instruction, char * opCode) {

}
