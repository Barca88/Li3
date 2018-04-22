#include "interface.h"
#include "common.h"
#include "parser.h"
#include "users.h"
#include "quest.h"
#include "answer.h"
#include "date.h"
#include "tcd.h"
#include "day.h"
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

static gboolean load_rank_gslist(gpointer key,gpointer value,gpointer data){ 
    TAD_community com = (TAD_community)GPOINTER_TO_SIZE(data);
    set_rank_n_posts(com, g_slist_prepend(get_rank_n_posts(com),value));
    return FALSE;
}

static gint comp_nr_posts(gconstpointer a,gconstpointer b){
    if(get_nr_posts_user((User)a)>get_nr_posts_user((User)b)) 
        return -1;
    else if(get_nr_posts_user((User)a)<get_nr_posts_user((User)b))
        return 1;
    else 
        return 0;
}

/*Função resposável por carregar uma estrutura. */
TAD_community load(TAD_community com, char* dump_path){
    streamTags(get_hash_tags(com),dump_path);
    streamUsers(get_hash_users(com),dump_path);
    streamPosts(com,dump_path);
    
    //load lista ligada de utilizadores organizada por nº de posts.
    g_hash_table_foreach(get_hash_users(com),(GHFunc)load_rank_gslist,
                         GSIZE_TO_POINTER(com));
    //Ordenar lista de utilizadores pelos nr_posts. 
    set_rank_n_posts(com,
                     g_slist_sort(get_rank_n_posts(com), comp_nr_posts));

    return com;
}  

/** QUERY 1 */
STR_pair info_from_post(TAD_community com, long id){
    STR_pair sp = NULL; 
    char* title = NULL;
    char* name = NULL;
    User u;
    Answer a;
    Quest q = (Quest)g_hash_table_lookup(get_hash_quest_tcd(com), GSIZE_TO_POINTER(id));
    
    if(q){
        u = (User)g_hash_table_lookup(get_hash_users(com),
                GSIZE_TO_POINTER(get_owner_id_quest(q)));
        title = get_title_quest(q);
        name = get_displayname_user(u);
    }else{
        a = (Answer)g_hash_table_lookup(get_hash_answer_tcd(com),
             GSIZE_TO_POINTER(id)); 
        q = (Quest)g_hash_table_lookup(get_hash_quest_tcd(com), 
                GSIZE_TO_POINTER(get_parent_id_answer(a)));
        u = (User)g_hash_table_lookup(get_hash_users(com),
                GSIZE_TO_POINTER(get_owner_user_id_answer(a)));
        title = get_title_quest(q);
        name = get_displayname_user(u);
    }

    printf("Query 1 com id %ld: \n\n",id);
    printf("\tTitle: %s\n\tName: %s\n",title,name);
    printf("\n\n");

    return sp = create_str_pair(title,name);
}

/** QUERY 2 */
LONG_list top_most_active(TAD_community com, int N){
    LONG_list l = create_list(N);
    int i;
    User u;
    GSList *list = get_rank_n_posts(com);
    
    for(i=0;i<N;i++){
        u =(User) GPOINTER_TO_SIZE(list->data);
        set_list(l,i,get_id_user(u));
        list = list->next;
    }
    
    printf("Query 2 com %d elementos: \n\n",N);
    for(i=0;i<N;i++){
        printf("\tId do nº %d: %ld\n",i+1,get_list(l,i));
    }
    printf("\n\n");
    
    return l;
}

//----------------------------------------------------------------------

typedef struct aux3{
    Date begin;
    Date end;
    int nq;
    int na;
}* query3;

static gboolean count_posts(gpointer key,gpointer value,gpointer data){
    query3 ld = (query3)GPOINTER_TO_SIZE(data);
    Date b = ld->begin;
    Date e = ld->end;


    if ((date_compare(get_date_day(value),b)>0 && 
          date_compare(e,get_date_day(value))>0)){
            ld->nq += get_n_quest(value);
            ld->na += get_n_answer(value);
    }
    return FALSE;
}

/*static gint func_print(gpointer key, gpointer data){ 
    query3 ld = (query3)GPOINTER_TO_SIZE(data);
    Date b = ld->begin;
    Date e = ld->end;

    if ((date_compare(get_fst(key),b)>0 && 
          date_compare(e,get_fst(key))>0)){
         print_date(get_fst(key));
         ld->nq++;
         return -1;
    }else 
        return 0;
}*/

