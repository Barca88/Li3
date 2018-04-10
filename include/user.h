#ifndef __USER_H_
#define __USER_H_

typedef struct user* USER;

USER create_user(char* short_bio, long* post_history);

char* get_bio(USER u);

long* get_10_latest_posts(USER u); // caso um utilizador tenha menos 
                                   // de 10 posts, por -1 como padding 
void free_user(USER u);
#endif
