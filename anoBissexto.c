/*
    Implemente um programa em C que leia na entrada padr˜ao de texto um n´umero inteiro, representando um ano do calend´ario. Verifique se este ano ´e um ano bissexto. Em caso positivo, escreva na
    tela a palavra “SIM”, em caso negativo escreva a palavra “NAO”.
*/

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int ano = 0;

    printf("Digite um ano: ");
    scanf("%i", &ano);

    if((ano%4 == 0 && ano%100 !=0) || (ano%100 == 0 && ano%400 == 0)){
        printf("SIM\n");
    }else{
        printf("NAO\n");
    }

    return 0;
}