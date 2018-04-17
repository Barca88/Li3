#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "users.h"

typedef struct node{
    long Id;
    char* DisplayName;
    char* AboutMe;
    long  Reputation;
    int nr_posts;
    GSList* posts;
} nodeUser;

ptr_user init_user(long id, char* dn, char* am, long r){
    ptr_user n = malloc(sizeof(nodeUser));
    n->Id = id;
    n->DisplayName = dn;
    n->AboutMe = am;
    n->Reputation = r;
    n->nr_posts = 0;
    n->posts = NULL;
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
void set_posts_user(User user,GSList* p){
    user->posts = p;
}

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
GSList* get_posts_user(User user){
     return user->posts;
}

void inc_nr_posts(User user){
    (user->nr_posts)++;
}

void print_user(User user){
    if(user != NULL)
   printf("user:\n\nId: %ld\nName:  %s\nAbouteMe: %s\nReputation: %ld\nNr de Posts: %d\n",user->Id,user->DisplayName,user->AboutMe,user->Reputation,user->nr_posts); 
}
