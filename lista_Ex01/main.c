#include <stdio.h>
#include <stdlib.h>

typedef struct no lista;

struct no{
	int info;
	lista *prox;
};

int main(int argc, char const *argv[])
{
	int num;
	lista *ini = NULL;
	lista *fim = NULL;
	lista *p = NULL;

	scanf("%d", &num);

	while(num != -1){
		p = (lista *) malloc (sizeof(lista));
		p->info = num;
		p->prox = NULL;
		if(ini == NULL){//Lista Vazia
			ini = p;
			fim = p;
		}else{//Lista possui pelo menos um elemento
			fim->prox = p;
			fim = p;
		}
		scanf("%d", &num);
	}

	p = ini;

	while(p != NULL){
		printf("%d\n", p->info);
		p = p->prox;
	}
	while(ini != NULL){
		p = ini;
		ini = ini->prox;
		free(p);
	}
	return 0;
}