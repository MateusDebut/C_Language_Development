#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanho_palavra 255

int livros_ja_alugados = 0;

struct livros{
    char *nome_livro;
    int dias_aluguel;
};

/*CABEÇALHO DAS FUNÇÕES*/

int compara_palavras(char *p1, char *p2);
char *readLine(char *palavra);
int alugar(struct livros *dados, struct livros *alugados, int numero_livros, char *nome_aluguel);
void exibe_alugueis(struct livros *alugados);
struct livros *devolucao(struct livros *alugados, char *nome_devolucao);




/*MAIN*/

int main()
{
    int numero_livros = 0;//variável que armazena o numero total de livros da biblioteca
    scanf("%i ", &numero_livros);
    int operacao;
    char *nome_aluguel = (char*)malloc(tamanho_palavra*sizeof(char));
    char *nome_devolucao = (char*)malloc(tamanho_palavra*sizeof(char));

    //ALOCAÇÃO DINÂMICA DOS VETORES DADOS E ALUGADOS, DO TIPO STRUCT LIVROS
    struct livros *dados = (struct livros*) malloc(numero_livros * sizeof(struct livros));
    struct livros *alugados = (struct livros*) malloc(11 * sizeof(struct livros));
    for (int i = 0; i < numero_livros; i++)
    {
        dados[i].nome_livro = (char*)malloc(tamanho_palavra*sizeof(char));
    }
    for (int i = 0; i < 11; i++)
    {
        alugados[i].nome_livro = (char*)calloc(tamanho_palavra, sizeof(char));
    }

    //RECEBIMENTO DO NOME E DOS DIAS DE ALUGUEL DOS LIVROS
    for (int i = 0; i < numero_livros; i++)
    {
        dados[i].nome_livro = readLine(dados[i].nome_livro);
        scanf("%i ", &dados[i].dias_aluguel);
    }


    //CHAMARÁ A EXECUÇÃO DAS OPERAÇÕES DIGITADAS ENQUANTO ELAS FOREM != 4
    do{
        scanf("%i ", &operacao);
        if (operacao == 1)
        {
            alugar(dados, alugados, numero_livros, nome_aluguel);
        }else if (operacao == 2)
        {
            exibe_alugueis(alugados);
        }else if (operacao == 3)
        {
            alugados = devolucao(alugados, nome_devolucao);
        }else if (operacao == 4)
        {
            printf("Programa finalizado\n");
        }
    }while(operacao != 4);


    //LIBERAÇÃO DA HEAP ALOCADA
    for (int i = 0; i < numero_livros; i++)
    {
        free(dados[i].nome_livro);
    }
    free(dados);

    for (int i = 0; i < 11; i++)
    {
       free(alugados[i].nome_livro);
    }
    free(alugados);
    free(nome_aluguel);
    free(nome_devolucao);
    return 0;
}



/*FUNÇÕES*/

char *readLine(char *palavra){
  int i = 0, q = 0;
  char aux;
  do{
    if (i % tamanho_palavra == 0){
      q = i / tamanho_palavra + 1;
      palavra = (char*) realloc(palavra, q * tamanho_palavra);
    }
    //VARIÁVEL RECEBE O CHAR ANTES DE COLOCALO NO VETOR, SE ELE FOR != DE '\r', ELA INSERE ELE NO VETOR PALAVRA
    aux = getc(stdin);
    if (aux != '\r'){
      palavra[i] = aux;
    }else{
      palavra[i] = '\n';
    }
  }while(palavra[i++] != '\n' && !feof(stdin));
  //AJUSTA O TAMANHO DO VETOR DE ACORDO COM O TAMANHO DA PALAVRA E COLOCA O TERMINADOR DE STRING
  palavra = (char *) realloc(palavra,i);
  palavra[i-1] = '\0';
  return palavra;
}




