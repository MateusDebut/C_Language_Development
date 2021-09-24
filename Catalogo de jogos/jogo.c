#include "jogo.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

struct jogo
{
    char *nome;
    char *empresaProdutora;
    char *anoLancamento;
};

Jogo *criarJogo(char *nome, char *empresaProdutora, char *anoLancamento){
    Jogo *novoJogo = (Jogo *) malloc(sizeof(Jogo));
    novoJogo->nome = nome;
    novoJogo->empresaProdutora = empresaProdutora;
    novoJogo->anoLancamento = anoLancamento;
    return novoJogo;
}

void imprimirJogo(Jogo *jogo){
    printf("%s\n",jogo->nome);
}

void desalocarJogo(Jogo *jogo){
    if(jogo != NULL){
        if(jogo->nome != NULL) free(jogo->nome);
        if(jogo->empresaProdutora != NULL) free(jogo->empresaProdutora);
        if(jogo->anoLancamento != NULL) free(jogo->anoLancamento);
        free(jogo);
        jogo = NULL;
    }
}

char *obterAnoLancamento(Jogo *jogo){
    return jogo->anoLancamento;
}

char *obterProdutora(Jogo *jogo){
    return jogo->empresaProdutora;
}

char *obterNome(Jogo *jogo){
    return jogo->nome;
}

void inserirNomeJogo(Jogo *jogo, char *nome){
    jogo->nome = nome;
}

void inserirProdutoraJogo(Jogo *jogo, char *produtora){
    jogo->empresaProdutora = produtora;
}

void inserirAnoLancamentoJogo(Jogo *jogo, char *ano){
    jogo->anoLancamento = ano;
}

