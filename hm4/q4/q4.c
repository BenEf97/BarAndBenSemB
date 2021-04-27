#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0 
#define SIZE 100

typedef struct Node{
	char data;
	struct Node* next;
}Node;

typedef struct Stack {
	Node* head;
}Stack;

void push(Stack *s, char data)
{
	Node* newNode = (Node*)calloc(1, sizeof(Node));
	
	//if allocation failed
	if (!newNode)
	{
		printf("Out of memory!\n");
		exit(1);
	}
	
	//putting the new data in the node
	newNode->data = data;

	//if the stack is empty, the next will be null
	if (!isEmpty(s))
		newNode->next = s->head;
	s->head = newNode;
}


int isEmpty(Stack* s)
{
	if (s->head == NULL)
		return TRUE;
	else return FALSE;
}


//takes out the head, setting the next one. frees the one out and returns the data.
char pop(Stack* s)
{
	char out;
	//stack is empty, will return null
	if (isEmpty(s))
	{
		printf("The stack is empty!\n");
		return '\0';
	}
	Node* temp = s->head;
	out = s->head->data;
	s->head = temp->next;
	free(temp);
	return out;
}

char* strInput()
{
	char str[SIZE];
	printf("Please enter up to %d letter string: ",SIZE);
	fseek(stdin, 0, SEEK_END);
	gets(str);
	return str;
}

void printStack(Stack *s)
{
	while (!isEmpty(s))
	{
		printf("%c",pop(s));
	}
}

void hashFlipper(char* str)
{
	int i = 0;
	Stack* temp1 = (Stack*)calloc(1, sizeof(Stack));
	if (!temp1)
	{
		printf("Out of memory!");
		exit(1);
	}


	while (str[i]!='\0')
	{
		if (str[i]=='#')
		{
			i++;
			while (str[i]!='#')
			{
				push(temp1,str[i]);
				i++;
			}
			printStack(temp1);
			i++;
			continue;
		}
		printf("%c",str[i]);
		i++;
	}

	free(temp1);
}

void stackInput(Stack* s)
{
	char str[SIZE];
	int i=0;
	fseek(stdin,0,SEEK_END);
	gets(str);
	while (str[i]!='\0')
	{
		push(s,str[i]);
		i++;
	}
}

int isPlindrom(Stack s)
{
	Stack* temp=(Stack*)calloc(1,sizeof(Stack));
	if (!temp)
	{
		printf("Out of memory!");
		exit(1);
	}

	int even, count=0;
	char middle;
	if (isEmpty(&s))
	{
		printf("The stack is empty!\n");
		return 0;
	}

	while(!isEmpty(&s))
	{
		push(temp, pop(&s));
		count++;
	}

	if (count == 1)
	{
		printf("The stack has only 1 character!\n");
		return;
	}

	if (count%2) even=TRUE;
	else even=FALSE;

	count/=2;
	for (int i=0;i<count;i++)
	{
		push(&s,pop(temp));
	}
	if (!even)
		middle=pop(temp);

	while (!isEmpty(&s))
	{
		if (pop(&s) != pop(temp))
		{
			free(temp);
			return FALSE;
		}
	}
	free(temp);
	return TRUE;
}


void main()
{
	////Hash Flipper start
	//printf("***Hash Flipper***\nThis function will receive a string, print it and flip the letters between two hashtags '#'\n");
	//char str[] = { "Remem#reb# thi#carp s#tice" };
	//hashFlipper(str);
	////Hash Flipper end

	printf("\n");
	Stack pilandromS;
	pilandromS.head = (Node*)calloc(1, sizeof(Node));
	stackInput(&pilandromS);
	isPlindrom(pilandromS);
	system("pause");
}
