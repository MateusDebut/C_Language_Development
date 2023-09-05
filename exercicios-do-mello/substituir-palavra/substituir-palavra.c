#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanhoPalavra 200
#define numero_de_palavras 200

int contador = 0;//contara quantas palavras existem na frase/texto


/*    FUNÇÕES    */

//Armazena dinâmicamente a palavra que será substituída e sua substituta
char *read_word(char *palavra);

//Armazena dinâmicamente a frase ou texto a ser escrito. Divide ele em várias palavras armazenadas em um vetor de vetores.
char **read_text(char **texto);

//localiza todas as incidências de palavra1 no ponteiro duplo frase e substitui cada aparição por
//palavra2 (copiando a palavra2 para os vetores frase[i] que forem iguai à palavra 1)
char **substituir(char *palavra1, char **frase, char *palavra2);


/********FIM FUNÇÕES**********/

int main() {
  char *palavra1 = (char *)malloc(tamanhoPalavra);
  char *palavra2 = (char *)malloc(tamanhoPalavra);
  char **frase = (char **)malloc(numero_de_palavras * sizeof(char*));

  for (int i = 0; i < numero_de_palavras; i++)
  {
    frase[i] = (char*)malloc(tamanhoPalavra * sizeof(char));
  }

  palavra1 = read_word(palavra1);
  palavra2 = read_word(palavra2);
  frase = read_text(frase);
  frase = substituir(palavra1, frase, palavra2);

  //imprime a nova frase
  for (int i = 0; i < contador; i++)
  {
    printf("%s ", frase[i]);
  }
  printf("\n");

  free(palavra1);
  free(palavra2);
  //libera todas as palavras que existiam no ponteiro duplo
  for (int i = 0; i < contador; i++)
  {
    free(frase[i]);
  }
  free(frase);

  return 0;
}


        /**** FUNÇÕES ****/

char *read_word(char *palavra){
  int i = 0, q = 0;//indice e quociente
  char aux;

//Este laço coloca os caracteres digitados no vetor entrada e realoca o vetor sempre que i % tamanhoPalavra == 0
  do{
    if (i % tamanhoPalavra == 0)
    {
      q = i / tamanhoPalavra + 1;
      palavra = (char*) realloc(palavra, q * tamanhoPalavra);
    }
    aux = getc(stdin);
    if (aux != '\r')
    {
      palavra[i] = aux;
    }else{
      palavra[i] = '\n';
    }    
  }while(palavra[i++] != '\n' && !feof(stdin));

  palavra[i-1] = '\0';//coloca o terminador de string onde havia o \n;
  return palavra;
}




char **read_text(char **texto){
  int j = 0, q1 = 0, q2 = 0, i = 0;//indices e quocientes
  char aux;

//Este laço armazena os caracteres da frase em vetores. Sempre que encontra um "espaço" o indice i é incrementado
//e outro vetor passa a ser usado para armazenar a nova palavra. Ele para o armazenamento quando encontra um '\n'.
  do{
    j = 0;
    //condição para realocar o ponteiro duplo caso o número de palavras exceda o limite (qi * numero_de_palavras)
    if (i % numero_de_palavras == 0)
    { 
      q1 = i / numero_de_palavras + 1;
      texto = (char**) realloc(texto, q1 * numero_de_palavras * sizeof(char*));
    }
    do{
      //condição para realocar os vetores que armazenam as palavras individualmente, caso o numero de caracteres
      //exceda o limite (q2 * tamanhoPalavra)
      if (j % tamanhoPalavra == 0)
      {
        q2 = j / tamanhoPalavra + 1;
        texto[i] = (char*) realloc(texto[i], q2 * tamanhoPalavra * sizeof(char));
      }
      aux = getc(stdin);
      if (aux != '\r')
      {
        texto[i][j] = aux;
      }else{
        texto[i][j] = '\n';
      }
      j++;
    }while(texto[i][j-1] > 32);
    contador = contador + 1;// incrementa quando uma palavra é lida por inteiro
    i++;
  }while (texto[i-1][j-1] != '\n' && !feof(stdin));
  texto[i-1][j-1] = '\0';//coloca o terminador de string onde havia o \n;

  //coloca o terminador de string nas palavras individualmente
  for (int i = 0; i < contador; i++)
  {
    if (texto[i][strlen(texto[i]) - 1] <= 32)
    {
      texto[i][strlen(texto[i]) - 1] = '\0';
    }
  }

  //libera os ponteiros que sobraram
  for (int i = contador;i < numero_de_palavras ; i++)
  {
    free(texto[i]);
  }

  //Realoca o ponteiro duplo que guarda as palavras da frase para que use apenas o número de palavras necessárias
  texto = (char**)realloc(texto, contador * sizeof(char*));
  return texto;
}




char **substituir(char *palavra1, char **frase, char *palavra2){
  for (int i = 0; i < contador; i++)
  {
    //a função strstr compara duas palavras. Se elas forem iguais (Ou uma estiver contida dentro da outra)
    //ela retorna um ponteiro com o endereço onde a segunda aparece na primeira. Se forem diferentes, retorna NULL
    if (strstr(frase[i], palavra1) != NULL)
    { 
      //Condição que verifica a existência de pontuações depois da palavra que deve ser substituída. Caso encontre
      //Ajusta a cópia da string para que a pontuação seja inserida.
      if ((frase[i][(strlen(frase[i])) - 1] < 64) && (frase[i][(strlen(frase[i])) - 1] > 32))
      {   palavra2[strlen(palavra2)] = frase[i][(strlen(frase[i])) - 1];
          strcpy(frase[i], palavra2);
          frase[i][strlen(palavra2)] = '\0';
          palavra2[strlen(palavra2) - 1] = '\0';
      }else{
        strcpy(frase[i], palavra2);
        frase[i][strlen(palavra2)] = '\0';
      }
    }
  }
  return frase;
}
