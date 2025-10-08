// 링크드 리스트 기본형? 
#include <stdio.h>
#include <stdlib.h>
typedef struct _node {
  int data;
  struct  _node* next;
} Node;

void main() {
  Node* node1 = malloc(sizeof(Node));
  Node* node2 = malloc(sizeof(Node));

  node1 -> data = 3;
  node2 -> data = 4;
  node1 -> next = node2;

  printf("%d\n", node1->data);
  printf("%d\n", node1->next->data);

  free(node1);
  free(node2);
  return;
}