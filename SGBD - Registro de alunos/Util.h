#ifndef UTIL_H
#define UTIL_H

#define STRING_LENGTH 50

typedef struct indice Indice;

#include <stdio.h>
#include <stdlib.h>
#include "Aluno.h"

char *readline(FILE *stream);
void executaComandos(char *linha, FILE *arquivoRegistros, FILE *arquivoIndices);
static int verificaComandos(char *comando);
void salvaIndiceRegistro(FILE *arquivoRegistros, FILE *arquivoIndice,Aluno *aluno);
void imprimeIndice(Indice *indice);
Indice *leIndiceDoArquivo(FILE *filepointer);
int indiceGetChave(Indice *indice);
long int indiceGetPosicaoNoArquivo(Indice *indice);

#endif // UTIL_H