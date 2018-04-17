#ifndef __USERS_H__
#define __USERS_H__

#include <glib.h>

typedef struct node* ptr_user;

ptr_user init_user();

void set_id_user(ptr_user user, gint64 id);
void set_displayname_user(ptr_user user, char* dn);
void set_aboutme_user(ptr_user user, char* am);
void set_reputation_user(ptr_user user, long r); 
void set_posts_user(ptr_user user,GSList* p);

long get_id_user(ptr_user user);
char* get_displayname_user(ptr_user user);
char* get_aboutme_user(ptr_user user);
long get_reputation_user(ptr_user user);
int get_nr_posts_user(ptr_user user);
GSList* get_posts_user(ptr_user user);

void inc_nr_posts(ptr_user user);

void print_user(ptr_user user);

#endif
