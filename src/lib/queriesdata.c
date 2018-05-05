#include "queriesdata.h"
#include "quest.h"
#include "tcd.h"

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

void free_3(query3 q){
    free(q);
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

void free_4(query4 q){
    g_slist_free(q->list);
    free(q);
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
void free_6(query6 q){
    g_slist_free(q->list);
    free(q);
}
//-----------------------------------------------------
struct aux7{
    Date begin;
    Date end;
    GSList* list;
};


query7 init_query7(Date b,Date e){
    query7 ld = (query7)malloc(sizeof(struct aux7));
    ld->begin = b;
    ld->end = e;
    ld->list = NULL;
    return ld;
}
Date get_begin_7(query7 q){
    return q->begin;
}

Date get_end_7(query7 q){
    return q->end;
}

GSList* get_list_7(query7 q){
    return q->list;
}

void set_list_7(query7 q,GSList* l){
    q->list = l;
}

void free_7(query7 q){
    if(q){
        if(q->list)g_slist_free_full(q->list,free_g_quest);
        free(q);
    }
}
//-----------------------------------------------------
struct aux8{
    char* word;
    GSList* list;
};

query8 init_query8(char* word){
    query8 aux = (query8)malloc(sizeof(struct aux8));
    aux->word = word;
    aux->list = NULL;
    return aux;
}

char* get_word_8(query8 q){
    return q->word;
}

GSList* get_list_8(query8 q){
    return q->list;
}

void set_list_8(query8 q,GSList* l){
    q->list = l;
}

void free_8(query8 q){
    g_slist_free(q->list);
    free(q);
}

//------------------------------------------------------
struct aux9{
    GHashTable* h;
    GSList* l;
};

query9 init_query9(GHashTable* com){
    query9 aux = (query9)malloc(sizeof(struct aux9));
    aux->h = com;
    aux->l = NULL;
    return aux;
}
GHashTable* get_hash_9(query9 q){
    return q->h;
}

GSList* get_slist_9(query9 q){
    return q->l;
}

void set_slist_9(query9 q,GSList* lista){
    q->l = lista;
}

void set_hash_9(query9 q,GHashTable* hash){
    q->h = hash;
}

void free_9(query9 q){
    g_slist_free(q->l);
    free(q);
}

//------------------------------------------------------
struct aux11{
    GHashTable* ht;
    Date begin;
    Date end;
};

query11 init_query11(TAD_community com,Date b,Date e){
    query11 aux = malloc(sizeof(struct aux11));
    aux->ht = get_hash_tags(com);
    aux->begin = b;
    aux->end = e;
    return aux;
}

Date get_begin_11(query11 q){
    return q->begin;
}
Date get_end_11(query11 q){
    return q->end;
}
GHashTable* get_ht_11(query11 q){
    return q->ht;
}
void free_11(query11 q){
    free(q->ht);
}