/** QUERY 3 */
LONG_pair total_posts(TAD_community com, Date begin, Date end){
    query3 ld = malloc(sizeof(struct aux3));
    ld->begin = begin;
    ld->end = end;
    ld->nq = 0;
    ld->na = 0;

    g_tree_foreach(get_tree_days(com),(GTraverseFunc)count_posts,
            GSIZE_TO_POINTER(ld));

//g_tree_search(get_tree_days(com),(GCompareFunc)func_print,GSIZE_TO_POINTER(ld));

    printf("Query 3: \n\n");
    printf("\tNumero de users: %d\n",g_hash_table_size(get_hash_users(com)));
    printf("\tNumero de respostas: %d\n",ld->na);
    printf("\tNumero de perguntas: %d\n",ld->nq);
    printf("\tNumero de posts: %d\n",ld->na+ld->nq);
    printf("\n\n");

    LONG_pair lp = create_long_pair(ld->nq,ld->na);
    return lp;
}

//----------------------------------------------------------------------

typedef struct aux4{
    Date begin;
    Date end;
    char* tag;
    GSList* list;
}* query4;

static void comp_tags(gpointer key,gpointer value,gpointer data){
    query4 ld = (query4)GPOINTER_TO_SIZE(data);
    char* t = ld->tag;
    GSList* l = ld->list;
    if (strstr(get_tags_quest(value),t)){
        ld->list = g_slist_prepend(l,value);    
    }
    
}

static gboolean iter_day(gpointer key,gpointer value,gpointer data){
    query4 ld = (query4)GPOINTER_TO_SIZE(data);
    Date b = ld->begin;
    Date e = ld->end;
    GHashTable* ht = get_hash_quest_day((Day)value);

    if ((date_compare(get_date_day(value),b)>0 && 
         date_compare(e,get_date_day(value))>0)){
         g_hash_table_foreach(ht,(GHFunc)comp_tags,data);
    }
    return FALSE;
}

static gint date_compare_aux(gconstpointer a,gconstpointer b){
    return date_compare(GSIZE_TO_POINTER(get_date_quest((Quest)a)),GSIZE_TO_POINTER(get_date_quest((Quest)b))); 
}

/*static void func_print(gpointer data,gpointer user){
    print_quest(data);
}*/
/** QUERY 4 */
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
    query4 ld = malloc(sizeof(struct aux4));
    ld->begin = begin;
    ld->end = end;
    ld->tag = tag;
    ld->list = NULL;

    g_tree_foreach(get_tree_days(com),(GTraverseFunc)iter_day,
                   GSIZE_TO_POINTER(ld));
    ld->list = g_slist_sort(ld->list,date_compare_aux);

   // g_slist_foreach (ld->list,func_print,NULL);

    int i,N = g_slist_length(ld->list);
    Quest q;
    LONG_list l = create_list(N);
    GSList* list = ld->list;
    for(i=0;i<N;i++){
        q = (Quest)GPOINTER_TO_SIZE(list->data);
        set_list(l,i,get_id_quest(q));
        list = list->next;
    }
    
    printf("Query 4 com %d elementos: \n\n",N);
    for(i=0;i<N;i++)
        printf("\tId do nº %d: %ld\n",i+1,get_list(l,i));
    printf("\n\n");

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
    quests = g_slist_sort(quests,quest_compare);
    answers = g_slist_sort(answers,answer_compare);
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

             dq = get_date_quest(q);
             da = get_date_answer(a);
             if(date_compare(dq,da) <= 0){
                 l[i] = get_id_quest(q);
                 quests = quests->next;
             }else {
                 l[i] = get_id_answer(a);
                 answers = answers->next;
             }
        }
    }
    printf("Query 5 com id %ld: \n\n",get_id_user(u));
    printf("\n\tAbout Me do USER: \n%s\n",am);
    for(i=0;i<10;i++)
        printf("\tId post mais recente nº %d: %ld\n",i+1,l[i]);
    printf("\n\n");
    USER r = create_user(am,l);
    return r;
}

//----------------------------------------------------------------------

typedef struct aux6{
    Date begin;
    Date end;
    GSList* list;
}* query6;

//Quest para a lista ligada.
static void to_list(gpointer key,gpointer value,gpointer data){
    query6 ld = (query6)GPOINTER_TO_SIZE(data);
    ld->list = g_slist_prepend(ld->list,value);    
}

//Função resposável pelo que fazer por cada dia.
static gboolean iter_day6(gpointer key,gpointer value,gpointer data){
    query6 ld = (query6)GPOINTER_TO_SIZE(data);
    Date b = ld->begin;
    Date e = ld->end;
    GHashTable* ha = get_hash_answer_day((Day)value);

    if ((date_compare(get_date_day(value),b)>0 && 
         date_compare(e,get_date_day(value))>0)){
         g_hash_table_foreach(ha,(GHFunc)to_list,data);
    }
    return FALSE;
}

