#include <stdlib.h>
#include <glib.h>
#include <stdio.h>
#include "date.h"
#include "quest.h"
#include "answer.h"

/* Definição da estrutura de datas (date). */
struct date {
  int day; /* Dia de uma data. */
  int month; /* Mês de uma data. */
  int year; /* Ano de uma data. */
};

/* Função reponsável pela criação de uma data. */
Date createDate(int day, int month, int year) {
    Date d = malloc(sizeof(struct date));
    d->day = day;
    d->month = month;
    d->year = year;
    return d;
}

/* Gets (Obter valor das variaveis da estrutura) */
int get_day(Date d) {
    return d->day;
}

int get_month(Date d) {
    return d->month;
}

int get_year(Date d) {
    return d->year;
}

/* Imprimir o conteudo da data. */
void print_date(Date d){
    if(d)
        printf("%dd-%dm-%da\n",d->day,d->month,d->year);
}

//Retorna -1 se d1 é mais antigo, 0 se iguais, 1 se d1 é mais recente
int date_compare(gconstpointer t1, gconstpointer t2){
    Date d1 = (Date)GPOINTER_TO_SIZE(t1);
    Date d2 = (Date)GPOINTER_TO_SIZE(t2);

    if (get_year(d1) < get_year(d2))
        return -1;
    else if (get_year(d1) > get_year(d2))
        return 1;
    if (get_year(d1) == get_year(d2)){
        if (get_month(d1) < get_month(d2))
            return -1;
        else if (get_month(d1) > get_month(d2))
            return 1;
        else if (get_day(d1) < get_day(d2))
            return -1;
        else if(get_day(d1) > get_day(d2))
            return 1;
        else return 0;
    }
    return -2;
}

//Cria uma data a partir de uma string.  
Date date_from_string(char* date){
    *(date + 10) = '\0';
    char* day = date+8;
    *(date + 7) = '\0';
    char* month = date+5;
    *(date + 4) = '\0';
    char* year = date;

    Date a = createDate(atoi(day),atoi(month),atoi(year));
    return a;
}

/* Apaga a data dando free na memoria alocada. */
void free_date(Date d) {
    free(d);
}
//free utilizado pela g_tree_new_full
void free_g_date(gpointer g){
    Date d = (Date)GPOINTER_TO_SIZE(g);
    free_date(d);
    g_free(g);
}
