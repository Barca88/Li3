/** @file quest.h
 *  @brief Protótipos das funções que trabalham com as Quest.
 *
 *  O ficheiro contem os prototipos das funçoes da estrutura Quest.
 *
 *  @author Grupo 19
 */

#ifndef __QUEST_H__
#define __QUEST_H__

#include "queriesdata.h"
#include "answer.h"
#include "date.h"
#include <glib.h>
#include <stdlib.h>

/**
 * @brief Declaração do tipo Quest, um tipo abstrato.
 */
typedef struct quest* Quest;

/** @brief Inicializa a estrutura Quest, alocando espaço para a mesma.
 *  @param id id da quest.
 *  @param cd creationDate.
 *  @param s score.
 *  @param ouid ownerUserId .
 *  @param ti título.
 *  @param ta tags.
 *  @param ac answerCount .
 *  @param cc commentCount.
 *  @param fc favoriteCount.
 *  @return Quest.
 */
Quest init_quest(long id, Date cd, int s,long ouid, char* ti, char* ta, int ac,
        int cc, int fc);

//Getters

/** @brief Retorna o id da quest.
 *
 *  @param q Quest.
 *  @return Id da pergunta.
 */
long get_id_quest(Quest q);
/** @brief Retorna a data da criação da quest.
 *
 *  @param q Quest.
 *  @return date quest.
 */
Date get_date_quest(Quest q);
/** @brief Retorna o score de uma quest.
 *
 *  @param q Quest.
 *  @return score da quest.
 */
int get_score_quest(Quest q);
/** @brief Retorna o ownerUserId do utilizador que fez a quest.
 *
 *  @param q Quest.
 *  @return ownerUserId.
 */
long get_owner_id_quest(Quest q);
/** @brief Retorna o título de uma quest.
 *
 *  @param q Quest.
 *  @return title.
 */
char* get_title_quest(Quest q);
/** @brief Retorna a tag de uma quest.
 *
 *  @param q Quest.
 *  @return tag.
 */
char* get_tags_quest(Quest q);
/** @brief Retorna answerCount de uma quest.
 *
 *  @param q Quest.
 *  @return Nº de respostas a uma quest.
 */
int get_answer_c_quest(Quest q);
/** @brief Retorna commentCount de uma quest.
 *
 *  @param q Quest.
 *  @return Nº de comentários de uma quest.
 */
int get_comment_c_quest(Quest q);
/** @brief Retorna nº de votos de uma quest.
 *
 *  @param q Quest.
 *  @return Quest com mais pontuação.
 */
int get_favorite_c_quest(Quest q);
/** @brief Retorna lista com as answers e quest.
 *
 *  @param q Quest.
 *  @return lista.
 */
GSList* get_answer_list_quest(Quest q);

/** @brief Associa as perguntas às respostas.
 *
 *  @param q Quest.
 *  @param l lista.
 *  @return Void.
 */
void set_answer_list_quest(Quest q,GSList* l);

void set_tags_quest(Quest q,char* t);
/** @brief Compara a data de uma quest.
 *
 *  @param p1 Apontador para uma data1.
 *  @param p2 Apontador para uma data2.
 *  @return quest compare.
 */
int compare_quest(gconstpointer p1, gconstpointer p2);

void comp_tags_quest(gpointer key,gpointer value,gpointer data);

/** @brief Quest to ID
  * @param data Apontador para a quest
  * @param user_Data Apontador para Hash de longs
  */
void iter_quest9(gpointer data, gpointer user_data);

/* Imprime o conteudo do post */
void print_quest(Quest post);

/* Função resposável por adicionar as answers às quests. */
void add_answer_quest(Quest q, Answer a);

/*Liberta a memoria alocada para a quest */
void free_quest(Quest q);
void free_g_quest(gpointer g);
#endif
