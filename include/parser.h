#ifndef __PARSER_H__
#define __PARSER_H__

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <xmlreader.h>
#include <string.h>
#include <glib.h>
#include "interface.h"
#include "nodeUser.h"
#include "date.h"
#include "post.h"

void streamUsers(GHashTable* hu,char* path);

void streamPosts(TAD_community com,char* path);

#endif
