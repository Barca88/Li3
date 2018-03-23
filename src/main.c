#include "interface.h"

int main(int argc,char** argv){

    TAD_community new = init();
    new = load(new,argv[1]);
    info_from_post(new,245691);
    return 0;
} 
