#ifndef __POST_H__
#define __POST_H__
typedef struct post* Post;

// Post definitions
Post creat_post(long id, int postTypeID, long ownerUserID, 
        Date creationDate,char* title, char* tags); 
void set_
