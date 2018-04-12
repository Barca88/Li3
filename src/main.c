#include "interface.h"
#include <time.h>
#include <stdio.h>

int main(int argc,char** argv){
    clock_t tpf;
    tpf =clock();

    TAD_community new = init();
    new = load(new,argv[1]);

    info_from_post(new,1);
    Date a,b;
    a = createDate(1,2,2016);
    b = createDate(3,10,2017);

    total_posts(new,a,b);

    tpf =clock() -tpf;
    printf("Demorou %f segundos a ler\n",((float)tpf)/CLOCKS_PER_SEC);

    return 0;
} 
