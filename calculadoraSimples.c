/*
Implemente um programa em C que leia na entrada padrão de texto um número real a,
um operador (char) op e outro número real b. 
Em seguida, imprima na tela o resultado da operação matemática aopb. 
O operador op pode ser um dos quatro caracteres que representam as funções básicas +,−,∗ e /,
ou o símbolo %. Neste caso, você deve imprimir a porcentagem que a representa de b (Exemplo:
8%50 = 16%)
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    float a, b;
    char operacao;

    printf("Digite os valores e a operacao no seguinte formato: \n");
    printf("numero operacao numero\n");
    printf("Exemplos: \n");
    printf("4 * 2\n");
    printf("ou \n");
    printf("2 + 3\n\n");
    

    scanf("%f %c %f", &a, &operacao, &b);
    switch(operacao){
        case '+':
        printf("%.2f \n", a+b);
        break;
        case '-':
        printf("%.2f \n", a-b);
        break;
        case '*':
        printf("%.2f \n", a*b);
        break; 
        case '/':
        printf("%.2f \n", a/b);
        break;
        case '%':
        printf("%.2f \n",(a*100)/b);
        break;     
    }
	return 0;
}