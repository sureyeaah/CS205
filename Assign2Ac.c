#include "stdio.h"
// print binary form. started denotes whether we have printed something yet or not.
void binary(int n, int started) {
    if(n) binary(n >> 1, 1);
    if(n || !started) printf("%d", n&1);
    if(!started) printf("\n");
}

int main(void) {
   int a;
   scanf("%d", &a);
   binary(a, 0);
}
