#include "interface.h"
#include "parser.h"
#include "users.h"
#include "post.h"
#include "date.h"
#include "tcd.h"
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <time.h>

TAD_community init()
{
    return init_tcd();
}

// query 0
TAD_community load(TAD_community com, char* dump_path){
    streamUsers(get_hash_users(com),dump_path);
    streamPosts(com,dump_path);
   return com;
}  

// query 1
STR_pair info_from_post(TAD_community com, long id){

    STR_pair sp; 
    char* title, *name;
    ptr_user a;
    ptr_post p = (ptr_post)g_hash_table_lookup(get_hash_posts(com),
            GSIZE_TO_POINTER(id));

    if(get_post_type_id(p)==1){
        a = (ptr_user)g_hash_table_lookup(get_hash_users(com),
                GSIZE_TO_POINTER(get_owner_user_id(p)));
        title = get_title(p);
        name = get_displayname_user(a);
    }else if(get_post_type_id(p) == 2){
        p = (ptr_post)g_hash_table_lookup(get_hash_posts(com), 
                GSIZE_TO_POINTER(get_parent_id(p)));
        a = (ptr_user)g_hash_table_lookup(get_hash_users(com),
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
    /*GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, com->hashPosts);
   
    while(g_hash_table_iter_next(&iter, &key, &value) && N>0){
        //TODO struct ordenada por data
    }*/
    return l;
}
        

// query 9
LONG_list both_participated(TAD_community com, long id1, long id2, int N);

// query 10
long better_answer(TAD_community com, long id);

// query 11
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end);

TAD_community clean(TAD_community com);
