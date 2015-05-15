/*
* File: assemble.h
* Author: Preston Stosur-Bassett
* Date: 13.5.15
* Description: Header file for assemble.c
*/

/* START: DEFINE LABEL_H */

#ifndef LABEL_H
#define LABEL_H

/* THE DATA STRUCTURES */

/* The first type definition defines the type for a single entry in the
 * table.  The second defines the type for the table as a whole.
 */

typedef struct {
        char * label;           /* label name */
        int   address;           /* address of label */
} LabelEntry;

typedef struct {
        int capacity;           /* capacity of the table */
        int nbrLabels;          /* actual nbr of entries in table */
        LabelEntry * entries;
} LabelTable;


/* THE FUNCTIONS */

void tableInit  (LabelTable * table);
        /* Postcondition: table is initialized to indicate that there
         *       are no label entries in it.
         */

int tableResize (LabelTable * table, int newSize);
        /* Postcondition: table now has the capacity to hold newSize
         *      label entries.  If the new size is smaller than the
         *      old size, the table is truncated after the first
         *      newSize entries.
         * Returns 1 if everything went OK; 0 if memory allocation error
         *      or table doesn't exist.
         */

int addLabel    (LabelTable * table, char * labelName, int memLoc);
        /* Postcondition: if label was already in table, the table is
         *      unchanged; otherwise a new entry has been added to the
         *      table with the specified label name and instruction address
         *      (memory location) and the table has been resized if necessary.
         * Returns 1 if no fatal errors occurred; 0 if memory allocation error
         *      or table doesn't exist.
         */

int findLabel (LabelTable * table, char * label);
        /* Returns the address associated with the label; -1 if label is
         *      not in the table or if table doesn't exist
         */

void printLabels (LabelTable * table);
        /* Postcondition: all the labels in the table have been printed
         *      to the standard output.
         */

#endif

/* END: DEFINE LABEL_H */

/* START: DEFINE ASSEMBLER */

#ifndef ASSEMBLER
#define ASSEMBLER

/*
*   TODO: write the function spec for this function
*/
char * getOpCode(char * operation);

/*
*   TODO: write the function spec for this function
*/
int getFormat(char * opCode);

/*
*   TODO: write the function spec for this function
*/
char * getFunctionCode(char * operation);

/*
*   TODO: write the function spec for this function
*/
char * parseReg(char ** regName);

/*
*   TODO: write the function spec for this function
*/
void parseR(char * instruction, char * opCode, char * operation, char ** superTokenBegin, char ** superTokenEnd, int lineNum);

/*
*   TODO: write the function spec for this function
*/
void parseI(char *  instruction, char * opCode, char ** superTokenBegin, char ** superTokenEnd, int lineNum, LabelTable table);

/*
* Description: parseJ handles how to parse, format, and print J type assembly instructions and prints them out in their proper binary format.
* Pre-Condition: TODO: write the preconditions for this function
* Post-Condition: The J type instruction is printed out to the console (TODO: update this when it writes out to a file)
* @param <code>char * instruction</code> is a NON-NULL well-defined "string" of the instruction itself.
* @param <code>char * opCode</code> is a NON-NULL well-defined "string" of the opCode in binary format
* @param <code>char ** superTokenBegin</code> is a NON-NULL well-defined "string" address of the beginning of the current token for the current instruction
* @param <code>char ** superTokenEnd</code> is a NON-NULL well-defined "string" address of the end of the current token for the current instruction
* @param <code>int lineNum</code> is an integer value that corresponds to the current line number of assembly code.
* @param <code>LabelTable * table</code> is a LabelTable that contains all the labels for the current assembly code file (created in pass1)
*/
void parseJ(char * instruction, char * opCode, char ** superTokenBegin, char ** superTokenEnd, int lineNum, LabelTable table);

#endif

/* END: DEFINE ASSEMBLER */
