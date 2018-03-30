#include <stdlib.h>
#include "date.h"

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
int date_compare(Date d1, Date d2){
    if (d1.year < d2.year)
        return -1;
    else if (d1.year > d2.year)
        return 1;
    if (d1.year == d2.year){
        if (d1.month < d2.month)
            return -1;
        else if (d1.month > d2.month)
            return 1;
        else if (d1.day < d2.day)
            return -1;
        else if(d1.day > d2.day)
            return 1;
        else
            return 0;
    }
}

void free_date(Date d) {
    free(d);
}

