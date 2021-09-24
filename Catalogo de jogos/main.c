#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catalogo.h"
#include "jogo.h"
#include "util.h"

int main(int argc, char const *argv[])
{
    Jogo **listaDeJogos = NULL;
    int indice = 0;
    //char *text = readline(stdin);

    /*loop que realiza o input dos dados dos jogos e criação da lista de jogos*/
    do
    {
        char *nomeDoJogo = readline(stdin);

        //Se encontrar um 'F', sai do loop
        if (strcmp(nomeDoJogo, "F") == 0)
        {
            free(nomeDoJogo);
            break;
        }

        char *produtoraDoJogo = readline(stdin);
        char *anoDeLancamento = readline(stdin);

        listaDeJogos = (Jogo **)realloc(listaDeJogos, (indice + 1) * sizeof(Jogo *));

        listaDeJogos[indice] = criarJogo(nomeDoJogo, produtoraDoJogo, "anoDeLancamento");
        indice++;
    } while (1);

    
    Catalogo *catalogo = criarCatalogo();
    inserirListaDeJogosNoCatalogo(catalogo, listaDeJogos);  

    /*loop que realiza as buscas no catalogo*/
    do
    {
        char *tipoDeBusca = readline(stdin);
        //printf("tipo de busca: %d\n", tipoDeBusca[]);
        if (strcmp(tipoDeBusca, "F") == 0)
        {
            free(tipoDeBusca);
            break;
        }

        char *itemASerBuscado = readline(stdin);

        if (strcmp(tipoDeBusca, "A") == 0)
            buscaPorAno(catalogo, itemASerBuscado);

        else if (strcmp(tipoDeBusca, "E") == 0)
            buscaPorProdutora(catalogo, itemASerBuscado);

        free(itemASerBuscado);
        free(tipoDeBusca);
    } while (1);

    desalocarCatalogo(catalogo);
    free(listaDeJogos);

    return 0;
}