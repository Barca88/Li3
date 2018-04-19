#include "interface.h"
#include <time.h>
#include <stdio.h>

int main(int argc,char** argv){
    clock_t tpf;
    tpf =clock();

    TAD_community new = init();
    new = load(new,argv[1]);

    Date a,b;
    a = createDate(1,2,1900);
    b = createDate(3,10,2020);

    info_from_post(new,1);
    top_most_active(new,12);
    total_posts(new,a,b);
    questions_with_tag(new,"handcent-sms",a,b);
    get_user_info(new,88);
    most_voted_answers(new,10,a,b);
    //most_answered_questions(new,10,a,b);
    //contains_word(new,"rooting",10);
    //both_participated(new,1,2,10);
    //better_answer(new,1);
    //most_used_best_rep(new,a,b);

    tpf =clock() - tpf;
    printf("Demorou %f segundos a ler\n",((float)tpf)/CLOCKS_PER_SEC);

    return 0;
} 
