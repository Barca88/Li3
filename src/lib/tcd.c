#include "tcd.h"

struct TCD_community{
    GHashTable* hashUsers;
    GHashTable* hashPosts;
    GTree* treePosts;
}; 

TAD_community init_tcd(){
    TAD_community n = malloc(sizeof(struct TCD_community));

    n->hashUsers = g_hash_table_new(g_direct_hash, g_direct_equal);
    n->hashPosts = g_hash_table_new(g_direct_hash, g_direct_equal);
    n->treePosts = g_tree_new((GCompareFunc)date_pair_compare); 

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


