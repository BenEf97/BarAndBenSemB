/*need to change the function, can't acsess directly, only with data retaree*/



#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0 
#define SIZE 100


typedef struct Node
{
	unsigned int data;
	struct Node *next;
}Node;

typedef struct Queue
{
	Node *head;
	Node *tail;
} Queue;

int dequeue(Queue* s) 
{
	Node* temp = s->head;
	unsigned int data = temp->data;

	if (isEmpty(s)) 
	{
		printf("empty!");
		return -1;
	}

	s->head = s->head->next;
	if (s->head == NULL)
		s->tail = NULL;
	
	free(temp);
	return data;
}

void enqueue(Queue* s, unsigned int data)
{
	Node* newNode = (Node*)calloc(1, sizeof(Node));
	newNode->data = data;

	if (!isEmpty(s)) {
		s->tail->next = newNode;
		s->tail = newNode;
		return;
	}
	s->head = s->tail = newNode;
}

//if the Queue is empty, will return TRUE, else will return FALSE
int isEmpty(Queue* s) 
{
	if (s->head == NULL && s->tail == NULL)
		return TRUE;
	else return FALSE;
}

//maayan initqueue
void initQueue(Queue* s) 
{
	s->head = s->tail = NULL;
}

int sizeQueue(Queue s)
{
	int size=0;
	while (isEmpty(&s))
	{
		dequeue(&s);
		size++;
	}
	return size;
}

void rotate(Queue* s)
{
	unsigned int first,last;
	Queue temp;

	//checking if the queue is empty, if it does will return to main
	if (isEmpty(s))
	{
		printf("The queue is empty!\n");
		return;
	}
	first=dequeue(s);
	enqueue(s,first);
	while (!isEmpty(s))
	{
		last++;
	}
	
}



void main()
{
	Queue test;
	initQueue(&test);
	for (unsigned int num=1;num<5;num++) 
		enqueue(&test,num);
	printf("size is %d\n",sizeQueue(test));
	printf("1 is empty, 0 isn't: %d",isEmpty(&test));
}