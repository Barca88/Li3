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
void add_quest_day(Day d, Quest q){
    GHashTable* hq = d->hash_quest;
    g_hash_table_insert(hq,GSIZE_TO_POINTER(get_id_quest(q)),q);
    (d->n_quest)++;
   // print_quest(q);
}
void add_answer_day(Day d, Answer a){
    GHashTable* ha = d->hash_answer;
    g_hash_table_insert(ha,GSIZE_TO_POINTER(get_id_answer(a)),a);
    (d->n_answer)++;
}

//Getters
int get_n_quest(Day d){
    return d->n_quest;
}
int get_n_answer(Day d){
    return d->n_answer;
}
GHashTable* get_hash_quest_day_day(Day d){
    return d->hash_quest;
}
GHashTable* get_hash_answer_day_day(Day d){
    return d->hash_answer;
}
Date get_date_day(Day d){
    return createDate(get_day(d->day),get_month(d->day),get_year(d->day));
}

//Imprimir o conteudo da data.
void print_day(Day day){
    if(day != NULL) {
        print_date(day->day);
        printf("Day:\n\n\tN_quest: %d\n\tN_answer: %d\n\t",
                day->n_quest,day->n_answer); 
        printf("\n\n"); 
    }
}

