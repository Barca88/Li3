#include "tcd.h"
#include "tag.h"
#include "users.h"
#include "quest.h"
#include "answer.h"
#include "day.h"
#include "queriesdata.h"

/* Definição da estrutura dos tcd (TCD_community). */
struct TCD_community{
    GHashTable* hashTags;    /* Hash das tags.     */
    GHashTable* hashUsers;   /* Hash dos users.    */
    GHashTable* hashQuests;  /* Hash das quest.    */
    GHashTable* hashAnswers; /* Hash das answers.  */
    GTree* treeDays;         /* Tree dos days.     */
    GSList* rankNPosts;      /* Lista numero de posts. */
    GSList* bestUsers;       /* Lista reputacao users. */
};

/* Função que inicia a estrutura tcd. */
TAD_community init_tcd(){
    TAD_community n = malloc(sizeof(struct TCD_community));

    n->hashTags = g_hash_table_new_full(g_str_hash, g_str_equal, NULL,
        free_g_tag);
    n->hashUsers = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL,
        free_g_users);
    n->hashQuests = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL,
        free_g_quest);
    n->hashAnswers = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL,
        free_g_answer);
    n->treeDays = g_tree_new_full((GCompareDataFunc)date_compare, NULL, NULL,
        (GDestroyNotify)free_g_day);
    n->rankNPosts = NULL;
    n->bestUsers = NULL;
    return n;
}

/* Gets (Obter valor das variaveis da estrutura) */
GHashTable* get_hash_tags(TAD_community root){
    return root->hashTags;
}
GHashTable* get_hash_users(TAD_community root){
    return root->hashUsers;
}
GHashTable* get_hash_quest_tcd(TAD_community root){
    return root->hashQuests;
}
GHashTable* get_hash_answer_tcd(TAD_community root){
    return root->hashAnswers;
}
GTree* get_tree_days(TAD_community root){
    return root->treeDays;
}
GSList* get_rank_n_posts(TAD_community root){
    return root->rankNPosts;
}
GSList* get_best_user_tcd(TAD_community root){
    return root->bestUsers;
}

void set_rank_n_posts(TAD_community root, GSList *new){
    root->rankNPosts = new;
}
void set_best_user_tcd(TAD_community root, GSList *new){
    root->bestUsers = new;
}

gboolean load_rank_gslist_tcd(gpointer key,gpointer value,gpointer data){
    TAD_community com = (TAD_community)GPOINTER_TO_SIZE(data);
    set_rank_n_posts(com, g_slist_prepend(get_rank_n_posts(com),value));
    return FALSE;
}
void sort_rank_tcd(TAD_community root){
    g_hash_table_foreach(root->hashUsers,(GHFunc)load_rank_gslist_tcd,root);
    root->rankNPosts = g_slist_sort(root->rankNPosts,comp_nr_posts_user);
}
void sort_best_tcd(TAD_community root){
    g_hash_table_foreach(root->hashUsers,create_list11,root);
    root->bestUsers = g_slist_sort(root->bestUsers,comp_reput_user);
}

//Diz qual é o tipo do id recebido 1 quest 2 answer e 0 se não existe
int isQuest(TAD_community root, long id){
    if(g_hash_table_contains(root->hashQuests,GSIZE_TO_POINTER(id)))
        return 1;
    else if(g_hash_table_contains(root->hashAnswers,GSIZE_TO_POINTER(id)))
        return 2;
    return 0;
}
STR_pair get_info_post_tcd(TAD_community root, int x, long id){
    char* title = NULL;
    char* name = NULL;
    Quest q;
    User u;
    if(x == 1){
        q = g_hash_table_lookup(root->hashQuests, GSIZE_TO_POINTER(id));
        u = g_hash_table_lookup(root->hashUsers,
            GSIZE_TO_POINTER(get_owner_id_quest(q)));
        title = get_title_quest(q);
        name = get_displayname_user(u);
    }
    else if(x == 2){
        Answer a = g_hash_table_lookup(root->hashAnswers,GSIZE_TO_POINTER(id));
        u = g_hash_table_lookup(root->hashUsers,
            GSIZE_TO_POINTER(get_owner_user_id_answer(a)));
        q = g_hash_table_lookup(root->hashQuests,
            GSIZE_TO_POINTER(get_parent_id_answer(a)));
        title = get_title_quest(q);
        name = get_displayname_user(u);
    }
    return create_str_pair(title,name);
}
LONG_list get_most_active_tcd(TAD_community root, int N){
    GSList *list = root->rankNPosts;
    if(g_slist_length(list) < N) N = g_slist_length(list);
    LONG_list l = create_list(N);
    int i;
    User u;
    for(i=0;i<N;i++){
        u = (User) GPOINTER_TO_SIZE(list->data);
        set_list(l,i,get_id_user(u));
        list = list->next;
    }
    return l;
}
void query3_tcd(TAD_community root,query3 ld){
    g_tree_foreach(root->treeDays,(GTraverseFunc)count_posts_day,
            GSIZE_TO_POINTER(ld));
}

void foreach_hash_tcd(TAD_community root, char c, GHFunc func,void* data){
    GHashTable* h;
    switch (c) {
        case 't':
            h = root->hashTags;
            break;
        case 'u':
            h = root->hashUsers;
            break;
        case 'q':
            h = root->hashQuests;
            break;
        case 'a':
            h = root->hashQuests;
            break;
        default:
            return;
    }
    g_hash_table_foreach(h, func, data);
}
void insert_tree_tcd(TAD_community root, void* key, void* value){
    GTree* t = root->treeDays;
    g_tree_insert(t,key,value);
}
void insert_hash_tcd(TAD_community root,char c, void* key, void* value){
    GHashTable* h;
    switch (c) {
        case 't':
            h = root->hashTags;
            break;
        case 'u':
            h = root->hashUsers;
            break;
        case 'q':
            h = root->hashQuests;
            break;
        case 'a':
            h = root->hashQuests;
            break;
    }
    g_hash_table_insert(h,key,value);
}
//-----------------------------------------------------------
/* Apaga a tcd dando free na memoria alocada. */
void free_tcd(TAD_community root){
    g_hash_table_destroy(root->hashTags);
    g_hash_table_destroy(root->hashUsers);
    g_hash_table_destroy(root->hashQuests);
    g_hash_table_destroy(root->hashAnswers);
    //g_tree_destroy(root->treeDays);
    g_slist_free(root->rankNPosts);
    printf("RankNPosts out\n");
}
