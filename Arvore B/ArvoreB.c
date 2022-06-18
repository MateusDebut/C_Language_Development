//
// Created by mateus on 06/06/22.
//

#define PAGESIZE 4096
#define TREEHEADER PAGESIZE
#define MAXKEYS 204
#define AUX_FIELDS_SIZE_ON_PAGE (2+1) //number of keys and ”isleaf” bool

#define FREE_SPACE_ON_PAGE (PAGESIZE - ((MAXKEYS * 4) + (MAXKEYS * 8) + ((MAXKEYS + 1) * 8) + 3))

#include <stdio.h>
#include <stdlib.h>
#include "ArvoreB.h"

struct indice{
    int chavePrimaria;
    long RRN;
};

struct pagina{
    Indice *indices;
    long RRNDosFilhos[MAXKEYS+1];
    short numeroDechaves;
    char ehFolha;
};

typedef struct chavePromovida{
    int chave;
    long RRN;
    long filhos[2];
}ChavePromovida;

// Funções de exemplo

Pagina *criaPagina(){
    Pagina *pagina = (Pagina *) malloc(sizeof(Pagina));
    pagina->indices = (Indice *) malloc(sizeof(Indice) * MAXKEYS);
    for(int i = 0; i < MAXKEYS; i++){
        pagina->indices[i].RRN = -1;
        pagina->indices[i].chavePrimaria = -1;
    }

    pagina->numeroDechaves = 0;
    pagina->ehFolha = 1;
    for(int i = 0; i < MAXKEYS+1; i++){
        pagina->RRNDosFilhos[i] = -1;
    }
    return pagina;
}

Pagina *lePaginaDoArquivo(FILE *filepointer, long RRN){
    fseek(filepointer, 0, SEEK_SET);
    Pagina *pagina = criaPagina();
    fread(pagina->numeroDechaves, sizeof(short), 1, filepointer);
    fread(pagina->ehFolha, sizeof(char), 1, filepointer);
    for (int i = 0; i < MAXKEYS; i++) {
        fread(pagina->indices[i].chavePrimaria, sizeof(int), 1, filepointer);
        fread(pagina->indices[i].RRN, sizeof(long), 1, filepointer);
    }
    for (int i = 0; i <= MAXKEYS; i++) {
        fread(pagina->RRNDosFilhos[i], sizeof(long), 1, filepointer);
    }
    fread(NULL, 1, FREE_SPACE_ON_PAGE, filepointer);
    return pagina;
}

void escrevePaginaEmArquivo(long RRN, Pagina *pagina, FILE *filepointer){
    //Verifica se está tudo okay com os dados
    //Encontra local para escrita baseado no RRN
    //Escrever os dados
    // Atualiza valor do espaço livre na página
    // Dica: Criar uma função que só lida com a escrita dos dados e chamar aqui

    fseek(filepointer, RRN, SEEK_SET);
    fwrite(pagina->numeroDechaves, sizeof(short), 1, filepointer);
    fwrite(pagina->ehFolha, sizeof(char), 1, filepointer);
    for (int i = 0; i < MAXKEYS; i++) {
        fwrite(pagina->indices[i].chavePrimaria, sizeof(int), 1, filepointer);
        fwrite(pagina->indices[i].RRN, sizeof(long), 1, filepointer);
    }
    for (int i = 0; i <= MAXKEYS; i++) {
        fwrite(pagina->RRNDosFilhos[i], sizeof(long), 1, filepointer);
    }
    fwrite(NULL, 1, FREE_SPACE_ON_PAGE, filepointer);
}

long recuperaCabecalhoDaArvore(FILE *filepointer){
    long rrnDaRaiz;
    fseek(filepointer, 0, SEEK_SET);
    fread(&rrnDaRaiz, sizeof(long), 1, filepointer);
    return rrnDaRaiz;
}

void escreveCabecalhoDaArvore(FILE *filepointer, long RRNdaRaiz){
    //Calcula o espaço livre e escreve no cabeçalho da árvore, junto com o nó raiz
    fseek(filepointer, 0, SEEK_SET);
    fwrite(&RRNdaRaiz, sizeof(long), 1, filepointer);
    fwrite(NULL, 1, PAGESIZE - 8, filepointer);
}

