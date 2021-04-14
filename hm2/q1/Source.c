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

//The sturct Node has 2 options for linked lists- single way or double.
typedef struct Node
{
	int type;
	Trip* trip;
	union
	{
		struct { //8 bytes
			struct Node *prev;
			struct Node *nextDouble;
		}DoubleType;

		struct Node *nextSingle; //4 bytes
	}listType;
}Node;

//In case of failed memory allocation
void memoryFail()
{
	printf("Error! Out of memory!");
	exit(1);
}

//Checks if the list is empty
int emptyCheck(Node* list)
{
	if (list == NULL)
	{
		printf("The list is empty!\n");
		return FALSE;
	}
	else return TRUE;
}

//Date input, assuming for valid input.
Date dateInput()
{
	Date temp;
	printf("Please enter a valid date: ");
	scanf("%d/%d/%d", &temp.day, &temp.month, &temp.year);
	fseek(stdin, 0, SEEK_END);
	return temp;
}

//Adding a new node to the end of the list.
Node* AddNodeToEnd(Node* list,Trip* tripPtr) {
	Node* ptr = list;
	int tripCount=1;

	//Memory allocation
	Node* newNode = (Node*)calloc(1, sizeof(Node));
	if (newNode == NULL)
		memoryFail();

	newNode->trip = tripPtr;

	//If the list is empty
	if (list == NULL)
	{
		newNode->trip->numTrip = 1;
		newNode->type = 0;
		/*
		//Debug for Double way list
		printf("What type of linked list would you like?\n0-Single/ 1-Double: ");
		scanf("%d", &(newNode->type));
		fseek(stdin, 0, SEEK_END);
		//End of debug
		*/
		return newNode;

	}
	//Checking if the list is single wayed or double wayed
	if (!list->type)
		newNode->type = 0;
	else
		newNode->type = 1;
	
	//For double type list
	if (ptr->type)
	{
		//Getting to the last node, and counting the number of the trip
		for (; ptr->listType.DoubleType.nextDouble != NULL; ptr = ptr->listType.DoubleType.nextDouble,tripCount++);
		tripCount++;
		newNode->trip->numTrip = tripCount;
		newNode->listType.DoubleType.prev = ptr;
		ptr->listType.DoubleType.nextDouble = newNode;
		return list;
	}

	//For single type list
	else
	{
		//Getting to the last node, and counting the number of the trip
		for (; ptr->listType.nextSingle != NULL; ptr = ptr->listType.nextSingle,tripCount++);
		tripCount++;
		newNode->trip->numTrip=tripCount;
		ptr->listType.nextSingle = newNode;
		return list;
	}
}

//Creating a new trip
Trip* createTrip()
{
	Trip* newTrip = (Trip*)calloc(1, sizeof(Trip));
	if (newTrip == NULL)
		memoryFail();
	printf("Please enter destination: ");
	fseek(stdin, 0, SEEK_END);
	gets(newTrip->destination);
	newTrip->dateTrip = dateInput();
	fseek(stdin, 0, SEEK_END);
	return newTrip;
}

//Checking for a matching date
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

//After deleting a node, the trip numbers are updated
void numTripUpdate(Node* listPtr)
{
	Node *temp = listPtr;
	while (temp != NULL)
	{
		temp->trip->numTrip--;
		if (!temp->type)
		temp = temp->listType.nextSingle;
		else temp = temp->listType.DoubleType.nextDouble;
	}
}

//Freeing all the allocated memory
void freeNode(Node* ptr)
{
	free(ptr->trip);
	free(ptr);
}

