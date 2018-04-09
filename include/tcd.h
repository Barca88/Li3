#ifndef __TCD_H__
#define __TCD_H__

#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <time.h>
#include "interface.h"

typedef struct TCD_community TCD_community;

TAD_community init_tcd();

GHashTable* get_hash_users(TAD_community root);

GHashTable* get_hash_posts(TAD_community root);

GTree* get_tree_posts(TAD_community root);

#endif
