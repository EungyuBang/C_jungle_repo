//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

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

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
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
	문제에서 원하는 것
	1 눌렀을 때 : 새로운 노드 입력, 순서에 맞게 들어가야함. 1 3 5 7 이 있고 4가 입력될 때 1 3 4 5 7 이 되도록
	2 눌렀을 때 : 새로 들어온 노드의 index 번호 출력. 1 3 5 7 이 있고 4 입력 -> 1번에 의해서 1 3 4 5 7 됨 -> 2 입력 -> index = 2 출력
	3 눌렀을 때 : ll 정렬, 초기화 (이건 로직이 짜여져 있음)

	1 눌렀을 때 로직
	 - 1. 빈 ll 에 들어가는 경우.
	 - 2. 새로운 item 이 들어가는데 기존 head의 item보다 작은 경우 (쉽게 말하면 제일 앞으로 가야하는 경우).
	 - 3. 새로운 item 이 들어가는데 가장 끝에 들어가야 할 때.
	 	- 3.1 제일 끝에 들어왔으니까 newNode -> next = NULL
	 - 4. 새로운 item 이 pLeft , pRight 사이에 들어가야 할 때. (pRight는 pLeft->next 로 포현됨)
	 	- 4.1 새로운 item을 사이에 넣을 떄 pLeft -> next = newNode 를 newNode -> next = pLeft -> next 보다 먼저 해버리면 안됨
					왜냐 - 포인터가 가리키는게 달라져버림 지금 pLeft-> next 는 pRight임 근데 pLeft -> next = newNode 이걸 먼저 해버리면 pRight이 newNode가 되어버림
					그래서 newNode -> next = pRight을 먼저 newNode -> next에 넣어야 pLeft, newNode, pRight 순서에 맞춰서 들어가게됨.

	 2 눌렀을 때
	 - 1 눌렀을 때 1, 2 번은 인덱스가 무조건 0 이니까 return 0; 으로 처리
	 - 1 눌렀을 때 3, 4 번은 인덱스 증가 관리 해줘야함
*/

int insertSortedLL(LinkedList *ll, int item)
{
	int index = 0;

	if (ll->size == 0) {
		// 처음들어가는 경우 ( 아예 안들어 있는 경우 )
		ll-> head = malloc(sizeof(ListNode));
		ll-> size = 1;
		ll-> head -> item = item;
		ll -> head -> next = NULL;
		return 0;
	} 
	if (item < ll -> head-> item) {
		// 새로 들어오는 item이 기존 head의 item 보다 작으면 리스트 맨 앞에 삽입
		ListNode *newNode = malloc(sizeof(ListNode));
		newNode -> item = item;
		newNode -> next = ll -> head ;
		ll -> head = newNode ;
		ll -> size += 1 ;
		return 0;
	}
	// ll의 head 부터 탐색 시작
	ListNode *pLeft = ll->head;
	index = 0;
	while(1) {
		index++;
		if (pLeft -> next == NULL) {
			// 새로들어온게 제일 큰 값일때 오른쪽 NULL 처리 
			ListNode *newNode = malloc(sizeof(ListNode));
			newNode -> item = item ;
			newNode -> next = NULL ;
			pLeft -> next = newNode;
			ll -> size ++ ;
			// index++;
			break;
		}
		if(pLeft->item <= item && item < pLeft->next->item ) {
			// pLeft와 pRight의 사이에 item 삽입
			ListNode *newNode = malloc(sizeof(ListNode));
			newNode -> item = item ;
			newNode-> next = pLeft->next ;
			pLeft -> next = newNode ;
			ll -> size ++ ;
			// index++;
			break ;
		}
		// 포인터 이동 - 이 코드 없으면 순회 자체가 안 됨.
		pLeft = pLeft->next;
		// index++;
	}
	return index;
}

// int insertSortedLL(LinkedList *ll, int item) {
//     /* add your code here */
//     ListNode *cur = ll->head;
//     int index = 0;

//     if (ll == NULL) return -1;

//     // 인덱스 구하기
//     while (cur != NULL) {
//         if (item < cur->item) break;
//         if (item == cur->item) return -1;

//         cur = cur->next;
//         index++;
//     }

//     insertNode(ll, index, item);

//     return index;
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