//Delete all the trips at the given date
Node *deleteNode(Node* list, Date date)
{
	Node *ptr;
	Node *temp = NULL;
	int result = FALSE;
	//if list is empty
	if (!emptyCheck(list)) return list;
	
	//for single
	if (!list->type) {

		//delete first and update the list head
		while (dateCheck(date, list->trip->dateTrip))
		{
			temp = list;
			list = temp->listType.nextSingle;
			numTripUpdate(list);
			freeNode(temp);
			result = TRUE;
		}
		ptr = list;

		//delete middle and last
		while (ptr->listType.nextSingle != NULL)
		{
			//found a matching date in the middle
			if (dateCheck(date, ptr->listType.nextSingle->trip->dateTrip))
			{
				temp = ptr->listType.nextSingle;
				ptr->listType.nextSingle = temp->listType.nextSingle;
				freeNode(temp);
				numTripUpdate(ptr->listType.nextSingle);
				result = TRUE;
			}
			ptr = ptr->listType.nextSingle;
			if (!ptr) break;
		}
	}

	//for double
	else {
		//delete first and update the list head
		while (dateCheck(date, list->trip->dateTrip))
		{
			temp = list;
			list = temp->listType.DoubleType.nextDouble;
			list->listType.DoubleType.prev = NULL;
			numTripUpdate(list);
			freeNode(temp);
			result = TRUE;
		}
		ptr = list;

		while (ptr->listType.DoubleType.nextDouble != NULL)
		{
			//found a matching date in the middle
			if (dateCheck(date, ptr->listType.DoubleType.nextDouble->trip->dateTrip))
			{
				temp = ptr->listType.DoubleType.nextDouble;
				ptr->listType.DoubleType.nextDouble = temp->listType.DoubleType.nextDouble;
				if (temp->listType.DoubleType.nextDouble)
					temp->listType.DoubleType.nextDouble->listType.DoubleType.prev = ptr;
				freeNode(temp);
				numTripUpdate(ptr->listType.DoubleType.nextDouble);
				result = TRUE;
			}
			ptr = ptr->listType.DoubleType.nextDouble;
			if (!ptr) break;
		}
	}
	if (result) printf("All the trips at this date are deleted!\n");
	else printf("The date is not found! Please try another date.\n");
	return list;
}

//Counting the ammount of trips
int tripCounter(Node* list)
{
	Node* ptr = list;
	int count = 0;
	for (; ptr != NULL;ptr=ptr->listType.nextSingle,count++);
	return count;
}

//Reversing the order of the nodes
Node* revese(Node* list)
{
	if (!emptyCheck(list)) return NULL;

	//Check if single way
	if (!list->type)
	{
		Node *ptr = list, *nextmp = NULL, *ptrtmp;

		//testing the count
		int tripNum = tripCounter(list);

		printf("Reversing the list...\n");
		//revesing the pointers
		while (ptr!=NULL)
		{
			//Updating the new order
			ptr->trip->numTrip = tripNum;

			ptrtmp = ptr->listType.nextSingle;
			ptr->listType.nextSingle = nextmp;
			nextmp = ptr;
			ptr = ptrtmp;

			//this is the test...Works!
			tripNum--;

		}
		list = nextmp;
		printf("The list is reveresed!\n");
	}
	else printf("The list is double wayed.\n");
	return list;
}

Node* freeItems(Node* list)
{
	Node* ptr = list,*temp;
	if (!emptyCheck(list)) return NULL;
	

	printf("Freeing items...\n");
	//single type
	if (!list->type) {
		while (ptr != NULL)
		{
			temp = ptr->listType.nextSingle;
			freeNode(ptr);
			ptr = temp;
		}
	}
	//double type
	else {
		while (ptr != NULL)
		{
			temp = ptr->listType.DoubleType.nextDouble;
			freeNode(ptr);
			ptr = temp;
		}
	}
	return NULL;
}

void printList(Node* list) {
	Node* ptr = list;
	if (!emptyCheck(list)) return;

	(list->type) ? printf("\tDouble list:\n") : printf("\tSingle list:\n");
	while (ptr != NULL)
	{
		printf("Trip No. %d\n", ptr->trip->numTrip);
		printf("Destination: %s\n", ptr->trip->destination);
		printf("Date: %d/%d/%d\n", ptr->trip->dateTrip.day, ptr->trip->dateTrip.month, ptr->trip->dateTrip.year);
		if (!list->type) ptr = ptr->listType.nextSingle;
		else ptr = ptr->listType.DoubleType.nextDouble;
	}
}


void main()
{
	Node* head = NULL;
	char option;
	while (1)
	{
		printf("\n\t***Main Menu***\nPlease enter your action:\n1- Add New Node\n2- Delete Trip\n3- Reverse List\n4- Print List \n5- Delete whole list\n6- Quit\n");
		scanf("%c", &option);
		fseek(stdin, 0, SEEK_END);
		switch (option) {
		case '1':
			printf("**Add to End**\n");
			head = AddNodeToEnd(head, createTrip());
			printf("A new node has been added!\n");
			continue;
		case '2':
			printf("**Delete Trip**\n");
			head = deleteNode(head, dateInput());
			continue;
		case '3':
			printf("**Reverse**\n");
			head = revese(head);
			continue;
		case '4':
			printf("**Print List**\n");
			printList(head);
			continue;
		case '5':
			printf("**Delete List**\n");
			head = freeItems(head);
			continue;
		case '6':
			printf("Quiting the program...\n");
			freeItems(head);
			exit(0);
		default:
			printf("Error! Invalid input. Try again!\n");
			fseek(stdin, 0, SEEK_END);
			continue;
		}
	}
}


