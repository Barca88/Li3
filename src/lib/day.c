#include "day.h"

struct day {
    Date day;
    int n_p;
    int n_r;
    GHashTable* hash_p;
    GHashTable* hash_r;
};

Day init_day(Date day){
    Day d = malloc(sizeof(struct day));
    d -> day = day;
    d -> n_p = 0;
    d -> n_r = 0;
    d -> hash_p = g_hash_table_new(g_direct_hash, g_direct_equal);
    d -> hash_r = g_hash_table_new(g_direct_hash, g_direct_equal);
    return d;
}

//Métodos
void add_quest_day(Day d, Quest q){
    GHashTable* hq = d->hash_p;
    g_hash_table_insert(hq,GSIZE_TO_POINTER(get_id_quest(q)),q);
    (d->n_p)++;
}
void add_answer_day(Day d, Answer a){
    GHashTable* ha = d->hash_r;
    g_hash_table_insert(ha,GSIZE_TO_POINTER(get_id_answer(a)),a);
    (d->n_r)++;
}

//Getters
int get_n_p(Day d){
    return d->n_p;
}
int get_n_r(Day d){
    return d->n_r;
}
GHashTable* get_hash_p(Day d){
    return d->hash_p;
}
GHashTable* get_hash_r(Day d){
    return d->hash_r;
}
Date get_day_day(Day d){
    return createDate(get_day(d->day),get_month(d->day),get_year(d->day));
}
