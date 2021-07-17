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
//int nValueBst(BST* bst, int n);
//int nValue(Node* node, int n);
int levelSearch(Node* node);
int levelSearchBst(BST* bst);
int treeCompBst(BST* bst1, BST* bst2);
int treeComp(Node* node1, Node* node2);
int getLevelBst(BST* bst1, BST* bst2, int data);
int getLevel(Node *node, int data);
int getLevelUtil(Node *node, int data, int level);

void main()
{
	BST bst1 = { NULL };
	BST bst2 = { NULL };
	insertBST(&bst1, 5); //is root
	insertBST(&bst1, 2);//left for 5
	insertBST(&bst1, 8);//right for 5
	insertBST(&bst1, 1);//left for 2
	insertBST(&bst1, 4);//right for 2;
	insertBST(&bst1, 11);//right for 8;


	insertBST(&bst2, 5); //is root
	insertBST(&bst2, 2);//left for 5
	insertBST(&bst2, 8);//right for 5
	insertBST(&bst2, 1);//left for 2
	insertBST(&bst2, 4);//right for 2;
	insertBST(&bst2, 9);//right for 8;
	printBst(&bst1);
	int n = 3;
	//printf("\nThe value after %d elements is %d",n, nValueBst(&bst, n));
	printf("\n%d", levelSearchBst(&bst1));
	if (treeCompBst(&bst1,&bst2)) printf("\nare the same");
	else printf("\nnot the same\n");
	if (getLevelBst(&bst1, &bst2, 4))
	printf("True\n");
	else printf("False\n");
	if (getLevelBst(&bst1,&bst2,9))
	printf("True\n");
	else printf("False\n");

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

/*
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
}*/



/*
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
*/


int levelSearchBst(BST* bst)
{
	int rec=0,count=0;
	if (bst==NULL)
	{
		printf("The tree is empty");
		return 0;
	}

	int right = levelSearch(bst->root->right);
	int left = levelSearch(bst->root->left);
	if(left==right) 
	return 1;
	else return 0;
}


int levelSearch(Node* node)
{
    if (!node)
        return 0;
    if (!node->left&&!node->right)
        return 0;
    int left=levelSearch(node->left);
    int right=levelSearch(node->right);

    if (left<right)
        return right+1;
    else return left+1;
}

int treeCompBst(BST* bst1,BST* bst2)
{
	if (!bst1 || !bst2)
	{
		printf("One of the trees is invalid!\n");
		return 0;
	}
	return treeComp(bst1->root, bst2->root);
}

int treeComp(Node* node1, Node* node2)
{
	// Check if both the trees are empty
	if (node1 == NULL && node2 == NULL)
		return 1;
	// If any one of the tree is non-empty
	// and other is empty, return false
	else if (node1 != NULL && node2 == NULL)
		return 0;
	else if (node1 == NULL && node2 != NULL)
		return 0;
	else
	{
		// compare current data and the next data
		if (node1->data == node2->data && treeComp(node1->left, node2->left) && treeComp(node1->right, node2->right))
			return 1;
		else
			return 0;
	}
}
/* Helper function for getLevel().
	It returns level of the data if data is
   present in tree, otherwise returns 0.*/
int getLevelUtil(Node *node, int data, int level)
{
	if (node == NULL)
		return 0;

	if (node->data == data)
		return level;

	int downlevel = getLevelUtil(node->left,data, level + 1);
	if (downlevel != 0)
		return downlevel;

	downlevel = getLevelUtil(node->right, data, level + 1);
	return downlevel;
}

/* Returns level of given data value */
int getLevel(Node *node, int data)
{
	return getLevelUtil(node, data, 1);
}

int getLevelBst(BST* bst1, BST* bst2, int data)
{
	if (bst1 == NULL || bst2 == NULL)
	{
		printf("trees are empty");
		return 0;
	}
	if(getLevel(bst1->root,data)==getLevel(bst2->root, data))
	return 1;
	else return 0;
}