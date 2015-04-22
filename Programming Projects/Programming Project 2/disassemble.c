/*
 *   File:         disassemble.c
 *   Author:       Preston Stosur-Bassett
 *   Date:         17.4.15
 *   Description:  This file handles the main disassembly functions and converts decimal values to near-english equivalents.
*/

#include <stdio.h>
#include <string.h>
#include "verifiers.h"
#include "disassemble.h"
#include "getRegName.h"

/*
 * @Description: <code>opCode</code> gets the decimal value of the MIPS instruction op code and returns it as an integer.
 * @Pre-Condition <code>char instruction[]</code> is a 'string' (an array of char's) is a valid 32-bit MIPS instruction, where the first 6 bits is the op-code.
 * @Post-Condition: returns the correct decimal representation for the 6-bit opcode of the valid 32-bit MIPS instruction.
*/
int getOpCode(char instruction[]) {
  int decimalOpCode = binToDec(instruction, 0, 6);
  return decimalOpCode;
}

/*
 * @Description: <code>getFormat</code> gets the format of the MIPS instruction and returns it as a char
 * @Pre-Condition: <code>int decimalOpCode</code> is the decimal representation of the valid 32-bit MIPS instruction opCode.
 * @Post-Condition: returns the correct format for the instruction that was passed.
*/
char* getFormat(int decimalOpCode) {
  char* format;
  if(decimalOpCode == 0) {
    format = "R";
  }
  else if(decimalOpCode == 2 || decimalOpCode == 3) {
    format = "J";
  }
  else {
    format = "I";
  }
  return format;
}

/*
 * @Description: <code>getShiftAmount</code> gets the shift amount of the valid 32-bit MIPS instruction and returns it as an integer
 * @Pre-Condition: <code>char instruction[]</code> is a valid 32-bit MIPS instruction
 * @Post-Condition: returns the correct integer for R-type instructions that have a shift amount
*/
int getShiftAmount(char instruction[]) {
  int shiftAmount = binToDec(instruction, 21, 26);
  return shiftAmount;
}

/*
 * @Description: <code>getFunctionCode</code> gets the function decimal value for a valid 32-bit MIPS R-type MIPS instruction
 * @Pre-Condition: <code>char instruction[]</code> is a valid 32-bit MIPS instruction
 * @Post-Condition: returns the decimal equivalent of the R-Type function code as an integer value
*/
int getFunctionCode(char instruction[]) {
  int functionCode = binToDec(instruction, 26, 32);
  return functionCode;
}

/*
 * @Description: <code>getRegNum</code> gets the decimal value of the register
 * @Pre-Condition: <code>char instruction[]<code> is a valid 32-bit MIPS instruction. <code>int regPlacement</code> is the placement register number that should get returned (0 for rs, 1 for rt, 2 for rd)
 * @Post-Condition: returns the decimal value of the register number as an integer
*/
int getRegNum(char instruction[], int regPlacement) {
  int regNum = binToDec(instruction, 6 + 5*(regPlacement), 11 + 5*(regPlacement));
  return regNum;
}

/*
 * @Description: <code>getRFunction</code> gets the function name of the valid 32-bit MIPS R-format instruction.
 * @Pre-Codition: <code>int functionDecimal</code> is a integer of the decimal representation of the R-format function code.
 * @Post-Condition: returns the name of the function code if found, otherwise returns "NULL"
*/
char * getRFunction(int functionDecimal) {
  static char* RFunctionNames[44];
  RFunctionNames[32] = "add";
  RFunctionNames[33] = "addu";
  RFunctionNames[36] = "and";
  RFunctionNames[8] = "jr";
  RFunctionNames[39] = "nor";
  RFunctionNames[37] = "or";
  RFunctionNames[42] = "slt";
  RFunctionNames[43] = "sltu";
  RFunctionNames[0] = "sll";
  RFunctionNames[2] = "srl";
  RFunctionNames[34] = "sub";
  RFunctionNames[35] = "subu";

  if(RFunctionNames[functionDecimal] != NULL) {
    return RFunctionNames[functionDecimal];
  }
  else {
    return "NULL";
  }
}

/*
 * @Description: <code>getICommand</code> gets the name of the valid 32-bit MIPS instruction that is of type-I
 * @Pre-Condition: <code>int opCode</code> is the valid decimal opcode (the first 6-bits of the 32-bit MIPS instruction).
 * @Post-Condition: returns the correct command name for the given op code, if not found, returns "NULL"
*/
char * getICommand(int opCode) {
  static char* ICommands[44];
  ICommands[8] = "addi";
  ICommands[9] = "addiu";
  ICommands[12] = "andi";
  ICommands[4] = "beq";
  ICommands[5] = "bne";
  ICommands[36] = "lbu";
  ICommands[37] = "lhu";
  ICommands[48] = "ll";
  ICommands[15] = "lui";
  ICommands[35] = "lw";
  ICommands[13] = "ori";
  ICommands[10] = "slti";
  ICommands[11] = "sltiu";
  ICommands[40] = "sb";
  ICommands[56] = "sc";
  ICommands[41] = "sh";
  ICommands[43] = "sw";

  if(ICommands[opCode] != NULL) {
    return ICommands[opCode];
  }
  else {
    return "NULL";
  }
}

/*
 * @Description: <code>getJCommand</code> gets the name of the valid 32-bit MIPS instruction J-Command
 * @Pre-Condition: <code>int opCode</code> is a valid deciaml opCode for a 32-bit MIPS instruction in J-Format
 * @Post-Condition: returns the correct J-format command, if not found, returns "NULL"
*/
char * getJCommand(int opCode) {
  static char* JCommands[3];
  JCommands[2] = "j";
  JCommands[3] = "jal";
  if(JCommands[opCode] != NULL) {
    return JCommands[opCode];
  }
  else {
    return "NULL";
  }
}
