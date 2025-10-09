#include <stdio.h>
int main() {
  int num = 10 ;
  int *p = &num ; 
  /*
    위 코드 실행시
    int num = 10;   // num이라는 변수에 10을 저장
    int *p = &num;  // p는 int형 포인터, num의 주소를 저장
    주소 0x1000: num = 10
    주소 0x2000: p = 0x1000
  */
  printf("num = %d\n",num); // 그냥 num 출력 10진수니까 %d
  printf("&num = %p\n", (void*)&num); // num 변수가 저장되어있는 주소값 출력
  printf("p = %p\n", (void*)p); // num의 주소값 p에 저장했으니까 위랑 결과가 같음
  printf("*p = %d\n", *p); // p 주소값에 저장된 값 가져옴
	printf("&p = %p\n", (void*)&p); // p의 주소값 가져옴

  // *p = 20;
  // printf("num (after *p = 20) = %d\n", num);
  return 0 ;
}