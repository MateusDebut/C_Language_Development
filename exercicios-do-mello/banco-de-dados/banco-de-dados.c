#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Fields
{
	char *fieldName;
	char *fieldType;
	int length;
	int quantidadeCampos;
}Fields;

typedef struct Metadados
{
	char *fileName;
	char *keyName;
	char *keyType;
	Fields *fields;
	int numberOfFields;
}Metadados;

//O nome é apenas uma abreviação de union mesmo
typedef union Uni{
	char *str;
	int valorInteiro;
	float valorFloat;
	double valorDoble;
}Uni;

typedef struct allData
{
	int key;
	Uni *coringa;
}allData;

/****FUNÇÕES PARA RECEBER OS METADADOS E ALOCALOS NA STRUCT META****/
char *readline(FILE *stream, char *string);
void liberaMatriz(char **matriz, int linha);
char **recebeDados(char **dados, char *nomeArquivo, FILE *fp, Metadados *meta);
char *recortaCampo(char *string, char *stringRetorno);
Metadados transpoeTodosOsCampos(Metadados *meta, int numberOfFields, char **dados);
int extraiCaractereNumerico(char *string);
void liberaStruct(Metadados meta);
void imprimeMetadados(Metadados meta);
/****FIM FUNÇÕES METADADOS *****/

/*FUNÇÕES PARA RECEBER E EXECUTAR OS COMANDOS*/
char **recebeComandos(char **comandos, FILE *stream, int *numeroDeComandos);
void imprimeMatriz(char **matriz, int num);
allData *alocaStructData(allData *data, int numeroDeComandos, Metadados meta,
		char **comandos, int *numeroDeInserts);
char **comandosIndex_e_Search(char **comandos, int numeroDeComandos, int numeroDeInserts,
	int *num_index_searchs, char **index_e_searchs);
void liberaStructData(allData *data, int numeroDeInserts, Metadados meta);
allData *carregaStructData(allData *data, int numeroDeInserts, Metadados meta,
		char **comandos, int *offset);
char *extraiString(char *stringOrigem, int length, char *stringDestino);
float extraiFloat_e_Double(char *string);
int comparaOrdem(const void *a, const void *b);
void imprimeData(allData *data, int numeroDeInserts, Metadados meta);
void escreveInsertsNoArquivo(allData *data, int numeroDeInserts, Metadados meta, int offset);
void leInsertsNoArquivo(allData *data, int numeroDeInserts, Metadados meta, int offset, int offsetDoRegistro);
char *criaArquivoIndex(char *nomeIndex, Metadados meta, int numeroDeInserts, int offset, allData *data);
int buscaBinaria(Metadados meta, int numeroDeInserts, allData *data, int numeroProcurado, int offset, char *nomeIndex);

int main(int argc, char const *argv[])
{
	char *nomeArquivo = NULL;
	nomeArquivo = readline(stdin, nomeArquivo);
	Metadados meta;
	char **dados = NULL;
	FILE *fp = NULL;
	dados = recebeDados(dados, nomeArquivo, fp, &meta);
	meta = transpoeTodosOsCampos(&meta, meta.numberOfFields, dados);
	liberaMatriz(dados, meta.numberOfFields);
	char **comandos = NULL;
	int numeroDeComandos = 0;
	comandos = recebeComandos(comandos, stdin, &numeroDeComandos);
	allData *data = NULL;
	int numeroDeInserts = 0;
	data = alocaStructData(data, numeroDeComandos, meta, comandos, &numeroDeInserts);
	int num_index_searchs = 0;
	char **index_e_searchs = NULL;
	index_e_searchs = comandosIndex_e_Search(comandos, numeroDeComandos, numeroDeInserts, &num_index_searchs, index_e_searchs);
	int offset = 0;
	data = carregaStructData(data, numeroDeInserts, meta, comandos, &offset);
	qsort(data, numeroDeInserts, sizeof(allData), comparaOrdem);
	escreveInsertsNoArquivo(data, numeroDeInserts, meta, offset);
	char *nomeIndex = NULL;

	for (int i = 0; i < num_index_searchs; i++)
	{
		if ((strstr(index_e_searchs[i], "index") != NULL) && nomeIndex == NULL)
		{
			if (nomeIndex == NULL)
			{
				nomeIndex = criaArquivoIndex(nomeIndex, meta,numeroDeInserts, offset, data);
			}
		}else if (strstr(index_e_searchs[i], "search") != NULL)
		{
			if (nomeIndex == NULL)
			{
				nomeIndex = criaArquivoIndex(nomeIndex, meta,numeroDeInserts, offset, data);
			}
			int numeroProcurado = extraiCaractereNumerico(index_e_searchs[i]);
			int offsetDoRegistro = buscaBinaria(meta, numeroDeInserts, data, numeroProcurado, offset, nomeIndex);
			if (offsetDoRegistro != -1)
			{
				leInsertsNoArquivo(data, numeroDeInserts, meta, offset, offsetDoRegistro);
				printf("\n");
			}
		}else if ((strstr(index_e_searchs[i], "exit") != NULL))
		{
			break;
		}
	}
	

	liberaStructData(data, numeroDeInserts, meta);
	free(nomeArquivo);	
	liberaStruct(meta);
	liberaMatriz(comandos, numeroDeComandos);
	liberaMatriz(index_e_searchs, num_index_searchs);
	free(nomeIndex);
	return 0;
}

