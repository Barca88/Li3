/** @file tag.h
 *  @brief Protótipos das funções que trabalham com as Tag.
 *
 *  O ficheiro contem os prototipos das funçoes da estrutura Tag.
 *
 *  @author Grupo 19
 */

#ifndef __TAG_H__
#define __TAG_H__

#include "common.h"
#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Declaração do tipo Tag, um tipo abstrato.
 */
typedef struct tag* Tag;

/** @brief Criação das Tags.
 *  @param id id da tag.
 *  @param tag tag pretendida.
 *  @param t_ctag count tag.
 *  @return Tag.
 */
Tag create_tag(long id,char* tag, int t_ctag);

//Setters

/** @brief Id da Tag.
 *
 *  @param t Tag.
 *  @param id_out id tag.
 *  @return Void.
 */
void set_id_tag (Tag t, long id_out);
/** @brief Tag.
 *
 *  @param t Tag.
 *  @param g_tag tag dada.
 *  @return Void.
 */
void set_tag (Tag t, char* g_tag);
/** @brief Nº de vezes que a tag foi usada.
 *
 *  @param t Tag.
 *  @param count_tag nº de vezes que uma tag é usada.
 *  @return Void.
 */
void set_n_used (Tag t, int count_tag);

//Getters

/** @brief Retorna o id da tag.
 *
 *  @param t Tag.
 *  @return Id da Tag.
 */
long get_id_tag (Tag t);
/** @brief Retorna a tag pretendida.
 *
 *  @param t Tag.
 *  @return Tag.
 */
char* get_tag (Tag t);
/** @brief Retorna o nº de vezes que uma tag é usada.
 *
 *  @param t Tag.
 *  @return Nº de vezes que uma tag é usada.
 */
int get_n_used (Tag t);

//Métodos
int equal_tag(Tag t,char* s);

void print_tag(Tag t);
/** @brief Liberta o espaço ocupado pela tag.
 *
 *  @param Tag.
 *  @return Void.
 */
void free_tag(Tag t);
void free_g_tag(gpointer g);
#endif
