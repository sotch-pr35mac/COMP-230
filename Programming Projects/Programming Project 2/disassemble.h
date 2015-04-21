/*
 * File: disassemble.h
 * Author: Preston Stosur-Bassett
 * Date: 17.4.15
 * Description: TODO: write this
*/

/* Gets the decimal value of the opCode of a valid 32-bit MIPS instruction. */
int opCode(char instruction[]);

/* Gets the format of the valid 32-bit MIPS instruction. */
char* getFormat(char instruction[]);
