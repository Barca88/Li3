#include <nodeUser.h>
#include <stdlib.h>

typedef struct node{
    long Id;
    char* DisplayName;
    char* AboutMe;
    long  Reputation;
} nodeUser;

ptr_user init_user(){
    ptr_user n = malloc(sizeof(nodeUser));
    n->Id = -1;
    n->DisplayName = "";
    n->AboutMe = "";
    n->Reputation = -1;
    return n;
}

void set_id_user(ptr_user user, long id){
    user->Id = id;
}
void set_displayname_user(ptr_user user, char* dn){
    user->DisplayName = dn;
}
void set_aboutme_user(ptr_user user, char* am){
    user->AboutMe = am;
}
void set_reputation_user(ptr_user user, long r){
    user->Reputation = r;
}

long get_id_user(ptr_user user){
    return user->Id;
}
char* get_displayname_user(ptr_user user){
    return user->DisplayName;
}
char* get_aboutme_user(ptr_user user){
    return user->AboutMe;
}
long get_reputation_user(ptr_user user){
    return user->Reputation;
}
