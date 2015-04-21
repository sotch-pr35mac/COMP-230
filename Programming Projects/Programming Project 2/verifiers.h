/*
 * Author: Preston Stosur-Bassett
 * Date Created: 5.4.15
 * File: verifiers.h
 * Description: This header file will be used to include all the required files for the disassembler to verify the instructions it receives.
*/

/* Tell the compiler that there is a function that will need to be used called binToDec  */
int binToDec(char string[], int begin, int end);

/* Tell the compiler that there is a function that will need to be used called verifyMIPSInstruction  */
int verifyMIPSInstruction(int lineNum, char * instr);