char *readline(FILE *stream, char *string){
	int indice = 0;
	char aux;
	do
	{
		string = (char*)realloc(string, (indice + 1) * sizeof(char));
		aux = fgetc(stream);
		if (aux !='\r')
		{
			string[indice] = aux;
		}else{
			string[indice] = '\n';
		}
	} while (string[indice++] != '\n' && !feof(stream));
	string[indice - 1] = '\0';
	string = (char *)realloc(string, (strlen(string) * sizeof(char)) + 1);
	return string;
}

char **recebeDados(char **dados, char *nomeArquivo, FILE *fp, Metadados *meta){
	int i = 0;
	fp = fopen(nomeArquivo, "rb");
	if (fp != NULL)
	{
		do
		{
			dados = (char**)realloc(dados, (i+1) * sizeof(char*));
			dados[i] = NULL;
			dados[i] = readline(fp, dados[i]);
			i++;
		} while (!feof(fp));
	}
	fclose(fp);
	meta->numberOfFields = i;
	return dados;
}

void liberaMatriz(char **matriz, int linha){
	for (int i = 0; i < linha; i++)
	{
		free(matriz[i]);
	}
	free(matriz);
}

//Separa o conteúdo do campo de seu nome
char *recortaCampo(char *string, char *stringRetorno){
	stringRetorno = NULL;
	int condicao = 0, k = 0;
	for (int i = 0; i <= strlen(string); i++)
	{
		if (string[i] == ':')
		{
			if (string[i+1] == 32)
			{
				i = i + 2;
				condicao = 1;
			}
		}
		if (condicao == 1)
		{
			stringRetorno = (char*) realloc(stringRetorno, ((k + 1) * sizeof(char)) + 1);
			stringRetorno[k] = string[i];
			k++;
		}
	}
	stringRetorno[k-1] = '\0';
	return stringRetorno;
}

int extraiCaractereNumerico(char *string){
	int i = 0, tamanhoString = 0, indice = 0;
	char *aux = NULL;
	do
	{
		if (string[i] >= 48 && string[i] <= 57)
		{
			aux = (char*) realloc(aux, (indice + 1) * sizeof(char));
			aux[indice] = string[i];
			indice++;
		}
	} while (string[i++] != '\0');
	aux = (char*) realloc(aux, (indice + 1) * sizeof(char));
	aux[indice] = '\0';
	tamanhoString = atoi(aux);
	free(aux);
	return tamanhoString;
}

Metadados transpoeTodosOsCampos(Metadados *meta, int numberOfFields, char **dados){
	meta->fields = NULL;
	int indice = 0;
	for (int i = 0; i < numberOfFields; i++)
	{
		if (strstr(dados[i], "filename") != NULL)
		{
			meta->fileName = NULL;
			meta->fileName = recortaCampo(dados[i], meta->fileName);
		}else if (strstr(dados[i], "key-name") != NULL)
		{
			meta->keyName = NULL;
			meta->keyName = recortaCampo(dados[i], meta->keyName);
		}else if (strstr(dados[i], "key-type") != NULL)
		{
			meta->keyType = NULL;
			meta->keyType = recortaCampo(dados[i], meta->keyType);
		}else if (strstr(dados[i], "field-name") != NULL)
		{
			meta->fields = (Fields*)realloc(meta->fields, (indice + 1) * sizeof(Fields));
			meta->fields[indice].fieldName = NULL;
			meta->fields[indice].fieldName = recortaCampo(dados[i], meta->fields[indice].fieldName);
		}else if (strstr(dados[i], "field-type") != NULL)
		{
			meta->fields[indice].fieldType = NULL;
			meta->fields[indice].fieldType = recortaCampo(dados[i], meta->fields[indice].fieldType);
			if (strstr(meta->fields[indice].fieldType, "char") != NULL)
			{
				meta->fields[indice].length = extraiCaractereNumerico(meta->fields[indice].fieldType);
			}
			indice++;
		}
	}
	meta->fields->quantidadeCampos = indice;
	return *meta;
}

