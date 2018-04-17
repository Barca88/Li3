#ifndef __TCD_H__
#define __TCD_H__

#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <time.h>
#include "date.h"
#include "interface.h"

typedef struct TCD_community TCD_community;

TAD_community init_tcd();

GHashTable* get_hash_users(TAD_community root);
GHashTable* get_hash_quests(TAD_community root);
GHashTable* get_hash_answers(TAD_community root);
GTree* get_tree_days(TAD_community root);
GSList* get_rank_n_posts(TAD_community root);

void set_rank_n_posts(TAD_community root,GSList *new);

#endif
