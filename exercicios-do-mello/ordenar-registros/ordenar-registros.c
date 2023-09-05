#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define word_size 10

int contador_numeros = 0;
int contador_nome = 0;

typedef struct{
    char *nome;
    int numero;
}data;


/*CABEÇALHO DAS FUNÇÕES*/

//Lerá todas as entradas do programa
char *read_line(FILE *stream);

//Copia os caracteres da string p2 na string p1, realocando o tamanho caso seja necessário
char *copia(char *p1, char *p2);

//Verifica qual a ordem alfabética entre as strings p1 e p2, retornando 1 caso p1 venha primeiro,
//2 caso p2 venha primeiro e 0 caso sejam identicas
int testa_ordem(char *p1, char *p2);

//localiza qualquer incidência de caracteres númericos numa string e os armazena numa nova string
data *localiza_numero(char *string, data *dados);

//recebe uma string apenas com caracteres numéricos e os converte para inteiro
int char_to_int(char *string);

//localiza e armazena apenas a parte literal de uma string (sem caracteres numéricos) e armazena
//no elemanto nome da struct dados
data *parte_literal(char *string, data *dados);

//função que fará a ordenação de todos os elementos da struct dados por ordem alfabética
data *ordem_alfabetica(int indice, data *dados);

//função que fará a ordenação de todos os elemntos da struct dados por ordem numérica
data *ordem_numerica(int indice, data *dados);
/*FIM FUNÇÕES*/




int main(int argc, char *argv[]){
    int opcao_ordenacao = 0, indice = 0;
    scanf("%i ", &opcao_ordenacao);

    //Este ponteiro duplo será responsável por armazenar as entradas de dados. Elas serão
    //inicialmente armazenadas todas como strings. Depois serão separadas em parte numérica e parte literal
    char **texto = NULL;
    do{
        texto = (char**)realloc(texto, (indice + 1)* sizeof(char*));
        texto[indice] = read_line(stdin);
        indice++;
    }while(!feof(stdin));

    //alocação de indice vezes a  struct dados (como um vetor de structs)
    data *dados = malloc(indice * sizeof(data));
    for (int i = 0; i < indice; i++)
    {
        dados->nome = NULL;
    }


    //Irá encontrar a parte numérica de todas as entradas e salva-la em outro vetor de char para poder
    //converte-la ao tipo int. Também irá armazenar a parte literal no elemento nome da struct dados.
    for (int i = 0; i < indice; i++)
    {
        localiza_numero(texto[i], dados);
        parte_literal(texto[i], dados);
    }

    //Laço que chama a função e printa a saída de acordo com a escolha do usuário
    if (opcao_ordenacao == 1)
    {
        ordem_alfabetica(indice, dados);
        for (int i = 0; i < indice; i++)
        {
            printf("%i\t%s\n", dados[i].numero, dados[i].nome);
        }
    }else if (opcao_ordenacao == 2)
    {
        ordem_numerica(indice, dados);
        for (int i = 0; i < indice; i++)
        {
            printf("%i\t%s\n", dados[i].numero, dados[i].nome);
        }
    }

    for (int i = 0; i < indice; i++)
    {
        free(texto[i]);
    }
    for (int i = 0; i < indice; i++)
    {
        free(dados[i].nome);
    }
    free(texto);
    free(dados); 
  
    return 0;
}




/*CORPO DAS FUNÇÕES*/


//Recebe um ponteiro do tipo File, que por sua vez armazena da entrada padão os dados que seão guardados
char *read_line(FILE *stream){
    char *string = NULL;
    //indice e quociente
    int i = 0, q = 0;
    //variável que armazena temporáriamente o caractere e, caso ele seja diferente de '\r', o salva na string
    char aux;
    do{
        if (i % word_size == 0)
        {
            q = i / word_size + 1;
            string = (char*)realloc(string, word_size * q);
        }
        aux = fgetc(stream);
        if(aux != '\r'){
            string[i] = aux;
        }
    }while(string[i++] != '\n' && !feof(stream));
    string[i-1] = '\0';
    string = (char*)realloc(string, strlen(string));
    return string;
}


//Recebe uma string e encontra nela qualquer parte numérica,
//usando outra função para converter essa perte de char para int. Armazena a parte numérica
//no elemento número da struct dados.
data *localiza_numero(char *string, data *dados){
    //ponteiro que guardará a parte numérica da string que foi passada como parâmetro à função.
    char *num = NULL;
    int j = 0;
    for (int i = 0; i < strlen(string); i++)
    {
        //Se string[i] for um caractere numérico, ou um sinal de menos, armazena no ponteiro num
        if ((string[i] >= 48 && string[i] <= 57) || (string[i] == 45 && string[i+1] >= 48 && string[i+1] <= 57))
        {
            num = (char*)realloc(num, (j / word_size + 1) * word_size);
            num[j] = string[i];
            j++;
        }
    }

    //coloca o terminador de string no ponteiro num
    for (int i = 0; i < strlen(num) + 1 ; i++)
    {
        if (num[i] > 57 || num[i] < 45)
        {
            num[i] = 0;
        }
    }

   //Converte a string num de char para int e salva o retorno no elemento numero da struct dados
   dados[contador_numeros].numero = char_to_int(num);
   contador_numeros = contador_numeros + 1;
   free(num);
   return dados;
}


