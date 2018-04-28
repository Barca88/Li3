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
