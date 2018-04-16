#include "tag.h"

struct tag {
	long id;
	char* tag;
	int n_used;
};

ptr_tag create_tag(long id,char* s,int n){
    ptr_tag t = malloc(sizeof(struct tag));
    set_id_tag(t,id);
    set_tag(t,s);
    set_n_used(t,n);
    return t;
}

long get_id_tag (ptr_tag t) {
	return t->id;
}

char* get_tag (ptr_tag t) {
	return mystrdup(t->tag);
}

int get_n_used (ptr_tag t) {
	return t->n_used;
}

void set_id_tag (ptr_tag t, long id_out) {
	t->id = id_out;
}

void set_tag (ptr_tag t, char* l) {
    free(t->tag);
	t->tag = mystrdup(l);
}

void set_n_used (ptr_tag t, int count_tag) {
	t->n_used = count_tag;
}

int equal_tag(ptr_tag t,char* s){
    if(t == NULL || s[0] == '\0') return -1;
    return strcmp(t->tag,s);
}

void free_tag(ptr_tag t){
    free(t->tag);
    free(t);
}
