//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 5 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
void frontBackSplitLinkedList(LinkedList* ll, LinkedList *resultFrontList, LinkedList *resultBackList);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *l);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c=1;
	int i;
	LinkedList ll;
	LinkedList resultFrontList, resultBackList;

	//Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	//Initialize the front linked list as an empty linked list
	resultFrontList.head = NULL;
	resultFrontList.size = 0;

	// Initialize the back linked list as an empty linked list
	resultBackList.head = NULL;
	resultBackList.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Split the linked list into two linked lists, frontList and backList:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
	    printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The resulting linked lists after splitting the given linked list are:\n");
			frontBackSplitLinkedList(&ll, &resultFrontList, &resultBackList); // You need to code this function
			printf("Front linked list: ");
			printList(&resultFrontList);
			printf("Back linked list: ");
			printList(&resultBackList);
			printf("\n");
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		case 0:
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
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
	문제 목표 : ll을 절반으로 나누기 (앞 절반 + 뒤 절반) -> 홀수개면 front + 1
	로직 생각 
		먼저 링크드 리스트 받고
		size 구하고 -> mid 설정해서 반으로 나눠버림 근데 size가 홀수면 앞 절반에 + 1
		그래서 resultFrontList, resultBackList 에 넣으면 되지 않을까?
*/
// 메모리 관리 측면에서 문제가 생긴다는데... double free?? 
void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
{
	/* add your code here */
	if (ll -> size == 0)  {
		resultFrontList -> head = NULL;
		resultFrontList -> size = 0;
		resultBackList -> head = NULL;
		resultBackList -> size = 0 ;
		return;
	}
	int mid = (ll -> size + 1) / 2 ;
	ListNode *midNode = findNode(ll, mid - 1);
// frontList 설정
	resultFrontList -> head = ll -> head;
	resultFrontList -> size = mid;
// backList 설정
	resultBackList -> head = midNode -> next;
	resultBackList -> size = ll -> size - mid;

	if (midNode != NULL)
    resultBackList->head = midNode->next;
	else
    resultBackList->head = NULL;
}
// void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
// {
//   // 1. 초기화 (Double Free 방지를 위해 입력 리스트의 헤드를 NULL로 설정)
//   resultFrontList->head = NULL;
//   resultFrontList->size = 0;
//   resultBackList->head = NULL;
//   resultBackList->size = 0;

//   // 2. 빈 리스트 처리
//   if (ll->head == NULL) {
//     // 이미 위의 초기화로 처리되었으나, 명시적 반환
//     ll->size = 0; // ll의 size도 0으로 명시적으로 설정
//     return;
//   }

//   // 3. 분할점 계산: 홀수일 때 앞부분에 하나 더 포함
//   int mid = (ll-> size + 1) / 2;
  
//   // 4. mid-1 인덱스 노드 (프론트 리스트의 꼬리 노드) 찾기
//   // findNode 함수가 index-1까지 순회해주므로, index = mid - 1 이 맞습니다.
//   ListNode *frontTail = findNode(ll, mid - 1);
  
//   // 5. 백 리스트의 머리 (frontTail의 다음 노드)
//   ListNode *backHead = NULL;
  
//   // 6. 연결 끊기 및 포인터 재설정 (가장 중요한 부분)
//   if (frontTail != NULL) {
//     backHead = frontTail->next; // 백 리스트의 시작 노드를 가져옴
//     // ⭐⭐ 핵심: 프론트 리스트의 꼬리를 NULL로 설정하여 ll에서 분리 ⭐⭐
//     frontTail->next = NULL; 
//   }
  
  // 7. 결과 리스트에 최종 할당
  // resultFrontList 설정
//   resultFrontList->head = ll->head;
//   resultFrontList->size = mid;
//   // resultBackList 설정
//   resultBackList->head = backHead;
//   resultBackList->size = ll->size - mid;

//   // 8. 원본 ll 리스트 초기화 (노드 소유권을 resultFrontList와 resultBackList에 넘김)
//   ll->head = NULL;
//   ll->size = 0;
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


ListNode * findNode(LinkedList *ll, int index){

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
