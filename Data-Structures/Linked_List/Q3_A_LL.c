//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

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
void moveOddItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
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


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
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
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
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
// 리스트를 순회하면서 홀수를 뒤로 보내고, 짝수는 앞으로 배치해서 리스트를 재구성
/*
	로직 
	리스트 순회하면서 짝수 따로 연결, 홀수 따로 연결 -> 이후 짝수, 홀수 비어있는지 여부에 따라 짝수 tail 이랑 홀수 head랑 연결 (짝수가 비어있다 -> 들어온게 다 홀수다 , 홀수는 반대)	
*/
void moveOddItemsToBack(LinkedList *ll)
{
	/* add your code here */
	ListNode *evenHead = NULL;
	ListNode *evenTail = NULL;
	ListNode *oddHead = NULL;
	ListNode *oddTail = NULL;

	ListNode *current = ll -> head ;
	while(current != NULL) {
		ListNode *nextNode = current -> next; // 다음 노드를 미리 기억
		current -> next = NULL; // 현재 노드 기존 연결 완전히 끊기  

		if (current-> item % 2 == 0) {
			// 짝수
			if (evenHead == NULL) {
				// 처음 들어가는 경우
				evenHead = current;
				evenTail = current;
			} // 이미 있는 경우 뒤에 붙여줘야 함
			else {
				evenTail->next = current;
				evenTail = current;
			}
		}
		// 홀수
		else {
			// 처음 들어가는 경우
			if(oddHead == NULL) {
				oddHead = current;
				oddTail = current;
				// 이미 있는 경우 뒤에 붙여줘야 함
			} else {
				oddTail -> next = current;
				oddTail = current;
			}
		}
		// 업데이트 
		current = nextNode; 
	}
	if (evenHead != NULL) {
		// 짝수 그룹이 비어있지 않은 경우 짝수 그룹부터 출력해야 하니까 head - evenhead
		ll -> head = evenHead;
		// 짝수 그룹이 비어있지 않고 홀수 그룹이 비어있지 않는 경우 evenTail, oddHead 연결
		if (oddHead != NULL) {
			evenTail -> next = oddHead;
		}
	}// 짝수 그룹이 비어있는 경우
	else {
		ll -> head = oddHead;
	}
}

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
