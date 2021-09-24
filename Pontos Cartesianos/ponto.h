#ifndef PONTO_H
#define PONTO_H

typedef struct ponto Ponto;

Ponto *criarPonto(double x, double y);
void imprimirPonto(Ponto *ponto);
void destruirPonto(Ponto *ponto);
double pegarCoordenadaX(Ponto *ponto);
double pegarCoordenadaY(Ponto *ponto);

#endif 