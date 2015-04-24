/*
 * This is a test driver for the getNTokens function.  To compile it,
 * you need to compile this file (getNTokensDriver.c), getNTokens.c,
 * and getToken.c, e.g.,
 *      gcc getNTokens*.c getToken.c -o tokenDriver
 *      ./tokenDriver    (or just ./a.out if you don't name the output)
 *
 * Author: Alyce Brady
 * Date:   5/21/14
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>		/* might be memory.h on some machines */

extern const int SAME;		/* useful for making strcmp readable */

void getToken (char ** tokBegin, char ** tokEnd);
int getNTokens (char * instructionBuffer, int N, char * results[]);
void runHardCodedTests ();

int main ()
{
    int i;
    char instrBuffer[BUFSIZ];
    char * tokBegin;
    char * tokEnd;
    char * opcodeString;
    char * restOfStatement;
    char * parameters[4];  /* max should be 3, but just in case... */

    /* The first test is close to how one would structure getting
     * tokens in Pass 2 of an assembler:
     *   Simulate reading line from file (should really be fgets),
     *   strip comments (same as Pass 1), skip label if there is one,
     *   get opcode, then get 3 more tokens (pretend this is R-format).
     */

    /* Simulate the loop that reads in lines of a file (loop once). */
    for (i = 0; i < 1; i++ )
    {
        strcpy (instrBuffer, "main: lw $a0, 0($t0)  # comment");
printf("Debug: Original full instruction = %s\n", instrBuffer);

        /* Get rid of comment at end of line (if any).
         * If the line starts with a comment, move on to next line.
         */
        if ( *instrBuffer == '#' ) continue;
        (void) strtok (instrBuffer, "#");

printf("Debug: After stripping comment, buffer = %s\n", instrBuffer);
        /* Get first token (label or opcode). */
        tokBegin = instrBuffer;
        getToken (&tokBegin, &tokEnd);
        if ( *tokBegin == '\0' || *tokEnd == '\0' )
            continue;       /* No tokens on this line. */

        /* Was first token a label? */
        if ( *(tokEnd) == ':' )
        {
            /* First token was a label; get next token. */
            tokBegin = tokEnd + 1;
printf("Debug: After stripping label, rest of statement = %s\n", tokBegin);
            getToken (&tokBegin, &tokEnd);
            if ( *tokBegin == '\0' || *tokEnd == '\0' )
                continue;       /* Line contained only a label, nothing else. */
        }

        /* Token at tokBegin is the opcode. */
        opcodeString = tokBegin;
        *tokEnd = '\0';

        /* Pretend this is an R-format instruction; we expect 3 more tokens. */
        restOfStatement = tokEnd + 1;  /* starts after end of opcodeString */
        if ( ! getNTokens(restOfStatement, 3, parameters) )
        {
            printf("Error on line 1: %s\n", parameters[0]);
            continue;
        }

        printf("Initial test case: opcode + 3 parameters: %s %s %s %s\n",
            opcodeString, parameters[0], parameters[1], parameters[2]);
    }

    /* Run additional hard-coded tests, based on assembler testfile. */
    printf("\nAdditional Hard-coded Tests:\n\n");
    runHardCodedTests();
}

