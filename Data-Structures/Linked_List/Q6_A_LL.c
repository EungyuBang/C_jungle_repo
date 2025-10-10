//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 6 */

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
int moveMaxToFront(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i, j;
	c = 1;

	LinkedList ll;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move the largest stored value to the front of the list:\n");
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
			j=insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveMaxToFront(&(ll.head));  // You need to code this function
			printf("The resulting linked list after moving largest stored value to the front of the list is: ");
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

////////////////////////////////////////////////////////////////////////
// 리스트를 순회하면서 가장 큰 값 배열 제일 앞으로 보내야 함 -> 리스트 한 번만 순회 가능, 노드 자체를 이동해야함.
// 그러면 리스트가 비었거나, 제일 앞에 이미 가장 큰 노드가 와있을 때 처리 해줘야함
/*
	로직 생각
	리스트가 비었으면 종료
	순회하면서 maxNode , preMax 저장
	맨 앞에 와있으면 그냥 출력하면 되는거 아님?
	맨 앞 아니면 최대값 노드 떼서 맨 앞에 위치.
*/ 
/*
	**ptrHead - 포인터를 가리키는 포인터 , ptrhead 는 head 포인터 자체를 가리킴 , *ptrHead = head
	ptrHead -> [10] -> [20] -> [30] -> NULL
	*ptrHead = [10] (첫 노드)
	(*ptrHead)->next = [20] (두 번째 노드)
	cur = [20]
*/
int moveMaxToFront(ListNode **ptrHead)
{
    /* add your code here */
		// 비어있을 때
		if (*ptrHead == NULL) {
			return 0;
		}
		ListNode *maxNode = *ptrHead; // 현재까지 maxNode = head
		ListNode *prevMax = NULL; // head에 maxNode 있으니까 maxNode 이전값 NULL 로 초기화
		ListNode *prev = *ptrHead; // 순회 중 현재 노드의 이전 값
		ListNode *cur = (*ptrHead) -> next; // cur에 head의 next 주소값 넣어줘서 순회 준비
		
		while (cur != NULL) {
			// 현재의 값이 다음의 값보다 작으면
			if (maxNode->item < cur->item) {
				maxNode	= cur	;
				prevMax = prev ;
			}
			prev = cur;
			cur = cur -> next;
		}
		// 최대값이 헤드에 있을때
		if (maxNode == *ptrHead) {
			return 0;
		}
		// 이제 가장 큰 값 헤드로 옮겨주면 됨
		prevMax->next = maxNode -> next ; // maxNode 제일 앞으로 옮길거니깐 prevMax -> next 랑 maxNode -> next 연결 시켜주고 
		maxNode->next = *ptrHead; // maxNode 가 헤드 될거니까 maxNode -> next 가 현재 head 값
		*ptrHead = maxNode; // 마지막으로 현재 헤드가 maxNode
		return 1;
}

//////////////////////////////////////////////////////////////////////////////////

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
