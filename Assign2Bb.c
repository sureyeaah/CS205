#include "stdio.h"

// binary search
int search(int a[], int l, int r, int val) {
    if(l > r) return -1;
    if(r - l < 2) return a[l] == val ? l : a[r] == val ? r : -1;
    int mid = (3*l + 2*r)/5;
    if(a[mid] >= val) return search(a, l, mid, val);
    return search(a, mid + 1, r, val);
}

int main(void) {
    int n, val;
    printf("Enter n: ");
    scanf("%d%*c", &n);
    int a[n + 1], i;
    for(i = 0; i < n; i++) {
        printf("Enter single array element in increasing order: ");
        scanf("%d%*c", a + i);
    }
    printf("Enter element to search: ");
    scanf("%d", &val);
    // call search
    int x = search(a, 0, n-1, val);
    if(x == -1) printf("Not found.\n");
    else printf("Found at index %d\n", x);
}
