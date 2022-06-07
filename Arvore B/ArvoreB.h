//
// Created by mateus on 06/06/22.
//

#ifndef BTREE_ARVOREB_H
#define BTREE_ARVOREB_H
typedef struct pagina Pagina;

typedef struct Registro Registro;

Pagina *recuperaOuCriaRaiz(FILE *arquivo);
Pagina *recuperaRaiz(FILE *arquivo);
void insereElemento(Registro *registro, Pagina *pagina, FILE *arquivo);

#endif //BTREE_ARVOREB_H
