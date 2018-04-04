#include <stdlib.h>
#include "date.h"
#include <glib.h>

struct date {
  int day;
  int month;
  int year;
};

Date createDate(int day, int month, int year) {
    Date d = malloc(sizeof(struct date));
    d->day = day;
    d->month = month;
    d->year = year;
    return d;
}

int get_day(Date d) {
    return d->day; 
}

int get_month(Date d) {
    return d->month;
}

int get_year(Date d) {
    return d->year;
}

//retorna -1 se d1 é mais antigo, 0 se iguais, 1 se d1 é mais recente
int date_compare(gconstpointer p1, gconstpointer p2){
    Date d1 = (Date)GPOINTER_TO_SIZE(p1);
    Date d2 = (Date)GPOINTER_TO_SIZE(p2);

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
        else
            return 0;
    }
    return -2;
}

void free_date(Date d) {
    free(d);
}

