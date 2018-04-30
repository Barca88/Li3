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

typedef struct aux4* query4;

query4 init_query4(Date b,Date e,char* tag);

Date get_begin_4(query4 q);

Date get_end_4(query4 q);

char* get_tag_4(query4 q);

GSList* get_list_4(query4 q);

void set_list_4(query4 q,GSList* l);

void free_4(query4 q);

typedef struct aux6* query6;

query6 init_query6(Date b,Date e);

GSList* get_list_6(query6 q);

Date get_begin_6(query6 q);

Date get_end_6(query6 q);

void set_list_6 (query6 q, GSList* l); 

typedef struct aux8* query8;

query8 init_query8(char* word);

char* get_word_8(query8 q);

GSList* get_list_8(query8 q);

void set_list_8(query8 q,GSList* l);

void free_8(query8 q);

#endif
