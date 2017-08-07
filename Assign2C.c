#include "stdio.h"

// simple recursive function
void recurse(int n, int steps) {
    
    if(!steps) {
        printf("Initial value is %d\n", n);
    }
    if(n == 1) {
        printf("Final value %d, number of steps %d\n", n, steps);
        return;
    }
    printf("Next value is %d\n", n);
    recurse(((n&1) ? 3*n + 1: n >> 1), steps + 1);
}

int main(void) {
	int n;
	printf("Enter n: ");
	scanf("%d", &n);
	if(n < 1) {
		printf("Error.\n");
		return 0;
	}
	recurse(n, 0);
}	
