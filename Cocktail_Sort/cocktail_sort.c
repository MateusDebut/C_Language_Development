#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verifica_ordem_alfabetica(char *string1, char *string2);
char **cocktail_sort(char **strings, int nStings);
char *readline(FILE *stream);

int main(int argc, char const *argv[])
{
	char **strings = (char**) malloc(10 * sizeof(char*));
	for (int i = 0; i < 10; i++)
	{
		strings[i] = (char*) malloc(256 * sizeof(char));
	}

	int numero;
	scanf("%d", &numero);

	for (int i = 0; i < numero; i++)
	{
		strings[i] = readline(stdin);
	}
	cocktail_sort(strings, numero);

	for (int i = 0; i < numero; i++)
	{
		printf("%s\n", strings[i]);
	}


	return 0;
}

//Retorna 1 se string 1 vem primeiro e 2 se string 2 vem primeiro. Retorna 0 se são a mesma palavra
int verifica_ordem_alfabetica(char *string1, char *string2){
	int tamanho;
	int testaDiferenca;
	if (strlen(string1) > strlen(string2)){
		tamanho = strlen(string1);
		testaDiferenca = 2;
	}
	else if(strlen(string1) < strlen(string2)){
		tamanho = strlen(string2);
		testaDiferenca = 1;
	}
	else{
		tamanho = strlen(string2);
		testaDiferenca = 0;
	}

	for (int i = 0; i < tamanho; i++)
	{
		if (string1[i] < string2[i])
			return 1;
		else if (string1[i] > string2[i])
			return 2;
	}

	if (testaDiferenca == 1)
		return 1;
	else if(testaDiferenca == 2)
		return 2;
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
	char *string = (char*) malloc(256 * sizeof(char));
	do
	{
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