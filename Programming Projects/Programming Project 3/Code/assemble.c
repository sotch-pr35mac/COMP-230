/*
*  File: assemble.c
*  Author: Preston Stosur-Bassett
*  Date: 13.5.15
*  Description: This is the main assembly file, that handles the pass 2 functions (including parsing the assembly code into binary)
*  Usage: TODO: write the usage documentation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LabelTable.h"
#include "assemble.h"
#include "decToBin.h"

/*
*  Description: getOpCode takes the MIPS operation name, and returns the corresponding operation code
*  Pre-Condition: TODO: write the precondition for this function
*  Post-Condition: TODO: write the post-condition for this function
*  @param <code>char * operation</code> is a NON-NULL well-defined "string" of the MIPS operation name
*  @return <code>char *</code> is a "string" of the binary equivalent of the MIPS operation name
*/
char * getOpCode(char * operation) {
    static int EQUAL = 0;

    /* Create a static array of MIPS operation names, where the index corresponds to an array with the correct opcode. */
    static char * operationNames[] = {
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
    };

    /* Create a static array of operation Codes where the index is respective to the array of MIPS operation names */
    static char * opCodes[] = {
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
    };

    /* Ensure that the lists are the same size */
    int opCodeListLength = sizeof(opCodes);
    int operationNamesListLength = sizeof(operationNames);

    if(opCodeListLength != operationNamesListLength) {
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
* Description: getFormat takes the opCode as a parameter and finds what format the instruction is in
* Pre-Condition: TODO: write the pre-condition for this function
* Post-Condition: TODO: write the post-condition for this function
* @param <code>char * opCode</code> is a NON-NULL well-defined "string" of the binary opCode
* @return <code>int</code> returns 0 for R type instructions, 1 for I type instructions, and 2 for J type instructions
*/
int getFormat(char * opCode) {
  static int EQUAL = 0;

  if(strcmp(opCode, "000000") == EQUAL) {
    /* If the opCode is 000000 then return 0, which stands for R type format instruction */
    return 0;
  }

  /* Create a static array of operation Codes where the index is respective to the array of MIPS format instruction */
  static char * opCodes[] = {
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
  };

  /* Create a static array of format codes (0 = R, 1 = I, 2 = J) where the index is respective to the opCodes */
  static int respectiveFormat[] = {
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
  };

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
* Description: getFunctCode takes the function code for R type instructions and returns the binary equivalent.
* Pre-Condition: TODO: write the preconditions for this function
* Post-Condition: TODO: write the postconditions for this function
* @param <code>char * operation</code> is a NON-NULL well-defined "string" of the name of the MIPS operation to get the binary equivalent for
* @return <code>char *</code> a "string" of the binary equivalent of the function code that was passed in as a parameter
*/
char * getFunctCode(char * operation) {
  static int EQUAL = 0;

  /* A list of the function names for R type instructions that has a repsective index for functCodes array */
  static char * functionNames[] = {
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
  };

  /* A list of functcodes that has repsective indexes for functinon names array */
  static char * functCodes[] = {
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
  };

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
* Description: parseReg takes in a MIPS register name and returns the binary value for that register
* Pre-Condition: TODO: write the precondition for this function
* Post-Condition: TODO: write the post-condition for this function
* @param <code>char * regName</code> a NON-NULL well-defined "string" of the register name to be parsed into a binary register
* @return <code>char *</code> a "string" of the binary register that should be the same as the one that was passed
*/
char * parseReg(char ** regName) {
  static int EQUAL = 0;

  /* An array of register names with respective indexes for the binary value*/
  static char * regNames[] = {
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
  };

  /* An array of register binary values with respetive indexes to the register names array */
  static char * regBin[] = {
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
  };

  /* Ensure the size of the lists are the same */
  int regNamesListLength = sizeof(regNames);
  int regBinListLength = sizeof(regBin);

  if(regNamesListLength != regBinListLength) {
    fprintf(stderr, "Error: the lendth of the two register lists is not the same. Moving on...\n");
  }

  int i = 0;
  while(i < regNamesListLength) {
    if(strcmp((char *)regName, regNames[i]) == EQUAL) {
      return regBin[i];
    }

    i++;
  }

  return "ERROR";
}

/*
* Description: parseR handles the formatting, printing and parsing of R type instructions
* Pre-Condition: TODO: write the preconditions for this function
* Post-Condition: The R format instruction is properly printed to the console in its correct binary format (TODO: update this when it supports printing to a files)
* @param <code>char * instruction</code> is a NON-NULL well defined "string" of the assembly instruction being parsed
* @param <code>char * opCode</code> is a NON-NULL well-defined "string" of the op code for the current assembly instruction in binary
* @param <code>char * operation</code> is a NON-NULL well-defined "string" of the operation (ie, add, sub, etc.) for the current assembly instruction
* @param <code>char ** superTokenBegin<code> is a NON-NULL well-defined "string" address for the current token of the current assembly instruction
* @param <code>char ** superTokenEnd</code> is a NON-NULL well-defined "string" address for the current token of the current assembly instruction
* @param <code>int lineNum</code> is a NON-NULL well-defined integer value that corresponds with the line number of the current assembly instruction
*/
void parseR(char * instruction, char * opCode, char * operation, char ** superTokenBegin, char ** superTokenEnd, int lineNum) {
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
    return;
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
    return;
  }
  else {
    /* Handle standard R format instructions here */
    /* Get the binary for the registers */
    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);
    char * rs = parseReg(superTokenBegin);

    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);
    char * rt = parseReg(superTokenBegin);

    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);
    char * rd = parseReg(superTokenBegin);

    /* Print the statement to the console. */
    printf("%i, %s%s%s%s00000%s\n", lineNum, opCode, rt, rd, rs, functCode);
    return;
  }
}

