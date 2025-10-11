//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 6 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _btnode
{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode
{
    BTNode *btnode;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    StackNode *top;
} Stack;


///////////////////////// Function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void printSmallerValues(BTNode *node, int m);

BTNode *createBTNode(int item);

BTNode *createTree();
void push( Stack *stack, BTNode *node);
BTNode* pop(Stack *stack);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    char e;
    int c, value;
    BTNode *root;

    c = 1;
    root = NULL;


    printf("1: Create a binary tree.\n");
    printf("2: Print smaller values.\n");
    printf("0: Quit;\n");

    while(c != 0)
    {
        printf("Please input your choice(1/2/0): ");
        if( scanf("%d",&c) > 0)
        {
            switch(c)
            {
            case 1:
                removeAll(&root);
                root = createTree();
                printf("The resulting binary tree is: ");
                printTree(root);
                printf("\n");
                break;
            case 2:
                printf("Enter an integer value to print smaller values: ");
                scanf("%d",&value);
                printf("The values smaller than %d are: ", value);
                printSmallerValues(root,value);
                printf("\n");
                removeAll(&root);
                break;
            case 0:
                removeAll(&root);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
        }
        else
        {printf("\n");
            scanf("%c",&e);
        }

    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////
/*
    문제에서 원하는 것
    이진 트리 내에서 주어진 값 m 보다 작은 모든 노드의 값을 출력 -> 출력도 inorder 방식으로 root -> left -> right
*/
/*
    문제 로직 생각
    흠 그러면 재귀를 돌다가 원하는 값나오면 멈추는 것도 아니고 그러면 그냥 트리를 순회 해야하지 않을까? -> inorder 방식으로 순회하면서 새로운 공간 만들어서 m 보다 작은 값 넣고 -> 그대로 출력 하면 되지 않을까? 
*/
// 내가 생각한 로직대로 작성된 코드
// void findSmallerValues(BTNode *node, int m, int arr[], int *count) {
//     if (node == NULL) {
//         return;
//     }

//     // 전위 순회(Pre-order) 방식: 루트 -> 왼쪽 -> 오른쪽
//     if (node->item < m) {
//         arr[*count] = node->item; // 배열에 값 저장
//         (*count)++;               // 저장된 값의 개수 증가
//     }

//     findSmallerValues(node->left, m, arr, count);
//     findSmallerValues(node->right, m, arr, count);
// }

// // 메인 함수: 배열을 만들고, 보조 함수를 호출한 뒤, 배열의 내용을 출력
// void printSmallerValues(BTNode *node, int m)
// {
//     if (node == NULL) {
//         return;
//     }
    
//     int results[100]; // 결과를 저장할 배열 (크기는 충분히 크게)
//     int count = 0;    // 배열에 저장된 숫자의 개수

//     // 1. 트리를 순회하며 배열(results)에 m보다 작은 값을 저장
//     findSmallerValues(node, m, results, &count);

//     // 2. 배열에 저장된 값들을 순서대로 출력
//     for (int i = 0; i < count; i++) {
//         printf("%d ", results[i]);
//     }
// }

void printSmallerValues(BTNode *node, int m)
{
    /* add your code here */
    if (node == NULL) {
        return;
    }

    // 2. 현재 노드 처리 (Pre-order: 가장 먼저 처리)
    // 현재 노드의 값이 m보다 작으면 바로 출력
    if (node->item < m) {
        printf("%d ", node->item);
    }

    // 3. 왼쪽 서브트리 순회
    printSmallerValues(node->left, m);

    // 4. 오른쪽 서브트리 순회
    printSmallerValues(node->right, m);
}
//////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item)
{
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//////////////////////////////////////////////////////////////////////////////////


BTNode *createTree()
{
    Stack stack;
    BTNode *root, *temp;
    char s;
    int item;

    stack.top = NULL;
    root = NULL;
    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if(scanf("%d",&item) > 0)
    {
        root = createBTNode(item);
        push(&stack,root);
    }
    else
    {
        scanf("%c",&s);
    }

    while((temp =pop(&stack)) != NULL)
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if(scanf("%d",&item)> 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if(scanf("%d",&item)>0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        if(temp->right != NULL)
            push(&stack,temp->right);
        if(temp->left != NULL)
            push(&stack,temp->left);
    }
    return root;
}

void push( Stack *stack, BTNode *node)
{
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if(temp == NULL)
        return;
    temp->btnode = node;
    if(stack->top == NULL)
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

BTNode* pop(Stack *stack)
{
    StackNode *temp, *top;
    BTNode *ptr;
    ptr = NULL;

    top = stack->top;
    if(top != NULL)
    {
        temp = top->next;
        ptr = top->btnode;

        stack->top = temp;
        free(top);
        top = NULL;
    }
    return ptr;
}

void printTree(BTNode *node)
{
    if(node == NULL) return;

    printTree(node->left);
    printf("%d ",node->item);
    printTree(node->right);
}

void removeAll(BTNode **node)
{
    if(*node != NULL)
    {
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}

