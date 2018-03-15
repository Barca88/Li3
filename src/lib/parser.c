#include "xmlreader.h"
#include "parser.h"

static int user_Id;
static char* user_DisplayName;
static char* user_AboutMe;
static int user_Reputation;



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

void streamFile(char *filename) {
    xmlTextReaderPtr stream;
    int nodeReader;
    

    stream = xmlNewTextReaderFilename(filename);
    if (stream != NULL) {
        nodeReader = xmlTextReaderRead(stream);
        while (nodeReader == 1) {
            processNode(stream);
            nodeReader = xmlTextReaderRead(stream);
        }
        xmlFreeTextReader(stream);
        if (nodeReader != 0) {
            printf("%s : failed to parse\n", filename);
        }
    } else 
        printf("Unable to open %s\n", filename);
}

    
