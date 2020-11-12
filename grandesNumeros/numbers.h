typedef int elem;
typedef stuct list list_t;

list_t *createList();
int putOnList(list_t *l, elem x);
int removeFromList(list_t *l, elem x);
void printList(list_t *l);
void printListBackwards(list_t *l);
void destroyList(list_t *l);