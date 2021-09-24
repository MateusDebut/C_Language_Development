#include <stdio.h>
#include "ponto.h"
#include "caminho.h"

int main(int argc, char const *argv[])
{
    int quantidadePontos;
    scanf("%d", &quantidadePontos);
    Caminho *caminho = criaCaminhoAPartirDasCoordenadas(quantidadePontos);
    printf("%.2lf\n", calcularDistanciaCartesiana(caminho));
    desalocarCaminho(caminho);
    return 0;
}