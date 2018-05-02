#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "users.h"

/* Definição da estrutura dos users. */
struct node{
    long Id; /* Id do user. */
    char* DisplayName; /* DisplayName de um user. */
    char* AboutMe; /* Short bio de um user. */
    long  Reputation; /* Reputação de um user. */
    int nr_posts; /* Nº de posts de um user. */
    GSList* quests; /* Lista das quest que um user fez. */
    GSList* answers; /* Lista das answer que um user fez. */
};

/* Função que inicia a estrutura dos users. */
User init_user(long id, char* dn, char* am, long r){
    User n = malloc(sizeof(struct node));
    n->Id = id;
    n->DisplayName = dn;
    n->AboutMe = am;
    n->Reputation = r;
    n->nr_posts = 0;
    n->quests = NULL;
    n->answers = NULL;
    return n;
}

void set_id_user(User user, long id){
    user->Id = id;
}
void set_displayname_user(User user, char* s){
    free(user->DisplayName);
    user->DisplayName = mystrdup(s);
}
void set_aboutme_user(User user, char* s){
    free(user->AboutMe);
    user->AboutMe = mystrdup(s);
}
void set_reputation_user(User user, long r){
    user->Reputation = r;
}
void set_quests_user(User user,GSList* q){
    user->quests = q;
}
void set_answers_user(User user,GSList* a){
    user->answers = a;
}

/* Gets (Obter valor das variaveis da estrutura) */
long get_id_user(User user){
    return user->Id;
}
char* get_displayname_user(User user){
    return mystrdup(user->DisplayName);
}
char* get_aboutme_user(User user){
   return mystrdup(user->AboutMe);
}
long get_reputation_user(User user){
    return user->Reputation;
}
int get_nr_posts_user(User user){
     return user->nr_posts;
}
GSList* get_quests_user(User user){
     return user->quests;
}
GSList* get_answers_user(User user){
     return user->answers;
}

void inc_nr_posts(User user){
    (user->nr_posts)++;
}

gint comp_nr_posts_user(gconstpointer a,gconstpointer b){
    if(((User)a)->nr_posts > ((User)b)->nr_posts)
        return -1;
    else if(((User)a)->nr_posts < ((User)b)->nr_posts)
        return 1;
    else
        return 0;
}

/* Imprimir o conteúdo de uma quest. */
void print_q(gpointer data,gpointer n){
    Quest q = (Quest)GPOINTER_TO_SIZE(data);
    print_quest(q);
}
/* Imprimir o conteúdo de uma answer. */
void print_a(gpointer data,gpointer n){
    Answer a = (Answer)GPOINTER_TO_SIZE(data);
    print_answer(a);
}

/* Imprimir o conteúdo de um user. */
void print_user(User user){
    if(user)
        printf("user:\n\n\tId: %ld\n\tName:  %s\n\tAbouteMe: %s\n\tReputation: %ld\n\tNr de Posts: %d\n\n",user->Id,user->DisplayName,user->AboutMe,user->Reputation,user->nr_posts); 
}
void free_users(User u){
    free(u->DisplayName);
    free(u->AboutMe);
    g_slist_free(u->quests);
    g_slist_free(u->answers);
    free(u);
}
void free_g_users(gpointer g){
    User u = (User)GPOINTER_TO_SIZE(g);
    free_users(u);
    g_free(g);
}
