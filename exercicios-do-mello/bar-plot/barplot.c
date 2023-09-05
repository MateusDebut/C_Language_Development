/*
 *Este programa exibe dados de forma visual, de maneira similar a um gráfico. Para isso, ele recebe um inteiro (rotulos)
 *que representa a quantidade de rótulos existentes nesse gráfico. Em seguida, recebe outro inteiro (numParametros)
 *representando a quantidade de parâmetros que serão passados a cada rótulo. Na sequência, o programa recebe
 *os parâmetros através do vetor (Vector) e, por fim, os imprime em ordem crescente (do maior rótulo para o menor).
*/

#include<stdio.h>
#include<stdlib.h>

int main(){
	int rotulos, numParametros, quantidade;
	scanf("%i", &rotulos);
	scanf("%i", &numParametros);

	int vector[numParametros];

	for (int i = 0; i < numParametros; i++)
	{
		scanf("%i", &vector[i]);
	}

	//bubble sort para ordenar vector em ordem crescente
	for (int i = 1; i < numParametros; i++)
   {
       for (int j = 0; j < numParametros - 1; j++)
       {
           if (vector[j] > vector[j+1])
           {
                quantidade = vector[j];
                vector[j] = vector[j+1];
                vector[j+1] = quantidade;
           }
       }
   }

   //bloco responsável pela impressão do gráfico
   for (int i = 0; i < numParametros; i++)
   {
   		quantidade = 1;//variável que contará a quantidade de vezes que um rótulo é repetido.
   					   //inicia em 1 pois o rótulo obrigatóriamente aparecerá pelo menos uma vez.

   	    while(vector[i] == vector[i+1])
   	    {
   			quantidade = quantidade + 1;
   			i++;
        }

        printf("%i - ", vector[i]);

        for (int i = 0; i < quantidade; i++)
        {
        	printf("#");
        }

        printf("\n");
   }
 

    return 0;
}