void runHardCodedTests ()
{
    int i;
    char * testStrings[] = {
        "main:   lw $a0, 0($t0)         # was lw $a0, item, but that's wrong",
        "begin:  addi $t0, $zero, 0      # beginning",
                "addi $t1, $zero, 1",
        "loop:   slt $t2, $a0, $t1      # top of loop",
                "bne $t2, $zero, finish",
                "add $t0, $t0, $t1",
                "addi $t1, $t1, 2",
                "j loop                 # bottom of loop",
        "finish: add $v0, $t0, $zero;",
        "bad:    add $t0, $t1",
        "bad:    add $t0, $t1, $t2, $t3"
    };
    char instrBuffer[100];
    char * results[6];

    strcpy (instrBuffer, testStrings[0]);
    (void) strtok (instrBuffer, "#");
    printf ("Line 1: %s\n\tExpect 5 tokens\n\tActual: ", instrBuffer);
    if ( getNTokens(instrBuffer, 5, results) == 0 )
    {
        printf("Error on line 1: %s", results[0]);
    }
    else
        for (i = 0; i < 5; i++ )
            printf("%s ", results[i]);
    printf("\n");

    strcpy (instrBuffer, testStrings[1]);
    (void) strtok (instrBuffer, "#");
    printf ("Line 2: %s\n\tExpect 5 tokens\n\tActual: ", instrBuffer);
    if ( getNTokens(instrBuffer, 5, results) == 0 )
    {
        printf("Error on line 2: %s", results[0]);
    }
    else
        for (i = 0; i < 5; i++ )
            printf("%s ", results[i]);
    printf("\n");

    strcpy (instrBuffer, testStrings[2]);
    (void) strtok (instrBuffer, "#");
    printf ("Line 3: %s\n\tExpect 4 tokens\n\tActual: ", instrBuffer);
    if ( getNTokens(instrBuffer, 4, results) == 0 )
    {
        printf("Error on line 3: %s", results[0]);
    }
    else
        for (i = 0; i < 4; i++ )
            printf("%s ", results[i]);
    printf("\n");

    strcpy (instrBuffer, testStrings[3]);
    (void) strtok (instrBuffer, "#");
    printf ("Line 4: %s\n\tExpect 5 tokens\n\tActual: ", instrBuffer);
    if ( getNTokens(instrBuffer, 5, results) == 0 )
    {
        printf("Error on line 4: %s", results[0]);
    }
    else
        for (i = 0; i < 5; i++ )
            printf("%s ", results[i]);
    printf("\n");

    strcpy (instrBuffer, testStrings[4]);
    (void) strtok (instrBuffer, "#");
    printf ("Line 5: %s\n\tExpect 4 tokens\n\tActual: ", instrBuffer);
    if ( getNTokens(instrBuffer, 4, results) == 0 )
    {
        printf("Error on line 5: %s", results[0]);
    }
    else
        for (i = 0; i < 4; i++ )
            printf("%s ", results[i]);
    printf("\n");

    strcpy (instrBuffer, testStrings[5]);
    (void) strtok (instrBuffer, "#");
    printf ("Line 6: %s\n\tExpect 4 tokens\n\tActual: ", instrBuffer);
    if ( getNTokens(instrBuffer, 4, results) == 5 )
    {
        printf("Error on line 6: %s", results[0]);
    }
    else
        for (i = 0; i < 4; i++ )
            printf("%s ", results[i]);
    printf("\n");

    strcpy (instrBuffer, testStrings[6]);
    (void) strtok (instrBuffer, "#");
    printf ("Line 7: %s\n\tExpect 4 tokens\n\tActual: ", instrBuffer);
    if ( getNTokens(instrBuffer, 4, results) == 0 )
    {
        printf("Error on line 7: %s", results[0]);
    }
    else
        for (i = 0; i < 4; i++ )
            printf("%s ", results[i]);
    printf("\n");

    strcpy (instrBuffer, testStrings[7]);
    (void) strtok (instrBuffer, "#");
    printf ("Line 8: %s\n\tExpect 2 tokens\n\tActual: ", instrBuffer);
    if ( getNTokens(instrBuffer, 2, results) == 0 )
    {
        printf("Error on line 8: %s", results[0]);
    }
    else
        for (i = 0; i < 2; i++ )
            printf("%s ", results[i]);
    printf("\n");

    strcpy (instrBuffer, testStrings[8]);
    (void) strtok (instrBuffer, "#");
    printf ("Line 9: %s\n\tExpect 5 tokens\n\tActual: ", instrBuffer);
    if ( getNTokens(instrBuffer, 5, results) == 0 )
    {
        printf("Error on line 9: %s", results[0]);
    }
    else
        for (i = 0; i < 5; i++ )
            printf("%s ", results[i]);
    printf("\n");

    strcpy (instrBuffer, testStrings[9]);
    (void) strtok (instrBuffer, "#");
    printf ("Line 10: %s\n\tAsk for 5 tokens; Expect error\n\tActual: ",
            instrBuffer);
    if ( getNTokens(instrBuffer, 5, results) == 0 )
    {
        printf("Error on line 10: %s", results[0]);
    }
    else
        for (i = 0; i < 5; i++ )
            printf("%s ", results[i]);
    printf("\n");

    strcpy (instrBuffer, testStrings[10]);
    (void) strtok (instrBuffer, "#");
    printf ("Line 11: %s\n\tAsk for 5 tokens; Expect error\n\tActual: ",
            instrBuffer);
    if ( getNTokens(instrBuffer, 5, results) == 0 )
    {
        printf("Error on line 11: %s", results[0]);
    }
    else
        for (i = 0; i < 5; i++ )
            printf("%s ", results[i]);
    printf("\n");

}
