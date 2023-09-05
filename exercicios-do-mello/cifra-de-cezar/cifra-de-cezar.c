//Este programa encripta e desencripta mensagens a partir de um método de criptografia chamado de cifra de César

#include <stdio.h> //biblioteca de input e output
#include <stdlib.h> // biblioteca de alocação de memória, controle e conversões
#include <string.h> // biblioteca para manipulação de strings
int main() {
	int decisao, chave = 0; // variavel decisão armazena o valor 1 para encriptar e o valor 2 para desencriptar
	char mensagem[100]; // a mensagem será tratada como um vetor de caracteres de no máximo 100 caracteres.

	scanf("%d", &decisao);
	scanf("%d ", &chave);

	if (decisao == 1){ // condicional que encripta a mensagem
		scanf("%[^\n]", mensagem);
		for (int i = 0; i < strlen(mensagem); i++)// Função strlen conta quantos caracteres temos na mensagem. Usaremos ela como limitadora do laço
		{
			if ((mensagem[i] >= 97 && mensagem[i] <=122) && (mensagem[i] + chave > 122))
			{
				mensagem[i] = ((mensagem[i] + chave) - 122) + 96; // Caso em que a letra somada da chave ultrapassa 122 ('z' na tabela ascii)
			}
			else if ((mensagem[i] >= 65 && mensagem[i] <= 90) && (mensagem[i] + chave > 90))
			{
				mensagem[i] = ((mensagem[i] + chave) - 90) + 64;
			}
			else if (mensagem[i] >= 32 && mensagem[i] <= 63)
			{
				mensagem[i] = mensagem[i];
			}
			else{
				mensagem[i] = mensagem[i] + chave;
			}
		}
		printf("%s \n", mensagem);
	}
	else if (decisao == 2) // Condicional que desencripta a mensagem
	{
		scanf("%[^\n]", mensagem);

		for (int i = 0; i < strlen(mensagem); i++)
		{
			if ((mensagem [i] >= 97 && mensagem[i] <=122) && (mensagem[i] - chave < 97))
			{
				mensagem[i] = ((mensagem[i] - chave) - 97) + 123; // caso em que a letra menos a chave antecede 97 ('a' na tabela ascii)
			}
			else if ((mensagem [i] >= 65 && mensagem[i] <=90) && (mensagem[i] - chave < 65))
			{
				mensagem[i] = ((mensagem[i] - chave) - 65) + 91; // caso em que a letra menos a chave antecede 97 ('a' na tabela ascii)
			}
			else if (mensagem[i] >= 32 && mensagem[i] <= 63)
			{
				mensagem[i] = mensagem[i];
			} 
			else{
				mensagem[i] = mensagem[i] - chave;
			}
		}
		printf("%s \n", mensagem);
	}
    
    return 0;
}