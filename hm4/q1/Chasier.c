#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 80

//structs
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

//fucntion list
void addGroceryItem(groceryList * pList);
void undo(groceryList * pList);
void CreateInvoice(groceryList * pList);
void CalcInvoiceRowSummary();
void allocationFail();
void openFileFailed();
char menu(groceryList * pList);
void freeList(groceryList * pList);

void main()
{

	//init
	groceryList pList;
	char option;

	//allocation memory, if fails will exit
	pList.listItems = (groceryItem**)calloc(1, sizeof(groceryItem));
	if (pList.listItems == NULL)
		allocationFail();

	pList.size = 0;
	//call for menu
	option = menu(&pList);
	if (!option)
		freeList(&pList);
}


//free the list
void freeList(groceryList * pList)
{
	//the list is already empty
	if (!pList->listItems)
		return;

	//free all the data in the list
	for (int idx = 0; idx < pList->size; idx++)
	{
		free(pList->listItems[idx]);
	}
	free(pList->listItems);
}

//Q1 e: main menu
char menu(groceryList * pList)
{
	//init
	char option='1';

	//prints all the options to the user, while option 1 and 2 will get the functions, 3 will get invoice and end the menu function
	while(1)
	{
		printf("\n\t***Main Menu***\n1. Add Grocery Item\n2. Undo- Remove last item\n3.Finish and get Invoice\n");
		fseek(stdin, 0, SEEK_END);
		scanf("%c", &option);

		switch (option)
		{
		case '1':
			printf("--Add Grocery Item--\n");
			addGroceryItem(pList);
			printf("The item has been added!\n");
			continue;
		case '2':
			printf("--Undo--\n");
			undo(pList);
			continue;
		case '3':
			printf("--Finish and get Invoice--\nThank you! The invoice will be at your program folder...\n");
			CreateInvoice(pList);
			CalcInvoiceRowSummary(pList);
			return NULL;
		default: 
			printf("Invalid Input! Please try again\n");
			continue;
		}
	}
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
	fseek(stdin, 0, SEEK_END);
	scanf("%d", &temp.quantity);

	//Input for price
	printf("Please enter the price of the item: ");
	fseek(stdin, 0, SEEK_END);
	scanf("%f", &temp.price);

	strcpy(pList->listItems[pList->size-1]->itemsName,temp.itemsName);	
	pList->listItems[pList->size - 1]->price = temp.price;
	pList->listItems[pList->size - 1]->quantity = temp.quantity;
}



/*Q1 b: The function gets a pointer to the list, deletes the last item on the list, freeing the memory of the item and reallocates the memory in a smaller size by 1*/
void undo(groceryList * pList)
{
	if (pList->listItems[0] == NULL ||pList->size==0)
	{
		printf("The cart is already empty!\n");
		return;
	}

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
	else
	{
		free(pList->listItems);
		pList->listItems == NULL;
	}

	printf("Undo complete!\n");
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
	if (!pfr)
		openFileFailed();

	FILE *pft = fopen("tmpfile.txt", "w+");
	if (!pft)
		openFileFailed();

	char c = fgetc(pfr), tmp[20];
	int  idx, num1;
	float sum, num2;

	//if the list is empty, will exit
	if (c == -1)
	{
		printf("The cart is empty! There is nothing to print...\n");
		exit(0);
	}
	
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

	//closing the files, and removing the tmpfile
	fclose(pft);
	fclose(pfr);
	//if the remove fails it will reopen and close to reset the file
	if (remove("tmpfile.txt") != 0)
	{
		pft=fopen("tmpfile.txt", "w");
		fclose(pft);
	}

}