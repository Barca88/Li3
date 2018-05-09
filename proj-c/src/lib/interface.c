#include "interface.h"
#include "queriesdata.h"
#include "common.h"
#include "parser.h"
#include "users.h"
#include "quest.h"
#include "answer.h"
#include "date.h"
#include "tcd.h"
#include "day.h"
#include "tag.h"
#include "answer.h"
#include "quest.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <time.h>


/*Função responsável por inicializar a estrutura. */
TAD_community init()
{
    return init_tcd();
}

/*Função resposável por carregar uma estrutura. */
TAD_community load(TAD_community com, char* dump_path){
    //Carregar hashTable tags.
    streamTags(get_hash_tags(com),dump_path);
    //Carregar hashTable user.
    streamUsers(get_hash_users(com),dump_path);
    //Carregar as hashs quests e answers e a tree de days.
    streamPosts(com,dump_path);
    //load lista ligada de utilizadores organizada por nº de posts.
    sort_rank_tcd(com);
    sort_best_tcd(com);
    return com;
}

/** QUERY 1 */
STR_pair info_from_post(TAD_community com, long id){
    int x = isQuest(com,id);
    STR_pair r = get_info_post_tcd(com,x,id);
    return r;
}

/** QUERY 2 */
LONG_list top_most_active(TAD_community com, int N){
    LONG_list l = get_most_active_tcd(com,N);
    return l;
}

/** QUERY 3 */
LONG_pair total_posts(TAD_community com, Date begin, Date end){
    query3 ld = init_query3(begin,end);

    query3_tcd(com,ld);

    LONG_pair lp = create_long_pair(get_nq_3(ld),get_na_3(ld));
    free_3(ld);
    return lp;
}

/** QUERY 4 */
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
    query4 ld = init_query4(begin,end,tag);

    //Criar uma lista com todas a quets encontradas em cada dia.
    g_tree_foreach(get_tree_days(com),(GTraverseFunc)iter_tag_day,
                   GSIZE_TO_POINTER(ld));
    //Organizar a lista de quests com a tag.
    set_list_4(ld,g_slist_sort(get_list_4(ld),compare_quest));

    //Colocar o id das quests na long list.
    int i,N = g_slist_length(get_list_4(ld));
    Quest q;
    LONG_list l = create_list(N);
    GSList* list = get_list_4(ld);
    for(i=0;i<N;i++){
        q = (Quest)GPOINTER_TO_SIZE(list->data);
        set_list(l,i,get_id_quest(q));
        list = list->next;
    }

    free_4(ld);
    return l;
}

/** QUERY 5 */
USER get_user_info(TAD_community com, long id){
    //Carregar a hash de users.
    GHashTable* users = get_hash_users(com);
    //Carregar o user da hash table.
    User u = g_hash_table_lookup(users,GSIZE_TO_POINTER(id));
    //Carregar as hashs de quests e as answers do user.
    GSList* quests = get_quests_user(u);
    GSList* answers = get_answers_user(u);
    //Ordenar as listas por data.
    quests = g_slist_sort(quests,compare_quest);
    answers = g_slist_sort(answers,compare_answer);
    //Atualizar o utilizador com as listas ordenadas.
    set_quests_user(u,quests);
    set_answers_user(u,answers);

    long l[10];
    char* am = get_aboutme_user(u);

    int i;
    Date dq,da;
    Quest q;
    Answer a;

    for(i=0;i<10;i++){
        if(!quests && !answers)l[i] = 0;
        else if(!quests){
               a = (Answer)GPOINTER_TO_SIZE(answers->data);
               l[i] = get_id_answer(a);
               answers = answers->next;
           }
        else if(!answers){
               q = (Quest)GPOINTER_TO_SIZE(quests->data);
               l[i] = get_id_quest(q);
               quests = quests->next;
           }
        else{
             Quest q = (Quest) GPOINTER_TO_SIZE(quests->data);
             Answer a = (Answer) GPOINTER_TO_SIZE(answers->data);
             long idq,ida;

             dq = get_date_quest(q);
             da = get_date_answer(a);
             idq = get_id_quest(q);
             ida = get_id_answer(a);
             if(date_compare(dq,da) > 0){
                 l[i] = get_id_quest(q);
                 quests = quests->next;
             }else if(date_compare(dq,da) < 0){
                 l[i] = get_id_answer(a);
                 answers = answers->next;
             }else if(idq > ida){
                 l[i] = get_id_quest(q);
                 quests = quests->next;
             }else{
                 l[i] = get_id_answer(a);
                 answers = answers->next;
             }
        }
    }
    USER r = create_user(am,l);
    return r;
}

