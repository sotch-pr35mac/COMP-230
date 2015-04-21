/*
 *   File:         disassemble.c
 *   Author:       Preston Stosur-Bassett
 *   Date:         17.4.15
 *   Description:  TODO: What does this file do
*/

#include <stdio.h>
#include <string.h>
#include "verifiers.h"
#include "disassemble.h"

/*
 * @Description: <code>opCode</code> gets the decimal value of the MIPS instruction op code and returns it as an integer.
 * @Pre-Condition <code>char instruction[]</code> is a 'string' (an array of char's) is a valid 32-bit MIPS instruction, where the first 6 bits is the op-code.
 * @Post-Condition: returns the correct decimal representation for the 6-bit opcode of the valid 32-bit MIPS instruction.
*/
int opCode(char instruction[]) {
  int decimalOpCode = binToDec(instruction, 0, 6);
  return decimalOpCode;
}

/*
 * @Description: <code>getFormat</code> gets the format of the MIPS instruction and returns it as a char
 * @Pre-Condition: <code>char instruction[]</code> is a 'string' (and array of char's) is a valid 32-bit MIPS instruction, where the first 6 bits are the op-code.
 * @Post-Condition: returns the correct format for the instruction that was passed.
*/
char* getFormat(char instruction[]) {
  int decimalOpCode = binToDec(instruction, 0, 6);
  char* format;
  if(decimalOpCode == 0) {
    format = "R";
  }
  else if(decimalOpCode == 2 || decimalOpCode == 3) {
    format = "J"
  }
  else {
    format = "I"
  }
  return format;
}

/*
 * TODO: write this function spec
*/
