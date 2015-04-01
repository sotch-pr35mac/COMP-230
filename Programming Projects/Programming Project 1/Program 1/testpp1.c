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
 *              DESCRIBE NECESSARY TEST CASES HERE
 *
 * Output:
 *      For each valid line, the program prints a series of decimal
 *      numbers to test binToDec, representing
 *
 *              DESCRIBE NECESSARY TEST CASES HERE
 *
 *      For each invalid line, the program prints an error message to
 *      stderr saying so.  (The program also prints an error message if
 *      it cannot open the file.)
 *
 * Author:  Your_Name(s)
 *        with assistance from:
 *
 * Creation Date:  Creation_Date
 *        modified: Modification_Date        reason
 *        modified: Modification_Date        reason
 *
 */

/* include files go here */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binToDec(char string[], int begin, int end);
int verifyMIPSInstruction (int lineNum, char string[]);

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

        /* Verify that the string is 32 0's and 1's.  If it is, do
         * various tests to ensure that binToDec works correctly.
         * If the string is invalid, verifyMIPSinstruction should print
         * an informative error message.
         */
        /* CODE MISSING !!!
         * An example of a test call to binToDec:
         *   printf("3..5: %d\n", binToDec(buffer, 3, 5));
         */

    }

    /* End-of-file encountered; close the file. */
    fclose (fptr);
    return 0;
}