void imprimeMetadados(Metadados meta){
	printf("%s\n", meta.fileName);
	printf("%s\n", meta.keyName);
	printf("%s\n", meta.keyType);
	for (int i = 0; i < meta.fields->quantidadeCampos; i++)
	{
		printf("%s\n", meta.fields[i].fieldName);
		if (strstr(meta.fields[i].fieldType, "char") != NULL)
		{
			printf("length: %i\n", meta.fields[i].length);
		}
		printf("%s\n", meta.fields[i].fieldType);
	}
}

void liberaStruct(Metadados meta){
		free(meta.fileName);
		free(meta.keyName);
		free(meta.keyType);
		for (int i = 0; i < meta.fields->quantidadeCampos; i++)
		{
			free(meta.fields[i].fieldName);
			free(meta.fields[i].fieldType);
		}
		free(meta.fields);
}


char **recebeComandos(char **comandos, FILE *stream, int *numeroDeComandos){
	int i = 0;
		do
		{
			comandos = (char**)realloc(comandos, (i+1) * sizeof(char*));
			comandos[i] = NULL;
			comandos[i] = readline(stream, comandos[i]);
			i++;
		} while (!feof(stream));
	*numeroDeComandos = i;
	return comandos;
}

void imprimeMatriz(char **matriz, int num){
	for (int i = 0; i < num; i++)
	{
		printf("%s\n", matriz[i]);
	}
}

allData *alocaStructData(allData *data, int numeroDeComandos, Metadados meta,
	char **comandos, int *numeroDeInserts)
{
			int k = 0;
			data = (allData *) malloc(numeroDeComandos * sizeof(allData));
			for (int i = 0; i < numeroDeComandos; i++)
			{
				data[i].coringa = NULL;
				if (strstr(comandos[i], "insert") != NULL)
				{
					data[i].coringa = (Uni *) realloc(data[i].coringa, 
							meta.fields->quantidadeCampos * sizeof(Uni));
					k++;
				}
			}
			*numeroDeInserts = k;
			return data;
}

char **comandosIndex_e_Search(char **comandos, int numeroDeComandos, int numeroDeInserts,
	int *num_index_searchs, char **index_e_searchs)
{ 
	int indice = 0;
	for (int i = numeroDeInserts; i < numeroDeComandos; i++)
	{
		index_e_searchs = (char**)realloc(index_e_searchs, (indice + 1) * sizeof(char*));
		index_e_searchs[indice] = NULL;
		for (int j = 0; j <= strlen(comandos[i]); j++)
		{
			index_e_searchs[indice] = (char*)realloc(index_e_searchs[indice], ((j + 1) * sizeof(char))+1);
			index_e_searchs[indice][j] = comandos[i][j];

		}
		indice++;
	}
	*num_index_searchs = indice;
	return index_e_searchs;
}

allData *carregaStructData(allData *data, int numeroDeInserts, Metadados meta,
		char **comandos, int *offset)
{
	char *retorno = NULL;
	for (int i = 0; i < numeroDeInserts; i++)
	{
		*offset = 0;
		for (int j = 0; j < meta.fields->quantidadeCampos + 1; j++)
		{
			if (j == 0)
			{
				retorno = strtok(comandos[i], ",");
				data[i].key = extraiCaractereNumerico(retorno);
				*offset = *offset + 1*sizeof(int);
			}else{
				retorno = strtok(NULL, ",");
				if (strstr(meta.fields[j - 1].fieldType, "char") != NULL)
				{
					data[i].coringa[j-1].str = NULL;
					data[i].coringa[j-1].str = extraiString(retorno, meta.fields[j-1].length, data[i].coringa[j-1].str);
					*offset = *offset + meta.fields[j-1].length;
				}else if (strstr(meta.fields[j - 1].fieldType, "int") != NULL)
				{
					data[i].coringa[j-1].valorInteiro = extraiCaractereNumerico(retorno);
					*offset = *offset + 1*sizeof(int);
				}else if (strstr(meta.fields[j - 1].fieldType, "float") != NULL)
				{
					data[i].coringa[j-1].valorFloat = extraiFloat_e_Double(retorno);
					*offset = *offset + 1*sizeof(float);
				}else if (strstr(meta.fields[j - 1].fieldType, "double") != NULL)
				{
					data[i].coringa[j-1].valorDoble = extraiFloat_e_Double(retorno);
					*offset = *offset + 1*sizeof(double);
				}
			}
		}
	}
	return data;
}

