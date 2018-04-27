/** @file answer.h
 *  @brief Protótipos das funções que trabalham com as Answer.
 *
 *  O ficheiro contem os prototipos das funçoes da estrutura Answer.
 *
 *  @author Grupo 19
 */

#ifndef __ANSWER_H__
#define __ANSWER_H__

#include "date.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Declaração do tipo Answer, um tipo abstrato. 
 */
typedef struct answer* Answer;

/** @brief Inicializa a estrutura Answer, alocando espaço para a mesma. 
 *  @param id id da answer.
 *  @param ptid parentId (id da quest à qual esta answer responde).
 *  @param cd creationDate.
 *  @param s score.
 *  @param ouid ownerUserId.
 *  @param cc commentCount.
 *  @param fc favoriteCount.
 *  @return Answer.
 */
Answer init_answer(long id,int ptid,Date cd,int s,long ouid,int cc,int fc);

//Getters

/** @brief Retorna o id da resposta.
 *
 *  @param a Answer.
 *  @return Id da resposta.
 */
long get_id_answer(Answer a);
/** @brief Retorna o id da quest à qual esta answer responde.
 *
 *  @param a Answer.
 *  @return parentId.
 */
long get_parent_id_answer(Answer a);
/** @brief Retorna a data da criação da answer.
 *
 *  @param a Answer.
 *  @return date answer.
 */
Date get_date_answer(Answer a);
/** @brief Retorna o score de uma answer.
 *
 *  @param a Answer.
 *  @return score da answer.
 */
int get_score_answer(Answer a);
/** @brief Retorna o ownerUserId do utilizador que fez a answer.
 *
 *  @param a Answer.
 *  @return ownerUserId.
 */
long get_owner_user_id_answer(Answer a);
/** @brief Retorna commentCount de uma answer.
 *
 *  @param a Answer.
 *  @return Nº de comentários de uma answer.
 */
int get_comment_count_answer(Answer a);
/** @brief Retorna o nº de votos de uma answer.
 *
 *  @param a Answer.
 *  @return Answer com mais pontuação.
 */
int get_favorite_count_answer(Answer a);
/** @brief Retorna a melhor respostas.
 *
 *  @param a Answer.
 *  @return average answer.
 */
float get_average_answer(Answer a);

/** @brief Média das answers. 
 *
 *  @param a Answer.
 *  @param f.
 *  @return Void.
 */
void set_average_answer(Answer a,float f);
/** @brief Compara a data de uma answer.
 *
 *  @param p1 Apontador para uma data1.
 *  @param p2 Apontador para uma data2. 
 *  @return answer compare.
 */
int compare_answer(gconstpointer p1, gconstpointer p2);

/* Imprime o conteudo do post */
void print_answer(Answer post);

/** @brief Liberta o espaço ocupado pela answer.
 *
 *  @param a Answer.
 *  @return Void.
 */
void free_answer(Answer a);

#endif
