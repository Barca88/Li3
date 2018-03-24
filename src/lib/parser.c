#include <string.h>
#include <stdlib.h>
#include <xmlreader.h>
#include "interface.h"
#include "parser.h"
#include "nodeUser.h"

//Processar informacao dos users. 
static void processUser(s_ptr_users hu ,xmlTextReaderPtr node) {
    ptr_user a;
    xmlChar *name;
    char *attributename;
    long* key;
    long auxid = -2;
    key = &auxid;
    name = xmlTextReaderName(node);
    if (name == NULL)
        name = xmlStrdup(BAD_CAST "--");


    if (xmlTextReaderHasAttributes(node)){
        printf("------------------------------------------------------------------\n");
         ptr_user newUser = init_user();
         while(xmlTextReaderMoveToNextAttribute(node)){
             attributename = (char*)xmlTextReaderName(node); 
             if(strcmp(attributename,"Id") == 0){
                        set_id_user(newUser,atol((char*)xmlTextReaderValue(node)));
                        auxid = get_id_user(newUser); 
             }else if(strcmp(attributename,"DisplayName") == 0)
                        set_displayname_user(newUser,(char*)xmlTextReaderValue(node));
             else if (strcmp(attributename,"AboutMe") == 0)
                        set_aboutme_user(newUser,(char*)xmlTextReaderValue(node));
             else if (strcmp(attributename,"Reputation") ==  0)
                        set_reputation_user(newUser,atol((char*)xmlTextReaderValue(node)));
             else printf("Needless attribute-->%s\n",xmlTextReaderName(node));
         }
        g_hash_table_insert(hu,(void*)key,newUser);
        a = (ptr_user)g_hash_table_lookup(hu,(void*)key);
        print_user(a);
     }

        printf("%p\n",a);
        printf("There are %d keys in the hash\n", g_hash_table_size(hu));
}


//Processar informacao dos posts. 
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

//Processar informacao dos votes. 
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
    char aux[128];
    strcpy(aux,path);
    xmlTextReaderPtr stream;
    int nodeReader;
         stream = xmlNewTextReaderFilename(strcat(aux,"Users.xml"));
         
         if (stream != NULL) {
             nodeReader = xmlTextReaderRead(stream);
             while (nodeReader == 1){
                 processUser(hu,stream);
                 nodeReader = xmlTextReaderRead(stream);
             }
             xmlFreeTextReader(stream);
             if (nodeReader != 0) {
                 printf("%s : failed to parse\n", "Users.xml");
             }
         } else 
          printf("Unable to open %s\n", "Users.xml");
}


