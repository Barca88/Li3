#ifndef __POST_H__
#define __POST_H__
typedef struct post* ptr_post;

// Metodo de Criação
ptr_post creat_post(long id);

//Setters
void set_post_type_id(int postTypeId, ptr_post p);
void set_Parent_id(long parentID, ptr_post p);
void set_creation_date(Date creationDate, ptr_post p);
void set_score(int score, ptr_post p);
void set_owner_ser_id(long ownerUserID, ptr_post p);
void set_title(char* title, ptr_post p);
void set_tags(char* tags, ptr_post p);
void set_answer_count(int answerCount, ptr_post p);
void set_comment_count(int commentCount, ptr_post p);
void set_favorite_count(int favoriteCount, ptr_post p);

//Getters
int get_Id(ptr_post p);
int get_post_type_id(ptr_post p);
long get_parent_id(ptr_post p);
Date get_creationDate(ptr_post p);
int get_score(ptr_post p);
long get_owner_user_id(ptr_post p);
char* get_title(ptr_post p);
char* get_tags(ptr_post p);
int get_answer_count(ptr_post p);
int get_comment_count(ptr_post p);
int get_favorite_count(ptr_post p);

//Clear
void free_post(ptr_post p);
#endif
