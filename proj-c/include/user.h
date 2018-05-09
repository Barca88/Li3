/** @file user.h
 *  @brief Protótipos das funções que trabalham com os User.
 *
 *  O ficheiro contem os prototipos das funçoes da estrutura User.
 *
 *  @author Grupo 19
 */

#ifndef __USER_H_
#define __USER_H_

/**
 * @brief Declaração do tipo User, um tipo abstrato. 
 */
typedef struct user* USER;

/** @brief Criação de um user.
 *  @param short_bio short bio do user.
 *  @param post_history Histórico do user.
 *  @return USER.
 */
USER create_user(char* short_bio, long* post_history);

/** @brief Retorna o ownerUserId do utilizador que fez a answer.
 *
 *  @param a Answer.
 *  @return ownerUserId.
 */
char* get_bio(USER u);

/** @brief Retorna os 10 últimos posts de um user. Caso um utilizador tenha menos de 10 posts, por -1 como padding.
 *
 *  @param u USER.
 *  @return 10 últimos posts de um utilizador.
 */
long* get_10_latest_posts(USER u);

/** @brief Liberta o espaço ocupado pelo user.
 *
 *  @param u USER.
 *  @return Void.
 */
void free_user(USER u);
#endif