/*
* Description: parseI handles how to parse, format, and print I type assembly instructions in binary
* Pre-Condition: TODO: write the preconditions for this functino
* Post-Conditions: The I type instruction is printed out to the console (TODO: update this when it can write out to a file)
* @param TODO: <code>char * instruction</code> is a NON-NULL well-defined "string" of the assembly instruction
* @param TODO: <code>char * opCode</code> is a NON-NULL well-defined "string" of the binary opCode for the instruction at hand
* @param TODO: <code>char ** superTokenBegin</code> is a NON-NULL well-defined "string" address of the current token of the instruction at hand
* @param TODO: <code>char ** superTokenEnd</code> is a NON-NULL well-defined "string" address of the current token of the instruction at hand
* @param TODO: <code>int lineNum</code> is a NON-NULL well-defined integer value that corresponds with the line number of the current instruction
* @param TODO: <code>LabelTable * table</code> is a LabelTable that is NON-NULL, well-defined and contains all the
*/
void parseI(char * instruction, char * opCode, char ** superTokenBegin, char ** superTokenEnd, int lineNum, struct LabelTable * table) {
  static int EQUAL = 0;

  if(strcmp(opCode, "100011") == EQUAL || strcmp(opCode, "101011") == EQUAL) {
    /* Handle lw and sw instructions here */
    /* Get the binary for the registers and offset immediates */
    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);
    char * rs = parseReg(superTokenBegin);

    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);
    char * offset = decToBin(superTokenBegin, 16);

    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);
    char * rd = parseReg(superTokenBegin);

    /* Print the statement to the console */
    printf("%i. %s%s%s%s\n", lineNum, opCode, rd, rs, offset);
  }
  else if(strcmp(opCode, "001111") == EQUAL) {
    /* Handle lui instructions here */
    /* Get the binary for the registers */
    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);
    char * rs = parseReg(superTokenBegin);

    /* Get the immediate value in binary */
    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);
    char * imm = decToBin(superTokenBegin, 16);

    /* Print the statement out to the console. */
    printf("%i. %s00000%s%s\n", lineNum, opCode, rs, imm);
    return;
  }
  else if(strcmp(opCode, "000100") == EQUAL || strcmp(opCode, "000101") == EQUAL) {
    /* Handle the bne and beq instructions here */
    /* Get the binary for the registers */
    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);
    char * rs = parseReg(superTokenBegin);

    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);
    char * rt = parseReg(superTokenBegin);

    /* Get the binary address of the label */
    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);

    int decAddress = findLabel(table, (char *)superTokenBegin);

    if(decAddress == -1) {
      char * superTokenChar = (char *) superTokenBegin;
      fprintf(stderr, "Error: Could not find the address for the label %s. Setting the label's address to 0....\n", superTokenChar);
      decAddress = 0;
    }

    char * addr = decToBinInt(decAddress, 16);

    /* Print the statement to the console */
    printf("%i. %s%s%s%s\n", lineNum, opCode, rt, rs, addr);
    return;
  }
  else {
    /* Handle the standard I type instructions here */
    /* Get the binary for the registers */
    /* TODO: Get this to work with LabelTables!!! */
    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);
    char * rs = parseReg(superTokenBegin);

    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);
    char * rd = parseReg(superTokenBegin);

    /* Get the immediate value in binary */
    superTokenBegin = superTokenEnd + 1;
    getToken(&superTokenBegin, &superTokenEnd);
    char * imm = decToBin(superTokenBegin, 16);

    /* Print the statement to the console */
    printf("%i. %s%s%s%s\n", lineNum, opCode, rd, rs, imm);
    return;
  }
}

/*
* Description: parseJ handles how to parse, format, and print J type assembly instructions and prints them out in their proper binary format.
* Pre-Condition: TODO: write the preconditions for this function
* Post-Condition: The J type instruction is printed out to the console (TODO: update this when it writes out to a file)
* @param <code>char * instruction</code> is a NON-NULL well-defined "string" of the instruction itself.
* @param <code>char * opCode</code> is a NON-NULL well-defined "string" of the opCode in binary format
* @param <code>char ** superTokenBegin</code> is a NON-NULL well-defined "string" address of the beginning of the current token for the current instruction
* @param <code>char ** superTokenEnd</code> is a NON-NULL well-defined "string" address of the end of the current token for the current instruction
* @param <code>int lineNum</code> is a NON-NULL well-defined integer value that corresponds to the current line number of assembly code.
* @param <code>LabelTable * table</code> is a LabelTable that is NON-NULL, well-defined and contains all the labels for the current assembly code file (created in pass1)
*/
void parseJ(char * instruction, char * opCode, char ** superTokenBegin, char ** superTokenEnd, int lineNum, struct LabelTable * table) {
  /* Handle J type instructions here */
  /* Get the value of the address */
  superTokenBegin = superTokenEnd + 1;
  getToken(&superTokenBegin, &superTokenEnd);

  int decAddress = findLabel(table, (char *)superTokenBegin);

  if(decAddress == -1) {
    char * superTokenChar = (char *) superTokenBegin;
    fprintf(stderr, "Error: The address for the label %s was not found. Setting address equal to 0...\n", superTokenChar);
    decAddress = 0;
  }

  char * addr = decToBinInt(decAddress, 26);

  /* Print the statement to the console. */
  printf("%i. %s%s\n", lineNum, opCode, addr);
  return;
}
