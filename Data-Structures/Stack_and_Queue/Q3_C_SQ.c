//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//////////////////////////////////   linked list /////////////////////////////////

typedef struct _listnode{
   int item;
   struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
   ListNode *tail;
} LinkedList;

////////////////////////////////// stack //////////////////////////////////////////
// 핵심: 스택의 유일한 멤버가 바로 LinkedList ll; - 이것은 스택의 모든 데이터와 관리 기능을 내부적으로 LinkedList 구조체를 통해 처리하겠다는 의미
typedef struct stack{
	LinkedList ll;
} Stack;

////////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int isStackPairwiseConsecutive(Stack *s);

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);

void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int c, value;

    Stack s;

    s.ll.head=NULL;
	s.ll.size =0;
	s.ll.tail =NULL;

    c =1;

    printf("1: Insert an integer into the stack:\n");
    printf("2: Check the stack is pairwise consecutive:\n");
    printf("0: Quit:\n");

    while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the stack: ");
			scanf("%d", &value);
			push(&s, value);
			printf("The stack is: ");
            printList(&(s.ll));
			break;
		case 2:
            if(isStackPairwiseConsecutive(&s))
            {
                printf("The stack is pairwise consecutive.\n");
            }
            else{
                printf("The stack is not pairwise consecutive.\n");
            }
            removeAllItems(&(s.ll));
            break;
		case 0:
			removeAllItems(&(s.ll));
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////
/*
	문제에서 원하는 것
	스택의 숫자들이 쌍으로 연속적인지 확인하는 C 함수 작성
	예시: (16, 15, 11, 10, 5, 4)는 쌍으로 연속적, (16, 15, 11, 10, 5, 1)은 연속적이지 않음.
*/
/*
	문제 로직 생각
	우선 스택의 크기가 홀수면 절대 안됨 -> return -1
	스택의 크기가 짝수일떄 시작 -> 2개씩 pop하면서 비교 - 쌍 맞으면 return 0 아니면 return -1 - 근데 pop 하면 값이 사라져버리니깐 보조 스택 만들어서 거기다가 push
	그래서 다 return 0 이면 된거 아님?
*/
int isStackPairwiseConsecutive(Stack *s)
{
  /* add your code here */
	int size = s -> ll.size;
	if (size % 2 == 1) return 0 ; // size가 홀수면 실패
	// 보조스택 선언
	Stack temp;
	temp.ll.head = NULL;
	temp.ll.tail = NULL;
	temp.ll.size = 0 ;
	// 두개 비교하기 위해서 first, second 선언
	int first, second;
	// 반복문 시작 s 가 비지 않을때까지
	while(!isEmptyStack(s)) {
		first = pop(s);
		second = pop(s);
		// first, second 차이가 1이면 조건 만족 -> 보조스택에 push
		if (abs(first-second) == 1) {
			push(&temp, second);
			push(&temp, first);
		}
		else {
			return 0;
		}
	}
	// 보조 스택에 있던 값들 원래 스택에 push
	while (!isEmptyStack(&temp)) {
		push(s, pop(&temp));
	}
	return 1;
}
// 위의 내 코드대로 하면 논리적으로는 맞음 근데 구현적으로 불안정
// 아래는 gpt 코드
// int isStackPairwiseConsecutive(Stack *s)
// {
//     if (s->ll.size % 2 == 1)
//         return 0;

//     Stack temp = {0};
//     int first, second;
//     int isConsecutive = 1;

//     while (!isEmptyStack(s)) {
//         first = pop(s);
//         if (isEmptyStack(s)) {
//             push(&temp, first);
//             break;
//         }
//         second = pop(s);

//         if (abs(first - second) != 1)
//             isConsecutive = 0;

//         push(&temp, second);
//         push(&temp, first);
//     }

//     while (!isEmptyStack(&temp))
//         push(s, pop(&temp));

//     return isConsecutive;
// }

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item){
   insertNode(&(s->ll), 0, item);
}

int pop(Stack *s){
   int item;
   if(!isEmptyStack(s)){
    item = ((s->ll).head)->item;
    removeNode(&(s->ll), 0);
    return item;
   }
    return INT_MIN;
}

int peek(Stack *s){
   return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s){
   if ((s->ll).size == 0)
      return 1;
   return 0;
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
