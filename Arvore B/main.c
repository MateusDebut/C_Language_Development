#include "Aluno.h"
#include "Util.h"
#include "ArvoreB.h"

int main(int argc, char const *argv[])
{
    FILE *arquivoRegistros = fopen("alunos.txt", "w+");
    FILE *arquivoIndices = fopen("indices.txt", "w+");

    for (int i = 0; !feof(stdin); ++i) {
        char *entrada = readline(stdin);
        executaComandos(entrada, arquivoRegistros, arquivoIndices);
    }

    fclose(arquivoRegistros);
    fclose(arquivoIndices);
}