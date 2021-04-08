#include <stdio.h>
#include <string.h>

int numOfShows(char* arr[], int size, char tav) {
	int count = 0;
	if (size == 0) return 0;
	char* i = *(arr + (size - 1));
	do {
		i = strchr(i + count, tav);
		if (i) count++;
	} while (i != NULL);
	count += numOfShows(arr, size - 1, tav);
	return count;
}

void main() {
	char* arr[] = { "maayan","snir","noa" };
	int totalshow, arrsize = 3;
	char tav = 'n';
	totalshow = numOfShows(arr, arrsize, tav);
	printf("the letter %c appears %d times in the array\n", tav, totalshow);
}