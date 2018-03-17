#include <string.h>
#include <xmlreader.h>
#include "parser.h"


//Processar informacao dos users. 
static void processUser(xmlTextReaderPtr node) {
    xmlChar *name;

    name = xmlTextReaderName(node);
    if (name == NULL)
        name = xmlStrdup(BAD_CAST "--");


    if (xmlTextReaderHasAttributes(node)){
        printf("------------------------------------------------------------------\n");
         while(xmlTextReaderMoveToNextAttribute(node))
                 printf("- %s: %s\n",
                         xmlTextReaderName(node),
                         xmlTextReaderValue(node));
     }
}


//Processar informacao dos posts. 
static void processPost(xmlTextReaderPtr node) {
    xmlChar *name;

    name = xmlTextReaderName(node);
    if (name == NULL)
        name = xmlStrdup(BAD_CAST "--");


    if (xmlTextReaderHasAttributes(node)){
        printf("------------------------------------------------------------------\n");
         while(xmlTextReaderMoveToNextAttribute(node))
                 printf("- %s: %s\n",
                         xmlTextReaderName(node),
                         xmlTextReaderValue(node));
     }
}

//Processar informacao dos votes. 
static void processVote(xmlTextReaderPtr node) {
    xmlChar *name;
    char *atributename;

    name = xmlTextReaderName(node);
    if (name == NULL)
        name = xmlStrdup(BAD_CAST "--");


    if (xmlTextReaderHasAttributes(node)){
        printf("------------------------------------------------------------------\n");
         while(xmlTextReaderMoveToNextAttribute(node)){
             atributename = (char*)xmlTextReaderName(node); 
             if(strcmp(atributename,"Id") == 0)
                        printf("- %s: %s\n",
                                 xmlTextReaderName(node),
                                 xmlTextReaderValue(node));
             else if(strcmp(atributename,"PostId") == 0)
                        printf("- %s: %s\n",
                                 xmlTextReaderName(node),
                                 xmlTextReaderValue(node));

             else if (strcmp(atributename,"VoteTypeId") == 0)
                        printf("- %s: %s\n",
                                 xmlTextReaderName(node),
                                 xmlTextReaderValue(node));
             else printf("Atribute needless-->%s\n",xmlTextReaderName(node));
         }
     }
}

//Montar estrutura em memoria e avancar linha a linha.
void streamFile(char *path) {
    char* aux;
    xmlTextReaderPtr stream;
    int nodeReader;
    char* dumps[3] = {"Users.xml","Posts.xml","Votes.xml"};
    
    for(int l = 0;l<3;l++){
         aux = strcpy(aux,path);
         stream = xmlNewTextReaderFilename(strcat(aux,dumps[l]));
         
         if (stream != NULL) {
             nodeReader = xmlTextReaderRead(stream);
             while (nodeReader == 1) {
                 switch(l){
                     case 0 :    
                         processUser(stream);
                         break;
                     case 1 :
                         processPost(stream);
                         break;
                     case 2 :
                         processVote(stream);
                         break;
                     default : printf("File unable. \n");
                 }
                 nodeReader = xmlTextReaderRead(stream);
             }
             xmlFreeTextReader(stream);
             if (nodeReader != 0) {
                 printf("%s : failed to parse\n", strcat(aux,dumps[l]));
             }
         } else 
            printf("Unable to open %s\n", strcat(aux,dumps[l]));
    }
}

