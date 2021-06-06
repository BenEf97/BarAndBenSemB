﻿/*To do:
-Special cases for every function
-createInvoice- fputs doing problems
-Debug*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 80
#define TRUE 1
#define FALSE 0
#define SIZE2 100

typedef struct groceryItem
{
	char itemsName[SIZE];
	int quantity;
	float price;
}groceryItem;

typedef struct groceryList
{
	groceryItem** listItems;
	int size;
}groceryList;

void addGroceryItem(groceryList * pList);
void undo(groceryList * pList);
void CreateInvoice(groceryList * pList);
void CalcInvoiceRowSummary();
void allocationFail();
void openFileFailed();

void main()
{
	//debug
	groceryList pList;
	pList.listItems = (groceryItem**)calloc(1, sizeof(groceryItem));
	pList.size = 0;
	addGroceryItem(&pList);
	addGroceryItem(&pList);
	CreateInvoice(&pList);
	CalcInvoiceRowSummary();
	undo(&pList);
	undo(&pList);
	//free(&pList.listItems);
}


//In case of failed memory allocation, the user will get an output and the program will exit
void allocationFail()
{
	printf("Out of memory! Exiting the program!\n");
	exit(1);
}


/*Q1 a: Recives a pointer to a grocery list, adds 1+ to the current size, allocates new memory at the end of the array
input: name of the item, price,  quantity and will save it in the last space.*/
void addGroceryItem(groceryList * pList)
{
	groceryItem temp;

	//Increasing the size of the array and allocation new memory to the array
	pList->size++;
	pList->listItems = (groceryItem**)realloc(pList->listItems, sizeof(groceryItem)*pList->size);
	
	//If allocation fails
	if (pList->listItems == NULL)
		allocationFail();

	//allocating the new item
	pList->listItems[pList->size-1] = (groceryItem*)calloc(1, sizeof(groceryItem));

	//If allocation fails
	if (pList->listItems[pList->size-1]==NULL)
		allocationFail();

	//User input for name of the item:
	printf("Please enter the name of the item: ");
	fseek(stdin, 0, SEEK_END);
	fgets(temp.itemsName, SIZE, stdin);
	temp.itemsName[strlen(temp.itemsName)-1] = '\0';

	//Input for quantity
	printf("Please enter the quantity of the item: ");
	scanf("%d", &temp.quantity);

	//Input for price
	printf("Please enter the price of the item: ");
	scanf("%f", &temp.price);

	strcpy(pList->listItems[pList->size-1]->itemsName,temp.itemsName);	
	pList->listItems[pList->size - 1]->price = temp.price;
	pList->listItems[pList->size - 1]->quantity = temp.quantity;
}



/*Q1 b: The function gets a pointer to the list, deletes the last item on the list, freeing the memory of the item and reallocates the memory in a smaller size by 1*/
void undo(groceryList * pList)
{
	//freeing the last element in the list
	free(pList->listItems[pList->size - 1]);
	
	//decreasing the size
	pList->size--;

	//if size is not 0
	if (pList->size)
	{
		//reallocating memory with smaller size
		pList->listItems = (groceryItem**)realloc(pList->listItems, sizeof(groceryItem)*pList->size);
		
		//if allocation failed
		if (pList->listItems == NULL)
			allocationFail();
	}

	//if the list is empty, it will free the list
	else free(pList->listItems);
}


//If file opening fails, the user will get output and the program will exit.
void openFileFailed()
{
	printf("The file didn't open!");
	exit(1);
}

/*Q1 c: this function gets a list and creates a recipet file for the specific list.*/
void CreateInvoice(groceryList * pList)
{
	//opens a file, if it doesn't exist a new one will be created
	FILE *pf = fopen("invoice.txt","w");

	//if the opening failed
	if (!pf)
		openFileFailed();

	//Printing the info into the file
	for (int idx = 0; idx < pList->size; idx++)
	{
		//debug: idk but if I comment fputs i get an error
		fputs(pList->listItems[idx]->itemsName,pf);
		fprintf(pf, " %d %f\n", pList->listItems[idx]->quantity, pList->listItems[idx]->price);
	}

	//Closing the file
	fclose(pf);
}

void CalcInvoiceRowSummary()
{
	//init all vars
	FILE *pfr = fopen("invoice.txt", "r+");
	FILE *pft = fopen("tmpfile.txt", "a+");
	char c = 0, tmp[20];
	int  idx, num1;
	float sum, num2;

	//setting the cur to the start
	fseek(pfr, 0, SEEK_SET);

	//while not at the end of the file
	while (!feof(pfr))
	{
		//skipping the name
		while ( c<'0' || c>'9')
		{
			c = fgetc(pfr);
			if(c<'0' || c>'9') fputc(c, pft);
		}

		//moving back to get the num
		fseek(pfr, -1, SEEK_CUR);
		idx = 0;

		//getting the first number, quantity
		while (c!= ' ')
		{
			c = fgetc(pfr);
			fputc(c, pft);
			tmp[idx] = c;
			idx++;
		}
		tmp[idx - 1] = '\0';
		num1 = atoi(tmp);
		idx = 0;

		//getting the 2nd num, price
		while (c !='\n')
		{
			c = fgetc(pfr);
			if(c!='\n') fputc(c, pft);
			tmp[idx] = c;
			idx++;
		}
		tmp[idx-1] = '\0';
		num2 = atof(tmp);
		sum = (float)num1 * num2;

		//moving to the end of the temp file, and printing to it
		fseek(pft, 0, SEEK_END);
		fprintf(pft, " %f\n",sum);		

		//checking if we are at the end, if not then it will get the cur one step back, else the while will end
		c = fgetc(pfr);
		if (c!=-1)
			fseek(pfr, -1, SEEK_CUR);

	}

	//moving both to the start
	fseek(pfr,0 , SEEK_SET);
	fseek(pft, 0, SEEK_SET);

	//copying all the content to the original
	c = fgetc(pft);
	while (!feof(pft))
	{
		fputc(c, pfr);
		c = fgetc(pft);
	}
	fclose(pft);
	fclose(pfr);
}
