#include <stdio.h>
#define TRUE 1
#define FALSE 0

int straightFlush(int arr[], int size, int num) {
	if (size == 0 && num <= 0)return TRUE;
	if (size == 0 && num > 0) return FALSE;
	if (arr[size - 1] == num) {
		return straightFlush(arr, size - 1, num - 1);
	}
	else return straightFlush(arr, size - 1, num);
}

void main() {
	int arr[] = { 7,1,1,2,3,5,1 };
	int size = 7, num = 3;
	if (straightFlush(arr, size, num)) printf("there is a straight flush in the array\n");
	else printf("there isn't a straight flush in the array\n");
}