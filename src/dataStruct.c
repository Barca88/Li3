#include <../lib/dataStruct.h>
#include <glib.h>
#include "date.h"

typedef struct post{
    long id;
    int postTypeId;
    Date creationDate;
    Char* title;
    int answerCount;
    char* tags;

}

typedef struct user{
    long id;
    int reputation;
    Char* short_Bio;
}

    
