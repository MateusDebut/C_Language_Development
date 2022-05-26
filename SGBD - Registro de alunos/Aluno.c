#include "Aluno.h"

struct aluno
{
	int numeroUsp;
	char nome[STRING_LENGTH];
    char sobrenome[STRING_LENGTH];
	char curso[STRING_LENGTH];
	float nota;	
};

static void alunoSetNome(char *nome, Aluno *aluno){
	for (int i = 0; i < strlen(nome) && i < STRING_LENGTH; i++)
    {
		aluno->nome[i] = nome[i];
	}
    aluno->nome[strlen(nome)] = '\0';
}

static void alunoSetSobrenome(char *sobrenome, Aluno *aluno){
    for (int i = 0; i < strlen(sobrenome) && i < STRING_LENGTH; i++)
    {
        aluno->sobrenome[i] = sobrenome[i];
    }
    aluno->sobrenome[strlen(sobrenome)] = '\0';
}

static void alunoSetCurso(char *curso, Aluno *aluno){
	for (int i = 0; i < strlen(curso) && i < STRING_LENGTH; i++)
	{
		aluno->curso[i] = curso[i];
	}
    aluno->curso[strlen(curso)] = '\0';
}

Aluno *alunoCreate(int numeroUsp, char *nome, char *sobrenome, char* curso, float nota){
	Aluno *aluno = 	(Aluno *) malloc(sizeof(Aluno));
	aluno->numeroUsp = numeroUsp;
	alunoSetNome(nome, aluno);
    alunoSetSobrenome(sobrenome, aluno);
	alunoSetCurso(curso, aluno);
	aluno->nota = nota;
	return aluno;
}

void registraAlunoEmArquivo(Aluno *aluno, FILE *arquivoRegistro, FILE *arquivoIndices){
	if(aluno == NULL) return;
    salvaIndiceRegistro(arquivoRegistro, arquivoIndices, aluno);
	fwrite(&aluno->numeroUsp, sizeof(int), 1, arquivoRegistro);
	fwrite(&aluno->nome, sizeof(char), STRING_LENGTH, arquivoRegistro);
    fwrite(&aluno->sobrenome, sizeof(char), STRING_LENGTH, arquivoRegistro);
	fwrite(&aluno->curso, sizeof(char), STRING_LENGTH, arquivoRegistro);
	fwrite(&aluno->nota, sizeof(float), 1, arquivoRegistro);
}

Aluno *leAlunoDoArquivo(FILE *filePointer){
	Aluno *aluno = (Aluno *) malloc(sizeof(Aluno));
	int tamanhoLido = fread(&aluno->numeroUsp, sizeof(int), 1, filePointer);

	if(tamanhoLido != 1) return NULL;

	fread(&aluno->nome, sizeof(char), STRING_LENGTH, filePointer);
    fread(&aluno->sobrenome, sizeof(char), STRING_LENGTH, filePointer);
	fread(&aluno->curso, sizeof(char), STRING_LENGTH, filePointer);
	fread(&aluno->nota, sizeof(float), 1, filePointer);
	return aluno;
}

Aluno **criaListaAlunosAPartirDoCSV(){
    Aluno **alunos = NULL;
	int counter = 0;
	do{
		alunos = (Aluno**) realloc(alunos,(1+counter) * sizeof(Aluno *));
		alunos[counter] = criaAlunoAPartirDeLinhaCSV(readline(stdin));
		counter++;
	}while(!feof(stdin));
	return alunos;
}

Aluno *criaAlunoAPartirDeLinhaCSV(char *string){
	if(isBlank(string)) return NULL;
	Aluno *aluno = (Aluno *) malloc(sizeof(Aluno));
    strtok(string, " ");
	aluno->numeroUsp = atoi(strtok(NULL, ","));
	alunoSetNome(strtok(NULL, ","), aluno);
    alunoSetSobrenome(strtok(NULL, ","), aluno);
	alunoSetCurso(strtok(NULL, ","), aluno);
	aluno->nota = atof(strtok(NULL, ","));
	return aluno;
}

