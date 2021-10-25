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
        string[index] = aux;
        index++;
    } while (string[index - 1] != '\n' && !feof(stream));
    string[index - 1] = '\0';
    if (strlen(string) == 0)
    {
        free(string);
        return NULL;
    }
    return string;
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