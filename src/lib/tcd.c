#include "tcd.h"
#include "tag.h"
#include "users.h"
#include "quest.h"
#include "answer.h"
#include "day.h"
#include "tag.h"

/* Definição da estrutura dos tcd (TCD_community). */
struct TCD_community{
    GHashTable* hashTags;    /* Hash das tags.     */
    GHashTable* hashUsers;   /* Hash dos users.    */
    GHashTable* hashQuests;  /* Hash das quest.    */
    GHashTable* hashAnswers; /* Hash das answers.  */
    GTree* treeDays;         /* Tree dos days.     */
    GSList* rankNPosts;      /* Lista com N posts. */
};

/* Função que inicia a estrutura tcd. */
TAD_community init_tcd(){
    TAD_community n = malloc(sizeof(struct TCD_community));

    n->hashTags = g_hash_table_new_full(g_direct_hash, g_direct_equal,NULL,free_g_tag);
    n->hashUsers = g_hash_table_new_full(g_direct_hash, g_direct_equal,NULL,free_g_users);
    n->hashQuests = g_hash_table_new_full(g_direct_hash, g_direct_equal,NULL,free_g_quest);
    n->hashAnswers = g_hash_table_new_full(g_direct_hash, g_direct_equal,NULL,free_g_answer);
    n->treeDays = g_tree_new_full((GCompareDataFunc)date_compare,NULL,free_g_date,free_g_day); 
    n->rankNPosts = NULL;
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
    return root->rankNPosts;
}

void set_rank_n_posts(TAD_community root, GSList *new){
    root->rankNPosts = new;
}

/* Apaga a tcd dando free na memoria alocada. */
void free_tcd(TAD_community root){
    g_hash_table_destroy(root->hashTags);
    g_hash_table_destroy(root->hashUsers);
    g_hash_table_destroy(root->hashQuests);
    g_hash_table_destroy(root->hashAnswers);
    g_tree_destroy(root->treeDays);
    g_slist_free(root->rankNPosts);
}
