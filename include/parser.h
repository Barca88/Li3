#ifndef __PARSER_H__
#define __PARSER_H__
#include <glib.h>
void streamUsers(GHashTable* hu,char* path);

void streamPosts(GTree* tp,GHashTable* hp,GHashTable* hu,char* path);

#endif
