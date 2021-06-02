#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0 


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

int isEmpty(Queue* s);
unsigned int dequeue(Queue* s);
void enqueue(Queue* s, unsigned int data);
void initQueue(Queue* s);
int sizeQueue(Queue *s);
void rotate(Queue* s);
void cutAndReplace(Queue *s);
void sort(Queue *s);
void printQueue(Queue* s);
void queueInput(Queue* s);
void resetQueue(Queue* s);

void main()
{
	Queue q;
	initQueue(&q);
	
	//Q1 Rotate start
	printf("Q1: Rotate- This function rotates the queue until the last node will be the first one\n");
	queueInput(&q);
	printf("The queue before: ");
	printQueue(&q);
	rotate(&q);
	printf("\nAfter the rotate: ");
	printQueue(&q);

	//reseting the queue, freeing all the allocations and preparing for the next one
	resetQueue(&q);
	//Rotate end

	//Q2 Cut and Replace start
	printf("\nQ2: Cut And Replace- This function cuts the queue in half, flips the second half, and replaces the halfs:\n");
	queueInput(&q);
	printf("The Queue before: ");
	printQueue(&q);
	cutAndReplace(&q);
	printf("\nAfter: ");
	printQueue(&q);
	resetQueue(&q);
	//Cut and replace end

	//Q3 Sort start
	printf("\nQ3: Sort-This function sorts the integers from the smallest to the biggest\n");
	queueInput(&q);
	printf("The queue before: ");
	printQueue(&q);
	sort(&q);
	printf("\nThe queue after: ");
	printQueue(&q);
	resetQueue(&q);
	//Sort end
}

//if the Queue is empty, will return TRUE, else will return FALSE
int isEmpty(Queue* s)
{
	if (s->head == NULL && s->tail == NULL)
			return TRUE;
	else return FALSE;
}

//Removing from the head, from lecture
unsigned int dequeue(Queue* s) 
{
	Node* temp = s->head;
	unsigned int data = temp->data;

	if (isEmpty(s)) 
	{
		printf("empty!");
		return 0;
	}

	s->head = s->head->next;
	if (s->head == NULL)
		s->tail = NULL;
	
	free(temp);
	return data;
}

//Enqueue new node to the end of the Queue. Used from lecture
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

//initQueue from lecture
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
	while (!isEmpty(s))
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

//Q1: Rotating the queue, taking the last to be the first
void rotate(Queue* s)
{
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

//Q2: gets a pointer for a queue, cuts it in half, excact same size, replace the order
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

//Q3: gets a pointer to the queue, sorting it from the smallest to the biggest
void sort(Queue *s)
{
	Queue temp1;
	unsigned int tmp, min;
	int size;
	
	//checking if the queue is empty, if it does will return
	if (isEmpty(s))
	{
		printf("The queue is empty!\n");
		return;
	}

	size = sizeQueue(s);

	//allocating the temporary queue
	initQueue(&temp1);
	
	//seeking for the minimal value, and returning to the original state
	while(!isEmpty(s))
	{		
		//init tmp and min to be the data of the head, and putting the data back
		tmp = min = dequeue(s);
		enqueue(s,min);
		
		//seeking for the smallest value
		for (int j=0;j<size-1;j++)
		{
			tmp=dequeue(s);
			if (tmp<min) min=tmp;
			enqueue(s,tmp);
		}

		//seeking and enqueue to the temp1
		for (int j=0;j<size;j++)
		{
			tmp=dequeue(s);
			//if tmp==min will enqueue to the tmp, else will continue without change
			if (tmp==min)
				{
					enqueue(&temp1,tmp);
					break;
				}
			enqueue(s,tmp);
		}
		size--;
	}

	//returning the organized queue to the original queue and at the same time free the temp queue
	while (!isEmpty(&temp1))
		enqueue(s, dequeue(&temp1));	
}

//print the queue 
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

//user input for the queue 
void queueInput(Queue* s)
{
	unsigned int num;
	int size;
	printf("Enter how many elements you want to add: ");
	scanf("%d", &size);
	for(int i=0;i<size;i++)
	{
		printf("Please enter unsigned integer: ");
		scanf("%u", &num);
		enqueue(s, num);
	}
	printf("\n");
}

//Freeing the nodes, and initilize the queue
void resetQueue(Queue* s)
{
	int size=sizeQueue(s);
	for (int i=0;i<size;i++)
		dequeue(s);
	initQueue(s);
}