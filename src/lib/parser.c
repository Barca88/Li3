#include <string.h>
#include <stdlib.h>
#include <xmlreader.h>
#include <glib.h>
#include "interface.h"
#include "parser.h"
#include "nodeUser.h"
#include "date.h"
#include "post.h"
#include <string.h>



//Create new user and insert in user struct. 
static void processUser(GHashTable* hu ,xmlTextReaderPtr node) {
    xmlChar *name = xmlTextReaderName(node);
    if (strcmp((char*)name,"row") != 0){
        name = xmlStrdup(BAD_CAST "--");
    }

    long id = -2;
    char* dn = NULL;
    char* am = NULL;
    long r = -2;
    char *attributename = NULL;

    while(xmlTextReaderMoveToNextAttribute(node)){
             attributename = (char*)xmlTextReaderName(node); 
             if(strcmp(attributename,"Id") == 0)
                 id = atol((char*)xmlTextReaderValue(node));
             else if(strcmp(attributename,"DisplayName") == 0)
                 dn = (char*)xmlTextReaderValue(node);
             else if (strcmp(attributename,"AboutMe") == 0)
                 am = (char*)xmlTextReaderValue(node);
             else if (strcmp(attributename,"Reputation") ==  0)
                 r  = atol((char*)xmlTextReaderValue(node));
             else;
    }
    
    ptr_user newUser = init_user(id,dn,am,r);
    g_hash_table_insert(hu,GSIZE_TO_POINTER(id),newUser);
}

static Date date_from_string(char* date){
    *(date + 10) = '\0';
    char* day = date+8;
    *(date + 7) = '\0';
    char* month = date+5;
    *(date + 4) = '\0';
    char* year = date;
    
    Date a = createDate(atoi(day),atoi(month),atoi(year));
    return a;
}

//Create new post and insert in post struct. 
static void processPost(GTree* tp,GHashTable* hp, xmlTextReaderPtr node) {
    xmlChar *name = xmlTextReaderName(node);
    if (strcmp((char*)name,"row") != 0){
        name = xmlStrdup(BAD_CAST "--");
    }

    long id = -2;
    int ptid = -2;
    long pid = -2; //Optional if postTypeId = 2
    Date cd = createDate(22,06,1995);
    int s = -2;
    long ouid = -2;
    char* ti = NULL;
    char* ta = NULL;
    int ac = -2;
    int cc = -2;
    int fc = -2;
    char *attributename = NULL;

    while(xmlTextReaderMoveToNextAttribute(node)){
         attributename = (char*)xmlTextReaderName(node); 
         if(strcmp(attributename,"Id") == 0)
                 id = atol((char*)xmlTextReaderValue(node));
         else if(strcmp(attributename,"PostTypeId") == 0)
                 ptid = atoi((char*)xmlTextReaderValue(node));
         else if (strcmp(attributename,"ParentId") == 0)
                 pid = atol( (char*)xmlTextReaderValue(node));
         else if (strcmp(attributename,"CreationDate") == 0)
                 cd = date_from_string((char*)xmlTextReaderValue(node));
         else if (strcmp(attributename,"Score") == 0)
                 s = atoi((char*)xmlTextReaderValue(node));
         else if (strcmp(attributename,"OwnerUserId") == 0)
                 ouid = atol((char*)xmlTextReaderValue(node));
         else if (strcmp(attributename,"Title") == 0)
                 ti = (char*)xmlTextReaderValue(node);
         else if (strcmp(attributename,"Tags") == 0)
                 ta = (char*)xmlTextReaderValue(node);
         else if (strcmp(attributename,"AnswerCount") == 0)
                 ac = atoi((char*)xmlTextReaderValue(node));
         else if (strcmp(attributename,"CommentCount") == 0)
                 cc = atoi((char*)xmlTextReaderValue(node));
         else if (strcmp(attributename,"FavoriteCount") == 0)
                 fc = atoi((char*)xmlTextReaderValue(node));
         else;
    }
    ptr_post new_post = init_post(id,ptid,pid,cd,s,ouid,ti,ta,ac,cc,fc);
    g_tree_insert(tp,GSIZE_TO_POINTER(id),new_post);
    g_hash_table_insert(hp,GSIZE_TO_POINTER(id),new_post);
    free_date(cd);
}

//Processar informacao de um vote. 
/*static void processVote(xmlTextReaderPtr node) {
    xmlChar *name;
    char *attributename;

    name = xmlTextReaderName(node);
    if (name == NULL)
        name = xmlStrdup(BAD_CAST "--");


    if (xmlTextReaderHasAttributes(node)){
        printf("------------------------------------------------------------------\n");
         while(xmlTextReaderMoveToNextAttribute(node)){
             attributename = (char*)xmlTextReaderName(node); 
             if(strcmp(attributename,"Id") == 0)
                        printf("- %s: %s\n",
                                 xmlTextReaderName(node),
                                 xmlTextReaderValue(node));
             else if(strcmp(attributename,"PostId") == 0)
                        printf("- %s: %s\n",
                                 xmlTextReaderName(node),
                                 xmlTextReaderValue(node));
             else if (strcmp(attributename,"VoteTypeId") == 0)
                        printf("- %s: %s\n",
                                 xmlTextReaderName(node),
                                 xmlTextReaderValue(node));
             else;
         }
     }
}*/

//Process Users.xml file.
void streamUsers(GHashTable* hu ,char *path) {
    char* aux = malloc(128 * sizeof(char));
    strcpy(aux,path);
    int nodeReader;
    xmlTextReaderPtr stream = xmlNewTextReaderFilename(strcat(aux,"Users.xml"));
    
    if (stream != NULL) {
        nodeReader = xmlTextReaderRead(stream);

        while (nodeReader == 1){
             if (xmlTextReaderHasAttributes(stream)){
                processUser(hu,stream);
             }
             nodeReader = xmlTextReaderRead(stream);
        }
        xmlFreeTextReader(stream);

        if (nodeReader != 0) {
            printf("%s : failed to parse\n", "Users.xml");
        }
    }else printf("Unable to open %s\n", "Users.xml");
}


//Process Posts.xml file.
void streamPosts(GTree* tp ,GHashTable* hp, char *path){
    char* aux = malloc(128 * sizeof(char));
    strcpy(aux,path);
    int nodeReader;
    xmlTextReaderPtr stream = xmlNewTextReaderFilename(strcat(aux,"Posts.xml"));
    
    if (stream != NULL) {
        nodeReader = xmlTextReaderRead(stream);

        while (nodeReader == 1){
             if (xmlTextReaderHasAttributes(stream)){
                processPost(tp,hp,stream);
             }
             nodeReader = xmlTextReaderRead(stream);
        }
        xmlFreeTextReader(stream);

        if (nodeReader != 0) {
            printf("%s : failed to parse\n", "Posts.xml");
        }
    }else  printf("Unable to open %s\n", "Posts.xml");
}
