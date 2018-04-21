/** @file pair.h
 *  @brief Protótipos das funções que trabalham com os Pair.
 *
 *  O ficheiro contem os prototipos das funçoes da estrutura Pair.
 *
 *  @author Grupo 19
 */

#ifndef __PAIR_H__
#define __PAIR_H__

/**
 * @brief Declaração do tipo STR_pair, um tipo abstrato. 
 */
typedef struct str_pair* STR_pair;

// STR_pair definitions
/** @brief Criação de um STR_pair.
 *  @param fst .
 *  @param str .
 *  @return STR_pair.
 */
STR_pair create_str_pair(char* fst, char* snd);
/** @brief . 
 *
 *  @param pair Par.
 *  @param str .
 *  @return Void.
 */
void set_fst_str(STR_pair pair, char* str);
/** @brief . 
 *
 *  @param pair Par.
 *  @param str .
 *  @return Void.
 */
void set_snd_str(STR_pair pair, char* str);
/** @brief Retorna .
 *
 *  @param pair Par.
 *  @return .
 */
char* get_fst_str(STR_pair pair);
/** @brief Retorna .
 *
 *  @param pair Par.
 *  @return .
 */
char* get_snd_str(STR_pair pair);
/** @brief Liberta o espaço ocupado pela str_pair.
 *
 *  @param pair Par.
 *  @return Void.
 */
void free_str_pair(STR_pair pair);

/**
 * @brief Declaração do tipo LONG_pair, um tipo abstrato. 
 */
typedef struct long_pair* LONG_pair;

/** @brief Criação de um LONG_pair.
 *  @param fst .
 *  @param str .
 *  @return LONG_pair.
 */
LONG_pair create_long_pair(long fst, long snd);
/** @brief . 
 *
 *  @param pair Par.
 *  @param l .
 *  @return Void.
 */
void set_fst_long(LONG_pair pair, long l);
/** @brief . 
 *
 *  @param pair Par.
 *  @param l .
 *  @return Void.
 */
void set_snd_long(LONG_pair pair, long l);
/** @brief Retorna .
 *
 *  @param pair Par.
 *  @return .
 */
long get_fst_long(LONG_pair pair);
/** @brief Retorna .
 *
 *  @param pair Par.
 *  @return .
 */
long get_snd_long(LONG_pair pair);
/** @brief Liberta o espaço ocupado pelo long_pair.
 *
 *  @param pair Par.
 *  @return Void.
 */
void free_long_pair(LONG_pair pair);

#endif
