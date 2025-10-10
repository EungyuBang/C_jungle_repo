#include <stdio.h>

int a = 5;
int *p = &a;
int **p2 = &p;

void main () {
  printf("%d\n", a); // 5
  printf("%p\n", p); // a의 주소값
  printf("%p\n",p2); // pointer 의 주소값
  printf("%p\n",*p2); // a의 주소값
  printf("%d\n",**p2); // 5
}