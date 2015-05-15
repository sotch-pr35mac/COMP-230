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
char * parseReg(char * regName);

/*
*   TODO: write the function spec for this function
*/
void parseR(char * instruction, char * opCode, char * operation, char ** superTokenBegin, char ** superTokenEnd, int lineNum);

/*
*   TODO: write the function spec for this function
*/
void parseI(char *  instruction, char * opCode, char ** superTokenBegin, char ** superTokenEnd, int lineNum, LabelTable * table);

/*
*   TODO: write the function spec for this function
*/
void parseJ(char * instruction, char * opCode, char ** superTokenBegin, char ** superTokenEnd, int lineNum, LabelTable * table);