//Função de comparação de score para ordenar uma lista ligada.
static gint score_compare(gconstpointer a,gconstpointer b){
     int f = get_score_answer((Answer)a);
     int s = get_score_answer((Answer)b);
     if(f<s) return 1;
     else if(f>s) return -1;
     else return 0;
}

/** QUERY 6 */
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
    query6 ld = malloc(sizeof(struct aux6));
    ld->begin = begin;
    ld->end = end;
    ld->list = NULL;

    g_tree_foreach(get_tree_days(com),(GTraverseFunc)iter_day6,
                   GSIZE_TO_POINTER(ld));
    ld->list = g_slist_sort(ld->list,score_compare);

    int i;
    Answer a;
    LONG_list l = create_list(N);
    GSList* list = ld->list;
    if(list){
        for(i=0;i<N;i++){
            a = (Answer)GPOINTER_TO_SIZE(list->data);
            set_list(l,i,get_id_answer(a));
            list = list->next;
        }

        printf("Query 6 com %d elementos: \n\n",N);
        for(i=0;i<N;i++)
            printf("\tId do nº %d: %ld\n",i+1,get_list(l,i));
    }else printf("Lista query6 vazia.\n");
    printf("\n\n");
    return l;
}

///----------------------------------------------------------------------

typedef struct aux7{
    Date begin;
    Date end;
    GSList* list;
}* query7;

static void to_list7(gpointer key,gpointer value,gpointer data){
    query7 ld = (query7)GPOINTER_TO_SIZE(data);
    ld->list = g_slist_prepend(ld->list,value);    
}

//Função resposável pelo que fazer por cada dia. 
static gboolean iter_day7(gpointer key,gpointer value,gpointer data){
    query7 ld = (query7)GPOINTER_TO_SIZE(data);
    Date b = ld->begin;
    Date e = ld->end;
    GHashTable* hq = get_hash_quest_day((Day)value);

    if ((date_compare(get_date_day(value),b)>0 && 
         date_compare(e,get_date_day(value))>0)){
         g_hash_table_foreach(hq,(GHFunc)to_list7,data);
    }
    return FALSE;
}

//Funcao de comparação de score para ordenar uma lista ligada.
static gint  answer_c_compare(gconstpointer a,gconstpointer b){
     int f = get_answer_c_quest((Quest)a);
     int s = get_answer_c_quest((Quest)b);
     if(f<s) return 1;
     else if(f>s) return -1;
     else return 0;
}

/** QUERY 7 */
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
    query7 ld = (query7)malloc(sizeof(struct aux7));
    ld->begin = begin;
    ld->end = end;
    ld->list = NULL;

    g_tree_foreach(get_tree_days(com),(GTraverseFunc)iter_day7,
                   GSIZE_TO_POINTER(ld));
    ld->list = g_slist_sort(ld->list,answer_c_compare);

    int i;
    Quest q;
    LONG_list l = create_list(N);
    GSList* list = ld->list;
    if(list){
        for(i=0;i<N;i++){
            q = (Quest)GPOINTER_TO_SIZE(list->data);
            set_list(l,i,get_id_quest(q));
            list = list->next;
        }

        printf("Query 7 com %d elementos: \n\n",N);
        for(i=0;i<N;i++)
            printf("\tId do nº %d: %ld\n",i+1,get_list(l,i));
    }else printf("Lista query7 vazia.\n");
    printf("\n\n");
    return l;
}
//----------------------------------------------------
typedef struct aux8{
    char* word;
    GSList* list;
}* query8;
static void iter_quest8(gpointer key, gpointer value, gpointer data){
    query8  aux = (query8) GPOINTER_TO_SIZE(data);
    char* w = aux->word;
    Quest q = (Quest) GPOINTER_TO_SIZE(value);
    char* t = get_title_quest(q);
    if(strstr(t,w)){
        aux->list = g_slist_prepend(aux->list,value);
    }
    free(t);
}
/** QUERY 10 */
LONG_list contains_word(TAD_community com, char* w, int N){
    query8 aux = (query8)malloc(sizeof(struct aux8));
    aux->word = mystrdup(w);
    aux->list = NULL;

    g_hash_table_foreach(get_hash_quest_tcd(com),(GHFunc)iter_quest8,aux);

    GSList *list = g_slist_sort(aux->list,quest_compare);
    LONG_list l = create_list(N);
    Quest q;
    int i;
    if(list){
        for(i=0;i<N;i++){
            q = (Quest)GPOINTER_TO_SIZE(list->data);
            set_list(l,i,get_id_quest(q));
            list = list->next;
        }
        printf("Query 8 title contains %s e com %d elementos: \n\n",w,N);
        for(i=0;i<N;i++)
            printf("\tId do nº %d: %ld\n",i+1,get_list(l,i));
    }else printf("Lista query8 vazia.\n");
    printf("\n\n");
    free(aux->word);
    free(aux);
    return l;
}

