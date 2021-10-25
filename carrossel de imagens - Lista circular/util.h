#ifndef UTIL_H_DEFINED
#define UTIL_H_DEFINED

#include <stdio.h>
#include <string.h>
#include "item.h"
#include "list.h"

#define STRING_SIZE 16
#define True 1
#define False 0

char *readline(FILE *stream);
int myStrcmp(char *string1, char *string2);

#endif //UTIL_H_DEFINED