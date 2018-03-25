#include <../lib/post.h>
#include "date.h"
#include "post.h"

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
    int AnswerCount;
    int CommentCount;
    int FavoriteCount;
};

Post creat_post_id(long id){
    Post p = malloc(sizeof(struc post));
    p->id = id;
    p->parentID = 0;
    return p;
}
   
void set_PostTypeId(int postTyepeId, Post p){
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
    p->title = title;
}
void set_tags(char* tags, Post p){
    p->
