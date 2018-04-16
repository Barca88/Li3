#include "parser.h"
#include "tcd.h"

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

//Create new post and insert in post struct. 
static void processPost(TAD_community com,xmlTextReaderPtr node) {
    GTree *tp = get_tree_posts(com);
    GHashTable *hp = get_hash_posts(com);
    GHashTable *hu = get_hash_users(com);

    xmlChar *name = xmlTextReaderName(node);
    if (strcmp((char*)name,"row") != 0){
        name = xmlStrdup(BAD_CAST "--");
    }

    long id = -2;
    int ptid = -2;
    long pid = -2; //Optional if postTypeId = 2
    Date cd = NULL;
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
    
    //Inserir na estrura dos posts.
    g_hash_table_insert(hp,GSIZE_TO_POINTER(id),new_post);

    DatePair pair = creat_date_pair(cd,id);
    ptr_post quest = (ptr_post)g_hash_table_lookup(hp,GSIZE_TO_POINTER(pid));

    if(ptid == 1){
        g_tree_insert(tp,GSIZE_TO_POINTER(pair),new_post);
        set_answer_tree(g_tree_new((GCompareFunc)date_pair_compare),new_post);
    }else if (ptid == 2)
        if(quest)
            g_tree_insert(get_answer_tree(quest),GSIZE_TO_POINTER(pair),new_post);

    //Incrementar o numero de posts do respetivo user.
    if(ouid!=-2){
        ptr_user nu = (ptr_user)g_hash_table_lookup(hu,GSIZE_TO_POINTER(ouid));
        inc_nr_posts(nu);
    }
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
    xmlTextReaderPtr stream = xmlNewTextReaderFilename(strcat(aux,"/Users.xml"));
    
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
void streamPosts(TAD_community com,char *path){

    char* aux = malloc(128 * sizeof(char));
    strcpy(aux,path);
    int nodeReader;
    xmlTextReaderPtr stream = xmlNewTextReaderFilename(strcat(aux,"/Posts.xml"));
    
    if (stream != NULL) {
        nodeReader = xmlTextReaderRead(stream);

        while (nodeReader == 1){
             if (xmlTextReaderHasAttributes(stream)){
                processPost(com,stream);
             }
             nodeReader = xmlTextReaderRead(stream);
        }
        xmlFreeTextReader(stream);

        if (nodeReader != 0) {
            printf("%s : failed to parse\n", "Posts.xml");
        }
    }else  printf("Unable to open %s\n", "Posts.xml");
}
