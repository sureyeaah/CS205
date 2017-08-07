#include "stdio.h"

int max(int a, int b) {
 return a > b ? a : b;
}
// recursively finds maximum and minimum digit
void recurse(long long int n, int* largest, int *smallest) {
	if(!n) {
	    // handling the case where n is initially 0
		if(*largest < 0) {
			*largest = *smallest = 0;
		}
		return;
	}
	*largest = max(*largest, n%10);
	*smallest = -max(-*smallest, -(n%10));
	recurse(n/10, largest, smallest);
}
// calls the recursive function
void minMaxDigit(long long int x) {
	int largest = -1, smallest = 10;
	recurse(x, &largest, &smallest);
	printf("Largest: %d\n", largest);
	printf("Smallest: %d\n", smallest);
}

int main(void) {
	long long int n;
	scanf("%lld", &n);
	minMaxDigit(n);
}
