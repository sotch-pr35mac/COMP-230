/*
 * Label Table: functions to access and manipulate a label table
 *
 * This file provides the definitions of a set of functions for
 * creating, maintaining, and using a table of assembly language
 * instruction labels and the memory addresses associated with them.
 *
 * Author: Alyce Brady, Preston Stosur-Bassett
 *
 * Creation Date:   2/16/99
 *   Modified:  12/20/2000   Updated postcondition information.
 *   Modified:  4/19/2013    Modernized call to fprintf for errors.
 *   Modified:  4/9/2015     Finsished Code
 *
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>             /* might be memory.h on some machines */

#include "LabelTable.h"

static const char * ERROR1 = "Error: cannot allocate space in memory.\n";
static const char * ERROR2 = "Error: a duplicate label was found.\n";
static const char * ERROR3 = "Error: table does not exist.\n";

const int SAME = 0;             /* useful for making strcmp readable */
                                /* e.g., if (strcmp (str1, str2) == SAME) */

/*
* Post-Condition: table is initialized to indicate that there are no label entries.
*/
void tableInit (LabelTable * table) {
  /* make sure that the table exists */
  if(table == NULL) {
    printf("%s", ERROR3);
    return;
  }

  //Initialize the table
  table->nbrLabels = 0;
  table->capacity = 0;
  table->entries = 0;
}

/* Postcondition: table now has the capacity to hold newSize
 *      label entries.  If the new size is smaller than the
 *      old size, the table is truncated after the first
 *      newSize entries.
 * Returns 1 if everything went OK; 0 if memory allocation error
 *      or table doesn't exist.
 */
int tableResize(LabelTable * table, int newSize) {
  char * ptr; /* points to any byte in memory */
  LabelEntry * newEntryList;
  int smaller;

  /* make sure that the table actually exists */
  if(table == NULL) {
    printf("Error! The table does not exist.\n");
    return 0;
  }

  /* create a new internal table of the specified size */
  if((newEntryList = malloc(newSize * sizeof(LabelEntry))) == NULL) {
    (void) fprintf(stderr, "%s", ERROR1);
    return 0;
  }

  /* if there were entries */
  if(table->entries) {
    /* move contents of internal table to new internal table */
    smaller = table->nbrLabels < newSize ? table->nbrLabels : newSize;
    (void) memcpy (newEntryList, table->entries, smaller * sizeof(LabelEntry));

    /* free the space taken up by the old internal table */
    free (table->entries);
    table->nbrLabels = smaller;
  }

  table->entries = newEntryList;
  table->capacity = newSize;
  return 1;
}

/* Postcondition: if label was already in table, the table is
 *      unchanged; otherwise a new entry has been added to the
 *      table with the specified label name and instruction address
 *      (memory location) and the table has been resized if necessary.
 * Returns 1 if no fatal errors occurred; 0 if memory allocation error
 *      or table doesn't exist.
 */
int addLabel(LabelTable * table, char * label, int PC) {
  char * labelDuplicate;

   /* make sure that the table actually exists */
   if(table == NULL) {
     return 0;
   }

   /* Create a dynamically allocated version of label that will persist. */
   /* NOTE: on some machines you may need to make this _strdup ! */
   if((labelDuplicate = strdup(label)) == NULL) {
     (void) fprintf(stderr, "%s", ERROR1);
     return 0; /* fatal error: couldn't allocate memory */
   }

   /* Was the label already in the table? */

   if(findLabel(table, label) == -1) {

     if(table->nbrLabels >= table->capacity+1) {
       /* Resize table */
       tableResize(table, table->capacity+1);
     }

    /* Add the label */
     LabelEntry *tabEntries = table->entries + table->nbrLabels;
     tabEntries->label = labelDuplicate;
     tabEntries->address = PC;
     table->nbrLabels++;
   }
   else {
     printf("The label already exists.\n");
   }

   return 1; /* everything worked great */
}

/* Returns the address associated with the label; -1 if label is
 *      not in the table or table doesn't exist
 */
int findLabel(LabelTable * table, char * label) {
  int i = 0;

  if(table == NULL) {
    printf("Label Table is a NULL pointer.\n");
    return -1;
  }
  else {
    /* create a pointer to the entries in the table */
    LabelEntry *tabEntries = table->entries;

    while(i < table->nbrLabels) {
      if(strcmp(tabEntries->label, label) == SAME) {
        printf("Found label %s at index %d\n", label, tabEntries->address);
        return tabEntries->address;
      }

      tabEntries++;
      i++;
    }
  }

  printf("The label %s was not found.\n", label);
  return -1;
}

/*
* Post-Condition: all the labels in the table have been printed to the standard output.
*/
void printLabels(LabelTable * table) {
  /* create a pointer to the entries in the table */
  LabelEntry *tabEntries = table->entries;
  int i;

  if(table == NULL) {
    (void) printf("Label Table is a NULL pointer.\n");
  }
  else {
    (void) printf("There are %d labels in the table:\n", table->nbrLabels);

    i = 0;
    while(i < table->nbrLabels) {
      printf("Label Address: %d | Label: %s\n", tabEntries->address, tabEntries->label);

      tabEntries++;
      i++;
    }
  }

  return;
}
