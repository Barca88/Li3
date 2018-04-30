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

static int id_compare_answer(long a,long b){
    if(a<b)
        return -1;
    else
        return 1;
    return 0;
}

int compare_answer(gconstpointer t1, gconstpointer t2){
    Date d1 = get_date_answer((Answer)GPOINTER_TO_SIZE(t1));
    Date d2 = get_date_answer((Answer)GPOINTER_TO_SIZE(t2));
    long id1 = get_id_answer((Answer)GPOINTER_TO_SIZE(t1));
    long id2 = get_id_answer((Answer)GPOINTER_TO_SIZE(t2));
    int c = 0;
    c = (-1)*date_compare(d1,d2);
    if(!c)
        c = id_compare_answer(id1,id2);
    return c;
}

//Função de comparação de score para ordenar uma lista ligada.
gint score_compare_answer(gconstpointer a,gconstpointer b){
     int f = get_score_answer((Answer)a);
     int s = get_score_answer((Answer)b);
     if(f<s) return 1;
     else if(f>s) return -1;
     else return -1*compare_answer(a,b);
}

/* Quest para a lista ligada. */
void to_list_answer(gpointer key,gpointer value,gpointer data){
    query6 ld = (query6)GPOINTER_TO_SIZE(data);
    set_list_6(ld,g_slist_prepend(get_list_6(ld),value));
}
/*adiciona o id da quest a qual a answer em causa responde*/
void iter_answer9(gpointer data,gpointer user_data){
    if(data != NULL){
        GHashTable* h = (GHashTable*)GPOINTER_TO_SIZE(user_data);
        Answer a = (Answer)GPOINTER_TO_SIZE(data);
        g_hash_table_add(h,GSIZE_TO_POINTER(get_parent_id_answer(a)));
    }
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
    free_date(a->creationDate);
    free(a);
}
void free_g_answer(gpointer g){
    Answer a = (Answer)GPOINTER_TO_SIZE(g);
    free_answer(a);
    g_free(g);
}
