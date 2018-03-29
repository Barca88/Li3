#include "interface.h"
#include "parser.h"
#include "nodeUser.h"
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>

struct TCD_community{
    GHashTable* hashUsers;
    GTree* treePosts;
}; 

static int compare_long(gconstpointer p1, gconstpointer p2) {
    long i1 = GPOINTER_TO_SIZE(p1);
    long i2 = GPOINTER_TO_SIZE(p2);
    return i1 == i2 ? 0 : i1 > i2 ? 1 : -1;
}

TAD_community init()
{
    TAD_community n = malloc(sizeof(struct TCD_community));
    n->hashUsers = g_hash_table_new(g_direct_hash, g_direct_equal);
    n->treePosts = g_tree_new((GCompareFunc)compare_long); 
    return n;
}


// query 0
TAD_community load(TAD_community com, char* dump_path){

    streamUsers(com->hashUsers,dump_path);
    streamPosts(com->treePosts,dump_path);
   return com;
}  

// query 1
STR_pair info_from_post(TAD_community com, long id){
    printf("------------------------------------------------------------------\n");
    gint64 id2 = 11;
    ptr_user a = (ptr_user)g_hash_table_lookup(com->hashUsers,GSIZE_TO_POINTER(id2));
    print_user(a);
    return NULL;
}

// query 2
LONG_list top_most_active(TAD_community com, int N);

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
LONG_list contains_word(TAD_community com, char* word, int N);

// query 9
LONG_list both_participated(TAD_community com, long id1, long id2, int N);

// query 10
long better_answer(TAD_community com, long id);

// query 11
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end);

TAD_community clean(TAD_community com);
