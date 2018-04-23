#include "answer.h"

/* Definição da estrutura das respostas (answer). */
struct answer{
    long id; /* Id da answer. */
    long parentId; /* Id da quest à qual esta answer responde. */
    Date creationDate; /* Data de criação da answer. */
    int score; /* Pontuação da answer. */
    long ownerUserId; /* Id do user que elaborou a answer. */
    int commentCount; /* Nº de comentários que a answer obteve. */
    int favoriteCount; /* Nº de votos favoritos */
    float average; /* Indica a melhor answer. */
};

/* Função que inicia a estrutura answer. */
Answer init_answer(long id,int pid,Date cd,int s,long ouid,int cc,int fc){
    Answer a = malloc(sizeof(struct answer));
    a->id = id;
    a->parentId = pid;
    a->creationDate = cd;
    a->score = s;
    a->ownerUserId = ouid;
    a->commentCount = cc;
    a->favoriteCount = fc;
    a->average = 0;
    return a;
}

/* Gets (Obter valor das variaveis da estrutura) */
long get_id_answer(Answer a){
    return a->id;
}
long get_parent_id_answer(Answer a){
    return a->parentId;
}
Date get_date_answer(Answer a){
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

float get_average_answer(Answer a){
    return a->average;
}

void set_average_answer(Answer a,float average){
    a->average = average;
}

/* Imprimir o conteudo da resposta. */
void print_answer(Answer post){
    if(post != NULL)
    print_date(post->creationDate);
    printf("Answer:\n\n\tId: %ld\n\tParentId: %ld\n\tScore: %d\n\tOwnerUserID: %ld\n\tCommentCount: %d\nFavoriteCount: %d\n",
            post->id,post->parentId,post->score,
            post->ownerUserId,post->commentCount,post->favoriteCount); 
    printf("\n\n");
}

/* Apaga a resposta dando free na memoria alocada. */
void free_answer(Answer a){
    free(a);
}
