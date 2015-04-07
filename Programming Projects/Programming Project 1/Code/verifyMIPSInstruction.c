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
 * TODO: Implementation:
 *	Describe interesting implementation details here, if any.
 *      (HOW does this function work?  What non-trivial data structures
 *	or algorithms does it use?  Does it have performance
 *	characteristics that the user should be aware of?)
 *
 * Author: Preston Stosur-Bassett
 *	with assistance from: Alyce Brady
 *
 * Creation Date:  3.4.15
 *
 */

#include <stdio.h>
#include <string.h>
#include "verifiers.h"

int verifyMIPSInstruction (int lineNum, char * instr)
  /*  returns 1 if instr contains 32 characters representing binary
   *  digits ('0' and '1'); 0 otherwise
   */
{
    int   length;
    int characterIterator;
    int returnValue = 0;

    length = strlen(instr);
    if (length != 32)
    {
        fprintf (stderr, "Error: line %d does not have 32 chars.\n", lineNum);
        return 0;
    }

   printf("about to iterate through the whole thing.\n");

    characterIterator = 0;
    while(characterIterator < 32) {
      if(characterIterator != 31) {
	/* Declair and Cast variables to be compared properly  */
	const char * one = "1";
	const char * zero = "0";
	const char * currentChar = &(instr[characterIterator]);

	if(strcmp(currentChar, zero) != 0 || strcmp(currentChar, one) != 0) {
          printf("Error! (line %d) contains non-binary values.\n", lineNum);
	  printf("%d (chatacter number: %d) is not a binary value.\n", instr[characterIterator], characterIterator);
	  printf("The instruction being processed is: %s\n", instr);
          return 0;
        }
      }
      else {
        if(instr[characterIterator] != '\0') {
          printf("Error! (line %d) does not contain a terminating null-byte.\n", lineNum);
        }
      }

      characterIterator++;
    }

    return 1;

}
