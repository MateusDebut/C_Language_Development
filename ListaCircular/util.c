#include "util.h"

char *readline(FILE *stream)
{
    int index = 0;
    char *string = NULL;
    char aux;
    do
    {
        if (index % STRING_SIZE == 0)
        {
            int newSize = STRING_SIZE * (index + 1);
            string = (char *)realloc(string, newSize);
        }
        aux = getc(stream);
        if (aux != '\t' && aux != 13)
        {
            string[index] = aux;
            index++;
        }
    } while (string[index - 1] != '\n' && !feof(stream));
    string[index - 1] = '\0';
    if (strlen(string) == 0)
    {
        free(string);
        return NULL;
    }
    return string;
}

char **separateStringsBySpace(char *string)
{
    if(string == NULL) return NULL;

    char **wordParts = (char **)malloc(MAXIMUM_NUMBER_OF_DIVISIONS * sizeof(char *));

    char *delimiter = "[ |\n]";
    wordParts[0] = strtok(string, delimiter);
    wordParts[1] = strtok(NULL, delimiter);
    wordParts[2] = strtok(NULL, delimiter);
    return wordParts;
}

void invocateOperation(char *operation, char *complement1, char *complement2, List *list)
{
    if (strcmp("p", operation) == 0)
    {
        findByProducer(list, complement1);
    }
    else if (strcmp("a", operation) == 0)
    {
        findByReleaseYear(list, complement1);
    }
    else if (strcmp("i", operation) == 0)
    {
        listPrint(list);
    }
    else if (strcmp("u", operation) == 0)
    {
        printItemByPosition(atoi(complement1), list);
    }
    else if (strcmp("mr", operation) == 0)
    {
        listMoveItemRight(atoi(complement1), atoi(complement2), list);
    }
    else if (strcmp("ml", operation) == 0)
    {
        listMoveItemLeft(atoi(complement1), atoi(complement2), list);
    }
    else if (strcmp("r", operation) == 0)
    {
        listDeleteRepeatedItens(list);
    }
    else if (strcmp("f", operation) == 0)
    {
        listDelete(list);
    }
}

char **readCsvFile(char *fileName)
{
    FILE *fp;
    char **data = NULL;
    int i = 0;
    fp = fopen(fileName, "rb");
    fseek(fp, 3, SEEK_SET);
    if (fp != NULL)
    {
        do
        {
            data = (char **)realloc(data, (i + 1) * sizeof(char *));
            data[i] = NULL;
            data[i] = readline(fp);
            i++;
        } while (!feof(fp));
    }
    fclose(fp);
    return data;
}

int countLines(char **strings)
{
    int index = 0;
    while (strings[index] != NULL)
    {
        index++;
    }
    return index;
}

void fillList(char **data, int numberOfItems, List *list)
{
    
    for (int i = 0; i < numberOfItems; i++)
    {
        char *delimiter = "[;|\n]";

        char *name = strtok(data[i], delimiter);
        char *releaseYear = strtok(NULL, delimiter);
        char *producer = strtok(NULL, delimiter);

        Item * item = itemCreate(name, releaseYear, producer);

        listPut(item, list);
    }
}

int myStrcmp(char *string1, char *string2)
{
    if (strlen(string1) != strlen(string2))
    {
        return -1;
    }

    for (int i = 0; i < strlen(string1); i++)
    {
        if (string1[i] != string2[i])
        {
            return -1;
        }
    }
    return 0;
}

void freeCharMatrix(int numberOfLines, char **matrix)
{
    for (int i = 0; i < numberOfLines; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}