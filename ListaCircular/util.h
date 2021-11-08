#ifndef UTIL_H_DEFINED
#define UTIL_H_DEFINED

#include <stdio.h>
#include <string.h>
#include "item.h"
#include "list.h"

#define STRING_SIZE 16
#define MAXIMUM_NUMBER_OF_DIVISIONS 3
#define True 1
#define False 0

char *readline(FILE *stream);
void invocateOperation(char *operation, char *complement1, char *complement2, List *list);
char **readCsvFile(char *fileName);
int countLines(char **strings);
void fillList(char **data, int numberOfItems, List *list);
char **separateStringsBySpace(char *string);
int myStrcmp(char *string1, char *string2);
void freeSeparatedInputs(char **separatedInputs);
void freeCharMatrix(int numberOfLines, char **matrix);

#endif //UTIL_H_DEFINED