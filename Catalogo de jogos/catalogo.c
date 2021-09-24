#include "catalogo.h"
#include "jogo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct catalogo
{
    Jogo **jogos;
    int numeroDejogos;
};

Catalogo *criarCatalogo(){
    Catalogo *catalogo = (Catalogo *) malloc(sizeof(Catalogo));
    catalogo->numeroDejogos = 0;
    return catalogo;
}

void inserirJogoNoCatalogo(Catalogo *catalogo, Jogo *jogo){
    if(catalogo != NULL){
        if(catalogo->numeroDejogos == 0){
            catalogo->jogos = (Jogo **) malloc(sizeof(Jogo *));
        }
        else{
            catalogo->jogos = (Jogo **) realloc(catalogo->jogos, (catalogo->numeroDejogos + 1) * sizeof(Jogo *));
        }
        catalogo->jogos[catalogo->numeroDejogos] = jogo;
        catalogo->numeroDejogos++;
    }
}

void inserirListaDeJogosNoCatalogo(Catalogo *catalogo, Jogo **jogos){
    if(catalogo != NULL){
        if(catalogo->numeroDejogos == 0)
            catalogo->jogos = NULL;

        int numeroDeJogosInicialmente = catalogo->numeroDejogos;
            
        for (int i = 0; jogos[i] != NULL; i++)
        {
            catalogo->jogos = (Jogo **) realloc(catalogo->jogos, (i+1 + numeroDeJogosInicialmente) * sizeof(Jogo *));
            catalogo->jogos[i + numeroDeJogosInicialmente] = jogos[i];   
            catalogo->numeroDejogos++;         
        }
    }
}

void desalocarCatalogo(Catalogo *catalogo){
    if (catalogo != NULL)
    {
        for (int i = 0; i < catalogo->numeroDejogos; i++){
            if(catalogo->jogos[i] != NULL){
                desalocarJogo(catalogo->jogos[i]);
            } 
        }
        if(catalogo->jogos != NULL){
            free(catalogo->jogos);
        }
        free(catalogo);
    }
}

void buscaPorAno(Catalogo *catalogo, char *ano){
    for (int i = 0; i < catalogo->numeroDejogos; i++)
    {
        //se a função strcmp retornar 0 o ano de lançamento passado por parâmetro
        //e o ano de lançamento do jogo na posição i é o mesmo
        if(strcmp(obterAnoLancamento(catalogo->jogos[i]), ano) == 0){
            imprimirJogo(catalogo->jogos[i]);
        }
    }
}

void buscaPorProdutora(Catalogo *catalogo, char *produtora){
    for (int i = 0; i < catalogo->numeroDejogos; i++)
    {
        //se a função strcmp retornar 0 a produtora passada por parâmetro e a produtora do
        //jogo na posição i é a mesma
        if(strcmp(obterProdutora(catalogo->jogos[i]), produtora) == 0){
            imprimirJogo(catalogo->jogos[i]);
        }
    }
}

void imprimirCatalogo(Catalogo *catalogo){
    for (int i = 0; i < catalogo->numeroDejogos; i++)
        imprimirJogo(catalogo->jogos[i]);
}
