#ifndef __DAY_H__
#define __DAY_H__

#include "post.h"
#include "date.h"
#include <glib.h>
#include <stdlib.h>
typedef struct day* Day;

//Metodos de criação
Day init_day(Date d);

//Métodos
void add_post_day(Day d, ptr_post);

//Gettres
int get_n_p(Day d);
int get_n_r(Day d);
GHashTable* get_hash_p(Day d);
GHashTable* get_hash_r(Day d);
Date get_day_day(Day d);

#endif
