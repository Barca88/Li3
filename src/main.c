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
    top_most_active(new,10);
    total_posts(new,a,b);
    //questions_with_tag(new,"rooting",a,b);

    tpf =clock() - tpf;
    printf("Demorou %f segundos a ler\n",((float)tpf)/CLOCKS_PER_SEC);

    return 0;
} 