int isBlank(char *string){
	if(string == NULL || string[0] == '\0' || strcmp(string, "") == 0){
		return 1;
	}
	return 0;
}

Aluno **leAlunosDoArquivo(FILE *filePointer){
	Aluno **alunos = NULL;
	int counter = 0;
	do{
		alunos = (Aluno**) realloc(alunos,(1+counter) * sizeof(Aluno *));
		alunos[counter] = leAlunoDoArquivo(filePointer);
		counter++;
	}while(alunos[counter-1] != NULL);
	return alunos;
}

Aluno **leUltimosDezAlunosDoArquivo(FILE *filePointer){
	fseek(filePointer, -10*108, SEEK_END);
	Aluno **alunos = NULL;
	int counter = 0;
	do{
		alunos = (Aluno**) realloc(alunos,(1+counter) * sizeof(Aluno *));
		alunos[counter] = leAlunoDoArquivo(filePointer);
		counter++;
	}while(alunos[counter-1] != NULL);
	return alunos;
}

void alunoPrint(Aluno *aluno){
    printf("-------------------------------\n");
	printf("USP number: %d\n", aluno->numeroUsp);
	printf("Name: %s\n", aluno->nome);
    printf("Surname: %s\n", aluno->sobrenome);
	printf("Course: %s\n", aluno->curso);
	printf("Test grade: %.2f\n", aluno->nota);
    printf("-------------------------------\n");
}

int retornaNumeroDeAlunosDoArray(Aluno **alunos){
	int numeroAlunos = 0;
	for(int counter = 0; alunos[counter] != NULL; counter++){
		numeroAlunos++;
	}
	return numeroAlunos;
}

Aluno *recuperaAlunoPorIndice(int chave, FILE *arquivoRegistros, FILE *arquivoIndices){
    Indice **indices = recuperaTodosOsIndicesDoArquivoDeIndices(arquivoIndices);
    int counter = 0;
    while (indices[counter] != NULL){
        counter++;
    }
    Aluno *aluno = verificaExistenciaDeAlunoPorChave(indices, chave, arquivoRegistros, counter);
    return aluno;
}

void deletaAlunoPorIndice(int chave, FILE *arquivoRegistros, FILE *arquivoIndices){
    Indice **indices = recuperaTodosOsIndicesDoArquivoDeIndices(arquivoIndices);
    int counter = 0;
    while (indices[counter] != NULL){
        counter++;
    }

    for (int i = 0; i < counter; ++i) {
        if(indiceGetChave(indices[i]) == chave){
            fseek(arquivoRegistros, indiceGetPosicaoNoArquivo(indices[i]), SEEK_SET);
            int indiceDeRemocao = -1;
            fwrite(&indiceDeRemocao, sizeof(int), 1, arquivoRegistros);
            return;
        }
    }
}

Aluno *verificaExistenciaDeAlunoPorChave(Indice **indices, int chave, FILE *filepointer, int counter){
    for (int i = 0; i < counter; i++) {
        if(indiceGetChave(indices[i]) == chave){
            fseek(filepointer, indiceGetPosicaoNoArquivo(indices[i]), SEEK_SET);
            Aluno *aluno = leAlunoDoArquivo(filepointer);
            return aluno;
        }
    }
    return NULL;
}

Indice **recuperaTodosOsIndicesDoArquivoDeIndices(FILE *arquivoIndice){
    fseek(arquivoIndice, 0, SEEK_SET);
    Indice **indices = NULL;
    int counter = 0;
    do{
        indices = (Indice **) realloc(indices,(1+counter) * sizeof(Indice *));
        indices[counter] = leIndiceDoArquivo(arquivoIndice);
        counter++;
    }while(indices[counter-1] != NULL);
    return indices;
}

int alunoGetNumeroUsp(Aluno *aluno){
	return aluno->numeroUsp;
}

char *alunoGetNome(Aluno *aluno){
	return aluno->nome;
}

char *alunoGetSobrenome(Aluno *aluno){
    return aluno->sobrenome;
}

char *alunoGetCurso(Aluno *aluno){
	return aluno->curso;
}

int alunoGetNota(Aluno *aluno){
	return aluno->nota;
}