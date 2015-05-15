/*
* File: assemble.h
* Author: Preston Stosur-Bassett
* Date: 13.5.15
* Description: Header file for assemble.c
*/

/*
*   TODO: write the function spec for this function
*/
char * getOpCode(char * operation);

/*
*   TODO: write the function spec for this function
*/
int getFormat(char * opCode);

/*
*   TODO: write the function spec for this function
*/
char * getFunctionCode(char * operation);

/*
*   TODO: write the function spec for this function
*/
char * parseReg(char ** regName);

/*
*   TODO: write the function spec for this function
*/
void parseR(char * instruction, char * opCode, char * operation, char ** superTokenBegin, char ** superTokenEnd, int lineNum);

/*
*   TODO: write the function spec for this function
*/
void parseI(char *  instruction, char * opCode, char ** superTokenBegin, char ** superTokenEnd, int lineNum, LabelTable * table);

/*
* Description: parseJ handles how to parse, format, and print J type assembly instructions and prints them out in their proper binary format.
* Pre-Condition: TODO: write the preconditions for this function
* Post-Condition: The J type instruction is printed out to the console (TODO: update this when it writes out to a file)
* @param <code>char * instruction</code> is a NON-NULL well-defined "string" of the instruction itself.
* @param <code>char * opCode</code> is a NON-NULL well-defined "string" of the opCode in binary format
* @param <code>char ** superTokenBegin</code> is a NON-NULL well-defined "string" address of the beginning of the current token for the current instruction
* @param <code>char ** superTokenEnd</code> is a NON-NULL well-defined "string" address of the end of the current token for the current instruction
* @param <code>int lineNum</code> is an integer value that corresponds to the current line number of assembly code.
* @param <code>LabelTable * table</code> is a LabelTable that contains all the labels for the current assembly code file (created in pass1)
*/
void parseJ(char * instruction, char * opCode, char ** superTokenBegin, char ** superTokenEnd, int lineNum, LabelTable * table);
