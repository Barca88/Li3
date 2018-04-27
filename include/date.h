/** @file date.h
 *  @brief Protótipos das funções que trabalham com as Date.
 *
 *  O ficheiro contem os prototipos das funçoes da estrutura Date.
 *
 *  @author Grupo 19
 */

#ifndef __DATE_H__
#define __DATE_H__
#include <glib.h>

/**
 * @brief Declaração do tipo Date, um tipo abstrato. 
 */
typedef struct date* Date;
/**
 * @brief Declaração do tipo DatePair, um tipo abstrato. 
 */
typedef struct date_id* DatePair;

/** @brief Estrutura responsável pela criação de uma Date. 
 *  @param day dia de uma data.
 *  @param month mês de uma data.
 *  @param year ano de uma data.
 *  @return Date.
 */
Date createDate(int day, int month, int year);

/** @brief Retorna o dia de uma data.
 *
 *  @param d Date.
 *  @return day.
 */
int get_day(Date d);
/** @brief Retorna o mês de uma data.
 *
 *  @param d Date.
 *  @return month.
 */
int get_month(Date d);
/** @brief Retorna o ano de uma data.
 *
 *  @param d Date.
 *  @return year.
 */
int get_year(Date d);
/** @brief Retorna uma data.
 *
 *  @param date Data.
 *  @return Data.
 */
Date date_from_string(char* date);

/** @brief Estrutura responsável pela criação de um par de datas. 
 *  @param d Data.
 *  @param id do post.
 *  @return DatePair.
 */
DatePair creat_date_pair(Date d,long id);
/** @brief Retorna uma data.
 *
 *  @param dp Datepair.
 *  @return Data.
 */
Date get_fst(DatePair dp);
/** @brief Retorna uma data.
 *
 *  @param dp Datepair.
 *  @return Data.
 */
long get_scd(DatePair dp);
/* Imprime o conteudo da data */
void print_date(Date d);

/** @brief Compara um date pair.
 *
 *  @param p1 Apontador para uma data1.
 *  @param p2 Apontador para uma data2. 
 *  @return date_pair compare.
 */
int date_pair_compare(gconstpointer p1, gconstpointer p2);
/** @brief Compara uma data.
 *
 *  @param p1 Apontador para uma data1.
 *  @param p2 Apontador para uma data2. 
 *  @return date compare.
 */
int date_compare(gconstpointer p1, gconstpointer p2);
/** @brief Compara a data de uma quest.
 *
 *  @param p1 Apontador para uma data1.
 *  @param p2 Apontador para uma data2. 
 *  @return quest compare.
 */
int compare_quest(gconstpointer p1, gconstpointer p2);
/** @brief Compara a data de uma answer.
 *
 *  @param p1 Apontador para uma data1.
 *  @param p2 Apontador para uma data2. 
 *  @return answer compare.
 */
int compare_answer(gconstpointer p1, gconstpointer p2);

/** @brief Liberta o espaço ocupado pela data.
 *
 *  @param d Data.
 *  @return Void.
 */
void free_date(Date d);
#endif