/** QUERY 6 */
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
    query6 ld = init_query6(begin,end);

    g_tree_foreach(get_tree_days(com),(GTraverseFunc)iter_vote_a_day,
                   GSIZE_TO_POINTER(ld));
    set_list_6(ld, g_slist_sort(get_list_6(ld),score_compare_answer));

    int i;
    Answer a;
    LONG_list l = create_list(N);
    GSList* list = get_list_6(ld);
    if(list){
        for(i=0;i<N;i++){
            a = (Answer)GPOINTER_TO_SIZE(list->data);
            set_list(l,i,get_id_answer(a));
            list = list->next;
        }
    }else printf("Lista query6 vazia.\n");
    free_6(ld);
    return l;
}

/** QUERY 7 */
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
    query7 ld = init_query7(begin,end);

    g_tree_foreach(get_tree_days(com),(GTraverseFunc)iter_day7,
                   GSIZE_TO_POINTER(ld));
    set_list_7(ld,g_slist_sort(get_list_7(ld),answer_c_compare_quest));

    int i;
    Quest q;
    LONG_list l = create_list(N);
    GSList* list = get_list_7(ld);
    if(list){
        for(i=0;i<N;i++){
            q = (Quest)GPOINTER_TO_SIZE(list->data);
            set_list(l,i,get_id_quest(q));
            list = list->next;
        }

    }else printf("Lista query7 vazia.\n");
    free_7(ld);
    return l;
}

/** QUERY 8 */
LONG_list contains_word(TAD_community com, char* w, int N){
    query8 aux = init_query8(w);
    g_hash_table_foreach(get_hash_quest_tcd(com),(GHFunc)comp_words_quest,aux);
    set_list_8(aux, g_slist_sort(get_list_8(aux),compare_quest));

    Quest q;
    int i,size = g_slist_length(get_list_8(aux));
    if( size < N) N = size;
    LONG_list l = create_list(N);

    for(i=0;i<N && get_list_8(aux) ;i++){
        q = (Quest)get_list_8(aux)->data;
        set_list(l,i,get_id_quest(q));
        set_list_8(aux, get_list_8(aux)->next);
    }

    free_8(aux);
    return l;
}

//------------------------------------------------------------------------------
//Função responsável por iterar a hash e retirar os elementos que não
//estão presentes em ambas hashs.
static gboolean iter_hash9(gpointer key, gpointer value, gpointer data){
    if(data != NULL){
        GHashTable* a = (GHashTable*)GPOINTER_TO_SIZE(data);
        if(g_hash_table_contains(a,key)) return FALSE;
    }
    return TRUE;
}
//povoa a lista da estrutura aux com quests
static void iter_id_to_quest(gpointer key,gpointer value,gpointer user_data){
    if(key != NULL){
        query9 aux = (query9)GPOINTER_TO_SIZE(user_data);
        GHashTable* q = get_hash_9(aux);
        GSList* list;
        if(g_hash_table_contains(q,key)){//evita a inserção de null na gslist se as quests não existirem na hash de Users
            list = g_slist_prepend(get_slist_9(aux), g_hash_table_lookup(q,key));
            set_slist_9(aux,list);
        }
    }
}

