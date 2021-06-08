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

void main(int argc, char *argv[])
{
	////debug: displays all the arguments
	//printf("argc=%d\n", argc);
	//for (int i = 0; i < argc; i++)
	//	printf("argv[%d]= %s\n", i, argv[i]);
	////system("pause");

	//argv[1]- operation (a/p) ,argv[2]- inventory file name, argv[3]- product name, argv[4]-quantity, argv[5]-price

	//Checking arguments
	if (argv[1][0] == 'a' || argv[1][0] == 'p')
	{
		switch (argv[1][0])
		{
		//print the stock file
		case 'p':

			//if the number of arguments is inaccurate, the program will exit
			if (argc != 3)
			{
				printf("ERROR! invalid number of elements entered!\nExiting program...");
				exit(1);
			}
			//function call to print the stock
			printStock(argv[2]);
			break;

		//add grocery
		case 'a':

			//if the number of arguments is inaccurate, the program will exit
			if (argc != 6)
			{
				printf("ERROR! invalid number of elements entered!\nExiting program...");
				exit(1);
			}

			//function call to add grocery
			addGroceryItem(argv[2], argv[3], atoi(argv[4]), atof(argv[5]));
			break;
		}
	}

	//if the value is invalid, an output will be displayed and it will exit the program
	else
	{
		printf("ERROR! invalid elements entered!\nExiting program...");
		exit(1);
	}
	system("pause");
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


//Q2 b: adds an item to the stock file, if already exits then it will be updated
void addGroceryItem(char* StorageFile, char* productName, int quantity, float price)
{
	//Init, opening the file, if fails will output error
	FILE *pf = fopen(StorageFile, "rb+");
	if (!pf)
		openFileFailed();

	groceryItem stk,tmp1,tmp2;
	int numOfByte, count = 0, sum;

	//getting the size of the file
	fseek(pf, 0, SEEK_END);
	sum = ftell(pf) / sizeof(groceryItem);

	//moving back to the start
	fseek(pf, 0, SEEK_SET);


	//getting the data and the location for the incoming product
	while (fread(&stk, sizeof(groceryItem), 1, pf) == 1)
	{
		//count bigger by one
		count++;

		//if the product is already in stock
		if (!strcmp(stk.itemsName, productName)) {
			
			//getting the number of bytes for each step, and moving one step backwards from the current position
			numOfByte = sizeof(groceryItem);
			fseek(pf, -numOfByte, SEEK_CUR);

			//quantity increase by the incoming count, and rewriting the value. Then return to main
			stk.quantity += quantity;
			fwrite(&stk, sizeof(groceryItem), 1, pf);
			fclose(pf);
			return;
		}

		//if the product name needs to be sorted in the exsiting stock
		if (strcmp(stk.itemsName, productName) > 0)
		{
			//getting the size for each step, and getting the incoming data to tmp1
			numOfByte = sizeof(groceryItem);
			fseek(pf, (-1)*numOfByte, SEEK_CUR);
			strcpy(tmp1.itemsName, productName);
			tmp1.quantity = quantity;
			tmp1.price = price;
			
			//if the item is in the middle
			if (count > 1 && count < sum)
			{
				//endless loop untill return or break
				while (1)
				{
					if (count > sum) //exit condition
					{
						fwrite(&tmp1, sizeof(groceryItem), 1, pf);
						break;
					}
					//sorting the data alphabeticly
					fread(&tmp2, sizeof(groceryItem), 1, pf);
					fseek(pf, -numOfByte, SEEK_CUR);
					fwrite(&tmp1, sizeof(groceryItem), 1, pf);
					count++;
					if (count > sum) //exit condioton
					{
						fwrite(&tmp2, sizeof(groceryItem), 1, pf);
						break;
					}
					//sorting once again
					fread(&tmp1, sizeof(groceryItem), 1, pf);
					fseek(pf, -numOfByte, SEEK_CUR);
					fwrite(&tmp2, sizeof(groceryItem), 1, pf);
					count++;
				}
				//closing the file and returning
				fclose(pf);
				return;
			}
			//if the item is the first item
			if (count == 1) 
			{
				//moving to the start, opening a temporary file for help
				fseek(pf, 0, SEEK_SET);
				FILE *tmpfirst = fopen("tmpfirst.dat", "wb+");
				
				//if opening fails
				if (!tmpfirst)
					openFileFailed();
				
				//copying the data to the tmp file
				fwrite(&tmp1, sizeof(groceryItem), 1, tmpfirst);
				while (fread(&tmp1, sizeof(groceryItem), 1, pf) == 1)
				{
					fwrite(&tmp1, sizeof(groceryItem), 1, tmpfirst);
				}

				//moving back to the start
				fseek(pf, 0, SEEK_SET);
				fseek(tmpfirst, 0, SEEK_SET);

				//copying to the original file
				while (fread(&tmp1, sizeof(groceryItem), 1, tmpfirst) == 1)
				{
					fwrite(&tmp1, sizeof(groceryItem), 1, pf);
				}
				
				//closing the files
				fclose(pf);
				fclose(tmpfirst);
				//removing the tmp file, if fails it will reopen and reset it
				if (remove("tempfirst.dat") != 0)
				{
					//reseting the file
					tmpfirst = fopen("tmpfirst.dat", "wb+");
					fclose(tmpfirst);
				}
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