/** @file parser.h
 *  @brief Protótipos das funções responsáveis por tratar dos ficheiros.
 *
 *  O ficheiro contem os prototipos das funçoes que implementam o parser.
 *
 *  @author Grupo 19
 */

#ifndef __PARSER_H__
#define __PARSER_H__

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <xmlreader.h>
#include <string.h>
#include <glib.h>
#include "interface.h"
#include "users.h"
#include "date.h"
#include "post.h"

/** @brief Resposável por fazer o parsing das tags.
 *
 *  @param GHashTable Estrutura.
 *  @param path Tags path.
 *  @return Void.
 */
void streamTags(GHashTable* ht,char* path);

/** @brief Resposável por fazer o parsing dos users.
 *
 *  @param GHashTable Estrutura.
 *  @param path Users path.
 *  @return Void.
 */
void streamUsers(GHashTable* hu,char* path);

/** @brief Resposável por fazer o parsing dos posts.
 *
 *  @param TAD_community Estrutura.
 *  @param path Posts path.
 *  @return Void.
 */
void streamPosts(TAD_community com,char* path);

#endif
