#ifndef __TAG_H__
#define __TAG_H__

#include "common.h"
#include <glib.h>
#include <string.h>
#include <stdlib.h>
typedef struct tag* Tag;

// Metodo de Criação
Tag create_tag(long id,char* tag, int t_ctag);

//Setters
void set_id_tag (Tag t, long id_out);
void set_tag (Tag t, char* g_tag);
void set_n_used (Tag t, int count_tag);

//Getters
long get_id_tag (Tag t);
char* get_tag (Tag t);
int get_n_used (Tag t);

//Metodos
int equal_tag(Tag t,char* s);
//free
void free_tag(Tag);

#endif
