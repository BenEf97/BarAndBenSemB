#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 80

typedef struct doubleType
{
	struct doubleType* prev;
	struct doubleType* next;
}doubleType;

typedef struct singleType
{
	struct singleType* next;
}singleType;

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
	Trip* pointer;
	union typeNode
	{
		doubleType *one;
		singleType *zero;
	};
}Node;


