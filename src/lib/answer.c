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
Answer init_answer(long id,int pid,Date cd,int s,long ouid,int cc,int fc){
    Answer a = malloc(sizeof(struct answer));
    a->id = id;
    a->parentId = pid;
    a->creationDate = cd;
    a->score = s;
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
void print_answer(Answer post){
    if(post != NULL)
    print_date(post->creationDate);
    printf("Answer:\n\n\tId: %ld\n\tParentId: %ld\n\tScore: %d\n\tOwnerUserID: %ld\n\tCommentCount: %d\nFavoriteCount: %d\n",
            post->id,post->parentId,post->score,
            post->ownerUserId,post->commentCount,post->favoriteCount); 
    printf("\n\n");
}

//Apaga a resposta dando free na memoria alocada.
void free_answer(Answer a){
    free(a);
}
