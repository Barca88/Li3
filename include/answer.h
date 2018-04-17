#ifndef __ANSWER_H__
#define __ANSWER_H__

#include "date.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct answer* Answer;

//Metodo de Criação
Answer init_answer(long id,int ptid,Date cd,int s,long ouid,int cc,int fc);

//Getters
int get_id_answer(Answer a);
long get_parent_id_answer(Answer a);
Date get_creation_date_answer(Answer a);
int get_score_answer(Answer a);
long get_owner_user_id_answer(Answer a);
int get_comment_count_answer(Answer a);
int get_favorite_count_answer(Answer a);

//Print
void print_answer(Answer aost);

//Clear
void free_answer(Answer a);

#endif
