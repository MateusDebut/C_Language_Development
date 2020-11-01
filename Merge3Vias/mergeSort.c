#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define tamanhoPalavra 256

typedef struct l{
	char *nomeLivro;
	float preco;
}livros_t;

void mergeSort(livros_t *livros, int inicio, int fim);
void merge(livros_t *livros, int inicio, int div1, int div2, int fim);
int *readVector(FILE *stream, int *i);
int calcularTamanhoVetor(int *vetor);
void imprimeVetor(livros_t *livros, int inicio, int fim);
char *readline(FILE *stream);
float separaParteNumerica(livros_t livro);

int main(int argc, char const *argv[])
{
	int numeroLivros;
	scanf(" %d ", &numeroLivros);
	//getc(stdin);

	livros_t *livros = (livros_t*) malloc(numeroLivros * sizeof(livros_t));
	for (int i = 0; i < numeroLivros; i++)
	{
		livros[i].nomeLivro = readline(stdin);
		livros[i].preco = separaParteNumerica(livros[i]);

	}
	mergeSort(livros, 0, numeroLivros);
	//imprimeVetor(livros, 0,numeroLivros);
	printf("\n");

	for (int i = 0; i < numeroLivros; i++)
	{
		for (int j = 0; j < strlen(livros[i].nomeLivro); j++)
		{
			if (livros[i].nomeLivro[j] == '!')
			{
				livros[i].nomeLivro[j] = '\0';
			}
		}
		printf("%s\n", livros[i].nomeLivro);
	}
	return 0;
}



//FUNÇÕES
void mergeSort(livros_t *livros, int inicio, int fim){
	imprimeVetor(livros, inicio, fim);
	if (inicio < fim) printf("\n");
	if (fim - inicio < 2) return;
		 
	int div1 = inicio + (int)ceil((fim - inicio)/3.0);
	int div2 = div1 + (int)round((fim-inicio)/3.0);

	mergeSort(livros, inicio, div1);
	mergeSort(livros, div1, div2);
	mergeSort(livros, div2, fim);
	merge(livros, inicio, div1, div2, fim);		
}

void merge(livros_t *livros, int inicio, int div1, int div2, int fim){
	livros_t *aux = (livros_t*)malloc ((fim-inicio) * sizeof(livros_t));
	int i = inicio;
	int j = div1;
	int k = div2;
	int l = 0;
	while((i < div1) && (j < div2) && (k < fim)){
		if (livros[i].preco < livros[j].preco)
		{
			if (livros[i].preco < livros[k].preco)
			{
				aux[l].nomeLivro = (char*)malloc(strlen(livros[i].nomeLivro) * sizeof(char));
				strcpy(aux[l].nomeLivro, livros[i].nomeLivro);
				aux[l++].preco = livros[i++].preco;
			}else{
				aux[l].nomeLivro = (char*)malloc(strlen(livros[k].nomeLivro) * sizeof(char));
				strcpy(aux[l].nomeLivro, livros[k].nomeLivro);
				aux[l++].preco = livros[k++].preco;
			}
		}else{
			if (livros[j].preco < livros[k].preco)
			{
				aux[l].nomeLivro = (char*)malloc(strlen(livros[j].nomeLivro) * sizeof(char));
				strcpy(aux[l].nomeLivro, livros[j].nomeLivro);
				aux[l++].preco = livros[j++].preco;
			}else{
				aux[l].nomeLivro = (char*)malloc(strlen(livros[k].nomeLivro) * sizeof(char));
				strcpy(aux[l].nomeLivro, livros[k].nomeLivro);
				aux[l++].preco = livros[k++].preco;
			}
		}
	}

	while((i < div1) && (j < div2)){
		if (livros[i].preco < livros[j].preco)
		{
			aux[l].nomeLivro = (char*)malloc(strlen(livros[i].nomeLivro) * sizeof(char));
			strcpy(aux[l].nomeLivro, livros[i].nomeLivro);
			aux[l++].preco = livros[i++].preco;
		}else{
			aux[l].nomeLivro = (char*)malloc(strlen(livros[j].nomeLivro) * sizeof(char));
			strcpy(aux[l].nomeLivro, livros[j].nomeLivro);
			aux[l++].preco = livros[j++].preco;
		}
	}

	while((j < div2) && (k < fim)){
		if (livros[j].preco < livros[k].preco)
		{
			aux[l].nomeLivro = (char*)malloc(strlen(livros[j].nomeLivro) * sizeof(char));
			strcpy(aux[l].nomeLivro, livros[j].nomeLivro);
			aux[l++].preco = livros[j++].preco;
		}else{
			aux[l].nomeLivro = (char*)malloc(strlen(livros[k].nomeLivro) * sizeof(char));
			strcpy(aux[l].nomeLivro, livros[k].nomeLivro);
			aux[l++].preco = livros[k++].preco;
		}
	}

	while((i < div1) && (k < fim)){
		if (livros[i].preco < livros[k].preco)
		{
			aux[l].nomeLivro = (char*)malloc(strlen(livros[i].nomeLivro) * sizeof(char));
			strcpy(aux[l].nomeLivro, livros[i].nomeLivro);
			aux[l++].preco = livros[i++].preco;
		}else{
			aux[l].nomeLivro = (char*)malloc(strlen(livros[k].nomeLivro) * sizeof(char));
			strcpy(aux[l].nomeLivro, livros[k].nomeLivro);
			aux[l++].preco = livros[k++].preco;
		}
	}

	while(i < div1){
		aux[l].nomeLivro = (char*)malloc(strlen(livros[i].nomeLivro) * sizeof(char));
		strcpy(aux[l].nomeLivro, livros[i].nomeLivro);
		aux[l++].preco = livros[i++].preco;
	}

	while(j < div2){
		aux[l].nomeLivro = (char*)malloc(strlen(livros[j].nomeLivro) * sizeof(char));
		strcpy(aux[l].nomeLivro, livros[j].nomeLivro);
		aux[l++].preco = livros[j++].preco;
	}

	while(k < fim){
		aux[l].nomeLivro = (char*)malloc(strlen(livros[k].nomeLivro) * sizeof(char));
		strcpy(aux[l].nomeLivro, livros[k].nomeLivro);
		aux[l++].preco = livros[k++].preco;
	}

	for (i = inicio, k = 0; i < fim; i++, k++)
	{
		strcpy(livros[i].nomeLivro, aux[k].nomeLivro);
		livros[i].preco = aux[k].preco;
	}

	//free(aux);
}

void imprimeVetor(livros_t *livros, int inicio, int fim){
	for (int i = inicio; i < fim; i++)
	{
		printf("%.2f ", livros[i].preco);
	}
}

char *readline(FILE *stream){
	int i = 0;
	char *string = NULL;
	char aux;

	do{
		if (i%tamanhoPalavra == 0)
		{
			string = (char*)realloc(string, tamanhoPalavra*sizeof(char));
		}
		aux = getc(stream);
		if (aux != '\r')
		{
			string[i] = aux;
		}
		i++;
	}while(string[i-1] != '\n' && !feof(stream));
	string[i-1] = '\0';
	string = (char*) realloc(string, tamanhoPalavra*sizeof(char));
	return string;
}

float separaParteNumerica(livros_t livro){
	char aux[6];
	int i = 0;
	int k = 0;
	while(livro.nomeLivro[i] != ','){
		i++;
	}
	i++;
	while(livro.nomeLivro[i] != '\0'){
		aux[k] = livro.nomeLivro[i];
		i++;
		k++;
	}
	aux[k] = '\0';
	return atof(aux);
}