/** QUERY 9 */
LONG_list both_participated(TAD_community com, long id1, long id2, int N){
    //Carregar a hash de users
    GHashTable* users = get_hash_users(com);

    if(g_hash_table_contains(users,GSIZE_TO_POINTER(id1)) &&
            g_hash_table_contains(users,GSIZE_TO_POINTER(id2))){
        //Carregar os users da hash table
        User a = (User) GPOINTER_TO_SIZE(g_hash_table_lookup(users,
                GSIZE_TO_POINTER(id1)));
        User b = (User) GPOINTER_TO_SIZE(g_hash_table_lookup(users,
                GSIZE_TO_POINTER(id2)));

        //Criar Hashtables temporarias para ids de quests
        GHashTable* ha = g_hash_table_new(g_direct_hash, g_direct_equal);
        GHashTable* hb = g_hash_table_new(g_direct_hash, g_direct_equal);

        //Cria listas de quests e answer de cada user(serve para simplificar)
        GSList* questsa  = get_quests_user(a);
        GSList* questsb  = get_quests_user(b);
        GSList* answersa = get_answers_user(a);
        GSList* answersb = get_answers_user(b);

        //Carrgar as hash com longs (ids de quests).
        g_slist_foreach(questsa ,iter_quest9 ,GSIZE_TO_POINTER(ha));
        g_slist_foreach(questsb ,iter_quest9 ,GSIZE_TO_POINTER(hb));
        g_slist_foreach(answersa,iter_answer9,GSIZE_TO_POINTER(ha));
        g_slist_foreach(answersb,iter_answer9,GSIZE_TO_POINTER(hb));

        //HashTable remove os ids que não estão presentes nas participaçoes
        //de ambos users
        g_hash_table_foreach_remove(ha,
                (GHRFunc)iter_hash9,GSIZE_TO_POINTER(hb));

        //Cria a estrutura aux e inicializa a mesma.
        query9 aux = init_query9(get_hash_quest_tcd(com));

        //Transforma hash de ids em lista de quests.
        g_hash_table_foreach(ha, (GHFunc)iter_id_to_quest,
                GSIZE_TO_POINTER(aux));

        //Ordena a lista de quests.
        GSList* list = g_slist_sort(get_slist_9(aux),(GCompareFunc)compare_quest);

        //verifica o tamanho das resposta
        if(g_slist_length(list) < N) N = g_slist_length(list);
        LONG_list l = create_list(N);

        Quest q;
        int i;
        if(list){
            for(i=0;i<N && list->data !=NULL;i++){
                q = (Quest)GPOINTER_TO_SIZE(list->data);
                set_list(l,i,get_id_quest(q));
                list = list->next;
            }
        }else printf("\tUps lista query 9 vazia.\n");
        free_9(aux);
        g_hash_table_destroy(ha);
        g_hash_table_destroy(hb);

        return l;
    }
    return create_list(0);
}

/** QUERY 10 */
long better_answer(TAD_community com, long id){
    GHashTable* hq = get_hash_quest_tcd(com);
    GSList *laux,*list = get_answer_list_quest((Quest)g_hash_table_lookup(hq,
                                          GSIZE_TO_POINTER(id)));

    if(list){
        for(laux = list;laux->next;laux=laux->next)
            average_answer((Answer)laux->data,get_hash_users(com));
        list = g_slist_sort(list,compare_average_answer);

        return get_id_answer(list->data);
    }else{
        printf("Query 10 sem respostas.\n\n");
        return -2;
    }
}


/** QUERY 11 */
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
    //estrutura auxiliar.
    query11 aux = init_query11(com,begin,end);
    clean_tags(get_hash_tags(com));

    //Incrementar o numero de vezes que a tag foi usada
    load_n_posts_tags_tcd(com,N,aux);

    //Criar lista ligada ordenada por n_used.
    GSList* tllist = NULL;
    GSList** tlist = &tllist;
    g_hash_table_foreach(get_ht_11(aux),tag_list11,tlist);
    tllist = g_slist_sort(tllist,comp_n_used_tag);

    int i;
    if(g_slist_length(tllist)<N) N = g_slist_length(tllist);
    LONG_list l = create_list(N);
    Tag t;
    if(tllist){
        for(i=0;i<N && tllist->data != NULL;i++){
             t = (Tag)GPOINTER_TO_SIZE(tllist->data);
            set_list(l,i,get_id_tag(t));
            tllist = tllist->next;
        }
    }else printf("\tUps lista query 11 vazia.\n");
    return l;
}

/** Função clean. */
TAD_community clean(TAD_community com){
    free_tcd(com);
    return com;
}
