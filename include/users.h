#ifndef __USERS_H__
#define __USERS_H__

#include <glib.h>

typedef struct node* User;

User init_user();

<<<<<<< HEAD
void set_id_user(ptr_user user, gint64 id);
void set_displayname_user(ptr_user user, char* dn);
void set_aboutme_user(ptr_user user, char* am);
void set_reputation_user(ptr_user user, long r); 
void set_quests_user(ptr_user user,GSList* q);
void set_answers_user(ptr_user user,GSList* a);

long get_id_user(ptr_user user);
char* get_displayname_user(ptr_user user);
char* get_aboutme_user(ptr_user user);
long get_reputation_user(ptr_user user);
int get_nr_posts_user(ptr_user user);
GSList* get_quests_user(ptr_user user);
GSList* get_answers_user(ptr_user user);
=======
void set_id_user(User user, gint64 id);
void set_displayname_user(User user, char* dn);
void set_aboutme_user(User user, char* am);
void set_reputation_user(User user, long r); 
void set_posts_user(User user,GSList* p);

long get_id_user(User user);
char* get_displayname_user(User user);
char* get_aboutme_user(User user);
long get_reputation_user(User user);
int get_nr_posts_user(User user);
GSList* get_posts_user(User user);
>>>>>>> refs/remotes/origin/master

void inc_nr_posts(User user);

void print_user(User user);

#endif
