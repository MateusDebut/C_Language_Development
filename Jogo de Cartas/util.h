#ifndef UTIL_H
#define UTIL_H

#define True 1
#define False 0

#define TAMANHO_DEFAULT_STRING 256

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

char *readline(FILE *stream);
int atoiReadline(FILE *stream);
void gameLogic(Stack *stack);

#endif //UTIL_H