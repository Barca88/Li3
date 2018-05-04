#include "tag.h"
#include "date.h"
#include "queriesdata.h"
#include "quest.h"

/* Definição da estrutura das tag. */
struct tag {
	long id; /* Id da tag. */
	char* tag; /* Tag pretendida. */
	int n_used; /* Nº de vezes que uma determinada tag foi usada. */
};

/* Funcao reponsável pela alocacao de memoria e a inicializacao dos campos, da tag.*/
Tag create_tag(long id, char* s){
    Tag t = malloc(sizeof(struct tag));
    t->id = id;
    t->tag = mystrdup(s);
    t->n_used = 0;
    return t;
}

/* Gets (Obter valor das variaveis da estrutura) */
long get_id_tag (Tag t) {
	return t->id;
}

char* get_tag (Tag t) {
	return mystrdup(t->tag);
}

int get_n_used (Tag t) {
	return t->n_used;
}

void set_id_tag (Tag t, long id_out) {
	t->id = id_out;
}

void set_tag (Tag t, char* l) {
    free(t->tag);
	t->tag = mystrdup(l);
}

void inc_n_used (Tag t) {
    if(t)
	    (t->n_used)++;
}

int equal_tag(Tag t,char* s){
    if(t == NULL || s[0] == '\0') return -1;
    return strcmp(t->tag,s);
}

int comp_n_used_tag(gconstpointer a,gconstpointer b){
     int r1 = get_n_used((Tag)a);
     int r2 = get_n_used((Tag)b);
     if(r1 < r2) return 1;
     else if(r1 > r2) return -1;
     else if(get_id_tag((Tag)a) < get_id_tag((Tag)b)) return -1;
     else return 1;
     return 0;
}

void tag_list11(gpointer key,gpointer value,gpointer data){
    GSList** d = (GSList**)GPOINTER_TO_SIZE(data);
    if (get_n_used((Tag)value) > 0){
        *d = g_slist_prepend(*d,(Tag)value);
    }
}

}
void load_n_used_tag(gpointer value,gpointer data){
    query11 aux = (query11)GPOINTER_TO_SIZE(data);
    Date b = get_begin_11(aux);
    Date e = get_end_11(aux);
    char* auxt = NULL;
    if (between_dates(b,e,get_date_quest(value))){
        auxt = get_tags_quest(value);
        auxt += 1;
        auxt[strlen(auxt)-1] = '\0';
        char *p;
        p = strtok (auxt,"><");
        while (p) {
            inc_n_used(g_hash_table_lookup(get_ht_11(aux),p));
            p = strtok (NULL, "><");
        }
		free(auxt-1);
    }
}

void print_tag(Tag t){
    if(t)
        printf("Tag:\n\tId: %ld\n\tTag name: %s\n\tN used: %d\n",t->id,t->tag,t->n_used);
}

static void set_zero_n_used(gpointer key, gpointer value, gpointer data){
	Tag t = (Tag)GPOINTER_TO_SIZE(value);
	t->n_used = 0;
}

/*Limpa todos os n_used*/
void clean_tags(GHashTable* tags){
	g_hash_table_foreach(tags, set_zero_n_used,NULL);
}
/* Apaga a tag dando free na memoria alocada. */
void free_tag(Tag t){
    free(t->tag);
    free(t);
}
void free_g_tag(gpointer g){
	Tag t = (Tag)GPOINTER_TO_SIZE(g);
	free_tag(t);
    //g_free(g);
}
