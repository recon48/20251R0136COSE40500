// gcc -O0 -z execstack -no-pie -fno-pic -o canary canary.c
#include <stdio.h>

int main(void){
  char a[40];
  for (int i=0; i<2; i++){
     read(0, a, 41);
     printf("%s\n", a);
  }
  return 0;
}
