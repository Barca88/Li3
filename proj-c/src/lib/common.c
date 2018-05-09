#include <common.h>
#include <string.h>
#include <stdlib.h>

// Definido para não dar warnings ao usar a função da GNU
char * mystrdup (const char *s) {
    if(s == NULL) return NULL;          
    char *d = malloc (strlen (s) + 1); 
    if (d == NULL) return NULL;       
    strcpy (d,s);                    
    return d;                       
}
