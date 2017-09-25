#include "stdio.h"
#include "stdlib.h"

// O(n log(n)) dp solution

int max(int a, int b) {
	return a > b ? a : b; 
}
// compare function to sort in increasing order
int compare (const void * a, const void * b) {
	return (*(int*) a - *(int*)b);
}

int main(void) {
	int n, m;
	printf("Enter n: ");
	scanf("%d", &n);
	printf("Enter m: ");
	scanf("%d", &m);
	// paired stores whether ith element has been paired with a smaller element or not.
	int dp[n+1], paired[n+1], arr[n], i;
	for(i = 0; i < n; i++) {
		printf("Enter an array element: ");
		scanf("%d%*c", arr + i);
	}
	// sort array in increasing order
	qsort(arr, n, sizeof(int), compare);
	// base case
	dp[0] = dp[1] = 0;
	// can't pair smallest element with a smaller element
	paired[1] = 0;
	// now pair ith element with i -1 th element or don't pair it.
	for(i = 1; i < n; i++) {
		// case when not paired.
		dp[i+1] = dp[i];
		paired[i+1] = 0;
		// if it can be paired, pair it.
		if(arr[i] - arr[i-1] <= m && dp[i+1] < dp[i-1] + arr[i] + arr[i-1]) {
			dp[i+1] = dp[i-1] + arr[i] + arr[i-1];
			paired[i+1] = 1;
		}
	}
	printf("Maximum sum is %d\n", dp[n]);
	printf("Pairs are:\n");
	i = n - 1;
	int pairsExist = 0;
	while(i >= 0) {
		if(paired[i+1]) {
			pairsExist = 1;
			printf("(%d, %d)\n", arr[i], arr[i-1]);
			i -= 2;
		} else i--;
	}
	if(!pairsExist)
		printf("No pairs formed.\n");
	return 0;
}
