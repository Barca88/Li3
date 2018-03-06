#include <date.h>
#include <stdio.h>
#include "interface.h"

int main(){

  Date d = createDate(1,2,2017);
  printf("Dia: %i\n", get_day(d));

  init();

  return 0;
} 
