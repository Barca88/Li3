#include "quest.h"

/* Definição da estrutura das perguntas (quest). */
struct quest{
    long id; /* Id da quest. */
    Date creationDate; /* Data de criação da quest. */
    int score; /* Pontuação da quest. */
    long ownerUserId; /* Id do user que elaborou a quest. */
    char* title; /* Título da pergunta. */
    char* tags; /* Tag da pergunta. */
    int answer_c; /* Nº de answer. */
    int comment_c; /* Nº de comentários que a quest obteve. */
    int favorite_c; /* Nº de quest com mais votos. */
    GSList* answerList; /* Lista das answer de uma quest. */
};

/* Função que inicia a estrutura quest. */
Quest init_quest(long id, Date cd, int s,long ouid, char* ti, char* ta, int ac,
        int cc, int fc){
    Quest q = malloc(sizeof(struct quest));
    q -> id = id;
    q -> creationDate = cd;
    q -> score = s;
    q -> ownerUserId = ouid;
    q -> title = mystrdup(ti);
    q -> tags = mystrdup(ta);
    q -> answer_c = ac;
    q -> comment_c = cc;
    q -> favorite_c = fc;
    q -> answerList = NULL;
    return q;
}

/* Gets (Obter valor das variaveis da estrutura) */
long get_id_quest(Quest q){
    return q->id;
}
Date get_date_quest(Quest q){
    Date d = q->creationDate;
    return createDate(get_day(d),get_month(d),get_year(d));
}
int get_score_quest(Quest q){
    return q->score;
}
long get_owner_id_quest(Quest q){
    return q->ownerUserId;
}
char* get_title_quest(Quest q){
    return mystrdup(q->title);
}
char* get_tags_quest(Quest q){
    return mystrdup(q->tags);
}
int get_answer_c_quest(Quest q){
    return q->answer_c;
}
int get_comment_c_quest(Quest q){
    return q->comment_c;
}
int get_favorite_c_quest(Quest q){
    return q->favorite_c;
}
GSList* get_answer_list_quest(Quest q){
    if(q)
        return q->answerList;
    return NULL;
}

void set_answer_list_quest(Quest q,GSList* l){
    if(q)
        q->answerList = l;
}

void set_tags_quest(Quest q,char* t){
    if(q)
        q->tags = t;
}

//Imprimir o conteudo da pergunta.
void print_quest(Quest q){
    if(q != NULL){
    print_date(q->creationDate);
    printf("Quest:\n\n\t Id: %ld\n\tScore: %d\n\tOwnerUserID: %ld\n\tTitle: %s\n\tI Tags: %s\n\t Answer_c: %d\n\tComment_c: %d\n\tFavorite_c: %d\n\t",
            q->id,q->score,
            q->ownerUserId,q->title,q->tags,q->answer_c,q->comment_c,q->favorite_c); 
    printf("\n\n");
    }
}

/* Função resposável por adicionar as answers às quests. */
void add_answer_quest(Quest q, Answer a){
    GSList* l = q->answerList;
    q->answerList = g_slist_prepend(l,a);
}
