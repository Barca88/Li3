#include "interface.h"
#include "parser.h"
#include "nodeUser.h"
#include <stdlib.h>
#include <stdio.h>
struct root{
    s_ptr_users hashUsers;
}; 

TAD_community init()
{
    TAD_community n = malloc(sizeof(struct root));
    n->hashUsers  = g_hash_table_new(g_int64_hash, g_int64_equal);
    return n;
}

// query 0
TAD_community load(TAD_community com, char* dump_path){
    //streamUsers(com->hashUsers,dump_path);

 /*   printf("------------------------------------------------------------------\n");
    long aux_id = 1;
    if(aux_id!=-1){ 
    ptr_user a = (ptr_user)g_hash_table_lookup(com->hashUsers,&aux_id);
    print_user(a);}*/

   return com;
}  

// query 1
STR_pair info_from_post(TAD_community com, int id){
        //ptr_user a = g_hash_table_lookup(com->hashUsers,(void*) &id);
        //print_user(a);
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
LONG_list better_answer(TAD_community com, int id);

// query 11
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end);

TAD_community clean(TAD_community com);
