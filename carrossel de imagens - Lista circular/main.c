#include "util.h"
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char ***dados = NULL;
    int numero_linhas = 0;
    int numeroDeItens = 0;
    int indiceLEtra = 0;

    FILE *fp = fopen("r+", "ascii.txt");

    while (!feof(fp))
    {
        dados = (char ***)realloc(dados, (numeroDeItens + 1) * sizeof(char **));
        dados[numeroDeItens] = NULL;
        numero_linhas = 0;
        do
        {
            dados[numeroDeItens] = (char **)realloc(dados[numeroDeItens], (numero_linhas + 1) * sizeof(char *));
            dados[numeroDeItens][numero_linhas] = readline(stdin);
            numero_linhas++;
        } while (myStrcmp(dados[numeroDeItens][numero_linhas - 1], "-42") != 0 
                    && myStrcmp(dados[numeroDeItens][numero_linhas - 1], "-47") != 0);
        if (myStrcmp(dados[numeroDeItens][numero_linhas - 1], "-47") == 0)
        {
            break;
        }
        numeroDeItens++;
    }

    Item **items = (Item **)malloc(numeroDeItens * sizeof(Item *));
    List *list = listCreate();

    for (int i = 0; i < numeroDeItens; i++)
    {
        items[i] = itemCreate(dados[i]);
        listPut(items[i], list);
    }
    listPrintNextItem(list);
    while (True)
    { 
        sleep(2);
        system("tput reset");
        listPrintNextItem(list);
    }

    return 0;
}