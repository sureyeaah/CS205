#include "stdio.h"
// linear dp solution

int min(int a, int b) {
	return a < b ? a : b; 
}

int main(void) {
	int n;
	printf("Enter n: ");
	scanf("%d", &n);
	// for n < 1, we can't take it to 1
	if(n < 1) {
		printf("Enter n > 1\n");
		return 0;
	}
	// dp array
	int dp[n+1];
	// base case
	dp[1] = 0;
	int i = 2;
	for(; i <= n; i++) {
		// pair with n-1
		dp[i] = dp[i-1] + 1;
		// now try to divide if 7,5,3,2 divides it.
		if(i % 7 == 0)
			dp[i] = min(dp[i], dp[i/7] + 1);
		if(i % 5 == 0)
		dp[i] = min(dp[i], dp[i/5] + 1);
		if(i % 3 == 0)
			dp[i] = min(dp[i], dp[i/3] + 1);
		if(i % 2 == 0)
			dp[i] = min(dp[i], dp[i/2] + 1);
	}
	printf("Minimum number of steps to reduce %d to 1 is %d\n", n, dp[n]);
}
