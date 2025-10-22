#include <stdio.h> 

int sum(int *a, int n);

int array[5] = {1, 2, 3, 4, 5};

int main() {
  int val = sum(array, 5);
  printf("Sum is: %d\n", val); 
  return 0; 
}
