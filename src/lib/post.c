#include <../lib/post.h>
#include "date.h"
#include "post.h"

// Post definitions
struct post {
    long id;
    int postTypeId;
    long parentID; //Optional if postTypeId = 2
    long ownerUserID;
    Date creationDate;
    char* title;
    char* tags;
};

Post creat_post(long id, int postTypeID, long ownerUserID, Date creationDate,
        char* title, char* tags){
   

