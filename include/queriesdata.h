#ifndef __QUERIESDATA_H__
#define __QUERIESDATA_H__

#include "date.h"

typedef struct aux3* query3;

query3 init_query3(Date b,Date e);

Date get_begin_3(query3 q);

Date get_end_3(query3 q);

int get_nq_3(query3 q);

int get_na_3(query3 q);

void inc_nq_3(query3 q,int v);

void inc_na_3(query3 q,int v);

#endif
