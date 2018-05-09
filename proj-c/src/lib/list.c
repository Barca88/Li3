#include <stdlib.h>
#include "list.h"

/* Definição da estrutura das listas (llist). */
struct llist {
  int size; /* Tamanho alocado para uma lista. */
  long * list; /* Apontador para uma lista. */
};

/* Função reponsável pela criação de uma lista. */
LONG_list create_list(int size) {
    if(size <= 0) return NULL;
    LONG_list l = malloc(sizeof(struct llist));
    l->size = size;
    l->list = malloc(sizeof(long) * size);
    return l;
}
int get_size(LONG_list l){
    return l->size;
}
/* Gets (Obter valor das variaveis da estrutura) */
long get_list(LONG_list l, int index) {
    return l->list[index];
}

void set_list(LONG_list l, int index, long value) {
    l->list[index] = value;
}
/* Apaga a lista dando free na memoria alocada. */
void free_list(LONG_list l) {
    if(l) {
        free(l->list);
        free(l);
    }
}
