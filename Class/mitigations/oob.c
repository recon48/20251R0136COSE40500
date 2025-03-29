// gcc -O0 -fno-stack-protector -z execstack -no-pie -fno-pic -o oob oob.c
#include <stdio.h>

int main(void){
  int idx;
  int p[] = {1, 2};
  char key[8] = "aabbccdd";

  scanf("%d", &idx);
  printf("%p\n", p[idx]);
  return 0;
}
