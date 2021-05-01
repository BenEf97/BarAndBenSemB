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

void push(Stack *s, char data);
int isEmpty(Stack* s);
char pop(Stack* s);
char* strInput();
void printStack(Stack *s);
void hashFlipper(char* str);
void stackStrInput(Stack* s);
int isPlindrom(Stack s);
void allocationFail();
void stackInit(Stack* s);
int stackSize(Stack *s);
void stackInput(Stack* s);
void rotate(Stack *s, int n);
char dataCheck(Stack* s);

void main()

{
	//Q1: Hash Flipper start
	printf("***Hash Flipper***\nThis function will receive a string, print it and flip the letters between two hashtags '#'\n");
	char str[] = { "Remem#reb# thi#carp s#tice" };
	printf("the original string is: ");
	puts(str);
	hashFlipper(str);
	//Hash Flipper end

	//Q2: Pilandrom start
	printf("***Is Plindrom***\n");
	Stack plindromS;
	stackInit(&plindromS);
	stackStrInput(&plindromS);
	(isPlindrom(plindromS) == TRUE) ? printf("is plindrom\n\n") : printf("is not plindrom\n\n");
	
	printf("***Rotate***\n");
	Stack Nstack;
	int n;
	stackInit(&Nstack);
	stackInput(&Nstack);
	printf("Please choose how much elements you want to replace: ");
	fseek(stdin, 0, SEEK_END);
	scanf("%d", &n);
	rotate(&Nstack, n);
	free(Nstack.head);
	printf("\n");
	//system("pause");
}

//Pushing new node and data to the stack
void push(Stack *s, char data)
{
	//allocating memory
	Node* newNode = (Node*)calloc(1, sizeof(Node));
	
	//if allocation failed will exit
	if (!newNode)
		allocationFail();
	
	//putting the new data in the node
	newNode->data = data;

	//if the stack is empty, the next will be null
	if (!isEmpty(s))
		newNode->next = s->head;

	s->head = newNode;
}

//Checking if the stack is empty, if it does will return TRUE(1), else will return FALSE(0)
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

	//setting a pointer at the head, getting the data on 'out'
	Node* temp = s->head;
	out = s->head->data;
	//setting the head to be the next ones
	s->head = temp->next;
	free(temp);
	return out;
}

//For q1, getting input for the string, assumming for correct input and returning the string to be used
char* strInput()
{
	char str[SIZE];
	printf("Please enter up to %d letter string: ",SIZE);
	fseek(stdin, 0, SEEK_END);
	scanf("%s",str);
	return str;
}

//Printing all the elements, and freeing them with pop
void printStack(Stack *s)
{
	while (!isEmpty(s))
	{
		printf("%c",pop(s));
	}
}

//Seek for hash #, creating a stack and flipping it. Prints the whole sentence.
void hashFlipper(char* str)
{
	int i = 0;
	Stack temp1;
	stackInit(&temp1);
	
	//Printing the fixed string, removing all # tags and flipping the sentence
	printf("The fixed string is: ");
	while (str[i]!='\0')
	{
		//if # found
		if (str[i]=='#')
		{
			//skipping to the next idx
			i++;

			//while being between 2 # tags, flipping the stack
			while (str[i]!='#')
			{
				push(&temp1,str[i]);
				i++;
			}

			//printing the new fixed stack
			printStack(&temp1);
			i++;
			continue;
		}

		//printing each character
		printf("%c",str[i]);
		i++;
	}
	printf("\n\n");
}

//Getting user input for a string
void stackStrInput(Stack* s)
{
	char str[SIZE];
	int i=0;
	printf("Please enter a %d character plindrom: ",SIZE);
	fseek(stdin,0,SEEK_END);
	scanf("%s",str);

	//pushing each character to the stack from the string
	while (str[i]!='\0')
	{
		push(s,str[i]);
		i++;
	}
}

