#include <stdio.h>

int main() {
  char str[20]; // 문자열 저장 배열
  char *pstr; // 문자열 포인터

  printf("문자열 입력: ");
  scanf("%19s", str);

  pstr = str;

  printf("\n === 문자열 출력 연습 === \n");
  printf("배열 문자열: %s\n", str);
  printf("포인터가 가리키는 문자열: %s\n", pstr);

  printf("\n === 문자 단위 출력 === \n");
  for(int i =0; *(pstr + i) != '\0'; i++) {
    printf("str[%d] = %c, *(pstr + %d) = %c\n", i, str[i], i, *(pstr + i));
  }

  printf("\n === 포인터 이동 연습 === \n");
  while(*pstr != '\0') {
    printf("%c ", *pstr);
    pstr++;
  }
  printf("\n");

  return 0;
}