#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct cabecalhoArquivo
{
	char assinatura[2];
	int tamanhoArquivo;
	int campoReservado;
	int deslocamento;
}cabecalhoArquivo;

typedef struct mapaBits
{
	int tamanhoMapaBits;
	int larguraImagem;
	int alturaImagem;
	short int numeroPlanos;
	short int bitPerPixel;
	int compressao;
	int tamanhoDadosImagem;
	int pixelMetroHorizontal;
	int pixelMetroVertical;
	int numeroCoresUsadas;
	int numeroCoresImportantes;
}mapaBits;

typedef struct paletaCores
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char reservado;
	
}paletaCores;

char *readline(FILE *stream, char *string);
void filtroNegativo(paletaCores *paleta, unsigned char **matrizDados, char *nomeArquivoBMP, mapaBits map,
	cabecalhoArquivo cabecalho, int alturaImagemPadding, int larguraImagemPadding);
char *separaString(char *string);
void filtroPB(paletaCores *paleta, unsigned char **matrizDados, char *nomeArquivoBMP, mapaBits map,
	cabecalhoArquivo cabecalho, int alturaImagemPadding, int larguraImagemPadding);

int main(int argc, char const *argv[])
{
	mapaBits map;
	cabecalhoArquivo cabecalho;
	paletaCores *paleta = (paletaCores *) malloc (256 * sizeof(paletaCores));

/*****************************LEITURA**************************************/
	char *nomeArquivoBMP = NULL;
	nomeArquivoBMP = readline(stdin, nomeArquivoBMP);
	int opcaoDeFiltro = 0;
	scanf("%d", &opcaoDeFiltro);


	FILE *fp = NULL;
	fp = fopen(nomeArquivoBMP, "rb");
	if (fp == NULL)
	{
		printf("Erro no arquivo\n");
		free(nomeArquivoBMP);
		free(paleta);
		exit(0);
	}

	//leitura struct cabecalho
	fread(cabecalho.assinatura, sizeof(char), 2, fp);
	fread(&cabecalho.tamanhoArquivo, sizeof(int), 1, fp);
	fread(&cabecalho.campoReservado, sizeof(int), 1, fp);
	fread(&cabecalho.deslocamento, sizeof(int), 1, fp);

	//leitura struct map
	fread(&map.tamanhoMapaBits, sizeof(int), 1, fp);
	fread(&map.larguraImagem, sizeof(int), 1, fp);
	fread(&map.alturaImagem, sizeof(int), 1, fp);
	fread(&map.numeroPlanos, sizeof(short int), 1, fp);
	fread(&map.bitPerPixel, sizeof(short int), 1, fp);
	fread(&map.compressao, sizeof(int), 1, fp);
	fread(&map.tamanhoDadosImagem, sizeof(int), 1, fp);
	fread(&map.pixelMetroHorizontal, sizeof(int), 1, fp);
	fread(&map.pixelMetroVertical, sizeof(int), 1, fp);
	fread(&map.pixelMetroHorizontal, sizeof(int), 1, fp);
	fread(&map.numeroCoresUsadas, sizeof(int), 1, fp);
	fread(&map.numeroCoresImportantes, sizeof(int), 1, fp);

	
	int larguraImagemPadding = map.larguraImagem;
	while(larguraImagemPadding % 4 != 0){
		larguraImagemPadding++;
	}

	int alturaImagemPadding = map.alturaImagem;
	while(alturaImagemPadding % 4 != 0){
		alturaImagemPadding++;
	}
	

	//Leitura Vetor de struct paleta
	for (int i = 0; i < 256; i++)
	{
		fread(&paleta[i].blue, sizeof(unsigned char), 1, fp);
		fread(&paleta[i].green, sizeof(unsigned char), 1, fp);
		fread(&paleta[i].red, sizeof(unsigned char), 1, fp);
		fread(&paleta[i].reservado, sizeof(unsigned char), 1, fp);
	}

	//Alocação e leitura de matriz de dados
	unsigned char **matrizDados = (unsigned char**) calloc(alturaImagemPadding, sizeof(unsigned char*));
	for (int i = 0; i < alturaImagemPadding; i++)
	{
		matrizDados[i] = (unsigned char *) calloc(larguraImagemPadding, sizeof(unsigned char));
	}
	for (int i = 0; i < alturaImagemPadding; i++)
	{
		for (int j = 0; j < larguraImagemPadding; j++)
		{
			fread(&matrizDados[i][j], sizeof(unsigned char), 1, fp);
		}
	}
	fclose(fp);
/*****************************FIM LEITURA**************************************/

	if ((strstr(nomeArquivoBMP, ".bmp") == NULL) || (cabecalho.assinatura[0] != 'B' || cabecalho.assinatura[1] != 'M'))
	{
		for (int i = 0; i < alturaImagemPadding; i++)
		{
			free(matrizDados[i]);
		}
		free(matrizDados);
		free(nomeArquivoBMP);
		free(paleta);
		printf("Arquivo nao eh do formato BMP\n");
		exit(0);
	}


	//filtro negativo == 1, filtro preto e branco == 2
	if (opcaoDeFiltro == 1)
	{
		filtroNegativo(paleta, matrizDados, nomeArquivoBMP, map, cabecalho, alturaImagemPadding, larguraImagemPadding);
	}else if (opcaoDeFiltro == 2)
	{
		filtroPB(paleta, matrizDados, nomeArquivoBMP, map, cabecalho, alturaImagemPadding, larguraImagemPadding);
	}

	for (int i = 0; i < alturaImagemPadding; i++)
	{
		free(matrizDados[i]);
	}
	free(matrizDados);
	free(nomeArquivoBMP);
	free(paleta);

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

void filtroNegativo(paletaCores *paleta, unsigned char **matrizDados, char *nomeArquivoBMP, mapaBits map,
	cabecalhoArquivo cabecalho, int alturaImagemPadding, int larguraImagemPadding){
	paletaCores *paletaNegativo = (paletaCores*) malloc(256 * sizeof(paletaCores));
	for (int i = 0; i < 256; i++)
	{
		paletaNegativo[i].blue = abs(paleta[i].blue - 255);
		paletaNegativo[i].green = abs(paleta[i].green - 255);
		paletaNegativo[i].red = abs(paleta[i].red - 255);
		paletaNegativo[i].reservado = abs(paleta[i].reservado);

	}
	nomeArquivoBMP = separaString(nomeArquivoBMP);
	char *nomeNegativo = (char*) malloc(255);
	strcpy(nomeNegativo, nomeArquivoBMP);
	strcat(nomeNegativo, "Negativo.bmp");

	FILE *pFILE = NULL;
	pFILE = fopen(nomeNegativo, "wb");

	//leitura struct cabecalho
	fwrite(cabecalho.assinatura, sizeof(char), 2, pFILE);
	fwrite(&cabecalho.tamanhoArquivo, sizeof(int), 1, pFILE);
	fwrite(&cabecalho.campoReservado, sizeof(int), 1, pFILE);
	fwrite(&cabecalho.deslocamento, sizeof(int), 1, pFILE);

	//leitura struct map
	fwrite(&map.tamanhoMapaBits, sizeof(int), 1, pFILE);
	fwrite(&map.larguraImagem, sizeof(int), 1, pFILE);
	fwrite(&map.alturaImagem, sizeof(int), 1, pFILE);
	fwrite(&map.numeroPlanos, sizeof(short int), 1, pFILE);
	fwrite(&map.bitPerPixel, sizeof(short int), 1, pFILE);
	fwrite(&map.compressao, sizeof(int), 1, pFILE);
	fwrite(&map.tamanhoDadosImagem, sizeof(int), 1, pFILE);
	fwrite(&map.pixelMetroHorizontal, sizeof(int), 1, pFILE);
	fwrite(&map.pixelMetroVertical, sizeof(int), 1, pFILE);
	fwrite(&map.pixelMetroHorizontal, sizeof(int), 1, pFILE);
	fwrite(&map.numeroCoresUsadas, sizeof(int), 1, pFILE);
	fwrite(&map.numeroCoresImportantes, sizeof(int), 1, pFILE);

	for (int i = 0; i < 256; i++)
	{
		fwrite(&paletaNegativo[i].blue, sizeof(unsigned char), 1, pFILE);
		fwrite(&paletaNegativo[i].green, sizeof(unsigned char), 1, pFILE);
		fwrite(&paletaNegativo[i].red, sizeof(unsigned char), 1, pFILE);
		fwrite(&paletaNegativo[i].reservado, sizeof(unsigned char), 1, pFILE);
	}

	//Para todo elemento linha x coluna, escreva seu conteúdo, do tamanho de um unsigned char
	for (int i = 0; i < alturaImagemPadding; i++)
	{
		for (int j = 0; j < larguraImagemPadding; j++)
		{
			fwrite(&matrizDados[i][j], sizeof(unsigned char), 1, pFILE);
		}
	}

	printf("CABECALHO:\n");
	printf("Iniciais: %c%c\n", cabecalho.assinatura[0], cabecalho.assinatura[1]);
	printf("Tamanho do arquivo: %i\n", cabecalho.tamanhoArquivo);
	printf("Reservado: %i\n", cabecalho.campoReservado);
	printf("Deslocamento, em bytes, para o inicio da area de dados: %i\n", cabecalho.deslocamento);
	printf("Tamanho em bytes do segundo cabecalho: %i\n", map.tamanhoMapaBits);
	printf("Resolucao: %i x %i\n", map.larguraImagem, map.alturaImagem);
	printf("Numero de planos: %d\n", map.numeroPlanos);
	printf("Bits por pixel: %d\n", map.bitPerPixel);
	printf("Compressao usada: %d\n", map.compressao);
	printf("Tamanho imagem: %d\n", map.tamanhoDadosImagem);
	printf("Resolucao horizontal: %d pixel por metro\n", map.pixelMetroHorizontal);
	printf("Resolucao Vertical: %d pixel por metro\n", map.pixelMetroVertical);
	printf("Numero de cores usadas: %d\n", map.numeroCoresUsadas);
	printf("Numero de cores importantes: %d\n", map.numeroCoresImportantes);

    printf("PALETA ORIGINAL:\n");
	for (int i = 0; i < 256; i++)
	{
		printf("Paleta[%d]: R:%d G:%d B:%d\n", i, paleta[i].red, paleta[i].green, paleta[i].blue);
	}

    printf("PALETA NOVA\n");
	for (int i = 0; i < 256; i++)
	{
		printf("Paleta[%d]: R:%d G:%d B:%d\n", i, paletaNegativo[i].red, paletaNegativo[i].green, paletaNegativo[i].blue);
	}

	long long int soma[alturaImagemPadding];
	for (int i = 0; i < alturaImagemPadding; i++)
	{
		soma[i] = 0;
	}
	int k = 0;

	for (int i = alturaImagemPadding - 1; i >= 0; i--)
	{
		for (int j = 0; j < larguraImagemPadding; j++)
		{
			if (matrizDados[i][j] > 255 || matrizDados[i][j] < 0)
			{
				soma[k] = soma[k] -1;
			}else{
				soma[k] = soma[k] + matrizDados[i][j];
			} 
		}
		printf("Soma linha %i: %lld\n", k, soma[k]);
		k++;
	}

	printf("%s\n", nomeNegativo);
	fclose(pFILE);
	free(paletaNegativo);
	free(nomeNegativo);
}

char *separaString(char *string){
	char *retorno = NULL;
	int i = 0;
	while(string[i] != '.'){
		retorno = (char*) realloc(retorno, (i+1) * sizeof(char));
		retorno[i] = string[i];
		i++;
	}
	retorno = (char*) realloc(retorno, (i+1) * sizeof(char));
	retorno[i] = '\0';
	strcpy(string, retorno);
	free(retorno);
	return string;
}

void filtroPB(paletaCores *paleta, unsigned char **matrizDados, char *nomeArquivoBMP, mapaBits map,
	cabecalhoArquivo cabecalho, int alturaImagemPadding, int larguraImagemPadding){
	paletaCores *paletaPB = (paletaCores*) malloc(256 * sizeof(paletaCores));
		for (int i = 0; i < 256; i++)
		{
			unsigned char media = (paleta[i].blue + paleta[i].green + paleta[i].red) / 3;
			paletaPB[i].blue = media;
			paletaPB[i].green = media;
			paletaPB[i].red = media;
		}	

	nomeArquivoBMP = separaString(nomeArquivoBMP);
	char *nomePB = (char*) malloc(255);
	strcpy(nomePB, nomeArquivoBMP);
	strcat(nomePB, "PretoBranco.bmp");

	FILE *pFILE = NULL;
	pFILE = fopen(nomePB, "wb");

	//leitura struct cabecalho
	fwrite(cabecalho.assinatura, sizeof(char), 2, pFILE);
	fwrite(&cabecalho.tamanhoArquivo, sizeof(int), 1, pFILE);
	fwrite(&cabecalho.campoReservado, sizeof(int), 1, pFILE);
	fwrite(&cabecalho.deslocamento, sizeof(int), 1, pFILE);

	//leitura struct map
	fwrite(&map.tamanhoMapaBits, sizeof(int), 1, pFILE);
	fwrite(&map.larguraImagem, sizeof(int), 1, pFILE);
	fwrite(&map.alturaImagem, sizeof(int), 1, pFILE);
	fwrite(&map.numeroPlanos, sizeof(short int), 1, pFILE);
	fwrite(&map.bitPerPixel, sizeof(short int), 1, pFILE);
	fwrite(&map.compressao, sizeof(int), 1, pFILE);
	fwrite(&map.tamanhoDadosImagem, sizeof(int), 1, pFILE);
	fwrite(&map.pixelMetroHorizontal, sizeof(int), 1, pFILE);
	fwrite(&map.pixelMetroVertical, sizeof(int), 1, pFILE);
	fwrite(&map.pixelMetroHorizontal, sizeof(int), 1, pFILE);
	fwrite(&map.numeroCoresUsadas, sizeof(int), 1, pFILE);
	fwrite(&map.numeroCoresImportantes, sizeof(int), 1, pFILE);

	for (int i = 0; i < 256; i++)
	{
		fwrite(&paletaPB[i].blue, sizeof(unsigned char), 1, pFILE);
		fwrite(&paletaPB[i].green, sizeof(unsigned char), 1, pFILE);
		fwrite(&paletaPB[i].red, sizeof(unsigned char), 1, pFILE);
		fwrite(&paletaPB[i].reservado, sizeof(unsigned char), 1, pFILE);
	}

	//Para todo elemento linha x coluna, escreva seu conteúdo, do tamanho de um unsigned char
	for (int i = 0; i < alturaImagemPadding; i++)
	{
		for (int j = 0; j < larguraImagemPadding; j++)
		{
			fwrite(&matrizDados[i][j], sizeof(unsigned char), 1, pFILE);
		}
	}

	printf("CABECALHO:\n");
	printf("Iniciais: %c%c\n", cabecalho.assinatura[0], cabecalho.assinatura[1]);
	printf("Tamanho do arquivo: %i\n", cabecalho.tamanhoArquivo);
	printf("Reservado: %i\n", cabecalho.campoReservado);
	printf("Deslocamento, em bytes, para o inicio da area de dados: %i\n", cabecalho.deslocamento);
	printf("Tamanho em bytes do segundo cabecalho: %i\n", map.tamanhoMapaBits);
	printf("Resolucao: %i x %i\n", map.larguraImagem, map.alturaImagem);
	printf("Numero de planos: %d\n", map.numeroPlanos);
	printf("Bits por pixel: %d\n", map.bitPerPixel);
	printf("Compressao usada: %d\n", map.compressao);
	printf("Tamanho imagem: %d\n", map.tamanhoDadosImagem);
	printf("Resolucao horizontal: %d pixel por metro\n", map.pixelMetroHorizontal);
	printf("Resolucao Vertical: %d pixel por metro\n", map.pixelMetroVertical);
	printf("Numero de cores usadas: %d\n", map.numeroCoresUsadas);
	printf("Numero de cores importantes: %d\n", map.numeroCoresImportantes);

    printf("PALETA ORIGINAL:\n");
	for (int i = 0; i < 256; i++)
	{
		printf("Paleta[%d]: R:%d G:%d B:%d\n", i, paleta[i].red, paleta[i].green, paleta[i].blue);
	}

    printf("PALETA NOVA\n");
	for (int i = 0; i < 256; i++)
	{
		printf("Paleta[%d]: R:%d G:%d B:%d\n", i, paletaPB[i].red, paletaPB[i].green, paletaPB[i].blue);
	}

	long long int soma[alturaImagemPadding];
	for (int i = 0; i < alturaImagemPadding; i++)
	{
		soma[i] = 0;
	}
	int k = 0;

	for (int i = alturaImagemPadding - 1; i >= 0; i--)
	{
		for (int j = 0; j < larguraImagemPadding; j++)
		{
			if (matrizDados[i][j] > 255 || matrizDados[i][j] < 0)
			{
				soma[k] = soma[k] -1;
			}else{
				soma[k] = soma[k] + matrizDados[i][j];
			} 
		}
		printf("Soma linha %i: %lld\n", k, soma[k]);
		k++;
	}

	printf("%s\n", nomePB);
	fclose(pFILE);
	free(paletaPB);
	free(nomePB);
}