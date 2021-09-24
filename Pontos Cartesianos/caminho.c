#include <stdlib.h>
#include <stdio.h>
#include "caminho.h"
#include "ponto.h"
#include <math.h>

struct caminho{
    int quantidadePontos;
    Ponto **pontos;
    double distancia;
};

Caminho *criarCaminhoVazio(){
    Caminho* caminho = (Caminho *) malloc(sizeof(Caminho));
    if(caminho != NULL){
        caminho->quantidadePontos = 0;

        return caminho;
    }
       
    printf("Erro de alocação! Caminho não criado...");
    return NULL;
}

Caminho *criaCaminhoAPartirDasCoordenadas(int quantidadePontos){
    Caminho *caminho = (Caminho *) malloc(sizeof(Caminho));

    if(caminho != NULL){
        caminho->quantidadePontos = quantidadePontos;
        caminho->pontos = (Ponto **) malloc(quantidadePontos * sizeof(Ponto*));

        for (size_t i = 0; i < quantidadePontos; i++)
        {
            double x;
            double y;
            scanf("%lf %lf", &x, &y);
            caminho->pontos[i] = criarPonto(x, y);
        }
        return caminho;
    }

    return NULL;
}

void imprimeCaminho(Caminho *caminho){
    for (int i = 0; i < caminho->quantidadePontos; i++)
    {
        imprimirPonto(caminho->pontos[i]);
    }
}

double calcularDistanciaCartesiana(Caminho *caminho){
    double distanciaEntrePontos;
    double somatorioDistancias = 0.0;
    for (int i = 0; i < caminho->quantidadePontos - 1; i++)
    {
        double coordenadaXPontoInicial = pegarCoordenadaX(caminho->pontos[i]);
        double coordenadaXPontoFinal = pegarCoordenadaX(caminho->pontos[i+1]);
        
        double coordenadaYPontoInicial = pegarCoordenadaY(caminho->pontos[i]);
        double coordenadaYPontoFinal = pegarCoordenadaY(caminho->pontos[i+1]);

        //calculo da distância euclidiana entre dois pontos
        distanciaEntrePontos = sqrt(pow(coordenadaXPontoFinal - coordenadaXPontoInicial, 2) +
                                    pow(coordenadaYPontoFinal - coordenadaYPontoInicial, 2));

        somatorioDistancias = somatorioDistancias + distanciaEntrePontos;
    }
    return somatorioDistancias;
}

void desalocarCaminho(Caminho *caminho){
    if(caminho == NULL) return;
    for (int i = 0; i < caminho->quantidadePontos; i++)
    {
        destruirPonto(caminho->pontos[i]);
    }
    free(caminho->pontos);
    free(caminho);
}
