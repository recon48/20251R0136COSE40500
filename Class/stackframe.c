#include <stdio.h>

int func1(int a, char *b){
  int c=10;
  char d[20]="hello";
  printf("%d %s", c, d);
  return 0;
}

int main(void){
  int a;
  char b[10];
  func1(a, b);
  return 0;
}











