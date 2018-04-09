#include "interface.h"
#include "parser.h"
#include "nodeUser.h"
#include "post.h"
#include "date.h"
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <time.h>

struct TCD_community{
    GHashTable* hashUsers;
    GHashTable* hashPosts;
    GTree* treePosts;
    GSList* sortUsers;
}; 
/*
GHashTable* get_hash_users(TDA_community root){
    return root->hashUser;
}

GHashTable* get_hash_post(TDA_community root){
    return root->hashUser;
}*/

TAD_community init()
{
    TAD_community n = malloc(sizeof(struct TCD_community));
    n->hashUsers = g_hash_table_new(g_direct_hash, g_direct_equal);
    n->hashPosts = g_hash_table_new(g_direct_hash, g_direct_equal);
    n->treePosts = g_tree_new((GCompareFunc)date_compare); 
    n->sortUsers = g_slist_alloc();
    return n;
}

// query 0
TAD_community load(TAD_community com, char* dump_path){
    streamUsers(com->hashUsers,dump_path);
    streamPosts(com->treePosts,com->hashPosts,com->hashUsers,dump_path);
   return com;
}  

// query 1
STR_pair info_from_post(TAD_community com, long id){

    STR_pair sp; 
    char* title, *name;
    ptr_post p = (ptr_post)g_hash_table_lookup(com->hashPosts,GSIZE_TO_POINTER(id));
    ptr_user a;

    if(get_post_type_id(p)==1){
        a = (ptr_user)g_hash_table_lookup(com->hashUsers,
                GSIZE_TO_POINTER(get_owner_user_id(p)));
        title = get_title(p);
        name = get_displayname_user(a);
    }else if(get_post_type_id(p) == 2){
        p = (ptr_post)g_hash_table_lookup(com->hashPosts, 
                GSIZE_TO_POINTER(get_parent_id(p)));
        a = (ptr_user)g_hash_table_lookup(com->hashUsers,
                GSIZE_TO_POINTER(get_owner_user_id(p)));
        title = get_title(p);
        name = get_displayname_user(a);
    }

    return sp =  create_str_pair(title,name);
}

// query 2
/*
LONG_list top_most_active(TAD_community com, int N){
    com->sortUsers = g_slist_insert_sorted(com->sortUsers,gpointer data,GCompareFunc func);
}
*/
// query 3
LONG_pair total_posts(TAD_community com, Date begin, Date end);

// query 4
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end);

// query 5
USER get_user_info(TAD_community com, long id);

// query 6
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end);

// query 7
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end);

// query 8
LONG_list contains_word(TAD_community com, char* word, int N){
    LONG_list l = create_list(N);
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, com->hashPosts);
   
    while(g_hash_table_iter_next(&iter, &key, &value) && N>0){
        //TODO struct ordenada por data
    }
    return l;
}
        

// query 9
LONG_list both_participated(TAD_community com, long id1, long id2, int N);

// query 10
long better_answer(TAD_community com, long id);

// query 11
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end);

TAD_community clean(TAD_community com);
