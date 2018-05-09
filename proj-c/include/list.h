/** @file list.h
 *  @brief Protótipos das funções que trabalham com as List.
 *
 *  O ficheiro contem os prototipos das funçoes da estrutura List.
 *
 *  @author Grupo 19
 */

#ifndef __LONG_LIST__
#define __LONG_LIST__

/**
 * @brief Declaração do tipo LONG_list, um tipo abstrato.
 */
typedef struct llist * LONG_list;

int get_size(LONG_list l);
/** @brief Criação de um LONG_list.
 *  @param size tamanho alocado para um LONG_list.
 *  @return LONG_list.
 */
LONG_list create_list(int size);
/** @brief Retorna lista.
 *
 *  @param l lista.
 *  @param index .
 *  @return Lista.
 */
long get_list(LONG_list l, int index);
/** @brief Lista.
 *
 *  @param l lista.
 *  @param index .
 *  @param value .
 *  @return Void.
 */
void set_list(LONG_list l, int index, long value);
/** @brief Liberta o espaço ocupado pela lista.
 *
 *  @param l lista.
 *  @return Void.
 */
void free_list(LONG_list l);
#endif