//Recebe uma string entre aspas e extrai apenas o conteúdo interno às aspas
char *extraiString(char *stringOrigem, int length, char *stringDestino){
	char *aux = NULL;
	int indice = 0;

	for (int i = 0; i < strlen(stringOrigem); i++)
	{
		if (stringOrigem[i] != '"' && !(i == 0 && stringOrigem[i] == 32))
		{
			aux = (char*)realloc(aux, (indice + 1) * sizeof(char));
			aux[indice] = stringOrigem[i];
			indice++;
		}
	}
	aux = (char*)realloc(aux, (indice+1) * sizeof(char));
	aux[indice] = '\0';
	stringDestino = (char*) calloc(length, sizeof(char));
	for (int i = 0; i < strlen(aux); i++)
	{
		stringDestino[i] = aux[i];
	}
	free(aux);
	return stringDestino;
}

float extraiFloat_e_Double(char *string){
	int i = 0, indice = 0;
	float tamanhoString = 0;
	char *aux = NULL;
	do
	{
		if ((string[i] >= 48 && string[i] <= 57) || string[i] == '.')
		{
			aux = (char*) realloc(aux, (indice + 1) * sizeof(char));
			aux[indice] = string[i];
			indice++;
		}
	} while (string[i++] != '\0');
	aux = (char*) realloc(aux, (indice + 1) * sizeof(char));
	aux[indice] = '\0';
	tamanhoString = atof(aux);
	free(aux);
	return tamanhoString;
}

void liberaStructData(allData *data, int numeroDeInserts, Metadados meta){
	for (int i = 0; i < numeroDeInserts; i++)
	{
		for (int j = 0; j < meta.fields->quantidadeCampos; j++)
		{
			if (strstr(meta.fields[j].fieldType, "char") != NULL)
			{
				free(data[i].coringa[j].str);
			}	
		}
	}
	for (int i = 0; i < numeroDeInserts; i++)
	{
		free(data[i].coringa);
	}
	free(data);
}

//Auxilia qsort
int comparaOrdem(const void *a, const void *b){
	allData *data1 = (allData *)a;
	allData *data2 = (allData *)b;
	if (data1->key == data2->key)
	{
		return 0;
	}else if (data1->key < data2->key)
	{
		return -1;
	}else{
		return 1;
	}
}

void imprimeData(allData *data, int numeroDeInserts, Metadados meta){
		for (int j = 0; j < numeroDeInserts; j++)
		{
			printf("chave: %i\n", data[j].key);
			for (int i = 0; i < meta.fields->quantidadeCampos; i++)
			{
				if (strstr(meta.fields[i].fieldType, "char") != NULL)
				{
					printf("%s\n", data[j].coringa[i].str);
				}
			}
		}
}

void escreveInsertsNoArquivo(allData *data, int numeroDeInserts, Metadados meta, int offset){
	FILE *fp = NULL;
	fp = fopen(meta.fileName, "ab");
	for (int i = 0; i < numeroDeInserts; i++)
	{
		for (int j = 0; j < meta.fields->quantidadeCampos + 1; j++)
		{
			if (j == 0)
			{
				fwrite(&data[i].key, sizeof(int), 1, fp);
			}else{
				if (strstr(meta.fields[j - 1].fieldType, "char") != NULL)
				{
					fwrite(data[i].coringa[j-1].str, sizeof(char), meta.fields[j-1].length, fp);
				}else if (strstr(meta.fields[j - 1].fieldType, "int") != NULL)
				{
					fwrite(&data[i].coringa[j-1].valorInteiro, sizeof(int), 1, fp);
				}else if (strstr(meta.fields[j - 1].fieldType, "float") != NULL)
				{
					fwrite(&data[i].coringa[j-1].valorFloat, sizeof(float), 1, fp);
				}else if (strstr(meta.fields[j - 1].fieldType, "double") != NULL)
				{
					fwrite(&data[i].coringa[j-1].valorDoble, sizeof(double), 1, fp);
				}
			}
		}
	}
	fclose(fp);
}

