#include "date.h"
#include "post.h"
#include "common.h"
#include <stdlib.h>

// Post definitions
struct post {
    long id;
    int postTypeId;
    long parentID; //Optional if postTypeId = 2
    Date creationDate;
    int score;
    long ownerUserID;
    char* title;
    char* tags;
    int answerCount;
    int commentCount;
    int favoriteCount;
};
//Metodo de Criação
Post creat_post_id(long id){
    Post p = malloc(sizeof(struct post));
    p->id = id;
    p->parentID = 0;
    p-> title = mystrdup("\0");
    p-> tags = mystrdup("\0");
    return p;
}
//Setters   
void set_PostTypeId(int postTypeId, Post p){
    p->postTypeId = postTypeId;
}
void set_ParentID(long parentID, Post p){
    p->parentID = parentID;
}
void set_CreationDate(Date creationDate, Post p){
    p->creationDate = creationDate;
}
void set_Score(int score, Post p){
    p->score = score;
}
void set_OwnerUserID(long ownerUserID, Post p){
    p->ownerUserID = ownerUserID;
}
void set_Title(char* title, Post p){
    free(p->title);
    p->title = mystrdup(title);  // isto fica mesmo assim? (mystrdup)
}
void set_tags(char* tags, Post p){
    free(p->tags);
    p->tags = mystrdup(tags);   // isto fica mesmo assim??
}
void set_AnswerCount(int answerCount, Post p){
    p->answerCount = answerCount;
}
void set_CommentCount(int commentCount, Post p){
    p->commentCount = commentCount;
}
void set_FavoriteCount(int favoriteCount, Post p){
    p->favoriteCount = favoriteCount;
}
//Getters
int get_Id(Post p){
    return p->id;
}
int get_PostTypeId(Post p){
    return p->postTypeId;
}
long get_ParentID(Post p){
    return p->parentID;
}
Date get_CreationDate(Post p){
    return p->creationDate;
}
int get_Score(Post p){
    return p->score;
}
long get_OwnerUserId(Post p){
    return p->ownerUserID;
}
char* get_Title(Post p){
    return p->title;      //TODO
} 
char* get_Tags(Post p){
    return p->tags;       // TODO
}
int get_AnswerCount(Post p){
    return p->answerCount;
}
int get_CommentCount(Post p){
    return p->commentCount;
}
int get_FavoriteCount(Post p){
    return p->favoriteCount;
}
//Apaga o post dando free na memoria pare ele alocada
void free_Post(Post p){
    free(p->title);
    free(p->tags);
    free(p);
}

