#include "quest.h"

// Questions definitions
struct quest{
    long id;
    Date creationDate;
    int score;
    long ownerUserId;
    char* title;
    char* tags;
    int answer_c;
    int comment_c;
    int favorite_c;
    GSList* answerList;
};

//Metodo de Criação
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

//Getters
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
    return q->answerList;
}

//Imprimir o conteudo da pergunta.
void print_quest(Quest post){
    if(post != NULL)
    print_date(post->creationDate);
    printf("Quest:\n\n\tId: %ld\n\tScore: %d\n\tOwnerUserID: %ld\n\tTitle: %s\n\t Tags: %s\n\t Answer_c: %d\n\tComment_c: %d\n\tFavorite_c: %d\n\t",
            post->id,post->score,
            post->ownerUserId,post->title,post->tags,post->answer_c,post->comment_c,post->favorite_c); 
    printf("\n\n");
}

void add_answer_quest(Quest q, Answer a){
    GSList* l = q->answerList;
    q->answerList = g_slist_prepend(l,a);
}
