/*אסור לגשת באופן ישיר לנתונים!! רק עם הכנסה והוצאה, רלוונטי גם לחלק א'*/



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

int isEmpty(Queue *s)
{
	if (s->head == NULL && s->tail == NULL) //&& is optional
		return 1;
	return 0; //there is no need for else
}

//adding to the tail, no limit and there is no need to check if empty
void enqueue(Queue *s, unsigned int data)
{
	//allocating memory, 
	//Node *newNode = (Node*)calloc(1, sizeof(Node)); //comment but if we use it then we don't need to set it on NULL
	Node *newNode = (Node*)malloc(sizeof(Node));

	//in case of memory allocation fail
	if (!newNode)
	{
		printf("Out of memory!\n");
		exit(1);
	}

	//placement of the data
	newNode->data = data;
	newNode->next = NULL;

	//checking if the queue is empty
	if (!isEmpty(s))
	{
		s->tail->next = newNode;
		s->tail = newNode;
		return;
	}

	//if the queue is empty then we do double placement
	s->head = s->tail = newNode;
}



//removing the head
unsigned int dequeue(Queue *s) //why isn't it void? we need the data value!
{
	unsigned int value = s->head->data;
	Queue *temp = s;

	//if the list is empty, will return 0
	if (isEmpty(s))
	{
		printf("The list is empty!\n");
		return 0;
	}

	//only one element
	if (s->tail == s->head)
	{
		free(s->head);
		s->head = NULL;
		s->tail = NULL;
	}

	else {
		s->head = temp->head->next;
		free(temp->head);
	}

	return value;
}


//gets a ptr for queue, switch between the head and the tail
/*[1][2][3][4]
to [4][1][2][3]
can only use enqueue and dequeue, add to last and remove first*/
void rotate(Queue *s)
{
	unsigned int last, first;

}


void main()
{

}