//recebe uma string com números e, talvez um sinal de negativo, e faz a conversão para inteiro
int char_to_int(char *string){
    int len = strlen(string);
    int soma = 0, i = 0;
    //Converte o caractere para inteiro se baseando no valor numérico do caractere na tabela ascii.
    //Caso encontre um sinal negativo, multiplica a conversão por -1.
    while(--len >= 0){
        //45 é o valor em ascii do caractere - (menos)
        if (string[len] != 45)
        {   //string[len] - '0', nos retorna o valor numérico daquele byte e não o seu valor em ascii.
            //ao multiplicarmos isso por uma potencia de 10, convertemos para a base decimal
            soma = soma + (string[len] - '0') * ((int) pow(10, i++));
        }else if (string[len] == 45)
        {
            soma = soma * -1;
        }
        
    }
    return soma;
}


//vasculha a string copiando a parte literal dela para o elemeto nome da struct dados.
//Quando encontra a parte numérica, para de copiar e coloca o terminador de string. 
data *parte_literal(char *string, data *dados){
    int i = 0, q = 0;
    //enquanto string[i] != de numerais (valor em ascii)
    while(string[i] < 48 || string[i] > 57){
        if (i % word_size == 0)
        {
            q = i / word_size + 1;
            dados[contador_nome].nome = (char*)realloc(dados[contador_nome].nome, q * word_size);
        }
        //copia o caractere
        dados[contador_nome].nome[i] = string[i];
        i++;
    }
    //coloca o terminador e incrementa o contador de nomes, para que na próxima chamada da função
    //ele armazene a parte literal em outra struct
    dados[contador_nome].nome[i - 1] = 0;
    contador_nome++;
    return dados;
}

//Irá ordenar as structs em ordem alfabética
data *ordem_alfabetica(int indice, data *dados){
    char *aux = NULL;
    int temp = 0;

    //Bubble sorte para ordenar as structs
    for (int i = 0; i < indice; i++)
    {
        for (int j = 0; j < indice - 1; j++)
        {
            //Se o retorno da função testa_ordem for igual a 1, significa que a string1 virá depois que
            //a string2 na ordenação
            if (testa_ordem(dados[j].nome, dados[j+1].nome) == 1)
            {

                aux = copia(aux, dados[j+1].nome);
                temp = dados[j+1].numero;


                dados[j+1].nome = copia(dados[j+1].nome, dados[j].nome);
                dados[j+1].numero = dados[j].numero;

                dados[j].nome = copia(dados[j].nome, aux);
                dados[j].numero = temp;

            }
        }
    }
    free(aux);
    return dados;
}

//Irá ordenar as structs em ordem numérica
data *ordem_numerica(int indice, data *dados){
    char *aux = NULL;
    int temp = 0;

    //Bubble sort
    for (int i = 0; i < indice; i++)
    {
        for (int j = 0; j < indice - 1; j++)
        {
            if (dados[j].numero > dados[j+1].numero)
            {
                aux = copia(aux, dados[j+1].nome);
                temp = dados[j+1].numero;

                dados[j+1].nome = copia(dados[j+1].nome, dados[j].nome);
                dados[j+1].numero = dados[j].numero;

                dados[j].nome = copia(dados[j].nome, aux);
                dados[j].numero = temp;
            }
        }
    }
    free(aux);
    return dados;
}


//Copia os caracteres de p2 em p1, ajustando o tamanho caso necessário e colocando o terminador de string
char *copia(char *p1, char *p2){
    int i = 0;
    //reajusta o tamanho da p1 para que a p2 caiba nela
    if (p2 != p1)
    {
       p1 = (char*)realloc(p1, strlen(p2) * sizeof(char) + 1);
    }
    //copia os caracteres de p2 para p1
    for (i = 0; i < strlen(p2); i++)
    {
        p1[i] = p2[i];
    }
    p1[i] = 0;
    return p1;
}

//Recebe duas strings e testa qual delas viria primeiro segundo a ordem alfabética
int testa_ordem(char *p1, char *p2){
    int menor = 0;
    //A variável menor receberá o tamanho da menor string para usar na contagem do laço
    if (p1 < p2)
    {
        menor = strlen(p1);
    }else{
        menor = strlen(p2);
    }
    //compara até encontrar algum caractere diferente
    for (int i = 0; i < menor; i++)
    {
        if (p1[i] > p2[i])
        {
            return 1;
        }else if (p1[i] < p2[i])
        {
            return 2;
        }
    }
    return 0;
}
