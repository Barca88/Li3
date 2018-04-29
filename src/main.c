#include "interface.h"
#include <time.h>
#include <stdio.h>

int main(int argc,char** argv){
    clock_t tpf;
    tpf =clock();

    TAD_community new = init();
    new = load(new,argv[1]);

    Date a,b,c,d,e,f,g,h,i,j,k;
    a = createDate(1,7,2016);
    b = createDate(31,7,2016);
    c = createDate(1,1,2014);
    d = createDate(31,12,2014);
    e = createDate(1,3,2013);
    f = createDate(31,3,2013);
    g = createDate(31,1,2014);
    h = createDate(01,11,2015);
    i = createDate(30,11,2015);
    j = createDate(1,5,2013);
    k = createDate(6,5,2013);

<<<<<<< HEAD
    info_from_post(new,801049);
    info_from_post(new,796430);
    top_most_active(new,10);
    top_most_active(new,100);
    total_posts(new,a,b);
    total_posts(new,c,d);
    questions_with_tag(new,"package-management",e,f);
    questions_with_tag(new,"nautilus",c,g);
    get_user_info(new,15811);
    get_user_info(new,449);
    most_voted_answers(new,5,h,i);
    most_voted_answers(new,50,j,k);
    most_answered_questions(new,2,a,b);
    contains_word(new,"Nexus",10);
    both_participated(new,1465,16575,10000);
=======

    free_str_pair(info_from_post(new,801049));
    free_str_pair(info_from_post(new,796430));
    free_list(top_most_active(new,10));
    free_list(top_most_active(new,100));
    free_long_pair(total_posts(new,a,b));
    free_long_pair(total_posts(new,c,d));
    free_list(questions_with_tag(new,"package-management",e,f));
    free_list(questions_with_tag(new,"nautilus",c,g));
    free_user(get_user_info(new,15811));
    free_user(get_user_info(new,449));
    free_list(most_voted_answers(new,11,a,b));
    free_list(most_answered_questions(new,2,a,b));
    free_list(contains_word(new,"Nexus",10));
    free_list(both_participated(new,1465,16575,10000));
>>>>>>> 198e8486339aefd5939587e565d1d02e6352d448
    better_answer(new,30334);
    free_list(most_used_best_rep(new,10,c,d));

    tpf =clock() - tpf;
    printf("Demorou %f segundos a ler\n",((float)tpf)/CLOCKS_PER_SEC);

    return 0;
}
