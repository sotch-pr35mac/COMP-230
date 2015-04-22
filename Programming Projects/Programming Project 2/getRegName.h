/*
 * File: getRegName.h
 * Author: Preston Stosur-Bassett
 * Date: 19.4.15
 * Description: This is the .h file that contains all the function declarations from getRegName.c
*/

/*
 * This function looks up and returns the mnemonic name for a given
 * register number.
 *
 *   Pre-condition: 0 <= registerNumber < 32
 *   Returns: returns the mnemonic name associated with registerNumber
 *
 * How to call this function:
 *    You do not need to allocate space for the mnemonic name that this
 *    function returns; it will return a pointer to a name (a string)
 *    that is statically scoped (i.e., does not disappear as soon as the
 *    function returns).  For example:
 *	  int rNbr1, rNbr2, rNbr3;	   // register numbers between 0 and 31
 *	  char *rName1, *rName2, *rName3;  // will point to names, e.g., "$t0"
 *	  ...				   // set register numbers
 *	  rName1 = getRegName (rNbr1);
 *	  rName2 = getRegName (rNbr2);
 *	  rName3 = getRegName (rNbr3);
 *	  printf ("add %s, %s, %s\n", rName1, rName2, rName3);
 *    If rNbr1 = 8, rNbr2 = 9, rNbr3 = 16, this will print:
 *		add $t0, $t1, $s0
 */
char * getRegName(int regNbr);
