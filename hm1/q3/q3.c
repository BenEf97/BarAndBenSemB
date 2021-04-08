#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define SIZE 20
int sameCharAndIdx(char* str1, char* str2);

void main() {
	//char str1[] = { "aBdRe" };
	//char str2[] = { "ASdRle" };
	char str1[SIZE];
	char str2[SIZE];
	printf("Please enter up to %d letter string: ", SIZE);
	gets(str1);
	printf("Please enter another up to %d letter string: ", SIZE);
	gets(str2);
	printf("Number of same characters in the same place is: %d\n", sameCharAndIdx(&str1, &str2));
}

int sameCharAndIdx(char* str1, char* str2) {
	int counter = 0;
	if (*str1 == '\0' || *str2 == '\0') return 0;
	if (*(str1) == *(str2) || *(str1)+32 == *(str2) || *(str1) == *(str2)+32) {
		counter = sameCharAndIdx(str1 + 1, str2 + 1) + 1;
	}
	else counter = sameCharAndIdx(str1 + 1, str2 + 1);
	return counter;
}
