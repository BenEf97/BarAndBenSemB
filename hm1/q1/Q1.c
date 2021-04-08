#include <stdio.h>
#define TRUE 1
#define FALSE 0


int switchNum(int num) {
	if (num / 10 == 0) return TRUE;
	if ((num % 2 == 0 && ((num / 10) % 2) - 1 == 0) || ((num % 2) - 1 == 0 && ((num / 10) % 2) == 0))
		return switchNum(num / 10);
	else return FALSE;
}

void main() {
	int num = 163789;
	int chk = switchNum(num);
	if (chk) printf("The number is a 'switcher'\n");
	else printf("The number is not a 'switcher'\n");
}
