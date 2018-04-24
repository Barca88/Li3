#include "interface.h"
#include <time.h>
#include <stdio.h>

int main(int argc,char** argv){
    clock_t tpf;
    tpf =clock();

    TAD_community new = init();
    new = load(new,argv[1]);

    Date a,b;
    a = createDate(15,7,1995);
    b = createDate(3,10,2020);

    info_from_post(new,1);
    top_most_active(new,12);
    total_posts(new,a,a);
    questions_with_tag(new,"battery-life",a,b);
    get_user_info(new,10);
    most_voted_answers(new,11,a,b);
    most_answered_questions(new,2,a,b);
    contains_word(new,"Nexus",10);
    both_participated(new,449,15811,10000);
    better_answer(new,154309);
    //most_used_best_rep(new,6,a,b);

    tpf =clock() - tpf;
    printf("Demorou %f segundos a ler\n",((float)tpf)/CLOCKS_PER_SEC);

    return 0;
}
