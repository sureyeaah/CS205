#include "stdio.h"
// returns digit sum recursively
int digitSum(int n) {
    return n ? digitSum(n/10) + n%10: 0;
}
// required recursive function
void recursiveSum(int n) {
    printf("%d", n);
    if(n/10 != 0) {
        printf(" -> ");
        recursiveSum(digitSum(n));
    }
    else
        printf("\n");
}
int main(void) {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    recursiveSum(n);
}
