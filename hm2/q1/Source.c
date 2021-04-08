#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 80


typedef struct
{
	int day;
	int month;
	int year;
}Date;

typedef struct
{
	int numTrip;
	char destination[SIZE];
	Date dateTrip;
}Trip;

typedef struct Node
{
	int type;
	Trip* trip;
	union Nodelist
	{
		struct Node{
			struct Node *prev;
			struct Node *nextDouble;
		}*DoubleType;

		struct Node *nextSingle;
	}*listType;
}Node;

void memoryFail()
{
	printf("Error! Out of memory!");
	exit(1);
}

Node* AddNodeToEnd(Node* list,Trip* tripPtr) {
	Node* ptr = list;
	int tripCount=1;
	//Memory allocation
	Node* newNode = (Node*)calloc(1, sizeof(Node));
	if (newNode == NULL)
		memoryFail();

	newNode->trip = tripPtr;

	//If the list is empty, the type is 0 because of calloc
	if (list == NULL)
	{
		newNode->trip->numTrip = 1;
		return newNode;
	}
	//For double type list
	if (ptr->type)
	{
		for (; ptr->listType->DoubleType->nextDouble != NULL; ptr = ptr->listType->DoubleType->nextDouble,tripCount++);
		
		newNode->trip->numTrip = tripCount;
		newNode->type = 1;
		newNode->listType->DoubleType->prev = ptr;
		ptr->listType->DoubleType->nextDouble = newNode;
		return list;
	}

	//For single type list
	else
	{
		for (; ptr->listType->nextSingle != NULL; ptr = ptr->listType->nextSingle,tripCount++);
		newNode->trip->numTrip=tripCount;
		ptr->listType->nextSingle = newNode;
		return list;
	}
}

Trip* createTrip()
{
	Trip* newTrip = (Trip*)calloc(1, sizeof(Trip));
	if (newTrip == NULL)
		memoryFail();
	printf("Please enter destination: ");
	fseek(stdin, 0, SEEK_END);
	gets(newTrip->destination);
	printf("Please enter date in DD/MM/YY format: ");
	scanf("%d/%d/%d", newTrip->dateTrip.day, newTrip->dateTrip.month, newTrip->dateTrip.year);
	fseek(stdin, 0, SEEK_END);
	
}
