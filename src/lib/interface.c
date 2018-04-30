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
    g_hash_table_foreach(get_hash_users(com),(GHFunc)load_rank_gslist_tcd,
                         GSIZE_TO_POINTER(com));
    //Ordenar lista de utilizadores pelos nr_posts.
    set_rank_n_posts(com,g_slist_sort(get_rank_n_posts(com),comp_nr_posts_user));

    return com;
}

/** QUERY 1 */
STR_pair info_from_post(TAD_community com, long id){
    STR_pair sp = NULL;
    char* title = NULL;
    char* name = NULL;
    User u;
    Answer a;
    Quest q = (Quest)g_hash_table_lookup(get_hash_quest_tcd(com),
                                         GSIZE_TO_POINTER(id));

    //Se quest processa, se answer processa a quest associada.
    if(q){
        u = (User)g_hash_table_lookup(get_hash_users(com),
                GSIZE_TO_POINTER(get_owner_id_quest(q)));
        title = get_title_quest(q);
        name = get_displayname_user(u);
    }else{
        a = (Answer)g_hash_table_lookup(get_hash_answer_tcd(com),
             GSIZE_TO_POINTER(id));
        if(a){
            q = (Quest)g_hash_table_lookup(get_hash_quest_tcd(com),
                GSIZE_TO_POINTER(get_parent_id_answer(a)));
            u = (User)g_hash_table_lookup(get_hash_users(com),
                GSIZE_TO_POINTER(get_owner_user_id_answer(a)));
            title = get_title_quest(q);
            name = get_displayname_user(u);
        }
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

    //Inserir N users da linked list na long list.
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

/** QUERY 3 */
LONG_pair total_posts(TAD_community com, Date begin, Date end){
    query3 ld = init_query3(begin,end);

    g_tree_foreach(get_tree_days(com),(GTraverseFunc)count_posts_day,
            GSIZE_TO_POINTER(ld));

    printf("Query 3: \n\n");
    printf("\tNumero de users: %d\n",g_hash_table_size(get_hash_users(com)));
    printf("\tNumero de respostas: %d\n",get_na_3(ld));
    printf("\tNumero de perguntas: %d\n",get_nq_3(ld));
    printf("\tNumero de posts: %d\n",get_na_3(ld)+get_nq_3(ld));
    printf("\n\n");

    LONG_pair lp = create_long_pair(get_nq_3(ld),get_na_3(ld));
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

             dq = get_date_quest(q);
             da = get_date_answer(a);
             if(date_compare(dq,da) > 0){
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

        printf("Query 6 com %d elementos: \n\n",N);
        for(i=0;i<N;i++)
            printf("\tId do nº %d: %ld\n",i+1,get_list(l,i));
    }else printf("Lista query6 vazia.\n");
    printf("\n\n");
    return l;
}

//----------------------------------------------------------------------

typedef  struct aux7{
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

    if ((date_compare(get_date_day(value),b)>=0 &&
         date_compare(e,get_date_day(value))>=0)){
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
    char* t = get_title_quest((Quest)value);
    if(strstr(t,w)){
        aux->list = g_slist_prepend(aux->list,value);
    }
    free(t);
}
/** QUERY 8 */
LONG_list contains_word(TAD_community com, char* w, int N){
    query8 aux = (query8)malloc(sizeof(struct aux8));
    aux->word = mystrdup(w);
    aux->list = NULL;

    g_hash_table_foreach(get_hash_quest_tcd(com),(GHFunc)iter_quest8,aux);
    aux->list = g_slist_sort(aux->list,compare_quest);

    LONG_list l = create_list(N);
    Quest q;
    int i;
    if(aux->list){
        for(i=0;i<N;i++){
            q = (Quest)GPOINTER_TO_SIZE(aux->list->data);
            set_list(l,i,get_id_quest(q));
            aux->list = aux->list->next;
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

        //verifica o size das resposta
        int size;
        (g_slist_length(list) < N) ? size = g_slist_length(list) : (size = N);

        LONG_list l = create_list(size);

        Quest q;
        int i;
        printf("Query 9 id1 = %ld, id2 = %ld e com %d elementos: \n\n",id1,id2,size);
        if(list){
            for(i=0;i<size && list->data !=NULL;i++){
                q = (Quest)GPOINTER_TO_SIZE(list->data);
                set_list(l,i,get_id_quest(q));
                list = list->next;
            }
            for(i=0;i<size;i++)
                printf("\tId do nº %d: %ld\n",i+1,get_list(l,i));
        }else printf("\tUps lista query 9 vazia.\n");
        printf("\n\n");
        free_9(aux);
        g_hash_table_destroy(ha);
        g_hash_table_destroy(hb);

        return l;
    }
    printf("\nQuerie 9 users com estes ids não existem em simultaneo\n\tid1: %ld\n\tid2: %ld\n\n",id1, id2);
    return create_list(0);
}

//----------------------------------------------------------------------------------

static void average_answer(Answer a,GHashTable* users){
    set_average_answer(a,(get_score_answer(a)*0.65)+
    (get_comment_count_answer(a)*0.1)+
    (get_reputation_user(g_hash_table_lookup(users,GSIZE_TO_POINTER(get_owner_user_id_answer(a))))*0.25));
}

static gint compare_average(gconstpointer a,gconstpointer b){
    float a1 = get_average_answer((Answer)a);
    float a2 = get_average_answer((Answer)b);
    if(a1<a2) return -1;
    else if(a1>a2) return 1;
    return 0;
}

/** QUERY 10 */
long better_answer(TAD_community com, long id){
    GHashTable* hq = get_hash_quest_tcd(com);
    GSList *laux,*list = get_answer_list_quest((Quest)g_hash_table_lookup(hq,
                                          GSIZE_TO_POINTER(id)));

    if(list){
        for(laux = list;laux->next;laux=laux->next)
            average_answer((Answer)laux->data,get_hash_users(com));
        list = g_slist_sort(list,compare_average);
        printf("Query 10 melhor resposta a pergunta %ld: \n\n\tMelhor resposta = %ld\n\n",id,get_id_answer(list->data));
        return get_id_answer(list->data);
    }else{
        printf("Query 10 sem respostas.\n\n");
        return -2;
    }
}


/** QUERY 11 */
 //----------------------------------------------------------------------------------
typedef struct aux11{
    GHashTable* ht;
    Date begin;
    Date end;
}* query11;

static void load_n_used(gpointer value,gpointer data){
    query11 aux = (query11)GPOINTER_TO_SIZE(data);
    Date b = aux->begin;
    Date e = aux->end;
    char* auxt = NULL;

    if ((date_compare(get_date_quest(value),b)>=0 &&
         date_compare(e,get_date_quest(value))>=0)){
        auxt = get_tags_quest(value);
        auxt += 1;
        auxt[strlen(auxt)-1] = '\0';
        set_tags_quest(value,auxt);
        char *p;
        p = strtok (auxt,"><");
        while (p) {
            inc_n_used(g_hash_table_lookup(aux->ht,p));
            p = strtok (NULL, "><");
        }
    }
}

static int comp_reput(gconstpointer a,gconstpointer b){
     int r1 = get_reputation_user((User)a);
     int r2 = get_reputation_user((User)b);
    if(r1<r2) return 1;
    else if(r1>r2) return -1;
    else return 0;
}

static int comp_n_used(gconstpointer a,gconstpointer b){
     int r1 = get_n_used((Tag)a);
     int r2 = get_n_used((Tag)b);
    if(r1<r2) return 1;
    else if(r1>r2) return -1;
    else return 0;
}

static void create_list11(gpointer key,gpointer value,gpointer data){
    GSList** d = (GSList**)GPOINTER_TO_SIZE(data);
    *d = g_slist_prepend(*d,value);
}

static void tag_list11(gpointer key,gpointer value,gpointer data){
    GSList** d = (GSList**)GPOINTER_TO_SIZE(data);
    if (get_n_used(value)>0)
        *d = g_slist_prepend(*d,value);
}

// query 11
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
    GHashTable* hu = get_hash_users(com);
    GSList* llist = NULL;
    GSList** list = &llist;


    //Inserir e ordenar numa lista ligada os user por reputacao.
    g_hash_table_foreach(hu,create_list11,list);
    llist = g_slist_sort(llist,comp_reput);

    query11 aux = malloc(sizeof(struct aux11));
    aux->ht = get_hash_tags(com);
    aux->begin = begin;
    aux->end = end;
    int c = N;

    //Incrementar o numero de vezes que a tag foi usada
    for(;llist && c;llist = (llist)->next,c--){
        g_slist_foreach(get_quests_user(llist->data),load_n_used,aux);
    }

    //Criar lista ligada ordenada por n_used.
    GSList* tllist = NULL;
    GSList** tlist = &tllist;
    g_hash_table_foreach(aux->ht,tag_list11,tlist);
    tllist = g_slist_sort(tllist,comp_n_used);

    int size,i;
    if(g_slist_length(tllist)<N) size = g_slist_length(tllist);
    else size = N;

    LONG_list l = create_list(size);
    Tag t;
    printf("Query 11\n");
    if(tllist){
        for(i=0;i<size && tllist->data != NULL;i++){
             t = (Tag)GPOINTER_TO_SIZE(tllist->data);
            set_list(l,i,get_id_tag(t));
            tllist = tllist->next;
        }
        for(i=0;i<size;i++)
            printf("\tId da tag nº %d: %ld\n",i+1,get_list(l,i));
    }else printf("\tUps lista query 11 vazia.\n");
    return l;
}

/** Função clean. */
TAD_community clean(TAD_community com){
    free_tcd(com);
    return com;
}
