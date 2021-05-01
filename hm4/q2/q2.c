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

//if the Queue is empty, will return TRUE, else will return FALSE
int isEmpty(Queue* s)
{
	if (s->head == NULL && s->tail == NULL)
		return TRUE;
	else return FALSE;
}

//Removing from the head
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

//maayan initqueue
void initQueue(Queue* s) 
{
	s->head = s->tail = NULL;
}

//Checks the size of the queue
int sizeQueue(Queue *s)
{
	int size = 0;
	Queue temp;
	initQueue(&temp);

	//Checking the size of the queue	
	while (!isEmpty(&s))
	{
		enqueue(&temp, dequeue(s));
		size++;
	}
	
	//returning to the original state
	while (!isEmpty(&temp))
	{
		enqueue(s, dequeue(&temp));
	}
	return size;
}

//Rotating the queue, taking the last to be the first
void rotate(Queue* s)
{
	unsigned int first,last;
	int size;

	//checking if the queue is empty, if it does will return to main
	if (isEmpty(s))
	{
		printf("The queue is empty!\n");
		return;
	}

	size=sizeQueue(s);
	if(size==1)
	{
		printf("The size of queue is 1, there is nothing to rotate\n");
		return;
	}

	//rotating the queue, stops when the last is the first
	for (int i=0;i<size-1;i++)
	{
		enqueue(s,dequeue(s));
	}
}

//gets a pointer for a queue, cuts it in half, excact same size, replace the order
void cutAndReplace(Queue *s)
{	
	int size;
	unsigned int average = 0;
	Queue tmp1, tmp2;

	//checking if the queue is empty
	if (isEmpty(s))
	{
		printf("The queue is empty!\n");
		return;
	}

	initQueue(&tmp1);
	initQueue(&tmp2);	
	size=sizeQueue(s);
	
	//if odd, will add the average to be the last node
	if (size%2)
	{
		//summing
		for (int i=0,tmp;i<size;i++)
		{
			tmp = dequeue(s);
			average += tmp;
			enqueue(s,tmp);
		}
		//calculating the average, and updating the size
		average/=size;
		size++;
		enqueue(s, average);
	}
	//cutting the size in half
	size/=2;

	//getting the first half out
	for (int i=0;i<size;i++)
		enqueue(&tmp1,dequeue(s));

	//getting the second half out
	for (int i = 0; i < size; i++)
		enqueue(&tmp2, dequeue(s));

	//rotating the 2nd queue and enqueuing into the original queue
	for(int i=0;i<size-1;i++)
	{
		rotate(&tmp2);
		enqueue(s,dequeue(&tmp2));
	}

	//enqueue the last one from 2nd queue
	enqueue(s,dequeue(&tmp2));

	//enqueue the first half
	for (int i=0;i<size;i++)
		enqueue(s,dequeue(&tmp1));
}

//gets a pointer to the queue, sorting it from the smallest to the biggest
void sort(Queue *s)
{
	Queue temp1;
	unsigned int tmp,i=1;
	int size;
	
	//checking if the queue is empty, if it does will return
	if (IsEmpty(s))
	{
		printf("The queue is empty!\n");
		return;
	}

	initQueue(&temp1);
	
	while (!isEmpty(s))
	{
		size=sizeQueue(s);
		for (int j = 0; j < size; j++)
		{
			tmp = dequeue(s);
			if (tmp < i) enqueue(&temp1, tmp);
			else enqueue(s, tmp);
		}
		i++;
	}
	while (!isEmpty(&temp1))
		enqueue(s, dequeue(&temp1));
}

void printQueue(Queue* s) 
{
	if (isEmpty(s))
	{
		printf("The queue is empty!");
		return;
	}
	Queue qtemp;
	initQueue(&qtemp);
	unsigned int data;
	while (!isEmpty(s))
	{
		data = dequeue(s);
		printf("%u\t", data);
		enqueue(&qtemp,data);
	}
	while (!isEmpty(&qtemp))
	{
		enqueue(s, dequeue(&qtemp));
	}
}

void queueInput(Queue* s)
{
	unsigned int num, size;
	printf("how much elements you want to add");
	scanf("%d", &size);
	for(int i=0;i<size;i++)
	{
		printf("Please enter unsigned integer: ");
		scanf("%u", &num);
		enqueue(s, num);
	}
	printf("Please enter unsigned integer: ");
	scanf("%u", &num);
}



void main()
{
	Queue q1,q2,q3;
	int size;
	initQueue(&q1);
	initQueue(&q2);
	initQueue(&q3);

	printf("Q1: Rotate:\n");
	queueInput(&q1);
	printf("The queue before: ");
	printQueue(&q1);
	rotate(&q1);
	printf("\nAfter the rotate: ");
	printQueue(&q1);

	size=sizeQueue(&q1);
	for (int i=0;i<size;i++)
	{
		dequeue(&q1);
	}

	printf("\nQ2: Cut And Replace:\n");
	queueInput(&q2);
	printf("The Queue before: ");
	printQueue(&q2);
	cutAndReplace(&q2);
	printf("After: ");
	printQueue(&q2);

	size=sizeQueue(&q2);
	for (int i=0;i<size;i++)
	{
		dequeue(&q2);
	}

	printf("\nQ3: Sort\n");
	queueInput(&q3);
	printf("The queue before: ");
	printQueue(&q3);
	rotate(&q3);
	printQueue(&q3);

	size=sizeQueue(&q3);
	for (int i=0;i<size;i++)
	{
		dequeue(&q3);
	}

}