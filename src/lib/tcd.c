#include "tcd.h"

struct TCD_community{
    GHashTable* hashUsers;
    GHashTable* hashQuests;
    GHashTable* hashAnswers;
    GTree* treeDays;
    GSList* rankNPosts;
}; 

TAD_community init_tcd(){
    TAD_community n = malloc(sizeof(struct TCD_community));

    n->hashUsers = g_hash_table_new(g_direct_hash, g_direct_equal);
    n->hashQuests = g_hash_table_new(g_direct_hash, g_direct_equal);
    n->hashAnswers = g_hash_table_new(g_direct_hash, g_direct_equal);
    n->treeDays = g_tree_new((GCompareFunc)date_compare); 
    n->rankNPosts = NULL;
    return n;
}

GHashTable* get_hash_users(TAD_community root){
    return root->hashUsers;
}
GHashTable* get_hash_quests(TAD_community root){
    return root->hashQuests;
}
GHashTable* get_hash_answers(TAD_community root){
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

 void free_tcd(TAD_community root); //TODO
