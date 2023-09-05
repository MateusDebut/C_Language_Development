#include<stdio.h>
#include<stdlib.h>

char **alocaTabela(int linha, int coluna);//função para a composição do tabuleiro inicial
void exibeTabela(char **tabuleiro);//Exibe o tabuleiro;
char **jogadaX(char **tabuleiro);//Avalia se a jogada de X é válida e, se positivo, marca a posição jogada
char **jogadaO(char **tabuleiro);//Avalia se a jogada de O é válida e, se positivo, marca a posição jogada
int verificaO(char **tabuleiro);//Verifica se o jogador O ganhou o jogo (preencheu uma sequência)
int verificaX(char **tabuleiro);//Verifica se o jogador X ganhou o jogo (preencheu uma sequência)
int velha(char **tabuleiro);


int main(){
  char **tabela;
  int verifica = 0;
  tabela = alocaTabela(3, 3);
  exibeTabela(tabela);
  printf("Jogo da velha!\n");

  for (int i = 0; verifica == 0 && i < 9; i++)
  {
    if (i % 2 == 0)
    {
    tabela = jogadaX(tabela);
    verifica = verificaX(tabela);
      if (verifica == 0)
      {
        exibeTabela(tabela);
      }
    }else{
    tabela = jogadaO(tabela);
    verifica = verificaO(tabela);
      if (verifica == 0)
      {
        exibeTabela(tabela);
      }
    }
  }

  verifica = velha(tabela);
  if (verifica == 1)
  {
    printf("Deu velha!\n");
  }

  for (int i = 0; i < 3; i++)
  {
    free(tabela[i]);
  }
  free(tabela);
    return 0;
}




// funções:

char **alocaTabela(int linha, int coluna){
  char **tabuleiro = (char**) malloc (linha*sizeof(char));//aloca as linhas da matriz
  int aux = 49;//variável temporária. irá apenas preencher o tabuleiro com numeros de 1 a 9

  for (int i = 0; i < coluna; i++)//aloca as colunas da matriz
  {
    tabuleiro[i] = (char*) malloc (coluna*sizeof(char));
  }

  //laço que preenche as casas do tabuleiro de 1 a 9
  for (int i = 0; i < 3; i++)
  {
      for (int j = 0; j < 3; j++)
      {
          tabuleiro[i][j] = aux;
          aux++;
      }
  }
  return(tabuleiro);
}

void exibeTabela(char **tabuleiro){
  for (int i = 0; i < 3; i++)
  {
      for (int j = 0; j < 3; j++)
      {
          printf("%c   |", tabuleiro[i][j]);//printa o conteúdo da célula, seguido de 3 espaços e 1 pipe
      }
      printf("\n----+----+-----");
      printf("\n");
  }
}

char **jogadaX(char **tabuleiro){
  char num;
  printf("Escolha um número para jogar, jogador X!\n");
  scanf(" %c", &num);

  //Este laço verifica se a jogada é válida ou não
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (tabuleiro[i][j] == num)//jogada válida. Marca a posição e encerra o laço
      {
        tabuleiro[i][j] = 88;
        j = 3;
        i = 3;
      }else if ((i == 2 && j == 2) && (tabuleiro[i][j] != num))//Jogada inválida. Pede um novo número e reinicia o laço
      {
        printf("Jogada inválida! Escolha outra casa.\n");
        scanf(" %c", &num);
        i = 0;
        j = -1;
      }
    }
  }
  return(tabuleiro);
}

char **jogadaO(char **tabuleiro){
  char num;
  printf("Escolha um número para jogar, jogador O!\n");
  scanf(" %c", &num);
 
  //Este laço verifica se a jogada é válida ou não
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (tabuleiro[i][j] == num)//jogada válida. Marca a posição e encerra o laço
      {
        tabuleiro[i][j] = 79;
        j = 3;
        i = 3;
      }else if ((i == 2 && j == 2) && (tabuleiro[i][j] != num))
      {
        printf("Jogada inválida! Escolha outra casa.\n");//Jogada inválida. Pede um novo número e reinicia o laço
        scanf(" %c", &num);
        i = 0;
        j = -1;
      }
    }
  }
  return(tabuleiro);
}

