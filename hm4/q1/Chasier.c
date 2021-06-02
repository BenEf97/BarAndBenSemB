#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 80

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

void main()
{
	//debug
	groceryList pList;
	pList.listItems = (groceryItem**)calloc(1, sizeof(groceryItem));
	pList.size = 0;
	addGroceryItem(&pList);
	printf("%s, %d\n", pList.listItems[0]->itemsName,pList.listItems[0]->quantity);
	addGroceryItem(&pList);
	printf("%s, %d\n", pList.listItems[1]->itemsName, pList.listItems[1]->quantity);
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

/*Q1 c: this function gets a list and creates a recipet file for the specific list.*/
void CreateInvoice(groceryList * pList){
	}void CalcInvoiceRowSummary(){
}