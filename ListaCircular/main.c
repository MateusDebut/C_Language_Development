#include "util.h"

int main(int argc, char const *argv[])
{
    char **data = readCsvFile("CSV.csv");
    int numberOfLines = countLines(data);

    List *list = listCreate();
    fillList(data, numberOfLines, list);

    while (!feof(stdin))
    {
        char *input = readline(stdin);
        char **separatedInputs = separateStringsBySpace(input);
        invocateOperation(separatedInputs[0], separatedInputs[1], separatedInputs[2], list);
        free(separatedInputs);
        free(input);
    }

    freeCharMatrix(numberOfLines, data);
    return 0;
}