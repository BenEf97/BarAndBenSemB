#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>






void printBits(int num)
{
    //if the number is 0 it will return
    if (!num)
        return;
    
    //moving it right by 1, also convert a signed to unsigned
    printBits((unsigned)num>>1);
    //look just on LST, and do AND with 1
    printf("%d",num&1);
}

void rightRotate(int n,int d)
{
    //trivial way:
    return(n<<sizeof(int)*8-d)|n>>d;
}

 void main()
 {
 int num = 5;
 printf("\nBinary representation of %4d - ", num);
 printbit(num);
 num = -5;
 printf("\nBinary representation of %4d - ", num);
 printbit(num);
 getch();
 }



int solve(int A, int B)
{
	int count = 0;

	// since, the numbers are less than 2^31
	// run the loop from '0' to '31' only
	for (int i = 0; i < 32; i++) {

		// right shift both the numbers by 'i' and
		// check if the bit at the 0th position is different
		if (((A >> i) & 1) != ((B >> i) & 1)) {
			count++;
		}
	}

	return count; 
}
/*
bool isPowerOfTwo(int n)
{
	if (n == 0)
		return false;

	return (ceil(log2(n)) == floor(log2(n)));
}*/