int alugar(struct livros *dados, struct livros *alugados, int numero_livros, char *nome_aluguel){
    printf("Digite o livro que voce procura:\n");
    nome_aluguel = readLine(nome_aluguel);

    //LAÇO QUE TESTA SE O LIVRO EXISTE NO ACERVO.
    //CASO NÃO EXISTA, EXIBE UMA MENSAGEM E RETORNA 1 PARA A MAIN
    for (int i = 0; i < numero_livros; i++)
    {  
        if (compara_palavras(dados[i].nome_livro, nome_aluguel) == 0)
        {
            i = numero_livros;
        }else if (compara_palavras(dados[i].nome_livro, nome_aluguel) != 0 && (i == numero_livros - 1))
        {
            printf("Livro nao encontrado na biblioteca\n");
            return 1;
        }
    }

    //SE O LIVRO EXISTE, MAS O USUÁRIO JÁ TEM 10 LIVROS ALUGADOS, EXIBE MENSAGEM E RETORNA 1 PARA A MAIN
    for (int i = 0; i < numero_livros; i++)
    {
        if ((livros_ja_alugados >=10))
        {
            printf("Voce ja tem 10 livros alugados\n");
            return 1;
        }
    }

    //SE O LIVRO JÁ ESTÁ ALUGADO, EXIBE MENSAGEM E RETORNA 1 PARA A MAIN
    for (int i = 0; i < 10; i++)
    {   
        if (compara_palavras(alugados[i].nome_livro, nome_aluguel) == 0)
        {
            printf("Livro ja alugado\n");
            return 1;
        }
    }

    //SE NÃO HÁ IMPEDITIVOS, REALIZA O ALUGUEL (COLOCANCO O LIVRO DA STRUCT DADOS NA STRUCT ALUGADOS)
    //E RETORNA 0 PARA A MAIN.
    for (int i = 0; i < numero_livros; i++)
    {
        if (compara_palavras(dados[i].nome_livro, nome_aluguel) == 0)
        {
            strcpy(alugados[livros_ja_alugados].nome_livro, dados[i].nome_livro);
            alugados[livros_ja_alugados].dias_aluguel = dados[i].dias_aluguel;
            printf("%s alugado com sucesso\n", alugados[livros_ja_alugados].nome_livro);
            livros_ja_alugados = livros_ja_alugados + 1;
            return 0;
        }
    }
    return 0;
}




void exibe_alugueis(struct livros *alugados){
    if (livros_ja_alugados == 0)
    {
        printf("Voce nao tem livros alugados\n");
    }else if (livros_ja_alugados != 0)
    {
        printf("Voce tem %i livro(s) alugado(s)\n", livros_ja_alugados);
        for (int i = 0; i < livros_ja_alugados; i++)
        {
            printf("Livro nome: %s\n", alugados[i].nome_livro);
            printf("Devolve-lo daqui %i dias\n", alugados[i].dias_aluguel);
        }
    }
}




struct livros *devolucao(struct livros *alugados, char *nome_devolucao){
    int k;
    printf("Digite o livro que deseja devolver:\n");
    nome_devolucao = readLine(nome_devolucao);

    //TESTA SE O USUÁRIO POSSUI O LIVRO.
    //SE SIM, PROSSEGUE COM A DEVOLUÇÃO. SE NÃO, EXIBE MENSAGEM E RETORNA A STRUCT ALUGADOS
    for (int i = 0; i < 10; i++)
    {
        if (compara_palavras(alugados[i].nome_livro, nome_devolucao) == 0)
        {
            i = 10;
        }else if ((compara_palavras(alugados[i].nome_livro, nome_devolucao) != 0) && (i == 9))
        {
            printf("Voce nao possui esse livro\n");
            return alugados;
        }
    }

    //ESSES LAÇOS BUSCARÃO O LIVRO A SER DEVOLVIDO DENTRO DO VETOR DE LIVROS ALUGADOS
    for (int i = 0; i < livros_ja_alugados; i++)
    {	//AO ENCONTRAR O LIVRO, O K RECEBE O VALOR DE I
        if (compara_palavras(alugados[i].nome_livro, nome_devolucao) == 0)
        {
            k = i;
            //PARA QUE O VALOR DE I NÃO SEJA ALTERADO, USAREMOS O INDICE K DENTRO DESSE LAÇO
            for (int j = 0; j <= (livros_ja_alugados - (i + 1)); j++)
            {
            	//COPIA O LIVRO SEGUINTE PARA A POSIÇÃO ATUAL DO VETOR, ATÉ QUE TODOS TENHAM SIDO
            	//PUXADOS UMA CASA PARA TRÁS, A PARTIR DO LIVRO ENCONTRADO
                strcpy(alugados[k].nome_livro, alugados[k+1].nome_livro);
                alugados[k].dias_aluguel = alugados[k+1].dias_aluguel;
                k++;
            }
            //RETIRA UMA UNIDADE DA VARIÁVEL GLOBAL livros_ja-alugados E RETORNA A STRUCT ALUGADOS ATUALIZADA
            printf("Livro %s foi devolvido com sucesso\n", nome_devolucao);
            i = livros_ja_alugados;
            livros_ja_alugados = livros_ja_alugados - 1;
            return alugados;
        }
    }
    return alugados;
}





int compara_palavras(char *p1, char *p2){
	//SE O TAMANHO DAS PALAVRAS É DIFERENTE, ELE NEM COMPARA
    if (strlen(p1) != strlen(p2))
    {
        return 1;
    //SE O TAMANHO DAS PALAVRAS FOR IGUAL, ELE COMPARA OS CARACTERES
    }else if (strlen(p1) == strlen(p2))
    {
        for (int i = 0; i < strlen(p1); i++)
        {
            if (p1[i] != p2[i])
            {
                return 1;
            }else if (p1[i] != p2[i] && (i == strlen(p1) - 1))
            {
                return 0;
            }
        }
    }
    return 0;
}