#include "stdio.h"

int oddDigitCount(int x) {
    return x ? oddDigitCount(x/10) + (x&1) : 0;
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("%d\n", oddDigitCount(n));
}
