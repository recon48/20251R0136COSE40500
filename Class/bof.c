#include <stdio.h>

int foo(){
  char buf[40];
  printf("%p\n", buf);
  scanf("%s", buf);
  return 0;
}

int main(void){
  foo();
  return 0;
}
