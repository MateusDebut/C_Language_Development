#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verificaOrdem(int linhas, int colunas);
void det_ordem1(int linhas);
void det_ordem2(int linhas);
void det_ordem3(int linhas);

int main(int argc, char const *argv[])
{
  int linhas, colunas, ordem;
  scanf("%i", &linhas);
  scanf("%i", &colunas);
  ordem = verificaOrdem(linhas, colunas);
  if (ordem == 1)
  {
    det_ordem1(linhas);
  }else if (ordem == 2)
  {
    det_ordem2(linhas);
  }else if (ordem == 3)
  {
    det_ordem3(linhas);
  }else if (ordem == 4)
  {
    printf("Entradas invalidas!\n");
  }else if (ordem == 0)
  {
    printf("A matriz de entrada nao possui determinante!\n");
  }

  return 0;
}

int verificaOrdem(int linhas, int colunas){
  if ((linhas == colunas) && (linhas == 1))
  {
    return 1;
  }else if ((linhas == colunas) && (linhas == 2))
  {
    return 2;
  }else if ((linhas == colunas) && (linhas == 3))
  {
    return 3;
  }else if ((linhas == colunas) && (linhas >= 4 || linhas <= 0))
  {
    return 4;
  }else if (linhas != colunas)
  {
    return 0;
  }
  return 0;
}

void det_ordem1(int linhas){
  int elemento;
  scanf("%i", &elemento);
  printf("O determinante da matriz de entrada equivale a %i e tem ordem %i\n", elemento, linhas);
}

void det_ordem2(int linhas){
  int **matriz;
  matriz = (int **)malloc(linhas*sizeof(int));
  for (int i = 0; i < linhas; i++)
  {
    matriz[i] = (int *)malloc(linhas*sizeof(int));
  }

  int determinante;

  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      scanf("%i", &matriz[i][j]);
    }
  }
  determinante = (matriz[0][0] * matriz[1][1]) - (matriz[0][1] * matriz[1][0]);
  printf("O determinante da matriz de entrada equivale a %i e tem ordem %i\n", determinante, linhas);
  for (int i = 0; i < linhas; i++)
    {
      free(matriz[i]);
    }
    free(matriz);
}

void det_ordem3(int linhas){
  int **matriz;
  int **novaMatriz;
  int principal[3], secundaria[3], determinante, k;
  matriz = (int **)malloc(linhas*sizeof(int*));
  //Esses dois laços seguintes alocam dinâmicamente os elementos da matriz
  for (int i = 0; i < linhas; i++)
  {
    matriz[i] = (int *)malloc(linhas*sizeof(int));
  }
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      scanf("%i", &matriz[i][j]);
    }
  }

  //Esses laços atribuem os elementos da matriz a uma nova matriz, para podermos fazer a regra de cramer
  novaMatriz = (int **)malloc((linhas)*sizeof(int*));
  for (int i = 0; i < 3; i++)
  {
    novaMatriz[i] = (int *)malloc(5*sizeof(int));
  }
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      novaMatriz[i][j] = matriz[i][j];
    }
  }
  for (int i = 0; i < 3; i++)
  {
    for (int j = 3; j < 5; j++)
    {
      novaMatriz[i][j] = matriz[i][j-3];
    }
  }

  //O vetor principal recebe a multiplicação dos membros da diagonal principal
  principal[0] = novaMatriz[0][0];
  principal[1] = novaMatriz[0][1];
  principal[2] = novaMatriz[0][2];

  //Laço para multiplicar os membros da diagonal principal entre si
  for (int i = 0; i < 3; i++)
  {
    k = 1;
    for (int j = i+1; k < 3; j++)
    {
      principal[i] = principal[i] * novaMatriz[k][j];
      k++;
    }
  }


  int l = 0; //variável l será necessária para decrementar o indice j do laço interno
  secundaria[0] = novaMatriz[0][4];
  secundaria[1] = novaMatriz[0][3];
  secundaria[2] = novaMatriz[0][2];

  //Laço que faz a multiplicação dos membros da variável
  for (int i = 0; i < 3; i++)
  {
    k = 1;
    for (int j = 3 - l; k < 3; j--)
    {
      secundaria[i] = secundaria[i] * novaMatriz[k][j];
      k++;
    }
    l++;
  }
  
  determinante = (principal[0]+principal[1]+principal[2]) - (secundaria[0]+secundaria[1]+secundaria[2]);
  printf("O determinante da matriz de entrada equivale a %i e tem ordem %i\n", determinante, linhas);
  
    for (int i = 0; i < 3; i++)
    {
      free(matriz[i]);
    }
    free(matriz);
    
    
    for (int i = 0; i < 3; i++)
    {
      free(novaMatriz[i]);
    }
    free(novaMatriz);

}