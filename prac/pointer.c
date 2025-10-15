#include <stdio.h>

// int main() { // 포인터 기본 문제
//     int value = 100;
//     int *ptr = &value; // 이러면 포인터 ptr이 가지고 있는 값은 value 라는 변수의 주소값
//     // 1번: value 자체의 값
//     printf("1. value의 값: %d\n", value); // -> 100
//     // 2번: value 변수의 메모리 주소
//     printf("2. value의 주소: %p\n", &value); // -> 뭐 예시로 0x100
//     // 3번: ptr 포인터 변수가 저장하고 있는 값 (누군가의 주소)
//     printf("3. ptr의 값: %p\n", ptr); // -> value의 주소  -> 0x100
//     // 4번: ptr이 가리키는 주소로 찾아가서 꺼내온 실제 값
//     printf("4. ptr이 가리키는 곳의 값: %d\n", *ptr); // -> 100
//     // [심화] ptr을 이용해 value의 값을 200으로 바꿔보세요.
//     *ptr = 200;
//     printf("5. 변경 후 value의 값: %d\n", value); //-> 이러면 바뀐거 아님? 
//     return 0;
// }

// void swap_fail(int x, int y) { // 스왑
//   int temp = x;
//   x = y;
//   y = temp;
// }
// void swap_correct(int *ptr_a, int *ptr_b) { // 인자로 a의 주소값, b의 주소값 받아옴 -> ptr_a 는 a의 주소 가리킴, ptr_b는 b의 주소 가리킴
//   int temp = *ptr_a; // 이거 사실상 투포인터 아님? 
//   *ptr_a = *ptr_b;
//   *ptr_b = temp;
// }
// int main() {
//   int a = 10;
//   int b = 20;
//   printf("바꾸기전 : a = %d, b = %d\n", a,b);
//   swap_fail(a, b);
//   printf("swap_fail 후: a = %d, b = %d\n", a, b);
//   swap_correct(&a, &b);
//   printf("swap_correct 후: a = %d, b = %d\n", a, b);
// }

/* void printArray(int *p_arr, int size) { // 배열의 이름이 포인터의 시작점. 활용해서 배열 요소 출력해보기 
    printf("배열 요소 출력: ");
    for (int i = 0; i < size; i++) {
        // 여기에 코드를 작성하여 배열의 각 요소를 출력하세요.
        // 예: printf("%d ", ...);
        printf("%d\n", *(p_arr + i));
    }
    printf("\n");
}
int main() {
    int numbers[5] = {10, 20, 30, 40, 50};
    
    // 배열의 이름 numbers는 배열의 시작 주소와 같습니다.
    printArray(numbers, 5);

    return 0;
} */

// int main() { // 포인터 크기 확인하는 함수
//     // 다양한 타입의 포인터 변수 선언
//     int *p_int;
//     char *p_char;
//     double *p_double;
//     int **p_d_int; // 이중 포인터
//     // 각 포인터 변수의 크기(바이트 단위)를 출력
//     printf("int 포인터의 크기: %zu 바이트\n", sizeof(p_int));
//     printf("char 포인터의 크기: %zu 바이트\n", sizeof(p_char));
//     printf("double 포인터의 크기: %zu 바이트\n", sizeof(p_double));
//     printf("이중 포인터의 크기: %zu 바이트\n", sizeof(p_d_int));
//     return 0;
// }

// ㅁㄴㅇㄹㄴㅁㅇㄹㅁㄹㄴㅇ