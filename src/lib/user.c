#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "common.h"

/* Definição da estrutura dos utilizadores (user). */
struct user {
  char* bio; /* Short bio de um user. */
  long posts[10]; /* 10 últimos posts de um user. */
};

/* Função reponsável pela criação dos user. */
USER create_user(char* bio, long* post_history) {
  USER u = malloc(sizeof(struct user)); 
  u->bio = mystrdup(bio);
  memcpy(u->posts, post_history, sizeof(long) * 10);
  return u;
}

/* Gets (Obter valor das variaveis da estrutura) */
char* get_bio(USER u) {
  if(u)
    return u->bio;
  return NULL;
}

long* get_10_latest_posts(USER u) {
  long* r = malloc(sizeof(long)*10);
  memcpy(r, u->posts, sizeof(long)*10);
  return r;
}

/* Apaga o utilizador dando free na memoria alocada. */
void free_user(USER u) {
  if(u) {
    free(u->bio);
    free(u);
  }
}
