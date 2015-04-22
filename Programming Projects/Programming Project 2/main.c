/*
 * Main driver for disassembler.
 *
 * This program reads lines from a file.  For each line, the program
 *      calls verifyMIPSInstruction.  If the line contains a valid
 *      MIPS instruction, the program parses the instructions into MIPS
 *
 * Author:  Preston Stosur-Bassett
 *        with assistance from: Alyce Brady
 *
 * Creation Date:  3.4.15
 * Updated On: 19.4.15
 *    Update Description: Updated to work with as the main function for the disassembler program.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "verifiers.h"
#include "disassemble.h"
#include "getRegName.h"

int main(int argc, char *argv[])
{
    char buffer[BUFSIZ];
    FILE* fptr;                           /* file pointer */
    int   lineNum = 0;
    int   length;

    /* Was a file passed in a parameter (e.g., on the command line)? */
    if ( argc == 2 )
    {
        /* Open the file for reading */
        if ((fptr = fopen (argv[1], "r")) == NULL)
        {
            fprintf (stderr, "Error: Cannot open file %s.\n", argv[1]);
            return 1;
        }
    }
    else  /* No file passed in; use standard input. */
        fptr = stdin;

    /* Continuously read next line of input until EOF is encountered.
     * Each line should contain a valid MIPS instruction and newline.
     */
    while (fgets (buffer, BUFSIZ, fptr))   /* fgets returns NULL if EOF */
    {
        lineNum++;

        /* If the last character in the string is a newline, "remove" it
         * by replacing it with a null byte.
         */
        length = strlen(buffer);
        if (buffer[length - 1] == '\n')
            buffer[length - 1] = '\0';      /* convert newline to null byte */

      /* Verify the current line is a valid 32-bit MIPS instruction */
      if(verifyMIPSInstruction(lineNum, buffer) != 0) {
        int opCode = getOpCode(buffer);
        char* format = getFormat(opCode);
        if(format == "R") {
          /* Handle R format instructions */
          /* Parse the instruction */
          int functionCode = getFunctionCode(buffer);
          char* functionName = getRFunction(functionCode);
          if(functionName == "NULL") {
            printf("There was an unrecognized function code in line %d\n", lineNum);
          }
          char * rs = getRegName(getRegNum(buffer, 0));
          char * rt = getRegName(getRegNum(buffer, 1));
          char * rd = getRegName(getRegNum(buffer, 2));
          if(rs == "NULL" || rt == "NULL" || rd == "NULL") {
            printf("There was an unrecognized register present in line %d\n", lineNum);
          }
          int shiftAmount = getShiftAmount(buffer);

          /* Print the formatted MIPS instruction */
          if(shiftAmount > 0) {
            printf("%d. %s %s, %s, %d\n", lineNum, functionName, rd, rt, shiftAmount);
          }
          else if(functionCode == 8) {
            printf("%d. %s %s\n", lineNum, functionName, rd);
          }
          else {
            printf("%d. %s %s, %s, %s\n", lineNum, functionName, rd, rs, rt);
          }
        }
        else if(format == 'I') {
          /* Handle I format instructions */
          /* Parse the instruction */
          char iCommand = getICommand(opCode);
          if(iCommand == "NULL") {
            printf("There was an unrecognized opcode in line %d\n", lineNum);
          }
          char * rs = getRegName(getRegNum(buffer, 0));
          char * rt = getRegName(getRegNum(buffer, 1));
          if(rs == "NULL" || rt == "NULL") {
            printf("There was an unrecognized register in line %d\n", lineNum);
          }
          int addr = binToDec(buffer, 16, 32);

           /* Print the formatted MIS instruction */
           if(opCode == 4 || opCode == 5) {
             /* Print the formatted BNE BEQ MIPS instruction */
             printf("%d. %s %s, %s, %d\n", lineNum, iCommand, rs, rt, addr*4);
           }
           else if(opCode > 5 && opCode < 14) {
             /* Print formatted MIPS instruction */
             printf("%d. %s %s, %s, %d\n", lineNum, iCommand, rs, rt, addr);
           }
           else if(opCode > 14 && opCode < 16) {
             /* Print formatted MIPS instruction */
             printf("%d. %s %s, %d\n", lineNum, iCommand, rt, addr);
           }
           else if(opCode > 16 && opCode <= 44) {
             /* Print the formatted MIPS instruction */
             printf("%d. %s %s, %d(%s)\n", lineNum, iCommand, rt, addr, rs);
           }
           else {
             printf("There was an unexpected error in line %d. The I-Format command could not be recognized.", lineNum);
           }
        }
        else if(format == 'J') {
          /* Handle J format instructions here */
          /* Parse the instruction */
          char jCommand = getJCommand(opCode);
          if(jCommand == "NULL") {
            printf("There was an unrecognized opcode in line %d\n", lineNum);
          }
          int addr = binToDec(buffer, 6, 32);
          printf("%d. %s %d\n", lineNum, jCommand, addr*4);
        }
        else {
          printf("An unexpected error occured on line: %d\n", lineNum);
        }
      }
      else {
        printf("Error in line %d: Not a valid 32-bit MIPS instruction.\n", lineNum);
      }
    }

    /* End-of-file encountered; close the file. */
    fclose (fptr);
    return 0;
}
