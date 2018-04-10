#ifndef __DATE_H__
#define __DATE_H__
#include <glib.h>

typedef struct date* Date;

Date createDate(int day, int month, int year);
int get_day(Date d);
int get_month(Date d); // must return a value between 0 and 11 
int get_year(Date d);
Date date_from_string(char* date);
int date_compare(gconstpointer p1, gconstpointer p2);
void free_date(Date d);
#endif
