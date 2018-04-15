#ifndef __TAG_H__
#define __TAG_H__

#include <glib.h>

typedef struct tag* ptr_tag;

// Metodo de Criação
ptr_tag init_tag(long id,char* tag, int t_ctag);

//Setters
void set_id_tag (struct tag* t, long id_out);
void set_tag (struct tag* g, char* g_tag);
void set_t_ctag (struct tag* c, int count_tag);

long get_id_tag (ptr_tag t);
char* get_tag (ptr_tag g);
int get_ctag (ptr_tag c);

#endif