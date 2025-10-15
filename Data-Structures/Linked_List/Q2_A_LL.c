//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	//Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
		    printf("The resulting linked lists after merging the given linked list are:\n");
			alternateMergeLinkedList(&ll1, &ll2); // You need to code this function
			printf("The resulting linked list 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
/*
	문제에서 원하는 것? - 두 개의 연결 리스트를 번갈아가면서 합치는 것
	ll1 , ll2 의 노드를 순서대로 번갈아가면서 연결
	남은 노드가 있는 리스트가 있으면 그 뒤에 붙임
	ll2는 마지막에 빈 리스트가 되도록 처리
	기존 노드 재사용, 새로운 노드 생성 필요 없음
*/
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
  // 1. 초기 예외 처리: ll1이 비어있는 경우 (ll2의 모든 노드를 ll1로 옮김)
  if (ll1 -> head == NULL) {
    ll1 -> head = ll2 -> head ;  // ll1의 head를 ll2의 head로 설정 (노드 이동)
    ll1 -> size = ll2 -> size ;  // ll1의 size를 ll2의 size로 업데이트
    ll2 -> head = NULL;          // ll2의 head를 NULL로 설정하여 ll2를 빈 리스트로 만듦
    ll2 -> size = 0;             // ll2의 size를 0으로 설정
    return;                      // 함수 종료
  }
  // 2. 초기 예외 처리: ll2가 비어있는 경우
  if (ll2 -> head == NULL) {
    return;                      // 병합할 것이 없으므로 함수 종료
  }
  // 3. 순회 포인터 설정 (ll1의 head를 보호하기 위해 cur1 사용)
  ListNode *cur1 = ll1 -> head;
  // 4. 병합 루프: cur1(ll1 노드)과 ll2->head(ll2 노드) 모두 노드가 있을 때만 반복
  while(cur1 != NULL && ll2 -> head != NULL) {
    // 다음 노드 주소 저장 (포인터 재연결 전에 백업하여 연결 끊김 방지)
    ListNode *ll1nextNode = cur1 -> next;    // ll1의 다음 노드 주소 백업
    ListNode *ll2nextNode = ll2 -> head -> next; // ll2의 다음 노드 주소 백업
    // 노드 연결 1단계: cur1 -> ll2.head 연결
    cur1 -> next = ll2 -> head;      // ll1의 현재 노드(cur1) 뒤에 ll2의 현재 head 노드를 연결
    // 노드 연결 2단계: ll2.head -> ll1의 다음 노드 연결
    cur1 -> next -> next = ll1nextNode; // 방금 연결된 ll2 노드(cur1->next) 뒤에 ll1의 원래 다음 노드(ll1nextNode)를 연결
    // 포인터 이동 1단계: ll2 노드 소모
    ll2 -> head = ll2nextNode;       // ll2의 head를 다음 노드로 이동 (현재 노드는 ll1로 넘어갔으므로)
    // 포인터 이동 2단계: cur1 건너뛰어 이동
    cur1 = ll1nextNode;              // cur1을 ll1의 원래 다음 노드로 이동 (ll2 노드를 건너뜀)
    // 리스트 크기 업데이트 (ll2의 노드 1개가 ll1로 이동)
    ll1 -> size++;                   // ll1의 크기 1 증가
    ll2 -> size--;                   // ll2의 크기 1 감소
  }
}

// void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
// {
// 	/* add your code here */
// 	if (ll1 -> head == NULL) {
// 		ll1->head = ll2->head;
// 		ll1->size = ll2->size;
// 		ll2->head = NULL;
// 		ll2->size = 0;
// 	}
// 	if (ll2 -> head == NULL) {
// 		return;
// 	}
// 	ListNode *curNode = ll1->head;
// 	while(curNode != NULL && ll2->head != NULL) {
// 	}
// }


///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