//Checking if a stack is pilandrom
int isPlindrom(Stack s)
{
	//result will determine if its a pilandrom or not.
	int even, count = 0,result=TRUE;
	//incase of uneven characters, the middle one will be out
	char middle;
	Stack temp;
	stackInit(&temp);

	//checking if the stack is empty
	if (isEmpty(&s))
	{
		printf("The stack is empty!\n");
		return 0;
	}

	//poping all the data from the stack and pushing into the new temporary stack
	while(!isEmpty(&s))
	{
		//if the data is '\0' then it will be popped
		if (dataCheck(&s) == '\0')
		{
			pop(&s);
			continue;
		}

		//pushing the data to the new temp stack
		push(&temp, pop(&s));
		//count the size of the stack
		count++;		
	}

	//if there is only one node will return FALSE
	if (count == 1)
	{
		printf("The stack has only 1 character!\n");
		pop(&temp);
		free(temp.head);
		return FALSE;
	}

	//checking if the size is even or odd. if even it will be TRUE, else FALSE
	if (!(count%2)) even=TRUE;
	else even=FALSE;

	//Splitting the size in half, and pushing half of the elements to the original stack
	for (int i=0;i<(count/2);i++)
	{
		push(&s,pop(&temp));
	}
	
	//if the size is odd, then it will pop the middle element
	if (!even)
		middle=pop(&temp);

	//checking if the elements are matching, also popping all the elements
	while (!isEmpty(&s))
	{
		//if missmatch, then the result will be FALSE.
		if (pop(&s) != pop(&temp))
		{
			result = FALSE;
		}
	}

	//free the temp.head, returns the result
	free(temp.head);
	return result;
}


//In case of failed memory allocation, the user will get an output and the program will exit
void allocationFail()
{
	printf("Out of memory! Exiting the program!\n");
	exit(1);
}

//Creating new stack
void stackInit(Stack* s)
{
	s->head = (Node*)calloc(1, sizeof(Node));
	if (!s->head)
		allocationFail();
}

//Getting the stack size, and keeping the original stack
int stackSize(Stack *s)
{
	Stack tmp;
	int count = 0;
	stackInit(&tmp);

	//pushing the data to the new temp stack
	while (dataCheck(s)!= '\0')
	{
		push(&tmp,pop(s));
		count++;
	}
	
	//pushing it back to the original stack
	while (dataCheck(&tmp)!= '\0')
	{
		push(s, pop(&tmp));
	}

	//freeing the temp head, returning count
	free(tmp.head);
	return count;
}

//Getting input from the user for the stack, assuming for correct input
void stackInput(Stack* s)
{
	int i = 1;
	char c;

	//while i is not 0, the program will keep getting input.
	while (i)
	{
		printf("Enter char to the stack (enter '0' to end): ");
		fseek(stdin, 0, SEEK_END);
		scanf("%c", &c);
		switch (c)
		{
			//incase the user wants to finish
			case '0':
				i = 0;
				break;
			default: 
				push(s, c);
		}
	}
}

//Q3: taking n size of the first enterd elements, and taking them as a whole to the end, without changing the order of the rest
void rotate(Stack *s, int n)
{
	int i = 0,size;
	Stack tmp1, tmp2;
	
	//if n==0 it will return
	if (!n)
	{
		printf("There is nothing to replace\n");
		return;
	}

	//if the stack is empty
	if (isEmpty(s))
	{
		printf("The stack is empty!\n");
		return;
	}
	
	//getting the size of the stack
	size = stackSize(s);
	
	//if the acutal size is smaller than n
	if (size<n)
	{
		printf("The stack is not big enough for replace\n");
		return;
	}

	stackInit(&tmp1);
	stackInit(&tmp2);

	//pushing half of the original to temp1 stack
	while (i < (size-n))
	{
		push(&tmp1, pop(s));
		i++;
	}

	//pushing from the the rest of the original to the temp2
	while (dataCheck(s) != '\0') push(&tmp2, pop(s));
	
	//pushing both back to the original in the new order
	while (dataCheck(&tmp1)!= '\0') push(s, pop(&tmp1));
	while (dataCheck(&tmp2)!= '\0') push(s, pop(&tmp2));

	//printing with tabs
	while (dataCheck(s) != '\0')
	{
		printf("%c\t", pop(s));
	}
	
	printf("\n");
	free(tmp1.head);
	free(tmp2.head);
}

//pops the data and pushing it back to the stack, reurns the data
char dataCheck(Stack* s)
{
	char data;
	data = pop(s);
	push(s, data);
	return data;
}
