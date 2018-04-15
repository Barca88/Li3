#include "tag.h"

struct tag {
	long id;
	char* tag;
	int t_ctag;
};

long get_id_tag (ptr_tag t) {
	return t->id;
}

char* get_tag (ptr_tag g) {
	return g->tag;
}

int get_ctag (ptr_tag c) {
	return c->t_ctag;
}

void set_id_tag (struct tag* t, long id_out) {
	t->id = id_out;
}

void set_tag (struct tag* g, char* g_tag) {
	g->tag = g_tag;
}

void set_t_ctag (struct tag* c, int count_tag) {
	c->t_ctag = count_tag;
}