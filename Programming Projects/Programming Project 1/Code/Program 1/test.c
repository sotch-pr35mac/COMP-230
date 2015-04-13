/*
 * Test Driver to test verifyMIPSInstruction and binToDec.
 *
 * This program reads lines from a file.  For each line, the program
 *      calls verifyMIPSInstruction.  If the line contains a valid
 *      MIPS instruction, the program calls binToDec for various
 *      segments of the instruction to test the binToDec function.
 *
 * Input:
 *      The program reads its input from a file passed in as a parameter
 *      on the command line, or reads from the standard input.
 *      To test verifyMIPSInstruction, the file should contain ...
 *
 *              -A 32 bit binary sequence
 *              -A non-32 bit binary sequence, any sequence of characters that the program should be able to handle and error report for.
 *
 * Output:
 *      For each valid line, the program prints a series of decimal
 *      numbers to test binToDec, representing
 *
 *             -A the decimal value for the binary value that was passed
 *
 *      For each invalid line, the program prints an error message to
 *      stderr saying so.  (The program also prints an error message if
 *      it cannot open the file.)
 *
 * Author:  Preston Stosur-Bassett
 *        with assistance from: Alyce Brady
 *
 * Creation Date:  3.4.15
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "verifiers.h"

/* int binToDec(char string[], int begin, int end); */
/* int verifyMIPSInstruction (int lineNum, char string[]); */

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

	if(verifyMIPSInstruction(lineNum, buffer) != 0) {
		printf("%i ... %i: %i\n", 0, 31, binToDec(buffer, 0, 31));
	}
    }

    /* End-of-file encountered; close the file. */
    fclose (fptr);
    return 0;
}
