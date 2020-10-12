#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verifica_ordem_alfabetica(char *string1, char *string2);
char **cocktail_sort(char **strings, int nStings);
char *readline(FILE *stream);
int buscarNomes(char **listaNomes, char *nomeBuscado, int numeroNomes);
char *nomeSemLocalidade(const char *nome);

int main(int argc, char const *argv[])
{
	int numeroNomes;
	scanf(" %d ", &numeroNomes);

	char **nomes = (char**) malloc(numeroNomes * sizeof(char*));
	for (int i = 0; i < numeroNomes; i++)
	{
		nomes[i] = (char*) malloc(256 * sizeof(char));
		nomes[i] = readline(stdin);
	}

	cocktail_sort(nomes, numeroNomes);

	for (int i = 0; i < numeroNomes; i++)
	{
		printf("%s\n", nomeSemLocalidade(nomes[i]));
	}

	int numeroBuscas, resultadoBusca;
	scanf(" %d ", &numeroBuscas);
	char **nomesBusca = (char **) malloc(numeroBuscas * sizeof(char*));
	for (int i = 0; i < numeroBuscas; i++)
	{
		nomesBusca[i] = (char *) malloc(256 * sizeof(char));
		nomesBusca[i] = readline(stdin);
		resultadoBusca = buscarNomes(nomes, nomesBusca[i], numeroNomes);
		printf("%d\n", resultadoBusca);
	}

	for (int i = 0; i < numeroNomes; i++)
	{
		free(nomes[i]);
	}
	free(nomes);
	for (int i = 0; i < numeroBuscas; i++)
	{
		free(nomesBusca[i]);
	}
	free(nomesBusca);

	return 0;
}

//Retorna 1 se string 1 vem primeiro e 2 se string 2 vem primeiro. Retorna 0 se são a mesma palavra
int verifica_ordem_alfabetica(char *string1, char *string2){
	char *novaString1 = (char*)malloc(512 * sizeof(char));
	char *novaString2 = (char*)malloc(512 * sizeof(char));

	strcpy(novaString1, string1);
	strcpy(novaString2, string2);

	for (int i = 0; i < strlen(novaString1); i++)
	{
		if (novaString1[i] >= 'a' && novaString1[i] <= 'z')
		{
			novaString1[i] = novaString1[i] - 32;
		}
	}

	for (int i = 0; i < strlen(novaString2); i++)
	{
		if (novaString2[i] >= 'a' && novaString2[i] <= 'z')
		{
			novaString2[i] = novaString2[i] - 32;
		}
	}

	int tamanho;
	int testaDiferenca;
	if (strlen(novaString1) > strlen(novaString2)){
		tamanho = strlen(novaString1);
		testaDiferenca = 2;
	}
	else if(strlen(novaString1) < strlen(novaString2)){
		tamanho = strlen(novaString2);
		testaDiferenca = 1;
	}
	else{
		tamanho = strlen(novaString2);
		testaDiferenca = 0;
	}

	for (int i = 0; i < tamanho; i++)
	{
		if (novaString1[i] < novaString2[i]){
			free(novaString1);
			free(novaString2);
			return 1;
		}
		else if (novaString1[i] > novaString2[i]){
			free(novaString1);
			free(novaString2);
			return 2;
		}
	}

	if (testaDiferenca == 1){
		free(novaString1);
		free(novaString2);
		return 1;
	}
	else if(testaDiferenca == 2){
		free(novaString1);
		free(novaString2);
		return 2;
	}
	free(novaString1);
	free(novaString2);
	return 0;
}

char **cocktail_sort(char **strings, int nStings){
	char auxiliar[256];
	int j = 0;
	int k = 0;

	for (int i = 0; i < nStings - 1; i++)
	{
		for (j = i; j < nStings - 1 - i; j++)
		{
			if (verifica_ordem_alfabetica(strings[j+1], strings[j]) == 1)
			{
				strcpy(auxiliar, strings[j+1]);
				strcpy(strings[j+1], strings[j]);
				strcpy(strings[j], auxiliar);
			}
		}

		for (k = j; k > 0 + i; k--)
		{
			if (verifica_ordem_alfabetica(strings[k], strings[k-1]) == 1)
			{
				strcpy(auxiliar, strings[k]);
				strcpy(strings[k], strings[k-1]);
				strcpy(strings[k-1], auxiliar);
			}
		}
	}
	return strings;
}

char *readline(FILE *stream){
	int i = 0;
	char aux;
	char *string = NULL;
	do
	{
		if (i%256 == 0)
		{
			string = (char*) realloc(string, (i+1)*256*sizeof(char));
		}
		aux = getc(stream);
		if(aux == '\n' && i == 0)
			i--;
		else if(aux != '\r')
			string[i] = aux;
		else
			string[i] = '\n';
		i++;
	} while (string[i-1] != '\n' && !feof(stream));
	string[i-1] = '\0';
	return string;
}

int buscarNomes(char **listaNomes, char *nomeBuscado, int numeroNomes){
	for (int i = 0; i < numeroNomes; i++)
	{
		if ((strstr(listaNomes[i], nomeBuscado) != NULL) && (strstr(listaNomes[i], "Sao Carlos")))
			return 1;
	}
	return 0;
}

char *nomeSemLocalidade(const char *nome){
	char *novoNome = (char *) malloc(256 *sizeof(char));
	for (int i = 0; i < strlen(nome); i++)
	{
		if (nome[i] != '.')
		{
			novoNome[i] = nome[i];
		}
		else{
			novoNome[i] = '.';
			novoNome[i+1] = '\0';
			break;
		}
	}
	return novoNome;
}