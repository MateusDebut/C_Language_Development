typedef int elem;
typedef struct list list_t;
typedef struct node node_t;
typedef struct commands commands_t;

struct commands
{
	char *commandName;
	int *num1;
	int *num2;
	int sizeNum1;
	int sizeNum2;
};

struct node
{
	elem *numberVector;
	node_t *previous;
	node_t *next;
	int size;
};

list_t *createList();
int putOnList(list_t *l, elem *vector, int size);
void printList(list_t *l);
void printListBackwards(list_t *l);
void destroyList(list_t *l);
char *readline(FILE *stream);
char **divideLine(char *string);
commands_t divideCommands(char *string);
node_t *sum(list_t *l);
int selectCommand(char *command);
int eql(list_t *l);
int big(list_t *l);
int sml(list_t *l);