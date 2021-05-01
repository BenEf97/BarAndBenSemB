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
	int size,average=0;
	Queue tmp1, tmp2;

	//checking if the queue is empty
	if (isEmpty(s))
	{
		printf("The queue is empty!\n");
		return;
	}

	initQueue(tmp1);
	initQueue(tmp2);	
	size=sizeQueue(s);
	
	//if odd, will add the average to be the last node
	if (size%2)
	{
		//summing
		for (int i=0,tmp;i<size;i++)
		{
			tmp = dequeue(s);
			agverage += tmp;
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
		enqueue(tmp1,dequeue(s));

	//getting the second half out
	for (int i = 0; i < size; i++)
		enqueue(tmp2, dequeue(s));

	//rotating the 2nd queue and enqueuing into the original queue
	for(int i=0;i<size-1;i++)
	{
		rotate(tmp2);
		enqueue(s,dequeue(tmp2));
	}

	//enqueue the last one from 2nd queue
	enqueue(s,dequeue(tmp2));

	//enqueue the first half
	for (int i=0;i<size;i++)
		enqueue(s,dequeue(tmp1));
}

//gets a pointer to the queue, sorting it from the smallest to the biggest
void sort(Queue *s)
{
	Queue temp1,temp2;
	
	//checking if the queue is empty, if it does will return
	if (IsEmpty(s))
	{
		printf("The queue is empty!\n");
		return;
	}
	
}

//don't forget to delete
void plushminus(QUEUE* q) 
{
	if (isEmpty(q))
	{
		printf("empty!");
		return;
	}

	QUEUE pos, neg;// , zero;
	initQueue(&pos);
	initQueue(&neg);
	//initQueue(&zero);
	int data, count=0;
	while (!isEmpty(q))
	{
		data = dequeue(q);
		if (data > 0)
			enqueue(&pos, data);
		else if (data < 0)
			enqueue(&neg, data);
		else
			count++;
			//enqueue(&zero,data);
	}

	while (!isEmpty(&neg))
		enqueue(q, dequeue(&neg));

	for (int i = 0; i < count; i++)
		enqueue(q,0);
	
	/*while (!isEmpty(&zero))
		enqueue(q, dequeue(&zero));*/

	while (!isEmpty(&pos))
		enqueue(q, dequeue(&pos));

}



void main()
{
	Queue test;
	initQueue(&test);
	for (unsigned int num=1;num<5;num++) 
		enqueue(&test,num);
	printf("size is %d\n",sizeQueue(&test));
	printf("1 is empty, 0 isn't: %d",isEmpty(&test));
}