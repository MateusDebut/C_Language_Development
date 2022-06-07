#ifndef ALUNO_H
#define ALUNO_H


typedef struct aluno Aluno;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Util.h"

Aluno *alunoCreate(int numeroUsp, char *nome, char *sobrenome, char* curso, float nota);

int alunoGetNumeroUsp(Aluno *aluno);

char *alunoGetNome(Aluno *aluno);

char *alunoGetSobrenome(Aluno *aluno);

char *alunoGetCurso(Aluno *aluno);

int alunoGetNota(Aluno *aluno);

void registraAlunoEmArquivo(Aluno *aluno, FILE *arquivoRegistro, FILE *arquivoIndices);

Aluno *leAlunoDoArquivo(FILE *filePointer);

Aluno **leAlunosDoArquivo(FILE *filePointer);

int retornaNumeroDeAlunosDoArray(Aluno **alunos);

Aluno *criaAlunoAPartirDeLinhaCSV(char *string);

Aluno **criaListaAlunosAPartirDoCSV();

int isBlank(char *string);

Aluno **leUltimosDezAlunosDoArquivo(FILE *filePointer);

void alunoPrint(Aluno *aluno);

Aluno *recuperaAlunoPorIndice(int chave, FILE *arquivoRegistros, FILE *arquivoIndices);

Aluno *verificaExistenciaDeAlunoPorChave(Indice **indices, int chave, FILE *filepointer, int counter);

Indice **recuperaTodosOsIndicesDoArquivoDeIndices(FILE *arquivoIndice);

void deletaAlunoPorIndice(int chave, FILE *arquivoRegistros, FILE *arquivoIndices);

#endif //ALUNO_H