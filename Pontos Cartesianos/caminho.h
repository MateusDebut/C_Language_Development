#ifndef CAMINHO_H
#define CAMINHO_H

#include "ponto.h"

typedef struct caminho Caminho;
Caminho *criaCaminhoAPartirDasCoordenadas(int quantidadePontos);
void imprimeCaminho(Caminho *caminho);
double calcularDistanciaCartesiana(Caminho *caminho);
void desalocarCaminho(Caminho *caminho);

#endif