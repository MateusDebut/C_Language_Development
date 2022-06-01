#include "lista.h"

struct node{
	Node *anterior;
	Node *proximo;
	Item *item;
};

struct lista
{
	Node *primeiroNo;
	int numeroDeItens;	
};

Lista *criarLista(){
	Lista *lista = (Lista *) malloc(sizeof(Lista));
	if(lista == NULL){
		printf("Erro na criação da lista!\n");
		return NULL;
	}
	lista->numeroDeItens = 0;
	return lista;
}

void incluirItemNaLista(Item *item, Lista *lista){
	if(ehListaNula(lista) || ehItemNulo(item)){
		return;
	}

	if(lista->numeroDeItens == 0){
		lista->primeiroNo = (Node *) malloc(sizeof(Node));
		lista->primeiroNo->item = item;
		lista->primeiroNo->anterior = lista->primeiroNo;
		lista->primeiroNo->proximo = lista->primeiroNo;
		lista->numeroDeItens++;
		return;
	}

	Node *noTemporario = lista->primeiroNo;

	while(noTemporario->proximo != lista->primeiroNo){
		noTemporario = noTemporario->proximo;
	}

	noTemporario->proximo = (Node *) malloc(sizeof(Node));
	noTemporario->proximo->anterior = noTemporario;
	noTemporario->proximo->proximo = lista->primeiroNo;
	noTemporario->proximo->item = item;
	lista->numeroDeItens++;
}

void removerItemDalista(Item *item, Lista *lista){
	if(ehListaNula(lista) || ehItemNulo(item)){
		return;
	}

	if(lista->numeroDeItens == 0){
		printf("A lista está vazia!\n");
		return;
	}


	if(lista->numeroDeItens == 1){
		lista->primeiroNo->anterior = NULL;
		lista->primeiroNo->proximo = NULL;
		destruirItem(item);
		free(lista->primeiroNo);
		lista->primeiroNo = NULL;
		lista->numeroDeItens = 0;
		return;
	}

	Node *noTemporario = lista->primeiroNo;
	int index = 0;
	while(index < lista->numeroDeItens){
		if(!saoItensIguais(item, noTemporario->item) && index == lista->numeroDeItens){
			printf("O item não está presente na lista\n");
			return;
		}
		if(saoItensIguais(item, noTemporario->item)){
			break;
		}
		noTemporario = noTemporario->proximo;
		index++;
	}

	noTemporario->anterior->proximo = noTemporario->proximo;
	noTemporario->proximo->anterior = noTemporario->anterior;
	destruirItem(noTemporario->item);
	free(noTemporario);
	noTemporario = NULL;
	lista->numeroDeItens--;
}

int getNumeroItens(Lista *lista){
	return lista->numeroDeItens;
}

void imprimirLista(Lista *lista){
	Node *noTemporario = lista->primeiroNo;
	int index = 0;
	while(index < lista->numeroDeItens){
		printItem(noTemporario->item);
		noTemporario = noTemporario->proximo;
		index++;
	}
}

static int ehListaNula(Lista *lista){
	if(lista == NULL){
		printf("Erro! Lista não pode ser nula\n");
		return 1;
	}
	return 0;
}

static int ehItemNulo(Item *item){
	if(item == NULL){
		printf("Erro! item não pode ser nulo\n");
		return 1;
	}
	return 0;
}