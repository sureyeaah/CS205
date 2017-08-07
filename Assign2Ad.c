#include "stdio.h"

int max(int arr[], int a, int b) {
    return arr[a] > arr[b] ? a : b;
}
int min(int arr[], int a, int b) {
    return arr[a] < arr[b] ? a : b;
}

// finds index of max and min in array a from l to r
void maxMin(int a[], int l, int r, int* _max, int* _min) {
    if(l > r) return;
    *_max = max(a, *_max, l);
    *_min = min(a, *_min, r);
    maxMin(a, l + 1, r, _max, _min);
}
// swaps two numbers
void swap(int* a, int * b) {
    int tmp = *b;
    *b = *a;
    *a = tmp;
}
// sort function
void sort(int a[], int l, int r) {
    if(l >= r) return; // done
    int max = l, min = l;
    maxMin(a, l, r, &max, &min); // find max min index
    swap(a + l, a + min); // swap l and min
    if(max == l) max = min;
    swap(a + r, a + max);
    sort(a, l + 1, r - 1);
}

int main(void) {
    int n;
    printf("Enter n: ");
    scanf("%d%*c", &n);
    int a[n + 1], i = 0;
    printf("Enter integers: ");
    for(; i < n; i++) scanf("%d%*c", a + i);
    sort(a, 0, n-1);
    printf("sorted: ");
    for(i = 0; i < n; i++) printf("%d ", a[i]); 
    printf("\n");
}
