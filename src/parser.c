#include "usr/include/libxml2/libxml/xmlreader.h"
#include "parser.h"

static void processNode(xmlTextReaderPtr node) {
    xmlChar *name, *value;

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

int streamFile(char *filename) {
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
    } else {
        printf("Unable to open %s\n", filename);
    }
}

    
