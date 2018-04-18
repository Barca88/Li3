#include "tag.h"

struct tag {
	long id;
	char* tag;
	int n_used;
};

Tag create_tag(long id,char* s,int n){
    Tag t = malloc(sizeof(struct tag));
    t->id = id;
    t->tag =  mystrdup(s);
    t->n_used = n;
    return t;
}

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

void set_n_used (Tag t, int count_tag) {
	t->n_used = count_tag;
}

int equal_tag(Tag t,char* s){
    if(t == NULL || s[0] == '\0') return -1;
    return strcmp(t->tag,s);
}

void free_tag(Tag t){
    free(t->tag);
    free(t);
}
