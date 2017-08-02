#include <stdio.h>
#include <stdlib.h>
// function to compute max of 2 integers
int max(int a, int b) {
    return a > b ? a : b;
}
// recursively return largest digit
int LargeDigit(int num) {
    return num ? max(LargeDigit(num/10), num%10): 0;
}
int main() {
    int n;
    printf("Enter n: ");
    scanf("%d%*c", &n);
    // array to store boxes
    int * a = (int*) malloc(sizeof(int)*( n + 1));
    // dp array to store our states
    int * dp = (int*) calloc(sizeof(int)*( n + 1), 0);
    int i = 0;
    // get each box
    for(; i < n; i++) {
        scanf("%d%*c", a + i);
    }
    // filling the dp table
    for(i = 0; i < n; i++) {
        dp[i+1] = max(dp[i], (i-1 >= 0 ? dp[i-1]: 0) + a[i]);
    }
    // output
    printf("Required sum: %d\n", dp[n]);
    printf("Largest Digit: %d\n", LargeDigit(dp[n]));
    return 0;
}