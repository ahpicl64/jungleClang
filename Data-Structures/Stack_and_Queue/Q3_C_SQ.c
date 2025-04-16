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

int isStackPairwiseConsecutive(Stack *s)
{
	// 스택의 숫자들이 쌍으로 연속되는지 검사하는 함수?
	// boolean이 없으니까 0또는 1로 return해줘야, 이후 프린트문에서 if, else로 출력 가능
	// pop을 사용하니까. pop으로 쭉 꺼내고, 연속되는지 확인
	// 6개짜리 스택의 경우, 1-2 3-4 5-6 연속되는지 2개씩 쌍으로 확인
	// 인덱스를 따로 관리해서, 비교 숫자를 1,2, 순서로 넣고 인덱스가 짝수인 순간에 비교를 하게
	// 비교하고, 연속되지 않은게 나오자마자 이탈하게

	int compareNum1, compareNum2;
	while(!isEmptyStack(s)){ // 스택이 빌때까지 순회
		// 인덱스가 짝수일 경우 검사 시작
		compareNum1 = pop(s);
		compareNum2 = pop(s);
		if (abs(compareNum1-compareNum2) != 1){
			return 0;
		}
	}
	compareNum1, compareNum2 = 0;
	return 1;
}

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