int verificaO(char **tabuleiro){
  int verificacao;//Se o valor retornado for diferente de 0 significa que o jogador preencheu uma sequencia

  //este laço verifica se as alguma linha foi completamente preenchida
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if ((tabuleiro[i][j] == 79) && (tabuleiro[i][j+1] == 79) && (tabuleiro[i][j+2] == 79))
      {
        exibeTabela(tabuleiro);
        printf("Fim do jogo! O jogador O venceu!\n");
        i=3;
        j=3;
        verificacao = 2;
        return verificacao;
      }
    }
  }
  //este laço verifica se as alguma coluna foi completamente preenchida
    int i = 0;
    for (int j = 0; j < 3; j++)
    {
      if ((tabuleiro[i][j] == 79) && (tabuleiro[i+1][j] == 79) && (tabuleiro[i+2][j] == 79))
      {
        exibeTabela(tabuleiro);
        printf("Fim do jogo! O jogador O venceu!\n");
        j=3;
        verificacao = 2;
        return verificacao;
      }
    }
    //estas condicionais testam se as diagonais foram preenchidas
    if ((tabuleiro[0][0] == 79) && (tabuleiro[1][1] == 79) && (tabuleiro[2][2] == 79))
    {
      exibeTabela(tabuleiro);
      printf("Fim do jogo! O jogador O venceu!\n");
      verificacao = 2;
      return verificacao;
    }else if ((tabuleiro[0][2] == 79) && (tabuleiro[1][1] == 79) && (tabuleiro[2][0] == 79))
    {
      exibeTabela(tabuleiro);
      printf("Fim do jogo! O jogador O venceu!\n");
      verificacao = 2;
      return verificacao;
    }


  return 0;
}

int verificaX(char **tabuleiro){
  int verificacao;//Se o valor retornado for diferente de 0 significa que o jogador preencheu uma sequencia

  //este laço verifica se as alguma linha foi completamente preenchida
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if ((tabuleiro[i][j] == 88) && (tabuleiro[i][j+1] == 88) && (tabuleiro[i][j+2] == 88))
      {
        exibeTabela(tabuleiro);
        printf("Fim do jogo! O jogador X venceu!\n");
        i=3;
        j=3;
        verificacao = 2;
        return verificacao;
      }
    }
  }
  //este laço verifica se as alguma coluna foi completamente preenchida
    int i = 0;
    for (int j = 0; j < 3; j++)
    {
      if ((tabuleiro[i][j] == 88) && (tabuleiro[i+1][j] == 88) && (tabuleiro[i+2][j] == 88))
      {
        exibeTabela(tabuleiro);
        printf("Fim do jogo! O jogador X venceu!\n");
        j=3;
        verificacao = 2;
        return verificacao;
      }
    }
    //estas condicionais testam se as diagonais foram preenchidas
    if ((tabuleiro[0][0] == 88) && (tabuleiro[1][1] == 88) && (tabuleiro[2][2] == 88))
    {
      exibeTabela(tabuleiro);
      printf("Fim do jogo! O jogador X venceu!\n");
      verificacao = 2;
      return verificacao;
    }else if ((tabuleiro[0][2] == 88) && (tabuleiro[1][1] == 88) && (tabuleiro[2][0] == 88))
    {
      exibeTabela(tabuleiro);
      printf("Fim do jogo! O jogador X venceu!\n");
      verificacao = 2;
      return verificacao;
    }


  return 0;
}


int velha(char **tabuleiro){
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if ((tabuleiro[i][j] != 79) && (tabuleiro[i][j] != 88))//
      {
        return 0;
      }else if (i == 2 && j == 2)
      {
        return 1;
      }
    }
  }
  return 0;
}


