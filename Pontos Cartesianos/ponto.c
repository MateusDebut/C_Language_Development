#include <stdlib.h>
#include <stdio.h>
#include "ponto.h"

struct ponto
{
    double x;
    double y;
};

Ponto *criarPonto(double x, double y){
    Ponto* ponto = (Ponto *) malloc(sizeof(Ponto));
    if (ponto != NULL){
        ponto->x = x;
        ponto->y = y;
        return ponto;
    }
        
    printf("Erro de alocação. Não foi possível criar o elemento ponto");
    return NULL;
}

void imprimirPonto(Ponto *ponto){
    printf("x: %.2lf y: %.2lf\n", ponto->x, ponto->y);
}

double pegarCoordenadaX(Ponto *ponto){
    return ponto->x;
}

double pegarCoordenadaY(Ponto *ponto){
    return ponto->y;
}

void destruirPonto(Ponto *ponto){
    free(ponto);
}
