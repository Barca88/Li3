#ifndef __PARSER_H__
#define __PARSER_H__
#include "interface.h"
#include <glib.h>

void streamUsers(GHashTable* hu,char* path);

void streamPosts(GTree* hu,char* path);

#endif
