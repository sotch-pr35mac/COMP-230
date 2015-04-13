/*
* Test: Testing driver for Label Table
*
* This file serves as a driver function for Label Table, and can be used to ensure the functionality of LabelTable.c
*
* Author: Preston Stosur-Bassett
*
* Date: April 9, 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LabelTable.h"

int main(int argc, char *argv[]) {
  /* Create success and failure counters. */
  int successCounter = 0;
  int failureCounter = 0;

  /* Create a test label entry */
  char * firstEntryChar = "test";
  LabelEntry testerEntry = {firstEntryChar, *firstEntryChar};

  /* Create a second test label entry for a different table */
  char * secondEntryChar = "differentTest";
  LabelEntry secondEntry = {secondEntryChar, *secondEntryChar};

  /* Create a test label table */
  LabelTable * firstTable = {1, 1, secondEntry};

  /* Test tableInit from LabelTable.c */
  tableInit(firstTable);

  /* Initialize testTable */
  LabelTable * testTable = {1, 1, testerEntry};

  /* Test tableResize from LabelTabel.c */
  int tableResizeResult = tableResize(testTable, 2);
  if(tableResizeResult == 0) {
    printf("Resizing table: success\n");
    successCounter++;
  }
  else {
    printf("Resizing table: FAILED\n");
    failureCounter++;
  }

  /* Test addLabel from LabelTable.c */
  char * newLabel = "Label 2";
  int addLabelResult = addLabel(testTable, newLabel, *newLabel);
  if(addLabelResult == 1) {
    printf("Adding Label: success\n");
    successCounter++;
  }
  else {
    printf("Adding Label: FAILED\n");
    failureCounter++;
  }

  /* Test findLabel from LabelTable.c */
  int findLabelResult = findLabel(testTable, "test");
  if(findLabelResult == -1) {
    printf("Finding Label: FAILED\n");
    failureCounter++;
  }
  else {
    printf("Finding Label: success\n");
    successCounter++;
  }

  /* Test printLabels from LabelTable.c */
  printLabels(testTable);

  printf("Test complete. Your program passed %d tests, and failed %d tests.\n", successCounter, failureCounter);
  return 1;
}
