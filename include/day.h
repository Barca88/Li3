/** @file day.h
 *  @brief Protótipos das funções que trabalham com os Day.
 *
 *  O ficheiro contem os prototipos das funçoes da estrutura Day.
 *
 *  @author Grupo 19
 */

#ifndef __DAY_H__
#define __DAY_H__

#include "queriesdata.h"
#include "date.h"
#include "answer.h"
#include "quest.h"
#include <glib.h>
#include <stdlib.h>

/**
 * @brief Declaração do tipo Day, um tipo abstrato. 
 */
typedef struct day* Day;

/** @brief Inicializa a estrutura Day, alocando espaço para a mesma. 
 *  @param d Date.
 *  @return Day.
 */
Day init_day(Date d);

//Métodos

/** @brief Quest num dia. 
 *
 *  @param d Day.
 *  @param q Quest.
 *  @return Void.
 */
void add_quest_day(Day d, Quest q);
/** @brief Answer num dia. 
 *
 *  @param d Day.
 *  @param a Answer.
 *  @return Void.
 */
void add_answer_day(Day d, Answer a);

//Gettres

/** @brief Retorna o nº de pergundas num dia.
 *
 *  @param d Day.
 *  @return Nº de quest num dia.
 */
int get_n_quest(Day d);
/** @brief Retorna o nº de respostas num dia.
 *
 *  @param d Day.
 *  @return Nº de answer num dia.
 */
int get_n_answer(Day d);
/** @brief Retorna hash com as quest de um determinado dia.
 *
 *  @param d Day.
 *  @return hash.
 */
GHashTable* get_hash_quest_day(Day d);
/** @brief Retorna hash com as answer de um determinado dia.
 *
 *  @param d Day.
 *  @return hash.
 */
GHashTable* get_hash_answer_day(Day d);
/** @brief Retorna a data de um dia.
 *
 *  @param d Day.
 *  @return hash.
 */
Date get_date_day(Day d);

gboolean count_posts_day(gpointer key,gpointer value,gpointer data);

gboolean iter_tag_day(gpointer key,gpointer value,gpointer data);

gboolean iter_vote_a_day(gpointer key,gpointer value,gpointer data);

gboolean iter_day7(gpointer key,gpointer value,gpointer data);


//Print
void print_aux(gpointer key,gpointer value,gpointer data);
/* Imprime o conteudo de um dia */
void print_day(Day d);
void free_day(Day d);
void free_g_day(gpointer g);
#endif
