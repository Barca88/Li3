#include "day.h"

/* Definição da estrutura dos dias (day). */
struct day {
    Date day; /* Data de um dia. */
    int n_quest; /* Nº de quest num dia. */
    int n_answer; /* Nº de answer num dia. */
    GHashTable* hash_quest; /* Hash com as quest. */
    GHashTable* hash_answer; /* Hash com as answer. */
};

/* Função que inicia a estrutura Day. */
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
    g_hash_table_insert(d->hash_quest,GSIZE_TO_POINTER(get_id_quest(q)),q);
    (d->n_quest)++;
   // print_quest(q);
}
void add_answer_day(Day d, Answer a){
    g_hash_table_insert(d->hash_answer,GSIZE_TO_POINTER(get_id_answer(a)),a);
    (d->n_answer)++;
}

/* Gets (Obter valor das variaveis da estrutura) */
int get_n_quest(Day d){
    return d->n_quest;
}
int get_n_answer(Day d){
    return d->n_answer;
}
GHashTable* get_hash_quest_day(Day d){
    return d->hash_quest;
}
GHashTable* get_hash_answer_day(Day d){
    return d->hash_answer;
}
Date get_date_day(Day d){
    return createDate(get_day(d->day),get_month(d->day),get_year(d->day));
}

gboolean count_posts_day(gpointer key,gpointer value,gpointer data){
    query3 ld = (query3)GPOINTER_TO_SIZE(data);
    Date b = get_begin_3(ld);
    Date e = get_end_3(ld);

    if (between_dates(b,e,get_date_day(value))){
            inc_nq_3(ld,get_n_quest(value));
            inc_na_3(ld,get_n_answer(value));
    }
    return FALSE;
}

gboolean iter_tag_day(gpointer key,gpointer value,gpointer data){
    query4 ld = (query4)GPOINTER_TO_SIZE(data);
    Date b = get_begin_4(ld);
    Date e = get_end_4(ld);
    GHashTable* ht = get_hash_quest_day((Day)value);

    if (between_dates(b,e,get_date_day(value))){
         g_hash_table_foreach(ht,(GHFunc)comp_tags_quest,data);
    }
    return FALSE;
}

//Função resposável pelo que fazer por cada dia.
 gboolean iter_vote_a_day(gpointer key,gpointer value,gpointer data){
    query6 ld = (query6)GPOINTER_TO_SIZE(data);
    Date b = get_begin_6(ld);
    Date e = get_end_6(ld);
    GHashTable* ha = get_hash_answer_day((Day)value);

    if ((date_compare(get_date_day(value),b)>=0 &&
    date_compare(e,get_date_day(value))>=0)){
    g_hash_table_foreach(ha,(GHFunc)to_list_answer,data);
    }
   return FALSE;
}

void print_aux(gpointer key,gpointer value,gpointer data){
    Quest q = (Quest)GPOINTER_TO_SIZE(value);
    print_quest(q);
}

/* Imprimir o conteúdo de uma data. */
void print_day(Day day){
    if(day != NULL) {
        print_date(day->day);
        printf("Day:\n\n\n\tN_quest: %d\n\tN_answer: %d\n\t",
                day->n_quest,day->n_answer);
        g_hash_table_foreach(day->hash_quest,(GHFunc)print_aux,NULL);
        printf("\n\n");
    }
}
/*liberta a memoria alocada para o Day d*/
void free_day(Day d){
    free_date(d->day);
    g_hash_table_destroy(d->hash_quest);
    g_hash_table_destroy(d->hash_answer);
    free(d);
}
void free_g_day(gpointer g){
    Day d = (Day)GPOINTER_TO_SIZE(g);
    free_day(d);
    g_free(g);
}
