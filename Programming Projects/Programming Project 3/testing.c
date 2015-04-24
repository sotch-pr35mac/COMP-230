/* 
 * This is a driver to test pass1 and the Label Table functions.
 *
 * Author: Alyce Brady
 * Date: 2/18/99
 *
 * Modified by:  Alyce Brady, 6/10/2014
 *      Modified to use either a filename passed in as a parameter on the
 *      command line or the standard input (stdin), as the Disassembler
 *      project does, rather than a hard-coded filename, as the 1999
 *      version did.  In a related modification, the main function now
 *      opens the file and passes the file pointer to pass1 and (after
 *      rewinding) to pass2, rather than just passing the filename to
 *      pass1 and pass2, as it did before, and requiring them to open
 *      the file.  This change was necessary to support the option of
 *      reading the input from stdin.
 */

#include <stdio.h>
#include "LabelTable.h"

LabelTable pass1 (FILE * fp);

int main ()
{
    FILE * fptr;            /* file pointer */
    LabelTable table;

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

    table = pass1 (fptr);
    rewind (fptr);

    printLabels (&table);

    return 0;
}
