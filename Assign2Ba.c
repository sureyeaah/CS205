#include "stdio.h"

// binary search
int search(int a[], int l, int r, int val) {
    if(l > r) return -1;
    if(r - l < 2) return a[l] == val ? l : a[r] == val ? r : -1;
    int mid2 = (l + 2*r)/3, mid1 = (2*l + r)/3;
    if(a[mid1] >= val) return search(a, l, mid1, val);
    if(a[mid2] <= val) return search(a, mid2, r, val);
    return search(a, mid1, mid2, val);
}

int main(void) {
    int n, val;
    printf("Enter n: ");
    scanf("%d%*c", &n);
    int a[n + 1], i;
    // get input
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
