#include "tcd.h"

struct TCD_community{
    GHashTable* hashUsers;
    GHashTable* hashPosts;
    GTree* treePosts;
    GSList* rankNPosts;
}; 

TAD_community init_tcd(){
    TAD_community n = malloc(sizeof(struct TCD_community));

    n->hashUsers = g_hash_table_new(g_direct_hash, g_direct_equal);
    n->hashPosts = g_hash_table_new(g_direct_hash, g_direct_equal);
    n->treePosts = g_tree_new((GCompareFunc)date_pair_compare); 
    n->rankNPosts = NULL;
    return n;
}

GHashTable* get_hash_users(TAD_community root){
    return root->hashUsers;
}

GHashTable* get_hash_posts(TAD_community root){
    return root->hashPosts;
}

GTree* get_tree_posts(TAD_community root){
    return root->treePosts;
}
void set_rank_n_posts(TAD_community root, GSList *new){
    root->rankNPosts = new;
}
GSList* get_rank_n_posts(TAD_community root){
    return root->rankNPosts;
}

//TODO free_tcd(TAD_community root)
