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
long get_id_answer(Answer a);
long get_parent_id_answer(Answer a);
Date get_date_answer(Answer a);
int get_score_answer(Answer a);
long get_owner_user_id_answer(Answer a);
int get_comment_count_answer(Answer a);
int get_favorite_count_answer(Answer a);
float get_average_answer(Answer a);
void set_average_answer(Answer a,float f);

//Print
void print_answer(Answer post);

//Clear
void free_answer(Answer a);

#endif
