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
ptr_post creat_post_id(long id){
    ptr_post p = malloc(sizeof(struct post));
    p->id = id;
    p->parentID = 0;
    p-> title = mystrdup("\0");
    p-> tags = mystrdup("\0");
    return p;
}
//Setters   
void set_post_type_id(int postTypeId, ptr_post p){
    p->postTypeId = postTypeId;
}
void set_parent_id(long parentID, ptr_post p){
    p->parentID = parentID;
}
void set_creation_date(Date creationDate, ptr_post p){
    p->creationDate = creationDate;
}
void set_score(int score, ptr_post p){
    p->score = score;
}
void set_owner_user_id(long ownerUserID,ptr_post p){
    p->ownerUserID = ownerUserID;
}
void set_title(char* title,ptr_post p){
    free(p->title);
    p->title = mystrdup(title);  // isto fica mesmo assim? (mystrdup)
}
void set_tags(char* tags, ptr_post p){
    free(p->tags);
    p->tags = mystrdup(tags);   // isto fica mesmo assim??
}
void set_answer_count(int answerCount, ptr_post p){
    p->answerCount = answerCount;
}
void set_comment_count(int commentCount, ptr_post p){
    p->commentCount = commentCount;
}
void set_favorite_count(int favoriteCount, ptr_post p){
    p->favoriteCount = favoriteCount;
}

//Getters
int get_id(ptr_post p){
    return p->id;
}
int get_post_type_id(ptr_post p){
    return p->postTypeId;
}
long get_parent_id(ptr_post p){
    return p->parentID;
}
Date get_creation_date(ptr_post p){
    return p->creationDate;
}
int get_score(ptr_post p){
    return p->score;
}
long get_owner_user_id(ptr_post p){
    return p->ownerUserID;
}
char* get_title(ptr_post p){
    return p->title;      //TODO
} 
char* get_tags(ptr_post p){
    return p->tags;       // TODO
}
int get_answer_count(ptr_post p){
    return p->answerCount;
}
int get_comment_count(ptr_post p){
    return p->commentCount;
}
int get_favorite_count(ptr_post p){
    return p->favoriteCount;
}

//Apaga o post dando free na memoria pare ele alocada
void free_post(ptr_post p){
    free(p->title);
    free(p->tags);
    free(p);
}

