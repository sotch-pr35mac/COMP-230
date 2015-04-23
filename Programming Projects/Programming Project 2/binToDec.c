/*
 * binToDec
 *
 * This function converts the binary digits from string[begin] to
 * string[end] to a decimal integer.
 *
 * int binToDec(char string[], int begin, int end)
 *   Pre-condition:  begin and end are valid indices in array string;
 *   		     every character from string[begin] to string[end]
 *		     (including those two) has a character value '0' or '1'
 *   Returns: the decimal equivalent of the binary number represented by
 *	      the characters in string[begin] - string[end].
 *            (If begin > end, this function arbitrarily returns 0.)
 *
 * For example, assume A is a character array that contains the
 *    following characters:
 *            '1'  '0'  '1'  '1'  '0'  '1'  '0'  '0'  '1'
 *    The call binToDec(A, 2, 5) converts the binary number 1101
 *    (represented by the substring A[2] - A[5]) to the decimal integer
 *    13 and returns it.
 *
 * Note: The decimal value returned may appear to be negative if the
 * string being converted is long enough (end - begin + 1 == 32)
 * and if the first character is '1'.
 *
 * Implementation:
 * binToDec takes an array of char values and parses through them to find the decimal interger value from the beginning and end index provided
 *
 * Author:  Preston Stosur-Bassett
 *	with assistance from: Alyce Brady
 *
 * Creation Date:  Apr 1 2015
 *
 */

#include "verifiers.h"

/*
*	@param: char stringp[] is a non-empty string of '1' or '0' characters, with binary values of 49 or 48 respectively
*	@param: int begin is an integer value for where to start the the binary to decimal conversion
*	@param: int end is an integer value for where to end the binary to decimal conversion
*	@Post-Condition: decimal is a decimal integer value for the beginning and end index in the string of binary values
*/
int binToDec(char instruction[], int begin, int end)
{
	int i = begin;
	int decimal = 0;

	while(i <= end) {
		decimal = 2 * decimal + ((instruction[i] == '1') ? 1 : 0);

		i++;
	}

	return decimal;
}