//---------------------------
typedef struct aux9{
    TAD_community com;
    GSList* l;
}* query9;
//adiciona o id da quest na hash
static void iter_quest9(gpointer data, gpointer user_data){
    if(data != NULL){
        GHashTable* h = (GHashTable*)GPOINTER_TO_SIZE(user_data);
        Quest q = (Quest)GPOINTER_TO_SIZE(data);
        g_hash_table_add(h,GSIZE_TO_POINTER(get_id_quest(q)));
    }
}
//adiciona o id da quest a qual a answer em causa responde
static void iter_answer9(gpointer data,gpointer user_data){
    if(data != NULL){
        GHashTable* h = (GHashTable*)GPOINTER_TO_SIZE(user_data);
        Answer a = (Answer)GPOINTER_TO_SIZE(data);
        g_hash_table_add(h,GSIZE_TO_POINTER(get_parent_id_answer(a)));
    }
}
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
static void iter_id_to_quest(gpointer data,gpointer user_data){
    query9 aux = (query9)GPOINTER_TO_SIZE(user_data);
    long id = (long)GPOINTER_TO_SIZE(data);
    GHashTable* q = get_hash_quest_tcd(aux->com);
    aux->l = g_slist_prepend(aux->l,
            g_hash_table_lookup(q,GSIZE_TO_POINTER(id))); 
}
/** QUERY 9 */
LONG_list both_participated(TAD_community com, long id1, long id2, int N){
    //Carregar a hash de users
    GHashTable* users = get_hash_users(com);

    //Carregar os users da hash table
    User a = (User) GPOINTER_TO_SIZE(g_hash_table_lookup(users, GSIZE_TO_POINTER(id1)));
    User b = (User) GPOINTER_TO_SIZE(g_hash_table_lookup(users, GSIZE_TO_POINTER(id2)));
    
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
    g_hash_table_foreach_remove(ha,(GHRFunc)iter_hash9,GSIZE_TO_POINTER(hb));
   
    //Cria a estrutura aux e inicializa a mesma.
    query9 aux = (query9)malloc(sizeof(struct aux9));
    aux->com = com;
    aux->l = NULL;

    //Transforma hash de ids em lista de quests.
    g_hash_table_foreach(ha, (GHFunc)iter_id_to_quest,
            GSIZE_TO_POINTER(aux));

    //Ordena a lista de quests.
    GSList* list = g_slist_sort(aux->l, quest_compare);

    LONG_list l = create_list(N);
    Quest q;
    int i;
    printf("Query 9 id1 = %ld, id2 = %ld e com %d elementos: \n\n",id1,id2,N);
    if(list){
        for(i=0;i<N;i++){
            q = (Quest)GPOINTER_TO_SIZE(list->data);
            set_list(l,i,get_id_quest(q));
            list = list->next;
        }
        for(i=0;i<N;i++)
            printf("\tId do nº %d: %ld\n",i+1,get_list(l,i));
    }else printf("Ups lista query 9 vazia.\n");
    printf("\n\n");
    free(aux);
    return l;
}

static void average_answer(Answer a,GHashTable* users){
    set_average_answer(a,(get_score_answer(a)*0.45)+(get_comment_count_answer(a)*0.1)
              +(get_score_answer(a)*0.2)+(get_reputation_user(g_hash_table_lookup(users,GSIZE_TO_POINTER(get_owner_user_id_answer(a))))));
}

static gint compare_average(gconstpointer a,gconstpointer b){
        float a1 = get_average_answer((Answer)a);
        float a2 = get_average_answer((Answer)b);
        if(a1<a2) return -1;
        else if(a1>a2) return 1;
        else return 0;
}

/** QUERY 10 */
long better_answer(TAD_community com, long id){
    GHashTable* hq = get_hash_quest_tcd(com);
    GSList *laux,*list = get_answer_list_quest((Quest)g_hash_table_lookup(hq,
                                          GSIZE_TO_POINTER(id))); 
   
    for(laux = list;laux->next;laux=laux->next)
        average_answer((Answer)laux->data,get_hash_users(com));
    list = g_slist_sort(list,compare_average);

    printf("Query 10 melhor resposta a pergunta %ld: \n\n\tMelhor resposta = %ld\n\n",id,get_id_answer(list->data));

    return get_id_answer(list->data);

}

/** QUERY 11 */
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end);

/** Função clean. */
TAD_community clean(TAD_community com);
