#ifndef __QUEST_H__
#define __QUEST_H__

#include "answer.h"
#include "date.h"
#include <glib.h>
#include <stdlib.h>

typedef struct quest* Quest;

//Metodo de Criação
Quest init_quest(long id, Date cd, int s,long ouid, char* ti, char* ta, int ac, 
        int cc, int fc);

long get_id_quest(Quest q);
Date get_date_quest(Quest q);
int get_score_quest(Quest q);
long get_owner_id_quest(Quest q);
char* get_title_quest(Quest q);
char* get_tags_quest(Quest q);
int get_answer_c_quest(Quest q);
int get_comment_c_quest(Quest q);
int get_favorite_c_quest(Quest q);
GSList* get_answer_list_quest(Quest q);

void add_answer_quest(Quest q, Answer a);
#endif
