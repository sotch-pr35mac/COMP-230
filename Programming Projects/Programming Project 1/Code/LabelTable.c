/*
 * Label Table: functions to access and manipulate a label table
 *
 * This file provides the definitions of a set of functions for
 * creating, maintaining, and using a table of assembly language
 * instruction labels and the memory addresses associated with them.
 *
 * Author: Alyce Brady
 *
 * Creation Date:   2/16/99
 *   Modified:  12/20/2000   Updated postcondition information.
 *   Modified:  4/19/2013    Modernized call to fprintf for errors.
 *
 * WARNING: These functions are incomplete!!!!!
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>             /* might be memory.h on some machines */

#include "LabelTable.h"

static const char * ERROR1 = "Error: cannot allocate space in memory.\n";
static const char * ERROR2 = "Error: a duplicate label was found.\n";

const int SAME = 0;             /* useful for making strcmp readable */
                                /* e.g., if (strcmp (str1, str2) == SAME) */

void tableInit (LabelTable * table)
  /* Postcondition: table is initialized to indicate that there
   *       are no label entries in it.
   */
{
        /* make sure that table exists */
        if ( table == NULL )
            return;

        /* TODO: (this shit) code missing ! */
}

int tableResize (LabelTable * table, int newSize)
  /* Postcondition: table now has the capacity to hold newSize
   *      label entries.  If the new size is smaller than the
   *      old size, the table is truncated after the first
   *      newSize entries.
   * Returns 1 if everything went OK; 0 if memory allocation error
   *      or table doesn't exist.
   */
{
        char *       ptr;              /* points to any byte in memory */
        LabelEntry * newEntryList;
        int          smaller;

        /* make sure that table exists */
        if ( table == NULL )
            return 0;

        /* create a new internal table of the specified size */
        if ((newEntryList = malloc (newSize * sizeof(LabelEntry))) == NULL)
        {
            (void) fprintf (stderr, "%s", ERROR1);
            return 0;
        }

        if ( table->entries )           /* if there were entries */
        {
            /* move contents of internal table to new internal table */
            smaller = table->nbrLabels < newSize ? table->nbrLabels : newSize;
            (void) memcpy (newEntryList, table->entries,
                           smaller * sizeof(LabelEntry));

            /* free the space taken up by the old internal table */
            free (table->entries);
            table->nbrLabels = smaller;
        }

        table->entries = newEntryList;
        table->capacity = newSize;
        return 1;
}

int addLabel (LabelTable * table, char * label, int PC)
  /* Postcondition: if label was already in table, the table is
   *      unchanged; otherwise a new entry has been added to the
   *      table with the specified label name and instruction address
   *      (memory location) and the table has been resized if necessary.
   * Returns 1 if no fatal errors occurred; 0 if memory allocation error
   *      or table doesn't exist.
   */
{
        char * labelDuplicate;

        /* make sure that table exists */
        if ( table == NULL )
            return 0;

        /* Create a dynamically allocated version of label that will persist. */
        /*   NOTE: on some machines you may need to make this _strdup !  */
        if ((labelDuplicate = strdup (label)) == NULL)
        {
            (void) fprintf (stderr, "%s", ERROR1);
            return 0;           /* fatal error: couldn't allocate memory */
        }

        /* Was the label already in the table? */
           /* TODO: this shit: code missing ! */        /* BTW, this is not a FATAL error */

        /* Resize the table if necessary. */
        if ( table->nbrLabels >= table->capacity )
           /* TODO: This shit: code missing ! */
           /* Tip:  Choose a new size that will work even if current
            *       capacity is 0.
            */

        /* Add the label */
           /* TODO: this shit! code missing ! */

        return 1;               /* everything worked great! */
}

int findLabel (LabelTable * table, char * label)
  /* Returns the address associated with the label; -1 if label is
   *      not in the table or table doesn't exist
   */
{
        int i;

        if(table == NULL) {
          printf("Label Table is a NULL pointer.\n");
          return -1;
        }
        else {
          i = 0;
          while(i < table->nbrLabels) {
            if(label == table->entries[i]->label) {
              printf("Found label %s at index %d\n", label, i);
              return i;
            }
          }
        }

        printf("The label %s was not found.\n", label);
        return -1;
}

void printLabels (LabelTable * table)
  /* Postcondition: all the labels in the table have been printed
   *      to the standard output.
   */
{
        int i;

        if ( table == NULL )
            (void) printf ("Label Table is a NULL pointer.\n");
        else
        {
            (void) printf ("There are %d labels in the table:\n",
                                    table->nbrLabels);

            i = 0;
            while(i < table->nbrLabels) {
              printf("Label Number: %d | Label: %s\n", i+1, table->entries[i]->label);

              i++;
            }
        }
}
