#ifndef JOGO_H
#define JOGO_H

typedef struct jogo Jogo;

Jogo *criarJogo(char *nome, char *empresaProdutora, char *anoLancamento);
void imprimirJogo(Jogo *jogo);
char *obterAnoLancamento(Jogo *jogo);
char *obterProdutora(Jogo *jogo);
char *obterNome(Jogo *jogo);
void desalocarJogo(Jogo *jogo);
void inserirNomeJogo(Jogo *jogo, char *nome);
void inserirProdutoraJogo(Jogo *jogo, char *produtora);
void inserirAnoLancamentoJogo(Jogo *jogo, char *ano);


#endif