Pagina *criaArvore(FILE *filepointer){
    //Aloca espaço para a pagina raiz
    //inicializa os valores
    //Escreve a raiz no cabeçalho

    Pagina *pagina = (Pagina *) malloc(sizeof(Pagina));
    pagina->indices = (Indice *) malloc(sizeof(Indice) * MAXKEYS);
    for(int i = 0; i < MAXKEYS; i++){
        pagina->indices[i].RRN = -1;
        pagina->indices[i].chavePrimaria = -1;
    }

    pagina->numeroDechaves = 0;
    pagina->ehFolha = 1;
    for(int i = 0; i < MAXKEYS+1; i++){
        pagina->RRNDosFilhos[i] = -1;
    }
    escreveCabecalhoDaArvore(filepointer, PAGESIZE);
}

Pagina *recuperaRaiz(FILE *arquivo){
    //Verifica se a arvore já existe ou se precisa criar uma nova
    //Se a arvore não existir, cria ela
    //Se existir só pega o RRN da raiz
    //Pode ser adaptada para inserção e busca sem precisar de duas funções

    fseek(arquivo, 0, SEEK_SET);
    long RRN_Raiz;
    fread(&RRN_Raiz, sizeof(long), 1,  arquivo);
    Pagina *pagina = lePaginaDoArquivo(arquivo, RRN_Raiz);
    return pagina;
}

ChavePromovida *insereNoNode(Pagina *pagina, ChavePromovida *novaChave, FILE *filepointer){
    //procura local para inserir nova chave na página
    //Se não couber, Splita ele
    //Escreve dados na página
    long RRN = buscaNaArvore(pagina, novaChave, filepointer);

}

Pagina *procuraPosicaoNaPaginaEInsere(Pagina *pagina, ChavePromovida *novaChave){
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
    escrevePaginaEmArquivo();
    escreveCabecalhoDaArvore();


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

/*ChavePromovida *inserirNaArvore(PrimaryIndex *novoIndice, Pagina *raiz, FILE *filepointer){
    //Função mais abstrata de inserção
    //Prepara os dados da nova chave
    //Tenta inserir recursivamente
    //Se tiver chave promovida no final da recursão, significa que existe nova raiz
    //Chama as funções para criar nova raiz e atualizar o cabeçalho
}*/

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

    Indice indiceRetornado = buscaBinaria(pagina->indices, chave, 0, MAXKEYS-1);
    if(indiceRetornado.chavePrimaria == chave){
        return indiceRetornado.RRN;
    }

    if(pagina->ehFolha){
        return -1;
    }

    long RRNDaProximaPagina = localizaRRNProximaPagina(pagina, chave);
    pagina = lePaginaDoArquivo(filepointer, RRNDaProximaPagina);
    return buscaNaArvore(pagina, chave, filepointer);

}

Indice buscaBinaria(Indice *indices, int chaveBuscada, int inicio, int fim){
    int meioDoVetor = (fim + inicio) / 2;
    if(inicio > fim) return indices[inicio];

    if(indices[meioDoVetor].chavePrimaria == chaveBuscada){
        return indices[meioDoVetor];
    }

    if(chaveBuscada < indices[meioDoVetor].chavePrimaria){
        return buscaBinaria(indices, chaveBuscada, inicio, meioDoVetor-1);
    }else if(chaveBuscada > indices[meioDoVetor].chavePrimaria){
        return buscaBinaria(indices, chaveBuscada, meioDoVetor+1, fim);
    }
}

long localizaRRNProximaPagina(Pagina *pagina, int chave){
    long RRNDaProximaPagina;
    for (int i = 0; i < MAXKEYS-1; i++) {
        if(pagina->indices[i].chavePrimaria > chave){
            RRNDaProximaPagina = pagina->RRNDosFilhos[i];
            break;
        }else if(pagina->indices[i].chavePrimaria < chave && i >= MAXKEYS-1){
            RRNDaProximaPagina = pagina->RRNDosFilhos[i+1];
            break;
        }
    }
}