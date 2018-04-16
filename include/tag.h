#ifndef __TAG_H__
#define __TAG_H__

#include <glib.h>

typedef struct tag* ptr_tag;

// Metodo de Criação
ptr_tag create_tag(long id,char* tag, int t_ctag);

//Setters
void set_id_tag (ptr_tag t, long id_out);
void set_tag (ptr_tag t, char* g_tag);
void set_n_tag (ptr_tag t, int count_tag);

//Getters
long get_id_tag (ptr_tag t);
char* get_tag (ptr_tag t);
int get_n_tag (ptr_tag t);

//Metodos
int equal_tag(ptr_tag t,char* s);
//free
void free_tag(ptr_tag);

#endif