void leInsertsNoArquivo(allData *data, int numeroDeInserts, Metadados meta, int offset, int offsetDoRegistro){
	allData registro;
	registro.coringa = (Uni*) malloc(meta.fields->quantidadeCampos * sizeof(Uni));
	FILE *fp = NULL;
	fp = fopen(meta.fileName, "rb");
	fseek(fp, offsetDoRegistro, SEEK_SET);
			for (int j = 0; j < meta.fields->quantidadeCampos + 1; j++)
			{
				if (j == 0)
				{
						fread(&registro.key, sizeof(int), 1, fp);
				}else{
					if (strstr(meta.fields[j - 1].fieldType, "char") != NULL)
					{
						registro.coringa[j-1].str = (char*) malloc(meta.fields[j - 1].length * sizeof(char));
						fread(registro.coringa[j-1].str, sizeof(char), meta.fields[j-1].length, fp);
					}else if (strstr(meta.fields[j - 1].fieldType, "int") != NULL)
					{
						fread(&registro.coringa[j-1].valorInteiro, sizeof(int), 1, fp);
					}else if (strstr(meta.fields[j - 1].fieldType, "float") != NULL)
					{
						fread(&registro.coringa[j-1].valorFloat, sizeof(float), 1, fp);
					}else if (strstr(meta.fields[j - 1].fieldType, "double") != NULL)
					{
						fread(&registro.coringa[j-1].valorDoble, sizeof(double), 1, fp);
					}
				}
			}
	fclose(fp);
	printf("%s: %i\n", meta.keyName, registro.key);
		for (int i = 0; i < meta.fields->quantidadeCampos; i++)
		{
			if (strstr(meta.fields[i].fieldType, "char") != NULL)
				{
					printf("%s: %s\n", meta.fields[i].fieldName, registro.coringa[i].str);
				}else if (strstr(meta.fields[i].fieldType, "int") != NULL)
				{
					printf("%s: %i\n", meta.fields[i].fieldName, registro.coringa[i].valorInteiro);
				}else if (strstr(meta.fields[i].fieldType, "float") != NULL)
				{
					printf("%s: %.2f\n", meta.fields[i].fieldName, registro.coringa[i].valorFloat);
				}else if (strstr(meta.fields[i].fieldType, "double") != NULL)
				{
					printf("%s: %.2lf\n", meta.fields[i].fieldName, registro.coringa[i].valorDoble);
				}
		}
		for (int i = 0; i < meta.fields->quantidadeCampos; i++)
		{
			if (strstr(meta.fields[i].fieldType, "char") != NULL)
			{
				free(registro.coringa[i].str);
			}
		}
		free(registro.coringa);
}

char *criaArquivoIndex(char *nomeIndex, Metadados meta, int numeroDeInserts, int offset, allData *data){
	nomeIndex = (char*) realloc(nomeIndex, (strlen(meta.fileName) * sizeof(char)) + 1);
	strcpy(nomeIndex, meta.fileName);
	char aux[4] = ".idx";
	char *retorno = strtok(nomeIndex, ".");
	nomeIndex = strcat(retorno, aux);
	int offsetDeCadaRegistro = 0;
	FILE *fp = NULL;
	fp = fopen(nomeIndex, "ab");
	for (int i = 0; i < numeroDeInserts; i++)
	{
		offsetDeCadaRegistro = offset * i;
		fwrite(&data[i].key, sizeof(int), 1, fp);
		fwrite(&offsetDeCadaRegistro, sizeof(int), 1, fp);
	}
	fclose(fp);
	return nomeIndex;
}

int buscaBinaria(Metadados meta, int numeroDeInserts, allData *data, int numeroProcurado, int offset, char * nomeIndex){
	int offsetDoRegistro = -1;
	FILE *fp = NULL;
	fp = fopen(nomeIndex, "rb");
	int *vetorDeChaves = (int *) malloc(numeroDeInserts * sizeof(int));
	int *vetorDeOffset = (int *) malloc(numeroDeInserts * sizeof(int));
	for (int i = 0; i < numeroDeInserts; i++)
	{
		fread(&vetorDeChaves[i], sizeof(int), 1, fp);
		fread(&vetorDeOffset[i], sizeof(int), 1, fp);
	}

	int inicio = 0, fim = numeroDeInserts, meio = (inicio + fim)/2;
	do{
		meio = (inicio + fim)/2;
		if (vetorDeChaves[meio] == numeroProcurado)
		{
			offsetDoRegistro = vetorDeOffset[meio];
		}
		if (vetorDeChaves[meio] > numeroProcurado)
		{
			fim = meio - 1;
		}else
		{
			inicio = meio + 1;
		}
	}while(inicio <= fim && vetorDeChaves[meio] != numeroProcurado);
	fclose(fp);
	free(vetorDeChaves);
	free(vetorDeOffset);
	return offsetDoRegistro;
}