#include <stdio.h>

int main(void){
  char buf[40];

  read(0, buf, 40);
  printf("%s\n", buf);
  return 0;
}




