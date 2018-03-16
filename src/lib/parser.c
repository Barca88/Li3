#include <string.h>
#include <xmlreader.h>
#include "parser.h"


//Processar informacao dos users. 
static void processNode(xmlTextReaderPtr node) {
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

//Montar estrutura em memoria e avancar linha a linha.
void streamFile(char *path) {
    char* aux = strcpy(aux,path);
    xmlTextReaderPtr stream;
    int nodeReader;
    char* dumps[3] = {"Users.xml","Posts.xml","Votes.xml"};
    
    for(int l = 0;l<3;l++){
         aux = strcpy(aux,path);
         stream = xmlNewTextReaderFilename(strcat(aux,dumps[l]));
         for(int i=10;i!=0;i--)printf("%dº-------%s--------\n",i,path);
         if (stream != NULL) {
             nodeReader = xmlTextReaderRead(stream);
             while (nodeReader == 1) {
                 processNode(stream);
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

