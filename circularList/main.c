#include "lista.h"
#include "item.h"

int main(int argc, char const *argv[])
{
	Lista *lista = criarLista();
	Item *item1 = criarItem(7);
	Item *item2 = criarItem(812);
	Item *item3 = criarItem(-15);
	incluirItemNaLista(item1, lista);
	incluirItemNaLista(item2, lista);
	incluirItemNaLista(item3, lista);
	printf("numero de intens: %d\n", getNumeroItens(lista));
	imprimirLista(lista);
	printf("\n");
	removerItemDalista(item2, lista);
	imprimirLista(lista);
	return 0;
}