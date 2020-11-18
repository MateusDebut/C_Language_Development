typedef int elem;
typedef struct list list_t;
typedef struct node node_t;
typedef struct comands comands_t;

struct comands
{
	char *comandName;
	int *num1;
	int *num2;
	int sizeNum1;
	int sizeNum2;
};

list_t *createList();
int putOnList(list_t *l, elem *vector, int size);
int removeFromList(list_t *l, elem x);
void printList(list_t *l);
void printListBackwards(list_t *l);
void destroyList(list_t *l);
char *readline(FILE *stream);
char **divideLine(char *string);
comands_t divideComands(char *string);