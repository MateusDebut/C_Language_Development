/*MATEUS DOS SANTOS RIBEIRO - Ṇ° USP: 11796997*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define word_size 1

char *read_line(FILE *stream);
void menor_palavra(char **text, int indice);
void maior_palavra(char **text, int indice);
void palindromos(char **text, int indice);
int compara(const void *p1, const void *p2);
char* semelhanca(char *palavra_fixa, char *palavra_semelhante, char *palavra_rotativa);

int main(int argc, char *argv[]){
    //PONTEIRO QUE RECEBERÁ OS COMANDOS DE ABERTURA E FECHAMENTO DO ARQUIVO
    FILE *pFile = NULL;
    int indice = 0;

    //ENTRADA DE DADOS
    char *nome_do_arquivo = NULL;
    nome_do_arquivo = read_line(stdin);

    char *padrao1 = NULL;
    padrao1 = read_line(stdin);

    char *prefixo = NULL;
    prefixo = read_line(stdin);

    char *padrao3 = NULL;
    padrao3 = read_line(stdin);

    char *palavraW = NULL;
    palavraW = read_line(stdin);

    char **text = NULL;

    //ALOCAÇÃO DE TODAS AS PALAVRAS DO ARQUIVO
    pFile = fopen(nome_do_arquivo,"r");
    if (pFile != NULL)
    {
        do{
            text = (char**)realloc(text, (indice + 1) * sizeof(char*));
            text[indice] = read_line(pFile);
            indice++;
        }while(!feof(pFile));
    }
    fclose(pFile);
    //INDICE ARMAZENA O NUMERO TOTAL DE PALAVRAS NO ARQUIVO.
    //PRECISA SER DECREMENTADO EM FUNÇÃO DO USO DO DO WHILE (QUE O INCREMETARÁ UMA ULTIMA VEZ DESNECESSÁRIAMENTE)
    indice = indice - 1;

    printf("%i\n", indice); 
    menor_palavra(text, indice);
    maior_palavra(text, indice);

    //COMPILAÇÃO E EXECUÇÃO DE UMA EXPRESSÃO REGULAR (PADRÃO 1)
    regex_t my_regex;
    regcomp(&my_regex, padrao1, REG_EXTENDED);
    int ocorrencias_padrao1 = 0;
    for (int i = 0; i < indice; i++)
    {
        //TODA VEZ QUE O PADRÃO 1 FOR ENCONTRADO EM UMA PALAVRA, A VARIÁVEL DE OCORRENCIA SERÁ INCREMENTADA
        if (regexec(&my_regex, text[i], 0, NULL, 0) == 0)
        {
            ocorrencias_padrao1++;
        }
    }
    printf("%i\n", ocorrencias_padrao1);

    palindromos(text, indice);

    //BLOCO PARA DETECTAR AS OCORRENCIAS DO PREFIXO NAS PALAVRAS DO ARQUIVO
    char **palavras_prefixo = NULL;
    int contador = 0;
    regcomp(&my_regex, prefixo, REG_EXTENDED);
    for (int i = 0; i < indice; i++)
    {
        //TODA VEZ QUE O PREFIXO É DETECTADO NUMA PALAVRA, UMA CÓPIA DELA É FEITA PARA UMA MATRIZ DE CHAR NA HEAP
        //ESSAS PALAVRAS SERÃO SUBMETIDAS À FUNÇÃO MAIOR_PALAVRA PARA DETECTAR QUAL DELAS É A MAIOR
        if (regexec(&my_regex, text[i], 0, NULL, 0) == 0)
        {
            palavras_prefixo = (char**)realloc(palavras_prefixo, (contador + 1) * sizeof(char*));
            palavras_prefixo[contador] = NULL;
            palavras_prefixo[contador] = (char*)realloc(palavras_prefixo[contador], (strlen(text[i]) + 1) * sizeof(char));
            strcpy(palavras_prefixo[contador], text[i]);
            contador++;
        }
    }
    maior_palavra(palavras_prefixo, contador);
    //DESALOCAR A MAMÓRIA PARA EVITAR UMA POSSIVEL LOTAÇÃO DA HEAP DURANTE A EXECUÇÃO DO PROGRAMA
    for (int i = 0; i < contador; i++)
    {
        free(palavras_prefixo[i]);
    }
    free(palavras_prefixo);

    //DETECÇÃO DE TODAS AS PALAVRAS QUE CONTÊM O PADRÃO 3, SALVANDO-AS NUMA MATRIZ NA HEAP. A MATRIZ SERÁ
    //SUBMETIDA A FUNÇÃO QSORT (AUXILIADA PELA FUNÇÃO COMPARA), PARA ORDENAR AS PALAVRAS EM ORDEM ALFABÉTICA
    char **padrao3_words = NULL;
    contador = 0;
    regcomp(&my_regex, padrao3, REG_EXTENDED);
    for (int i = 0; i < indice; i++)
    {
        //SE UMA PALAVRA QUE CONTÉM O PADRÃO 3 FOR LOCALIZADA UMA CÓPIA DELA É FEITA E SALVA EM PADRAO3_WORDS[CONTADOR].
        if (regexec(&my_regex, text[i], 0, NULL, 0) == 0)
        {
            padrao3_words = (char**)realloc(padrao3_words, (contador + 1) * sizeof(char*));
            padrao3_words[contador] = NULL;
            padrao3_words[contador] = (char*)realloc(padrao3_words[contador], (strlen(text[i]) + 1) * sizeof(char));
            strcpy(padrao3_words[contador], text[i]);
            contador++;
        }
    }
    qsort(padrao3_words, contador, sizeof(char*), compara);
    for (int i = 0; i < contador; i++)
    {
        printf("%s\n", padrao3_words[i]);
    }
    for (int i = 0; i < contador; i++)
    {
        free(padrao3_words[i]);
    }
    free(padrao3_words);

    //PALAVRA SEMELHANTE COMEÇARÁ RECEBEDO A PRIMEIRA PALAVRA DO ARQUIVO. ELA SERÁ SUBMETIDA À FUNÇÃO SEMELHANÇA
    //QUE IRÁ COMPARA-LA COM PALAVRAW E COM AS DEMAIS PALAVRAS DO ARQUIVO, PARA LOCALIZAR A MAIS SEMELHANTE À PALAVRAW
    char *palavra_semelhante = malloc(strlen(text[0]));
    strcpy(palavra_semelhante, text[0]);
    for (int i = 0; i < indice; i++)
    {
        palavra_semelhante = semelhanca(palavraW, palavra_semelhante, text[i]);
    }
    printf("%s\n", palavra_semelhante);

    //LIBERAÇÃO DA HEAP
    for (int i = 0; i < indice; i++)
    {
        free(text[i]);
    }
    free(text);
    free(nome_do_arquivo);
    free(padrao1);
    free(prefixo);
    free(padrao3);
    free(palavraW);
    free(palavra_semelhante);
    regfree(&my_regex);

    return 0;
}

char *read_line(FILE *stream){
    char *string = NULL;
    char aux;
    //indice e quociente
    int i = 0, q = 0;
    //SALVARÁ O CONTEÚDO DE AUXILIAR NO VETOR STRING ENQUANTO ELE FOR DIFERENTE DE UM PULO DE LINHA E DE EOF
    do{
        if (i % word_size == 0)
        { 
            q = i / word_size + 1;
            string = (char*)realloc(string, word_size * q);
        }
        aux = fgetc(stream);
        //CHECA SE O CARACTERE DE RETORNO DE CARRO ESTÁ PRESENTE, CASO ESTEJA, NÃO O INSERE NO VETOR
        if (aux != '\r')
        {
            string[i] = aux;
        }
    }while((string[i++] != '\n') && !feof(stream));
    //COLOCA O TERMINADOR DE STRING E REALOCA O TAMANHO DA STRING
    string[i-1] = '\0';
    string = (char*)realloc(string, (strlen(string)) + 1);
    return string;
}

void menor_palavra(char **text, int indice){
    //ESSE PONTEIRO (ALOCADO) RECEBE INICIALMENTE A PRIMEIRA PALAVRA DO ARQUIVO E DEPOIS A COMPARA COM TODAS
    //AS DEMAIS. QUANDO ENCONTRA UMA PALAVRA MENOR DO QUE A QUE ESTÁ CONTIDA EM SI, RECEBE UMA CÓPIA DELA
    char *menor = (char*)malloc((strlen(text[0]) + 1) * sizeof(char));
    strcpy(menor, text[0]);
    for (int i = 1; i < indice; i++)
    {
        if (strlen(menor) > strlen(text[i]))
        {
            strcpy(menor, text[i]);
        }
    }
    printf("%s\n", menor);
    free(menor);
}

void maior_palavra(char **text, int indice){
    //ESSE PONTEIRO (ALOCADO) RECEBE INICIALMENTE A PRIMEIRA PALAVRA DO ARQUIVO E DEPOIS A COMPARA COM TODAS
    //AS DEMAIS. QUANDO ENCONTRA UMA PALAVRA MAIOR DO QUE A QUE ESTÁ CONTIDA EM SI, RECEBE UMA CÓPIA DELA    
    char *maior = (char*)malloc((strlen(text[0]) + 1)*sizeof(char));
    strcpy(maior, text[0]);
    for (int i = 1; i < indice; i++)
    {
        if (strlen(maior) < strlen(text[i]))
        {
            maior = (char*)realloc(maior, (strlen(text[i]) + 1));
            strcpy(maior, text[i]);
        }
    }
    printf("%s\n", maior);
    free(maior);
}

void palindromos(char **text, int indice){
    //VARIÁVEL SOMA PROGRESSIVAMENTE O NUMERO DE PALINDROMOS ENCONTRADOS
    int palindromos = 0;
    //ESSE LAÇO IRÁ SEMPRE FAZER COM QUE K COMEÇE NA PRIMEIRA LETRA DA PALAVRA E J NA ÚLTIMA E SE REPETIRÁ
    //PARA TODAS AS PALAVRAS DO ARQUIVO.
    for (int i = 0; i < indice; i++)
    {
        int k = 0, j = strlen(text[i]) - 1;
        //ENQUANTO A LETRA NA POSIÇÃO K (INICIAL) FOR IGUAL À LETRA A POSIÇÃO J (FINAL), INCREMENTE K E DECREMENTE J.
        //SE AS LETRAS SÃO IGUAIS E K ESTÁ POSICIONADO NA ÚLTIMA LETRA (E, CONSEQUENTEMENTE, J NA PRIMEIRA), UM
        //PALÍNDROMO FOI ENCONTRADO.
        while(text[i][k] == text[i][j] && k < strlen(text[i])){
            if (text[i][k] == text[i][j] && k == strlen(text[i]) - 1)
            {
                palindromos++;
            }
            k++;
            j--;
        }
    }
    printf("%i\n", palindromos);
}

//FUNÇÃO QUE AUXILIARÁ A QSORT. RETORNA UM INTEIRO (RETORNO DA STRCMP ENTRE P1 E P2)
int compara(const void *p1, const void *p2){
    int comparacao = strcmp(*(char**)p1, *(char**)p2);
    return comparacao;
}


//FUNÇÃO BASEADA NA LÓGICA DO ALGORITMO DE MATCHING PROPOSTO NA AULA 18 - ARITMÉTICA DE PONTEIROS
char* semelhanca(char *palavra_fixa, char *palavra_semelhante, char *palavra_rotativa){
    //O NUMERO DE LINHAS DE MATRIZ CORRSPONDERÁ, SEMPRE, AO NUMERO DE LETRAS DA PALAVRAW (TRATADA AQUI COMO PALAVRA_FIXA).
    //O NUMERO DE COLUNAS PODERÁ VARIAR ENTRE O NUMERO DE LETRAS DE PALAVRA_SEMELHANTE E O NÚMERO DE LETRAS DE PALAVRA
    //ROTATIVA.
    int **matriz = (int**)malloc(strlen(palavra_fixa) * sizeof(int*));

    //VARIÁVEIS QUE ARMAZENAM QUANTAS LETRAS SEMELHANTES HÁ ENTRE (PALAVRA_FIXA E PALAVRA_SEMELHANTE) E ENTRE
    //(PALAVRA_FIXA E PALAVRA ROTATIVA).
    int similaridade1 = 0, similaridade2 = 0;

    //PRIMEIRO, TESTAREMOS A SIMILARIDADE ENTRE PALAVRA FIXA E PALAVRA SEMELHANTE.
    for (int j = 0; j < strlen(palavra_fixa); j++)
    {
        matriz[j] = (int*)malloc((strlen(palavra_semelhante)) * sizeof(int));
    }

    //COMPARAÇÃO ENTRE CADA CARACTERE DE PALAVRA_FIXA (INDIVIDUALMENTE) COM TODOS OS CARACTERES DE
    //PALAVRA SEMELHANTE (SIMILAR A UM JOGO DE CAMPO MINADO). QUANDO ENCONTRARMOS UM CARACTERE EM PALAVRA_SEMELHANTE
    //IGUAL AO CARACTERE ANÁLISADO EM PALAVRA_FIXA, A POSIÇÃO DESSE MATCHING SOFRERÁ UMAS DAS POSSÍVEIS ALTERAÇÕES
    for (int i = 0; i < strlen(palavra_fixa); i++)
    {
        for (int j = 0; j < strlen(palavra_semelhante); j++)
        {
            //SE OCORRE O MATCHING E OS ÍNDICES ESTÃO NA EXTREMIDADE DA MATRIZ (DE MODO QUE NÃO POSSUAM
            //NENHUM ELEMENTO ANTERIOR NA DIAGONAL) ESSA POSIÇÃO DA MATRIZ RECEBE 1.
            if ((palavra_fixa[i] == palavra_semelhante[j]) && (i == 0 || j == 0))
            {
                matriz[i][j] = 1;
            }
            //SE OCORRE O MATCHING E OS ÍNDICES NÃO ESTÃO NA EXTREMIDADE DA MATRIZ, A POSIÇÃO DE MATCHING RECEBE O 
            //ELEMENTO DA DIAGONAL ATERIOR + 1.
            else if ((palavra_fixa[i] == palavra_semelhante[j]) && (i > 0 && j > 0))
            {
                matriz[i][j] = matriz[i-1][j-1] + 1;
            }
            //SE NÃO OCORRE O MATCHING E OS ÍNDICES NÃO ESTÃO NA EXTREMIDADE DA MATRIZ, A POSIÇÃO ATUAL RECEBE
            //UMA CÓPIA DO CONTEÚDO DE DO ELEMENTO DA DIAGONAL ANTERIOR A ELE.
            else if ((palavra_fixa[i] != palavra_semelhante[j]) && (i > 0 && j > 0))
            {
                matriz[i][j] = matriz[i-1][j-1];
            }
            //EM QUALQUER OUTRO CASO, RECEBE 0
            else{
                matriz[i][j] = 0;
            }
        }
    }
    //PERCEBA QUE TERMINAREMOS OS LAÇOS ANTERIORES COM ALGO SIMILAR À:
    /*
            PALAVRA_FIXA        PALAVRA_SEMELHENTE
               LOVE                   OVELHA

                         OVELHA
                       L 000100
                       O 100010
                       V 020001
                       E 003000
    */

    //ASSIM, SE PERCORRERMOS O LAÇO BUSCANDO QUAL O MAIOR ELEMENTO, ELE SERÁ O NOSSO FATOR DE SIMILARIDADE
    for (int i = 0; i < strlen(palavra_fixa); i++)
    {
        for (int j = 0; j < strlen(palavra_semelhante); j++)
        {
            if (similaridade1 <= matriz[i][j])
            {
                similaridade1 = matriz[i][j];
            }
        }
    }

    //REALOCAREMOS A MATRIZ E FAREMOS EXATAMENTE O MESMO PROCESSO, MAS AGORA PARA A PALAVRA ROTATIVA
    for (int j = 0; j < strlen(palavra_fixa); j++)
    {
        matriz[j] = (int*)realloc(matriz[j], (strlen(palavra_rotativa)) * sizeof(int));
    }

    for (int i = 0; i < strlen(palavra_fixa); i++)
    {
        for (int j = 0; j < strlen(palavra_rotativa); j++)
        {
            if ((palavra_fixa[i] == palavra_rotativa[j]) && (i == 0 || j == 0))
            {
                matriz[i][j] = 1;
            }else if ((palavra_fixa[i] == palavra_rotativa[j]) && (i > 0 && j > 0))
            {
                matriz[i][j] = matriz[i-1][j-1] + 1;
            }else if ((palavra_fixa[i] != palavra_rotativa[j]) && (i > 0 && j > 0))
            {
                matriz[i][j] = matriz[i-1][j-1];
            }else{
                matriz[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < strlen(palavra_fixa); i++)
    {
        for (int j = 0; j < strlen(palavra_rotativa); j++)
        {
            if (similaridade2 <= matriz[i][j])
            {
                similaridade2 = matriz[i][j];
            }
        }
    }

    //COMPARA O GRAU DE SIMILARIDADE ENTRE PALAVRA_SEMELHANTE E PALAVRA_ROTATIVA.
    //SE PALAVRA_SEMELHANTE TIVER MAIOR GRAU DE SIMILARIDADE, ELA CONTINUA COMO A PALAVRA SEMELHANTE
    //(PARA A PRÓXIMA ANÁLISE). SE PALAVRA_ROTATIVA FOR A MAIS SIMILAR, COPIAMOS ELA PARA PALAVRA SEMELHANTE.
    if (similaridade1 > similaridade2)
    {
        return palavra_semelhante;
    }else if (similaridade2 > similaridade1)
    {
        palavra_semelhante = (char*)realloc(palavra_semelhante, strlen(palavra_rotativa));
        strcpy(palavra_semelhante, palavra_rotativa);
    }else if (similaridade1 == similaridade2)
    {
        if (strlen(palavra_semelhante) < strlen(palavra_rotativa))
        {
            return palavra_semelhante;
        }else if (strlen(palavra_rotativa) < strlen(palavra_semelhante))
        {
            palavra_semelhante = (char*)realloc(palavra_semelhante, strlen(palavra_rotativa));
            strcpy(palavra_semelhante, palavra_rotativa);
        }
    }
    for (int i = 0; i < strlen(palavra_fixa); i++)
    {
        free(matriz[i]);
    }
    free(matriz);
    return palavra_semelhante;
}

/*Mateus dos Santos Ribeiro - Ṇ° USP: 11796997*/