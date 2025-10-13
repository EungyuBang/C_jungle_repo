//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 5
		 Implementing 'remove node' operation for BST*/
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
BSTNode* removeNodeFromTree(BSTNode *root, int value);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS2(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
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
	Q4 와 같이 후위순회 결과 출력 -> 근데 이번엔 스택을 두 개 씀, 왼쪽-> 오른쪽 ->루트
*/
/*
	문제 로직 생각
	스택을 두개 만들고, 초기화.
	1. stack 1에서는 루트부터 시작. 루트를 팝하면서 stack 2 로 푸시 -> 하면서 왼쪽 오른쪽 노드 있으면 순서대로 stack 1에 저장
	2. 제일 마지막 노드 계속 스택 2로 푸시 -> 이때 노드의 왼 오 있으면 스택 1에 계속 넣어줘야함.
	3. 그래서 스택1이 비면 스택2로 이동 다 한거임
	4. 스택 2 출력.
*/
void postOrderIterativeS2(BSTNode *root)
{
	 /* add your code here */
	 Stack stackOne;
	 Stack stackTwo;
	 stackOne.top = NULL;
	 stackTwo.top = NULL;

	 if(root == NULL) return;
	 push(&stackOne, root);

	 while(!isEmpty(&stackOne)) {
		BSTNode *st1CurNode = pop(&stackOne) ;
		push(&stackTwo, st1CurNode);
		if (st1CurNode -> left != NULL) {
			push(&stackOne, st1CurNode -> left);
		}
		if (st1CurNode -> right != NULL) {
			push(&stackOne, st1CurNode -> right);
		}
	 }
	 while(!isEmpty(&stackTwo)) {
		BSTNode *printfStackTwo = pop(&stackTwo);
		printf("%d ", printfStackTwo -> item);
	 }
}

/* Given a binary search tree and a key, this function
   deletes the key and returns the new root. Make recursive function. */
// BSTNode* removeNodeFromTree(BSTNode *root, int value)
// {
// 	/* add your code here */
// }
///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
