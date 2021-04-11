#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 80
#define TRUE 1
#define FALSE 0

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

int dateCheck(Date dateInput, Date dateList)
{
	if (dateInput.day == dateList.day) {
		if (dateInput.month == dateList.month) {
			if (dateInput.year == dateList.year){
				return TRUE;
			}
		}
	}
	return FALSE;
}
void numTripUpdate(Node* listPtr)
{
	Node *temp = listPtr;
	while (temp != NULL)
	{
		temp->trip->numTrip--;
		if (!temp->type)
		temp = temp->listType->nextSingle;
		else temp = temp->listType->DoubleType->nextDouble;
	}
}

void freeNode(Node* ptr)
{
	free(ptr->trip);
	free(ptr);
}

void deleteNode(Node* list, Date date)
{
	Node *ptr = list;
	Node *temp = NULL;
	//if list is empty
	if (list == NULL)
	{
		printf("The list is empty!\n");
		return;
	}
	//for single
	if (!list->type) {

		//delete first and update the list head
		while (dateCheck(date, list->trip->dateTrip))
		{
			temp = list;
			list = temp->listType->nextSingle;
			numTripUpdate(list);
			freeNode(temp);
		}

		//delete middle and last
		while (ptr->listType->nextSingle != NULL)
		{
			//delete last
			if (ptr->listType->nextSingle->listType->nextSingle == NULL)
			{
				freeNode(ptr->listType->nextSingle);
				ptr->listType->nextSingle = NULL;
				break;
			}

			//found a matching date in the middle
			if (dateCheck(date, ptr->listType->nextSingle->trip->dateTrip))
			{
				temp = ptr->listType->nextSingle;
				ptr->listType->nextSingle = temp->listType->nextSingle;
				freeNode(temp);
				numTripUpdate(ptr->listType->nextSingle);
			}
			ptr = ptr->listType->nextSingle;
		}
	}

	//for double
	//might be more than one
	else {
		//delete first and update the list head
		while (dateCheck(date, list->trip->dateTrip))
		{
			temp = list;
			list = temp->listType->DoubleType->nextDouble;
			list->listType->DoubleType->prev = NULL;
			numTripUpdate(list);
			freeNode(temp);
		}
		while (ptr != NULL)
		{
			//found a matching date in the middle
			if (dateCheck(date, ptr->trip->dateTrip))
			{
				temp = ptr;
				if (ptr->listType->DoubleType->nextDouble == NULL)
				{
					ptr->listType->DoubleType->prev->listType->DoubleType->nextDouble = temp->listType->DoubleType->nextDouble;
				}
				else
				{
					ptr->listType->DoubleType->prev->listType->DoubleType->nextDouble = temp->listType->DoubleType->nextDouble;
					ptr->listType->DoubleType->nextDouble->listType->DoubleType->prev = ptr->listType->DoubleType->prev;
					numTripUpdate(ptr->listType->DoubleType->nextDouble);
				}
				freeNode(temp);
			}
			ptr = ptr->listType->DoubleType->nextDouble;
		}
	}
}


void revese(Node* list)
{
	//Check if single way
	if (!list->type)
	{
		Node *prev=NULL,*next,*ptr;
		ptr=list; //0
		
		//revesing the pointers
		while (ptr!=NULL)
		{
			next=ptr->listType->nextSingle; //1	2 3 NULL
			ptr->listType->nextSingle=prev; //NULL	0 1 2
			prev=ptr; //0	1 2 3
			ptr=next; //1	2 3 NULL
		}
	}
	else printf("The list is double wayed.\n");
}

void freeItems(Node* list)
{
	Node* ptr = list,*temp;
	if (list == NULL)
	{
		printf("The list is empty.\n");
		return;
	}
	//signle type
	if (!list->type) {
		while (ptr != NULL)
		{
			temp = ptr->listType->nextSingle;
			freeNode(ptr);
			ptr = temp;
		}
	}
	//double type
	else {
		while (ptr != NULL)
		{
			temp = ptr->listType->DoubleType->nextDouble;
			freeNode(ptr);
			ptr = temp;
		}
	}
}

void printList(Node* list) {
	Node* ptr = list;
	if (list == NULL)
	{
		printf("The list is empty.\n");
		return;
	}
	(list->type) ? printf("\tDouble list:\n") : printf("\tSingle list:\n");
	while (ptr != NULL)
	{
		printf("Trip No. %d\n", ptr->trip->numTrip);
		printf("Destination: %s\n", ptr->trip->destination);
		printf("Date: %d/%d/%d\n", ptr->trip->dateTrip.day, ptr->trip->dateTrip.month, ptr->trip->dateTrip.year);
		if (!list->type) ptr = ptr->listType->nextSingle;
		else ptr = ptr->listType->DoubleType->nextDouble;
	}
}

Date dateInput()
{
	Date temp;
	printf("Please enter date to remove: ");
	scanf("%d/%d/%d", &temp.day, &temp.month, &temp.year);
	return temp;
}

void main()
{
	Node* head = NULL;
	char option;
	printf("\t***Main Menue***\nPlease enter your action:\n1- Add New Node\n2- Delete Node\n3- Reverse List\n4- Print List \n5- Delete whole list\n6- Quit");
	scanf("%c", option);
	fseek(stdin, 0, SEEK_END);
	while (1)
	{
		switch (option) {
		case '1':
			printf("**Add to End**\n");
			head = AddNodeToEnd(head, createTrip());
			continue;
		case '2':
			printf("**Delete Node**\n");
			deleteNode(head, dateInput());
			continue;
		case '3':
			printf("**Reverse**\n");
			revese(head);
			continue;
		case '4':
			printf("**Print List**\n");
			printList(head);
			continue;
		case '5':
			printf("**Delete List**\n");
			freeItems(head);
			continue;
		case '6':
			printf("Quiting the program...\n");
			freeItems(head);
			free(head);
			exit(0);
		default:
			printf("Error! Invalid input. Try again!\n");
			continue;
		}
	}
}


