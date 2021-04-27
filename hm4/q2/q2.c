#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0 
#define SIZE 100

typedef struct Node {
	char data;
	struct Node* next;
}Node;

typedef struct Stack {
	Node* head;
}Stack;

void push(Stack *s, char data)
{
	Node* newNode = (Node*)calloc(1, sizeof(Node));

	//if allocation failed
	if (!newNode)
	{
		printf("Out of memory!\n");
		exit(1);
	}

	//putting the new data in the node
	newNode->data = data;

	//if the stack is empty, the next will be null
	if (!isEmpty(s))
		newNode->next = s->head;
	s->head = newNode;
}


int isEmpty(Stack* s)
{
	if (s->head == NULL)
		return TRUE;
	else return FALSE;
}


//takes out the head, setting the next one. frees the one out and returns the data.
char pop(Stack* s)
{
	char out;
	//stack is empty, will return null
	if (isEmpty(s))
	{
		printf("The stack is empty!\n");
		return '\0';
	}
	Node* temp = s->head;
	out = s->head->data;
	s->head = temp->next;
	free(temp);
	return out;
}




int isPilandrom
void main()
{

}