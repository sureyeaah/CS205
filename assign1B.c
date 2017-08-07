#include <stdio.h>
#include <stdlib.h>
// gets a single integer. Must be followed by newline.
int getint() {
    int ret; char x;
    scanf("%d", &ret);
    if(ret < 0 || (scanf("%c", &x) && x !='\n')) {
        printf("Invalid input. Enter non negative integer followed by newline. Terminating.\n");
        exit(0);
    }
    return ret;
}
// function to compute max of 2 integers
int max(int a, int b) {
    return a > b ? a : b;
}
// recursively return largest digit
int LargeDigit(int num) {
    return num ? max(LargeDigit(num/10), num%10): 0;
}
int main() {
    printf("Enter n: ");
    int n = getint();
    // dp array to store our states
    int * dp = (int*) calloc(sizeof(int)*( n + 1), 0);
    int i = 0;
    // get value of each box and fill dp table
    for(i = 0; i < n; i++) {
        printf("Enter chocolates in box %d: ", i + 1);
        int x = getint();
        dp[i+1] = max(dp[i], (i-1 >= 0 ? dp[i-1]: 0) + x);
    }
    // output
    printf("Required sum: %d\n", dp[n]);
    printf("Largest Digit: %d\n", LargeDigit(dp[n]));
    return 0;
}