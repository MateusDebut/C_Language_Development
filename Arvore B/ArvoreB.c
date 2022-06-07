//
// Created by mateus on 06/06/22.
//

#define PAGESIZE 4096
#define TREEHEADER PAGESIZE
#define MAXKEYS 204
#define AUX_FIELDS_SIZE_ON_PAGE (2+1) //numberofkeysand ”isleaf” bool

#define FREE_SPACE_ON_PAGE (PAGESIZE - ((MAXKEYS * 4) + (MAXKEYS * 8) + ((MAXKEYS + 1) * 8) + 3))

#include <stdio.h>
#include "ArvoreB.h"

struct registro{
    int chave;
    long RRN;
};

struct pagina{
    Registro *registro;
    long filhos[4];
    short numeroDechaves;
    int ehFolha;
};

typedef struct chavePromovida{
    int chave;
    long RRN;
    long filhos[2];
}ChavePromovida;

// Funções de exemplo
Pagina *lePaginaDoArquivo(FILE *filepointer){
    // Aloca Espaço para carregar página
    // Lê dados da página do arquivo
}

void escrevePaginaEmArquivo(long RRN, Pagina *pagina, FILE *filepointer){
    //Verifica se está tudo okay com os dados
    //Encontra local para escrita baseado no RRN
    //Escrever os dados
    // Atualiza valor do espaço livre na página
    // Dica: Criar uma função que só lida com a escrita dos dados e chamar aqui
}

Pagina *recuperaPagina(long RRN, FILE *filepointer){
    //recupera uma página baseado no RRN
    //Procura e carrega seus dados
}

long recuperaCabecalhoDaArvore(FILE *filepointer){
    //carrega o cabeçalho da árvore, que está no início do arquivo
}

void escreveCabecalhoDaArvore(FILE *filepointer, long RRNdaRaiz){
    //Calcula o espaço livre e escreve no cabeçalho da árvore, junto com o nó raiz
}

Pagina *criaArvore(FILE *filepointer){
    //Aloca espaço para a raiz
    //inicializa os valores
    //Escreve a raiz no cabeçalho
}

Pagina *recuperaOuCriaRaiz(FILE *arquivo){
    //Verifica se a arvore já existe ou se precisa criar uma nova
    //Se a arvore não existir, cria ela
    //Se existir só pega o RRN da raiz
    //Pode ser adaptada para inserção e busca sem precisar de duas funções
}

ChavePromovida *insereNoNode(Pagina *pagina, ChavePromovida *novaChave, FILE *filepointer){
    //procura local para inserir nova chave na página
    //Se não couber, Splita ele
    //Escreve dados na página
}

Pagina *procuraPosicaoNaPaginaEInsere(){
    //Encontra a posição para inserir a chave
    //Se não existir espaço, precisa criar uma nova página (Usar uma função para criar)
    //Salvar dados da nova chave na página
}

Pagina *splitECriacaoDeNovoNo(Pagina **pagina){
    //Encontra a posição do meio das chaves
    //Cria espaço para as novas páginas
    //Copia metade das chaves para página nova
    //Limpa elas do nó antigo
    //Atualiza os filhos de ambas as páginas
    //Atualiza o numero de chaves de ambas
}

ChavePromovida *extrairChavePromovida(){
    //Aloca espaço para a chave
    //Tira ela da página
    //Atualiza os dados da página (filhos, numero de chaves e etc)
}

ChavePromovida *split(Pagina *pagina, FILE filepointer, ChavePromovida *novaChave){
    //Divide a página, cria o novo nó (fazer uma função auxiliar, pois é complexo)
    //Extrai a chave promovida e atualiza os filhos da chave
    //Escreve a página nova e a que foi dividida (com suas atualizações) no arquivo
}

Pagina *criaNoComChavePromovida(ChavePromovida *chavePromovida){
    //Se promoção, cria estrutura para nova raiz
    //Aloca espaço para ela
    //Salva dados da chave promovida na nova raiz
    //Atualiza os filhos deste novo nó/página
    //É possível reusar a função que cria página nova e adicionar somente especificidades
}

void setarNoComoRaiz(Pagina *pagina, FILE *filepointer){
    //Escreve página nova e atualiza o cabeçalho para conter ela como raiz
    //Deveria ser chamada junto com criação de novo nó, quando a promoção criar uma nova raiz
}

ChavePromovida *_inserirNaArvore(Pagina *no, ChavePromovida *chave, FILE *filepointer){
    //Se nó a ser inserido a chave é folha, tentar inserir
    //Caso a inserção crie uma promoção, precisa retornar a chave promovida para a recursão
    //Se não for nó folha, procura qual subarvore seguir para inserir numa folha
    //Encontra a posição correta e descer para filho à esquerda se a chave for menor
    //Descer para a direita se a chave for maior
    //Chamar a inserção recursiva para o filho escolhido
    //Se a inserção recursiva retornar uma chave promovida, precisa tentar inserir essa chave promovida no nó atual
    //Retornar chave promovida ou um valor NULL se não houver promoção
}

ChavePromovida *inserirNaArvore(PrimaryIndex *novoRegistro, Pagina *raiz, FILE *filepointer){
    //Função mais abstrata de inserção
    //Prepara os dados da nova chave
    //Tenta inserir recursivamente
    //Se tiver chave promovida no final da recursão, significa que existe nova raiz
    //Chama as funções para criar nova raiz e atualizar o cabeçalho
}

/**
 * Retona o RRN se a chave existe, se não existir, retorna -1
 * @param  pagina
 * @param  chave
 * @param  filepointer
 * @return      o RRN da chave buscada. Se ela não existir, retorna -1
 * */
long buscaNaArvore(Pagina *pagina, int chave, FILE *filepointer){
    //Procura no nó atual se a chave existe
    //Se não existir, tentar procurar no nó filho adequad, recursivamente
    //Se encontrar a chave, retorna o RRN dela
    //Se não encontrar, (chegar em um nó folha e ela não estiver lá) retorna -1
}