#include "tag.h"

/* Definição da estrutura das tag. */
struct tag {
	long id; /* Id da tag. */
	char* tag; /* Tag pretendida. */
	int n_used; /* Nº de vezes que uma determinada tag foi usada. */
};

/* Funcao reponsável pela alocacao de memoria e a inicializacao dos campos, da tag.*/
Tag create_tag(long id,char* s){
    Tag t = malloc(sizeof(struct tag));
    t->id = id;
    t->tag =  mystrdup(s);
    t->n_used = 0;
    return t;
}

/* Gets (Obter valor das variaveis da estrutura) */
long get_id_tag (Tag t) {
	return t->id;
}

char* get_tag (Tag t) {
	return mystrdup(t->tag);
}

int get_n_used (Tag t) {
	return t->n_used;
}

void set_id_tag (Tag t, long id_out) {
	t->id = id_out;
}

void set_tag (Tag t, char* l) {
    free(t->tag);
	t->tag = mystrdup(l);
}

void inc_n_used (Tag t) {
    if(t)
	    (t->n_used)++;
}

int equal_tag(Tag t,char* s){
    if(t == NULL || s[0] == '\0') return -1;
    return strcmp(t->tag,s);
}

void print_tag(Tag t){
    if(t)
        printf("Tag:\n\tId: %ld\n\tTag name: %s\n\tN used: %d\n",t->id,t->tag,t->n_used);
}

/* Apaga a tag dando free na memoria alocada. */
void free_tag(Tag t){
    free(t->tag);
    free(t);
}
void free_g_tag(gpointer g){
	Tag t = (Tag)GPOINTER_TO_SIZE(g);
	free_tag(t);
}
