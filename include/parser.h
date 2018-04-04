#ifndef __PARSER_H__
#define __PARSER_H__
#include <glib.h>
void streamUsers(GHashTable* hu,char* path);

void streamPosts(GTree* hu,GHashTable* hp,char* path);

#endif
