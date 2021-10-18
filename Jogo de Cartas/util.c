#include "util.h"
#include "stack.h"

char *readline(FILE *stream){
	int indice = 0;
	char *string = NULL;
    char aux;
	do
	{
		if (indice % TAMANHO_DEFAULT_STRING == 0)
		{
			string = (char*) realloc(string, ((indice % TAMANHO_DEFAULT_STRING) + 1) * TAMANHO_DEFAULT_STRING * sizeof(char));
		}
		aux = getc(stream);
        string[indice] = aux;
        indice++;

	} while (string[indice-1] != '\n' && string[indice-1] != 32 && !feof(stream));
	
    string[indice-1] = '\0';
    return (string[0] == '\0') ? NULL : string;

}

int atoiReadline(FILE *stream){
    char *text = readline(stream);
	if(text[0] >= '0' && text[0] <= '9'){
		int intValue = atoi(text);
		free(text);
		return intValue;
	}
    	
    free(text);
    return 10;
}

void gameLogic(Stack *stack){
	int sum = 0;
	while (sum < 21)
	{
		Card *card = stackPop(stack);
		sum = sum + cardGetValue(card);
	}

	if(sum == 21){
		printf("Ganhou ;)\n");
	}else{
		printf("Perdeu :(\nSoma :: %d\n", sum);
	}
	
}

