#include "answer.h"

// Answer definitions.
struct answer{
    long id;
    long parentId; 
    Date creationDate;
    int score;
    long ownerUserId;
    int commentCount;
    int favoriteCount;
};

// Criar nova resposta.
Answer init_answer(long id,int ptid,Date cd,int s,long ouid,int cc,int fc){
    Answer a = malloc(sizeof(struct answer));
    a->id = id;
    a->parentId = pid;
    p->creationDate = cd;
    p->score = s;
    a->ownerUserId = ouid;
    a->commentCount = cc;
    a->favoriteCount = fc;
    return a;
}

//Obter valor das variaveis da estrutura.
int get_id_answer(Answer a){
    return a->id;
}
long get_parent_id_answer(Answer a){
    return a->parentId;
}
Date get_creation_date_answer(Answer a){
    return a->creationDate;
}
int get_score_answer(Answer a){
    return a->score;
}
long get_owner_user_id_answer(Answer a){
    return a->ownerUserId;
}
int get_comment_count_answer(Answer a){
    return a->commentCount;
}
int get_favorite_count_answer(Answer a){
    return a->favoriteCount;
}

//Imprimir o conteudo da resposta.
void print_Answer(Answer post){
    if(post != NULL)
    printf("Answer:\n\nId: %ld\nPostTypeId: %d\nParentId: %ld\nScore: %d\nOwnerUserID:
            %ld\nTitle: %s\nTags: %s\nAnswerCount: %d\nCommentCount: 
            %d\nFavoriteCount: %d\n",post->id,post->postTypeId,post->parentID,
            post->score,post->ownerUserID,post->title,post->tags,
            post->answerCount,post->commentCount,post->favoriteCount); 
    print_date(post->creationDate);
    printf("\n\n");
}

//Apaga a resposta dando free na memoria alocada.
void free_answer(Answer a){
    free(a);
}
