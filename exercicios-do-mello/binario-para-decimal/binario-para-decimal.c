/*Este programa recebe um número "N" binário contido entre:
 *000000000000000000000000000000 <= N <= 111111111111111111111111111111
 *E o converte para o formato decimal*/

#include <stdio.h> //biblioteca de input e output
#include <stdlib.h> // biblioteca de alocação de memória, controle e conversões
#include <math.h>   //biblioteca para operações matemáticas mais avançadas (potenciação, radiciação, funoes trigonométicas, etc).
#include <string.h> // biblioteca para manipulação de strings
 
int main() {
    char binario[30]; // vetor que usarei para armezenar o número binário ( o número será armazenado como uma cadeia de caracteres)
    int decimal = 0; // variavél que armazenará nosso resultado da conversão

    scanf("%s", binario);

    for (int i = strlen(binario)-1; i >= 0 ; i--)//A função "strlen" calcula o comprimento de uma cadeia de caracteres.
    // variável i inicia com o valor equivalente ao numero de posições do vetor e decrementa até zero. Assim conseguiremos a soma na ordem correta.
    {
        if (binario[i]== '1')// Vamos operar apenas com o valor '1', uma vez que o '0' seria desconsiderado na soma final.
        {
            decimal = decimal + pow(2, strlen(binario)-1-i); //decimal receberá o somatório de todos os valores 1 multilpicados por 2 elevado a posição analisada
        }
    }
    printf("%d\n", decimal);
    
    return 0;
}