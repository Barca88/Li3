#include <string.h>
#include <stdlib.h>
#include <xmlreader.h>
#include "interface.h"
#include "parser.h"
#include "nodeUser.h"
#include "date.h"
#include "post.h"



//Processar informacao de um user. 
static void processUser(GHashTable* hu ,xmlTextReaderPtr node) {
    xmlChar *name = xmlTextReaderName(node);
    if (strcmp((char*)name,"row") != 0){
        name = xmlStrdup(BAD_CAST "--");
    }

    gint64 id = -2;
    char* dn = NULL;
    char* am = NULL;
    long r = -2;

    char *attributename = NULL;
    printf("\n------------------------------------------------\n");
    while(xmlTextReaderMoveToNextAttribute(node)){
             attributename = (char*)xmlTextReaderName(node); 
             if(strcmp(attributename,"Id") == 0){
                 id = g_ascii_strtoll((char*)xmlTextReaderValue(node),NULL,10);
             }else if(strcmp(attributename,"DisplayName") == 0)
                 dn = (char*)xmlTextReaderValue(node);
             else if (strcmp(attributename,"AboutMe") == 0)
                 am = (char*)xmlTextReaderValue(node);
             else if (strcmp(attributename,"Reputation") ==  0)
                 r  = atol((char*)xmlTextReaderValue(node));
             else printf("Needless attribute-->%s\n",xmlTextReaderName(node));
    }
    ptr_user newUser = init_user(id,dn,am,r);
    g_hash_table_insert(hu,GSIZE_TO_POINTER(id),newUser);
}

//Processar informacao de um  post. 
static void processPost(GTree* tp, xmlTextReaderPtr node) {
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

    printf("\n*********************************************\n");

    while(xmlTextReaderMoveToNextAttribute(node)){
         attributename = (char*)xmlTextReaderName(node); 
         if(strcmp(attributename,"Id") == 0)
                 id = atol((char*)xmlTextReaderValue(node));
         else if(strcmp(attributename,"PostTypeId") == 0)
                 ptid = atoi((char*)xmlTextReaderValue(node));
         else if (strcmp(attributename,"ParentId") == 0)
                 pid = atol( (char*)xmlTextReaderValue(node));
         else if (strcmp(attributename,"CreationDate") == 0);
                // cd  = (char*)xmlTextReaderValue(node);
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
         else printf("Needless attribute-->%s\n",xmlTextReaderName(node));
    }
    ptr_post new_post = init_post(id,ptid,pid,cd,s,ouid,ti,ta,ac,cc,fc);
    g_tree_insert(tp,GSIZE_TO_POINTER(id),new_post);
    free_date(cd);
    
printf("\n......................................................\n");
long id2 = 10;
ptr_post a = (ptr_post)g_tree_lookup(tp,GSIZE_TO_POINTER(id2));
print_post(a);
    
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
             else printf("Needless attribute-->%s\n",xmlTextReaderName(node));
         }
     }
}*/

//Montar estrutura em memoria e avancar linha a linha.
void streamUsers(GHashTable* hu ,char *path) {
    char* aux = malloc(128 * sizeof(char));
    strcpy(aux,path);
    xmlTextReaderPtr stream = xmlNewTextReaderFilename(strcat(aux,"Users.xml"));
    int nodeReader;
    
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
    }else  printf("Unable to open %s\n", "Users.xml");
}


//Montar estrutura em memoria e avancar linha a linha.
void streamPosts(GTree* tp ,char *path) {
    char* aux = malloc(128 * sizeof(char));
    strcpy(aux,path);
    xmlTextReaderPtr stream = xmlNewTextReaderFilename(strcat(aux,"Posts.xml"));
    int nodeReader;
    
    if (stream != NULL) {
        nodeReader = xmlTextReaderRead(stream);

        while (nodeReader == 1){
             if (xmlTextReaderHasAttributes(stream)){
             processPost(tp,stream);
             }
             nodeReader = xmlTextReaderRead(stream);
        }
        xmlFreeTextReader(stream);

        if (nodeReader != 0) {
            printf("%s : failed to parse\n", "Posts.xml");
        }
    }else  printf("Unable to open %s\n", "Posts.xml");
}
