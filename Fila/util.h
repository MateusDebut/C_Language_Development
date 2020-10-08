#include "fila.h"
#define wordSize 256

char *readline(FILE *stream);
int identificaEntrada(char *string);
//Recebe a entrada no formato "ENTRA Nome idade criterio" e retorna esses elementos separados dentro de um elem_t
elem_t separaEmPartes(char *string, elem_t elemento);