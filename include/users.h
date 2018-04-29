/** @file users.h
 *  @brief Protótipos das funções que trabalham com os Users.
 *
 *  O ficheiro contem os prototipos das funçoes da estrutura Users.
 *
 *  @author Grupo 19
 */

#ifndef __USERS_H__
#define __USERS_H__

#include <glib.h>
#include "answer.h"
#include "quest.h"

/**
 * @brief Declaração do tipo User, um tipo abstrato. 
 */
typedef struct node* User;

/** 
 * @brief Inicializa a estrutura User, alocando espaço para a mesma. 
 */
User init_user();

void set_id_user(User user, gint64 id);
void set_displayname_user(User user, char* dn);
void set_aboutme_user(User user, char* am);
void set_reputation_user(User user, long r); 
void set_quests_user(User user,GSList* q);
void set_answers_user(User user,GSList* a);

/** @brief Retorna o id do utilizador.
 *
 *  @param user User.
 *  @return Id do user.
 */
long get_id_user(User user);
/** @brief Retorna o displayname do utilizador.
 *
 *  @param user User.
 *  @return displayname user.
 */
char* get_displayname_user(User user);
/** @brief Retorna a short bio de um utilizador.
 *
 *  @param user User.
 *  @return aboutme de um user.
 */
char* get_aboutme_user(User user);
/** @brief Retorna a retupação de um utilizador.
 *
 *  @param user User.
 *  @return Reputation de um user.
 */
long get_reputation_user(User user);
/** @brief Retorna o nº de post de um user.
 *
 *  @param user User.
 *  @return Total de posts que um user fez.
 */
int get_nr_posts_user(User user);
/** @brief Retorna as quest de um user.
 *
 *  @param user User.
 *  @return Lista de quest.
 */
GSList* get_quests_user(User user);
/** @brief Retorna as answer de um user.
 *
 *  @param user User.
 *  @return Lista de answer.
 */
GSList* get_answers_user(User user);

/** @brief Nº de posts de um user. 
 *
 *  @param user User.
 *  @return Void.
 */
void inc_nr_posts(User user);

gint comp_nr_posts_user(gconstpointer a,gconstpointer b);

/** @brief Imprime o conteúdo de uma quest. 
 *
 *  @param data apontador para uma data.
 *  @param n apontador para um quest.
 *  @return Void.
 */
void print_q(gpointer data, gpointer n);
/** @brief Imprime o conteúdo de uma answers. 
 *
 *  @param data apontador para uma data.
 *  @param n apontador para uma answer.
 *  @return Void.
 */
void print_a(gpointer data, gpointer n);
/* Imprime o conteúdo de um user */
void print_user(User user);

#endif
