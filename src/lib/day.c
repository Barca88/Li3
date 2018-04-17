#include "day.h"

struct day {
    Date day;
    int n_quest;
    int n_answer;
    GHashTable* hash_quest;
    GHashTable* hash_answer;
};

Day init_day(Date day){
    Day d = malloc(sizeof(struct day));
    d -> day = day;
    d -> n_quest = 0;
    d -> n_answer = 0;
    d -> hash_quest = g_hash_table_new(g_direct_hash, g_direct_equal);
    d -> hash_answer = g_hash_table_new(g_direct_hash, g_direct_equal);
    return d;
}

//Métodos
<<<<<<< HEAD
void add_quest_day(Day d, Quest q){
    GHashTable* hq = d->hash_p;
    g_hash_table_insert(hq,GSIZE_TO_POINTER(get_id_quest(q)),q);
    (d->n_p)++;
}
void add_answer_day(Day d, Answer a){
    GHashTable* ha = d->hash_r;
    g_hash_table_insert(ha,GSIZE_TO_POINTER(get_id_answer(a)),a);
    (d->n_r)++;
=======
void add_post_day(Day d, ptr_post p){
    GHashTable *hash;
    if(get_post_type_id(p) == 1){
        hash = d->hash_quest;
        g_hash_table_insert(hash,GSIZE_TO_POINTER(get_id(p)),p);
        (d->n_quest) += 1;
    }
    if(get_post_type_id(p) == 2){
        hash = d->hash_answer;
        g_hash_table_insert(hash,GSIZE_TO_POINTER(get_id(p)),p);
        (d->n_answer) += 1;
    }
>>>>>>> refs/remotes/origin/master
}

//Getters
int get_n_quest(Day d){
    return d->n_quest;
}
int get_n_answer(Day d){
    return d->n_answer;
}
GHashTable* get_hash_quest(Day d){
    return d->hash_quest;
}
GHashTable* get_hash_answer(Day d){
    return d->hash_answer;
}
Date get_day_day(Day d){
    return createDate(get_day(d->day),get_month(d->day),get_year(d->day));
}
