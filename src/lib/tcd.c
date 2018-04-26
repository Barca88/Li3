#include "tcd.h"

/* Definição da estrutura dos tcd (TCD_community). */
struct TCD_community{
    GHashTable* hashTags; /* Hash das tags. */
    GHashTable* hashUsers; /* Hash dos users. */
    GHashTable* hashQuests; /* Hash das quest. */
    GHashTable* hashAnswers; /* Hash das answers. */
    GTree* treeDays; /* Tree dos days. */
    GSList* rankNrPosts; /* Lista com o nr posts. */
}; 

/* Função que inicia a estrutura tcd. */
TAD_community init_tcd(){
    TAD_community n = malloc(sizeof(struct TCD_community));

    n->hashTags = g_hash_table_new(g_str_hash, g_str_equal);
    n->hashUsers = g_hash_table_new(g_direct_hash, g_direct_equal);
    n->hashQuests = g_hash_table_new(g_direct_hash, g_direct_equal);
    n->hashAnswers = g_hash_table_new(g_direct_hash, g_direct_equal);
    n->treeDays = g_tree_new((GCompareFunc)date_compare); 
    n->rankNrPosts = NULL;
    return n;
}

/* Gets (Obter valor das variaveis da estrutura) */
GHashTable* get_hash_tags(TAD_community root){
    return root->hashTags;
}
GHashTable* get_hash_users(TAD_community root){
    return root->hashUsers;
}
GHashTable* get_hash_quest_tcd(TAD_community root){
    return root->hashQuests;
}
GHashTable* get_hash_answer_tcd(TAD_community root){
    return root->hashAnswers;
}
GTree* get_tree_days(TAD_community root){
    return root->treeDays;
}
GSList* get_rank_n_posts(TAD_community root){
    return root->rankNrPosts;
}

void set_rank_n_posts(TAD_community root, GSList *new){
    root->rankNrPosts = new;
}

gboolean load_rank_gslist_tcd(gpointer key,gpointer value,gpointer data){
    TAD_community com = (TAD_community)GPOINTER_TO_SIZE(data);
    set_rank_n_posts(com, g_slist_prepend(get_rank_n_posts(com),value));
    return FALSE;
}

/* Apaga a tcd dando free na memoria alocada. */
void free_tcd(TAD_community root); //TODO
