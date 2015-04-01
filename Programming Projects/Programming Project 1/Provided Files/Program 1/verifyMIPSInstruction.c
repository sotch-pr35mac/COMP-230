/*
 * verifyMIPSInstruction
 *
 * This function verifies that the string provided to it as a paramater
 * contains 32 characters representing binary digits (characters '0' and
 * '1'), followed by a null byte.  If the string contains the wrong
 * number of characters or contains invalid charaters (not '0' or '1'),
 * then the function prints an error message to stderr giving the line
 * number and an appropriate error message.
 *
 *   int verifyMIPSInstruction (int lineNum, char * instruction);
 *
 *	    Pre-condition:  instruction is a null-terminated string
 *	    Post-condition: the characters in "instruction" have not
 *			    been modified
 *	    Returns: 1 if instr contained 32 characters representing binary
 *			    digits ('0' and '1') followed by a null byte
 *		     0 if instr has the wrong number of characters or
 *		            contains invalid characters
 *	    Output: Prints an error message to stderr if necessary
 *
 * Implementation:
 *	Describe interesting implementation details here, if any.
 *      (HOW does this function work?  What non-trivial data structures
 *	or algorithms does it use?  Does it have performance
 *	characteristics that the user should be aware of?)
 *
 * Author: 
 *	with assistance from:
 *
 * Creation Date:  Creation_Date
 *	modified: Modification_Date	reason
 *	modified: Modification_Date	reason
 *
 */

#include <stdio.h>
#include <string.h>

int verifyMIPSInstruction (int lineNum, char * instr)
  /*  returns 1 if instr contains 32 characters representing binary
   *  digits ('0' and '1'); 0 otherwise
   */
{
    int   length;

    length = strlen(instr);
    if (length != 32)
    {
        fprintf (stderr, "Error: line %d does not have 32 chars.\n", lineNum);
        return 0;
    }

    /* CODE MISSING !!! */

}
