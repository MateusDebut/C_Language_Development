#include "Util.h"

enum comandos{INSERT=1, SEARCH=2, DELETE=3, EXIT=4};

struct indice{
    int chave;
    long int posicaoNoArquivo;
};

char *readline(FILE *stream){
    int index = 0;
    char *string = calloc(STRING_LENGTH, sizeof(char));
    do
    {
        char aux = getc(stream);
        if(aux < 32) {
            string[index] = '\n';
        }else{
            string[index] = aux;
        }
        index++;
    } while (string[index-1] != '\n' && string[index-1] != EOF);

    string[index-1] = '\0';
    return string;
}

void executaComandos(char *linha, FILE *arquivoRegistros, FILE *arquivoIndices){
    enum comandos comando = verificaComandos(linha);
    switch (comando) {
        case INSERT:;
            char *aux = calloc(strlen(linha), sizeof(char));
            strcpy(aux, linha);
            strtok(aux, " ");
            char *chaveDoIndice = strtok(NULL, ",");
            Indice **indices = recuperaTodosOsIndicesDoArquivoDeIndices(arquivoIndices);
            for (int i = 0; indices[i] != NULL; i++) {
                if(indiceGetChave(indices[i]) == atoi(chaveDoIndice)){
                    printf("O Registro ja existe!\n");
                    return;
                }
            }
            Aluno *aluno = criaAlunoAPartirDeLinhaCSV(linha);
            registraAlunoEmArquivo(aluno, arquivoRegistros, arquivoIndices);
            break;
        case SEARCH:;
            strtok(linha, " ");
            char *chave = strtok(NULL, "\n");
            Aluno *alunoRecuperado = recuperaAlunoPorIndice(atoi(chave), arquivoRegistros, arquivoIndices);
            if(alunoRecuperado != NULL && alunoGetNumeroUsp(alunoRecuperado) != -1){
                alunoPrint(alunoRecuperado);
            }else{
                printf("Registro nao encontrado!\n");
            }
            return;
        case DELETE:;
            strtok(linha, " ");
            char *key = strtok(NULL, "\n");
            deletaAlunoPorIndice(atoi(key), arquivoRegistros, arquivoIndices);
            return;
        case EXIT:
            exit(0);
        default:
            return;
    }
}

static int verificaComandos(char *linha){
    char *aux = malloc(strlen(linha));
    strcpy(aux, linha);
    char *comando = strtok(aux, " ");

    if(strcmp(comando, "insert") == 0){
        //free(aux);
        return 1;
    }else if(strcmp(comando, "search") == 0){
        //free(aux);
        return 2;
    }else if(strcmp(comando, "delete") == 0){
        //free(aux);
        return 3;
    }else if(strcmp(comando, "exit") == 0){
        //free(aux);
        return 4;
    }
    //free(aux);
    printf("Comando não mapeado\n");
    return 0;
}

void salvaIndiceRegistro(FILE *arquivoRegistros, FILE *arquivoIndice, Aluno *aluno){
    int indice = alunoGetNumeroUsp(aluno);
    long int localizacao = ftell(arquivoRegistros);
    fwrite(&indice, sizeof(int), 1, arquivoIndice);
    fwrite(&localizacao, sizeof(long int), 1, arquivoIndice);
}

void imprimeIndice(Indice *indice){
    printf("chave: %d\nposição: %ld\n", indice->chave, indice->posicaoNoArquivo);
}

Indice *leIndiceDoArquivo(FILE *filepointer){
    Indice *indice = (Indice *) malloc(sizeof(Indice));
    unsigned long int tamanhoLido;
    tamanhoLido = fread(&indice->chave, sizeof(int), 1, filepointer);
    if(tamanhoLido != 1){
        return NULL;
    }
    fread(&indice->posicaoNoArquivo, sizeof(long int), 1, filepointer);
    return indice;
}

int indiceGetChave(Indice *indice){
    return indice->chave;
}

long int indiceGetPosicaoNoArquivo(Indice *indice){
    return indice->posicaoNoArquivo;
}