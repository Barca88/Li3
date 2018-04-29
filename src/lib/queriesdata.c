#include "queriesdata.h"

struct aux3{
    Date begin;
    Date end;
    int nq;
    int na;
};

query3 init_query3(Date b,Date e){
    query3 ld = malloc(sizeof(struct aux3));
    ld->begin = b;
    ld->end = e;
    ld->nq = 0;
    ld->na = 0;
    return ld;
}

Date get_begin_3(query3 q){
    return q->begin;
}

Date get_end_3(query3 q){
    return q->end;
}

int get_nq_3(query3 q){
    return q->nq;
}

int get_na_3(query3 q){
    return q->na;
}

void inc_nq_3(query3 q,int v){
    q->nq += v;
}

void inc_na_3(query3 q,int v){
    q->na += v;
}
//------------------------------------------------------
struct aux4{
    Date begin;
    Date end;
    char* tag;
    GSList* list;
};


query4 init_query4(Date b,Date e,char* tag){
    query4 ld = malloc(sizeof(struct aux4));
    ld->begin = b;
    ld->end = e;
    ld->tag = tag;
    ld->list = NULL;
    return ld;
}    

Date get_begin_4(query4 q){
    return q->begin;
}

Date get_end_4(query4 q){
    return q->end;
}

char* get_tag_4(query4 q){
    return q->tag;
}

GSList* get_list_4(query4 q){
    return q->list;
}

void set_list_4(query4 q,GSList* l){
    q->list = l;
}

//-----------------------------------------------------
struct aux6{
    Date begin;
    Date end;
    GSList* list;
};

query6 init_query6(Date b,Date e){
    query6 ld = malloc(sizeof(struct aux6));
    ld->begin = b;
    ld->end = e;
    ld->list = NULL;
    return ld;
}    

Date get_begin_6(query6 q){
    return q->begin;
}

Date get_end_6(query6 q){
    return q->end;
}

GSList* get_list_6(query6 q){
    return q->list;
}

void set_list_6(query6 q,GSList* l){
    q->list = l;
}