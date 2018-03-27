#include <string.h>
#include <stdlib.h>
#include <xmlreader.h>
#include "interface.h"
#include "parser.h"
#include "nodeUser.h"



//Processar informacao de um user. 
static void processUser(s_ptr_users hu ,xmlTextReaderPtr node) {
    xmlChar *name = xmlTextReaderName(node);
    if (strcmp((char*)name,"row") != 0){
        name = xmlStrdup(BAD_CAST "--");
    }

    ptr_user newUser = init_user();
    gint64 key;

    char *attributename = NULL;

    while(xmlTextReaderMoveToNextAttribute(node)){
             attributename = (char*)xmlTextReaderName(node); 
             if(strcmp(attributename,"Id") == 0){
                 set_id_user(newUser,g_ascii_strtoll((char*)xmlTextReaderValue(node),NULL,10));
                 key = g_ascii_strtoll((char*)xmlTextReaderValue(node),NULL,10);
             }else if(strcmp(attributename,"DisplayName") == 0)
                 set_displayname_user(newUser,(char*)xmlTextReaderValue(node));
             else if (strcmp(attributename,"AboutMe") == 0)
                 set_aboutme_user(newUser,(char*)xmlTextReaderValue(node));
             else if (strcmp(attributename,"Reputation") ==  0)
                 set_reputation_user(newUser,atol((char*)xmlTextReaderValue(node)));
             else printf("Needless attribute-->%s\n",xmlTextReaderName(node));
    }
    g_hash_table_insert(hu,&key,newUser);
    printf("------------------------------------------------------------------\n");
    ptr_user a = (ptr_user)g_hash_table_lookup(hu,&key);
    print_user(a);
}

//Processar informacao de um  post. 
static void processPost(xmlTextReaderPtr node) {
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
             else if(strcmp(attributename,"PostTypeId") == 0)
                        printf("- %s: %s\n",
                                 xmlTextReaderName(node),
                                 xmlTextReaderValue(node));
             else if (strcmp(attributename,"OwnerUserId") == 0)
                        printf("- %s: %s\n",
                                 xmlTextReaderName(node),
                                 xmlTextReaderValue(node));
             else if (strcmp(attributename,"Title") == 0)
                        printf("- %s: %s\n",
                                 xmlTextReaderName(node),
                                 xmlTextReaderValue(node));
             else if (strcmp(attributename,"CreationDate") == 0)
                        printf("- %s: %s\n",
                                 xmlTextReaderName(node),
                                 xmlTextReaderValue(node));
             else if (strcmp(attributename,"Tags") == 0)
                        printf("- %s: %s\n",
                                 xmlTextReaderName(node),
                                 xmlTextReaderValue(node));
             else if (strcmp(attributename,"ParentId") == 0)
                        printf("- %s: %s\n",
                                 xmlTextReaderName(node),
                                 xmlTextReaderValue(node));
             else printf("Needless attribute-->%s\n",xmlTextReaderName(node));
         }
    }
}

//Processar informacao de um vote. 
static void processVote(xmlTextReaderPtr node) {
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
}

//Montar estrutura em memoria e avancar linha a linha.
void streamUsers(s_ptr_users hu ,char *path) {
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
        
   /* printf("------------------------------------------------------------------\n");
    gint64 key =(gint64) g_ascii_strtoll("10",NULL,10); 
    printf("VALOR KEY: %ld",key);
    ptr_user a = g_hash_table_lookup(hu,&key);
    print_user(a);*/
   
        printf("There are %d keys in the hash\n", g_hash_table_size(hu));

        if (nodeReader != 0) {
            printf("%s : failed to parse\n", "Users.xml");
        }
    }else  printf("Unable to open %s\n", "Users.xml");
}


