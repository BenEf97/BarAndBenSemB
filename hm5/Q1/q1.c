
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct of the tree
typedef struct node {
	int data;
	struct node* left;
	struct node* right;
} Node;


typedef struct
{
    Node* root;
}BST;

void insertBST(BST* bst, int data);
void insertNode(Node* node, int data);
void printInOrder(Node* node);
Node* createNode(int data);
void printBst(BST* bst);
void allocationFail(Node* node);

void main()
{
	BST bst = { NULL };
	insertBST(&bst, 5); //is root
	insertBST(&bst, 2);//left for 5
	insertBST(&bst, 8);//right for 5
	insertBST(&bst, 1);//left for 2
	insertBST(&bst, 4);//right for 2;
	insertBST(&bst, 9);//right for 8;

	//printBst(&bst);

}


//דגשים: הבן השמאלי תמיד קטן או שווה להורה, הימני תמיד גדול מההורה
//פונקצית המעטפת צריכה לקבל את המבנה המנהל ומשם להשתמש בפונקצתית עזר רקורסיבית
//Create new Node for the tree, gets the data, and left and right nodes
void insertBST(BST* bst, int data)
{
	if (bst->root == NULL)
	{
		bst->root = createNode(data);
		return;
	}
	insertNode(bst->root, data);
}
//assist function to insertBST
void insertNode(Node* node, int data)
{
	if (node->data < data)
	{
		if (node->right == NULL) {
			node->right = createNode(data);
			return;
		}

		insertNode(node->right, data);
	}
	else
	{
		if (node->left == NULL) {
			node->left = createNode(data);
			return;
		}
		insertNode(node->left, data);
	}
}
//allocating address to new node and data input
Node* createNode(int data)
{
	Node* newNode = (Node*)calloc(1, sizeof(Node));
	allocationFail(newNode);
	newNode->data = data;
	return newNode;
}//In case of failed memory allocation, the user will get an output and the program will exit
void allocationFail(Node* node)
{
	if (node == NULL) 
	{
		printf("Out of memory! Exiting the program!\n");
		exit(1);
	}
}
//assist function for print managervoid printInOrder(Node* node) {
	if (node == NULL) return;
	printInOrder(node->left);
	printf(" %d",node->data);
	printInOrder(node->right);
}

////print manager //void printBst(BST* bst)//{//	if (bst == NULL)
//	{
//		printf("There is nothing to print");
//		return;
//	}
//	printInOrder(bst->root);
//}//
