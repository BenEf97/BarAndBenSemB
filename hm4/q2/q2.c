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




void main()
{

}