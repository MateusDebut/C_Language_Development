typedef int elem;
typedef stuct list list_t;

list_t *createList();
int putInList(list_t *l, elem);
int removeFromList(list_t *l, elem x);
int printList(list_t *l);
int printListBackwards(list_t *l);
void destroyList(list_t *l);