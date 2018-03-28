#include <nodeUser.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
    gint64 Id;
    char* DisplayName;
    char* AboutMe;
    long  Reputation;
} nodeUser;

ptr_user init_user(){
    ptr_user n = malloc(sizeof(nodeUser));
    n->Id = 0;
    n->DisplayName = malloc(128 * sizeof(char));
    n->AboutMe = malloc(4096 * sizeof(char));
    n->Reputation = -1;
    return n;
}

void set_id_user(ptr_user user, gint64 id){
    user->Id = id;
}
void set_displayname_user(ptr_user user, char* dn){
    strcpy(user->DisplayName,dn);
}
void set_aboutme_user(ptr_user user, char* am){
    user->AboutMe = am;
    strcpy(user->AboutMe,am);
}
void set_reputation_user(ptr_user user, long r){
    user->Reputation = r;
}

gint64 get_id_user(ptr_user user){
    return user->Id;
}
char* get_displayname_user(ptr_user user){
    return strdup(user->DisplayName);
}
char* get_aboutme_user(ptr_user user){
    return strdup(user->AboutMe);
}
long get_reputation_user(ptr_user user){
    return user->Reputation;
}

void print_user(ptr_user user){
   printf("user:\n\nId: %ld\nName:  %s\nAbouteMe: %s\nReputation: %ld\n",user->Id,user->DisplayName,user->AboutMe,user->Reputation); 
}
