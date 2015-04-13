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
 * TODO: Implementation:
 *	Describe interesting implementation details here, if any.
 *      (HOW does this function work?  What non-trivial data structures
 *	or algorithms does it use?  Does it have performance
 *	characteristics that the user should be aware of?)
 *
 * Author:  Preston Stosur-Bassett
 *	with assistance from: Alyce Brady
 *
 * Creation Date:  Apr 1 2015
 *
 */

#include "verifiers.h"

int binToDec(char string[], int begin, int end)
{
	int i = 0;
	int decimal = 0;
	int beginPrime = begin;

	while(beginPrime < end) {
		decimal = 2 * decimal + ((string[i] == '1') ? 1 : 0);

		i++;
		beginPrime++;
	}

	return decimal;
}
