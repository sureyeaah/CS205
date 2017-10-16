#include "stdio.h"
#include "string.h"
void binary(long long a, int arr[]);
void multiply(int a[], int b[], int n, int result[]);
void add(int a[], int b[], int sum[], int n);
void subt(int a[], int b[], int n, int dif[]);
int main(void) {
    long long a, b;
    printf("Enter first number: ");
    scanf("%lld", &a);
    printf("Enter second number: ");
    scanf("%lld", &b);
    int num1[64], num2[64], ans[128];
    binary(a, num1);
    binary(b, num2);
    multiply(num1,num2,64,ans);
//    subt(num1,num2,64,ans);
    int i = 0;
    for(;i < 64; i++)
        printf("%d", ans[i]);
}
// ----- function definitions ---------
void binary(long long a, int arr[]) {
    int i;
    for(i = 0; i < 64; i++) {
        arr[i] = a&1;
        printf("%d", arr[i]);
        a >>= 1;
    }
    printf("\n");
}
void add(int a[], int b[], int sum[], int n) {
    int carry = 0, i = 0;
    for(int i = 0; i < n; i++) {
        sum[i+1] = carry^a[i]^b[i];
        carry = ( (carry + a[i] + b[i]) & 2) >> 1;
    }
    sum[n] = carry;
}

void shift(int a[], int n) {
    int i = 0;
    for(i = 0; i < n; i++)
        a[i] = a[i + n];
    for(; i < n<<1; i++)
        a[i] = 0;
}
void subt(int a[], int b[], int n, int diff[]) {
    int i, draw = 0;
    for(i = 0; i < n; i++) {
        if(a[i] - draw < b[i]) {
            diff[i] = (a[i] + 2) - draw - b[i];
            draw = 1;
        } else {
            diff[i] = a[i] - draw - b[i];
            draw = 0;
        }
    }
}
/* Karatsuba
 * a = 2^ n/2 . a0 + a1
 * b = 2^ n/2 . b0 + b1
 * ab = 2 ^ n a0b0 + a1b1 + 2^(n/2).((a1 + a0).(b1 + b0) - a1b1 - a0b0)
 */
void multiply(int a[], int b[], int n, int result[]) {
    // base case
    if(n == 1) {
        result[1] = a[0] & b[0];
        result[0] = 0;
    }
    // divide and conquer
    int n2 = n - (n >> 1);
    int a0[n2], a1[n2], b0[n2], b1[n2],
            ab00[n2 << 1], ab11[n2 << 1], ab[(n2 + 1) << 1],
            suma[n2+1], sumb[n2+1], sumab[2*(n2+1) + 1];
    memset(a0, 0, n2*sizeof(int));
    memset(a1, 0, n2*sizeof(int));
    memset(b0, 0, n2*sizeof(int));
    memset(a1, 0, n2*sizeof(int));
    memset(ab00, 0, 2*n2*sizeof(int));
    memset(ab11, 0, 2*n2*sizeof(int));
    memset(ab, 0, 2*(1+n2)*sizeof(int));
    memset(sumab, 0, 2*(1+n2)*sizeof(int));
    memset(suma, 0, (1+n2)*sizeof(int));
    memset(sumb, 0, (1+n2)*sizeof(int));

    memcpy(a0 + (n & 1), a + n2, n >> 1);
    memcpy(a1, a, n2);
    memcpy(b0 + (n & 1), b + n2, n >> 1);
    memcpy(b1, b, n2);

    multiply(a0, b0, n2, ab00);

    multiply(a1, b1, n2, ab11);

    add(a1, a0, suma, n2); // store a1 + a0 in suma
    add(b1, b0, sumb, n2); // store b1 + b0 in sumb
    multiply(suma, sumb, ab, n2+1);

    add(ab11, ab00, sumab, n2 + 1);
    subt(ab, sumab, , diff);
}