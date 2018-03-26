#ifndef __POST_H__
#define __POST_H__
typedef struct post* Post;

// Metodo de Criação
Post creat_post(long id);
//Setters
void set_PostTypeId(int postTypeId, Post p);
void set_ParentID(long parentID, Post p);
void set_CreationDate(Date creationDate, Post p);
void set_Score(int score, Post p);
void set_OwnerUserID(long ownerUserID, Post p);
void set_Title(char* title, Post p);
void set_tags(char* tags, Post p);
void set_AnswerCount(int answerCount, Post p);
void set_CommentCount(int commentCount, Post p);
void set_FavoriteCount(int favoriteCount, Post p);
//Getters
int get_Id(Post p);
int get_PostTypeId(Post p);
long get_ParentID(Post p);
Date get_CreationDate(Post p);
int get_Score(Post p);
long get_OwnerUserId(Post p);
char* get_Title(Post p);
char* get_Tags(Post p);
int get_AnswerCount(Post p);
int get_CommentCount(Post p);
int get_FavoriteCount(Post p);
//Clear
void free_Post(Post p);
#endif
