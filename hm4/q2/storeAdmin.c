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

void printStock(char* StorageFile);
void addGroceryItem(char* StorageFile, char* productName, int quantity, float price);
void openFileFailed();

void main()
{

	groceryItem debug = { "Avocado",2,5.5 };
	printStock("stock.dat");
	addGroceryItem("stock.dat",&debug.itemsName,debug.quantity,debug.price);
	printf("\n");
	printStock("stock.dat");
 }

//If file opening fails, the user will get output and the program will exit.
void openFileFailed()
{
	printf("The file didn't open!");
	exit(1);
}

//Q2 a: gets a pointer to a binary file, reads it and prints the data
void printStock(char* StorageFile)
{
	//opening binary file for read only
	FILE *pf = fopen(StorageFile, "rb");
	
	//if opening failed it will exit the program
	if (!pf)
		openFileFailed();

	//grocery item stock
	groceryItem stk;

	//read every term, and prints it to the output
	while (fread(&stk, sizeof(groceryItem), 1, pf) == 1)
	{
		printf("Name: %s\tQuantity: %d\tPrice per unit: %f\n", stk.itemsName, stk.quantity, stk.price);
	}

	//checking if the stock is empty
	if (ftell(pf) == 0)
	{
		printf("The stock is empty!\n");
		fclose(pf);
		return;
	}
	//close the file
	fclose(pf);
}

void addGroceryItem(char* StorageFile, char* productName, int quantity, float price)
{
	FILE *pf = fopen(StorageFile, "rb+");
	if (!pf)
		openFileFailed();
	groceryItem stk,tmp1,tmp2,in;
	int numOfByte, count = 0, sum;
	fseek(pf, 0, SEEK_END);
	sum = ftell(pf) / sizeof(groceryItem);
	printf("\ntest***%d***\n", sum);
	fseek(pf, 0, SEEK_SET);


	//checking if the product is already in stock
	while (fread(&stk, sizeof(groceryItem), 1, pf) == 1)
	{
		count++;
		//matching name
		if (!strcmp(stk.itemsName, productName)) {
			numOfByte = sizeof(groceryItem);
			fseek(pf, -numOfByte, SEEK_CUR);
			stk.quantity += quantity;
			fwrite(&stk, sizeof(groceryItem), 1, pf);
			fclose(pf);
			return;
		}

		if (strcmp(stk.itemsName, productName) > 0)
		{
			numOfByte = sizeof(groceryItem);
			fseek(pf, (-1)*numOfByte, SEEK_CUR);
			strcpy(tmp1.itemsName, productName);
			tmp1.quantity = quantity;
			tmp1.price = price;
			
			//if the item is in the middle
			if (count > 1 && count < sum)
			{
				while (1)
				{
					if (count > sum)
					{
						fwrite(&tmp1, sizeof(groceryItem), 1, pf);
						break;
					}
					fread(&tmp2, sizeof(groceryItem), 1, pf);
					fseek(pf, -numOfByte, SEEK_CUR);
					fwrite(&tmp1, sizeof(groceryItem), 1, pf);
					count++;
					if (count > sum)
					{
						fwrite(&tmp2, sizeof(groceryItem), 1, pf);
						break;
					}
					fread(&tmp1, sizeof(groceryItem), 1, pf);
					fseek(pf, -numOfByte, SEEK_CUR);
					fwrite(&tmp2, sizeof(groceryItem), 1, pf);
					count++;
				}
				fclose(pf);
				return;
			}
			//if the item is the first item
			if (count = 1) 
			{
				fseek(pf, 0, SEEK_SET);
				FILE *tmpfirst = fopen("tmpfirst.dat", "ab+");
				fwrite(&tmp1, sizeof(groceryItem), 1, tmpfirst);
				while (fread(&tmp1, sizeof(groceryItem), 1, pf) == 1)
				{
					fwrite(&tmp1, sizeof(groceryItem), 1, tmpfirst);
					count++;
				}
				fseek(pf, 0, SEEK_SET);
				fseek(tmpfirst, 0, SEEK_SET);
				while (fread(&tmp1, sizeof(groceryItem), 1, tmpfirst) == 1)
				{
					fwrite(&tmp1, sizeof(groceryItem), 1, pf);
				}
				
				fclose(pf);
				fclose(tmpfirst);
				return;
			}
			
		}

	}
	//if its the last item
	if (count >= sum)
	{
		strcpy(tmp1.itemsName, productName);
		tmp1.quantity = quantity;
		tmp1.price = price;
		fseek(pf, 0, SEEK_END);
		fwrite(&tmp1, sizeof(groceryItem), 1, pf);
		fclose(pf);
		return;
	}
}