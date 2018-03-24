#ifndef __NODEUSER_H__
#define __NODEUSER_H__

typedef struct node* ptr_user;

ptr_user init_user();

void set_id_user(ptr_user user, long id);

void set_displayname_user(ptr_user user, char* dn);

void set_aboutme_user(ptr_user user, char* am);

void set_reputation_user(ptr_user user, long r); 

long get_id_user(ptr_user user);

char* get_displayname_user(ptr_user user);

char* get_aboutme_user(ptr_user user);

long get_reputation_user(ptr_user user);

void print_user(ptr_user user);

#endif
