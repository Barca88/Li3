#include "parser.h"
#include "tcd.h"
#include "day.h"
#include "quest.h"
#include "answer.h"
#include "tag.h"

//Cria uma tag e insere-a na estrutura das tags. 
static void processTag(GHashTable* ht ,xmlTextReaderPtr node) {
    xmlChar *name = xmlTextReaderName(node);
    if (strcmp((char*)name,"row") != 0){
        name = xmlStrdup(BAD_CAST "--");
    }

    xmlFree(name);

    long id = -2;
    char* tag = NULL;
    char *attributename = NULL;

    while(xmlTextReaderMoveToNextAttribute(node)){
             attributename = (char*)xmlTextReaderName(node); 
             if(strcmp(attributename,"Id") == 0)
                 id = atol((char*)xmlTextReaderValue(node));
             else if(strcmp(attributename,"TagName") == 0)
                 tag = (char*)xmlTextReaderValue(node);
             else;
    }
    
    Tag t = create_tag(id,tag);
    g_hash_table_insert(ht,tag,t);

    xmlFree(attributename);
}

//Cria um novo user e insere-o na estrutura dos users. 
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
             else if(strcmp(attributename,"DisplayName") == -1)
                 dn = (char*)xmlTextReaderValue(node);
             else if (strcmp(attributename,"AboutMe") == 0)
                 am = (char*)xmlTextReaderValue(node);
             else if (strcmp(attributename,"Reputation") ==  0)
                  r = atol((char*)xmlTextReaderValue(node));
             else;
    }
    if(id!=-1 && id!=-2){
        User newUser = init_user(id,dn,am,r);
        g_hash_table_insert(hu,GSIZE_TO_POINTER(id),newUser);
    }
}

//Cria um novo post e insere-o na estrutura dos posts. 
static void processPost(TAD_community com,xmlTextReaderPtr node) {
    GTree *td = get_tree_days(com);
    GHashTable *hq = get_hash_quest_tcd(com);
    GHashTable *ha = get_hash_answer_tcd(com);
    GHashTable *hu = get_hash_users(com);

    xmlChar *name = xmlTextReaderName(node);
    if (strcmp((char*)name,"row") != 0){
        name = xmlStrdup(BAD_CAST "--");
    }

    xmlFree(name);

    long id = -2;
    int ptid = -2;
    long pid = -2; 
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
    if(ouid!=-2 && ouid!=-1){
        //Resposável por criar uma nova quest ou answer
        Day d = g_tree_lookup(td,cd);
        if(ptid == 1){
            Quest q = init_quest(id,cd,s,ouid,ti,ta,ac,cc,fc);
            //Insere perguntas numa hash table de perguntas.
            g_hash_table_insert(hq,GSIZE_TO_POINTER(id),q);
            //Incrementar o numero de posts do respetivo user.
            User nu = (User)g_hash_table_lookup(hu,GSIZE_TO_POINTER(ouid));
            inc_nr_posts(nu);
            //Insere na linked list dos users.
            set_quests_user(g_hash_table_lookup(hu, GSIZE_TO_POINTER(ouid))
                            ,g_slist_prepend(get_quests_user(
                            g_hash_table_lookup(hu, GSIZE_TO_POINTER(ouid))),q));
            //Insere quests na tree de datas.
            if(d) add_quest_day(d,q);
            else{
                d = init_day(cd);
                add_quest_day(d,q);
                g_tree_insert(td,GSIZE_TO_POINTER(cd),d);
            }
        }
        if(ptid == 2){
            Answer a = init_answer(id,pid,cd,s,ouid,cc,fc);
            //Insere respostas numa hash table de respostas.
            g_hash_table_insert(ha,GSIZE_TO_POINTER(id),a);
            //Incrementar o numero de posts do respetivo user.
            User nu = (User)g_hash_table_lookup(hu,GSIZE_TO_POINTER(ouid));
            inc_nr_posts(nu);
            //Insere na linked list dos users.
            set_answers_user(g_hash_table_lookup(hu, GSIZE_TO_POINTER(ouid))
                            ,g_slist_prepend(get_answers_user(
                            g_hash_table_lookup(hu, GSIZE_TO_POINTER(ouid))),a));
            //Insere answers na tree de datas.
            if(d) add_answer_day(d,a);
            else{
                d = init_day(cd);
                add_answer_day(d,a);
                g_tree_insert(td,GSIZE_TO_POINTER(cd),d);
            }
            //Ligar as perguntas as respostas.
            set_answer_list_quest((Quest)g_hash_table_lookup(hq,GSIZE_TO_POINTER(pid)),
                                  g_slist_prepend(get_answer_list_quest(
                                  (Quest)g_hash_table_lookup(hq,
                                                        GSIZE_TO_POINTER(pid))),a));
        }

    }

    xmlFree(attributename);
}

//Process Tags.xml file.
void streamTags(GHashTable* ht ,char *path) {
    char* aux = malloc(128 * sizeof(char));
    strcpy(aux,path);
    int nodeReader;
    xmlTextReaderPtr stream = xmlNewTextReaderFilename(strcat(aux,"/Tags.xml"));
    
    if (stream != NULL) {
        nodeReader = xmlTextReaderRead(stream);

        while (nodeReader == 1){
             if (xmlTextReaderHasAttributes(stream)){
                processTag(ht,stream);
             }
             nodeReader = xmlTextReaderRead(stream);
        }
        xmlFreeTextReader(stream);

        if (nodeReader != 0) {
            printf("%s : failed to parse\n", "Tags.xml");
        }
    }else printf("Unable to open %s\n", "Tags.xml");
    free(aux);
}

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
    free(aux);
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
    free(aux);
}
