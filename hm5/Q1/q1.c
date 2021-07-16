#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct of the tree
typedef struct Node {
	int data;
	struct Node* left;
	struct Node* right;
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
int nValueBst(BST* bst, int n);
Node* nValue(Node* node, int* n);

void main()
{
	BST bst = { NULL };
	insertBST(&bst, 5); //is root
	insertBST(&bst, 2);//left for 5
	insertBST(&bst, 8);//right for 5
	insertBST(&bst, 1);//left for 2
	insertBST(&bst, 4);//right for 2;
	insertBST(&bst, 9);//right for 8;
	insertBST(&bst, 10);
	insertBST(&bst, 11);
	printBst(&bst);
	int n = 3;
	printf("\nThe value after %d elements is %d",n, nValueBst(&bst, n));
	n = 6;
	printf("\nThe value after %d elements is %d", n, nValueBst(&bst, n));


}


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
}

//In case of failed memory allocation, the user will get an output and the program will exit
void allocationFail(Node* node)
{
	if (node == NULL)
	{
		printf("Out of memory! Exiting the program!\n");
		exit(1);
	}
}

////assist function for print manager
void printInOrder(Node* node)
{
	if (node == NULL)
		return;
	printInOrder(node->left);
	printf(" %d", node->data);
	printInOrder(node->right);
}


//print manager 
void printBst(BST* bst)
{
	if (bst == NULL)
	{
		printf("There is nothing to print");
		return;
	}
	printInOrder(bst->root);
}


//in order, left son father then right son
//int nValue(Node* node, int n)
//{
//	//static int count = 1;
//	int num = 0;
//	int count = 1;
//	if (!node)
//		return num;
//	 num=nValue(node->right, n);
//	 num = nValue(node->left, n);
//	if (count == n)
//	{
//		num = node->data;
//		//printf("\n%d", node->data);
//		count++;
//		return num;
//	}
//	count++;
// }



/*
// Function to find k'th largest element in BST
// Here count denotes the number of nodes processed so far
Node* nValue(Node* node, int* n)
{
    // base case
    if (node == NULL)
        return NULL;
 
    // search in RIGHT subtree
    Node* right = nValue(node->right, n);
 
    // if k'th smallest is found in left subtree, return it
    if (right != NULL)
        return right;
 
    // if current element is k'th smallest, return it
    n--;
    if (n == 0)
        return node;
 
    // else search in right subtree
    return nValue(node->left, n);
}
*/ 


//try fand failed
int nValue(Node* node,int n,int count)
{
	//check for end
	if (node==NULL || count==n)
		return 0;
	int res;
	//checking if there is a bigger number
	res=nValue(node->right,n,count);
	count++;
	if (n==count)
	{	
		res=node->data;
		return res;
	}
	else return count;
}




int nValueBst(BST* bst, int n)
{
	int count=1;
	if (bst == NULL)
	{
		printf("The tree is empty");
		return 0;
	}
	Node* node=nValue(bst->root, n,count);
	return node->data;
}



int levelSearchBst(BST* bst)
{
	int rec=0,count=0;
	if (bst==NULL)
	{
		printf("The tree is empty");
		return 0;
	}

	}
}

int levelSearch(Node* node, int rec,int count)
{
	if (node==NULL)
	return 1;
	if (count<=rec)
	{
	int left=levelSearch(node->left,rec+1,count+1);
	}
	


}

int heightRec(Node* node)
{
    if (!node)
        return 0;
    if (!node->left&&!node->right->right)
        return 0;
    int left=heightRec(node->left);
    int right=heightrec(node->right);

    if (left<right)
        return right+1;
    else return left+1;
}