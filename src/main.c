#include "interface.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "users.h"
static void p_tempo(clock_t t){
    printf("%fs\n",((float)t)/CLOCKS_PER_SEC);
}

int main(int argc,char** argv){
    clock_t tpf,lod,q1,q2,q3,q4,q5,q6,q7,q8,q9,q10,q11,cle;
    tpf = clock();

    TAD_community new = init();
    new = load(new,argv[1]);
    lod = clock()-tpf;
    Date a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q;
    a = createDate(1,7,2016);
    b = createDate(31,7,2016);
    c = createDate(1,1,2014);
    d = createDate(31,12,2014);
    e = createDate(1,3,2013);
    f = createDate(31,3,2013);
    g = createDate(31,1,2014);
    h = createDate(1,11,2015);
    i = createDate(30,11,2015);
    j = createDate(1,5,2013);
    k = createDate(6,5,2013);
    l = createDate(1,8,2014);
    m = createDate(11,8,2014);
    n = createDate(1,1,2012);
    o = createDate(31,12,2012);
    p = createDate(1,11,2013);
    q = createDate(30,11,2013);

    q1 = clock();
    //query1
    //info_from_post(new,801049);
    info_from_post(new,796430);
    q1 = clock()-q1;
    q2 = clock();
    //query2
    //top_most_active(new,10);
    top_most_active(new,100);
    q2 = clock() - q2;
    q3 = clock();
    //query3
    //total_posts(new,a,b);
    total_posts(new,c,d);
    q3 = clock() - q3;
    q4 = clock();
    //query4
    //questions_with_tag(new,"package-management",e,f);
    questions_with_tag(new,"nautilus",c,g);
    q4 = clock() - q4;
    q5 = clock();
    //query5
    //get_user_info(new,15811);
    get_user_info(new,449);
    q5 = clock() - q5;
    q6 = clock();
    //query6
    //most_voted_answers(new,5,h,i);
    most_voted_answers(new,50,j,k);
    q6 = clock() - q6;
    q7 = clock();
    //query7
    //most_answered_questions(new,10,l,m);
    most_answered_questions(new,100,n,o);
    q7 = clock() - q7;
    q8 = clock();
    //query8
    //contains_word(new,"kde",10);
    contains_word(new,"glib",10);
    q8 = clock() - q8;
    q9 = clock();
    //query9
    //both_participated(new,87,5691,10);
    both_participated(new,253,455,10);
    q9 = clock() - q9;
    q10 = clock();
    //query10
    //better_answer(new,30334);
    better_answer(new,5942);
    q10 = clock() - q10;
    q11 = clock();
    //query11
    //most_used_best_rep(new,5,p,q);
    most_used_best_rep(new,10,c,d);
    q11 = clock() - q11;
    cle = clock();
    clean(new);

    free(new);
    cle = clock() - cle;
    tpf =clock() - tpf;
    printf("Tempo total:\n");
    p_tempo(tpf);
    printf("\tLoad: ");
    p_tempo(lod);
    printf("\tQuerie 1: ");
    p_tempo(q1);
    printf("\tQuerie 2: ");
    p_tempo(q2);
    printf("\tQuerie 3: ");
    p_tempo(q3);
    printf("\tQuerie 4: ");
    p_tempo(q4);
    printf("\tQuerie 5: ");
    p_tempo(q5);
    printf("\tQuerie 6: ");
    p_tempo(q6);
    printf("\tQuerie 7: ");
    p_tempo(q7);
    printf("\tQuerie 8: ");
    p_tempo(q8);
    printf("\tQuerie 9: ");
    p_tempo(q9);
    printf("\tQuerie 10: ");
    p_tempo(q10);
    printf("\tQuerie 11: ");
    p_tempo(q11);
    printf("\tClean: ");
    p_tempo(cle);
    //int pois;
    //scanf("%d",&pois);
    return 0;
}
