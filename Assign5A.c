#include "stdio.h"
#include "stdlib.h"
#include "time.h"

// returns pivot depending on the type
int getPivot(int type, int n, int a[]) {
    if(type == 0)
        return 0;
    else if(type == 1)
        return rand() % n;
    else {
        // median
        int r, s, t;
        if (type == 2) {
            r = 0; s = n/2; t = n-1;
        } else {
            r = n/4; s = n/2; t = 3*n/4;
        }
        if(a[r] > a[s]){
            return (a[s] > a[t])? s : (a[r] > a[t]) ? t : r;
        } else {
            return (a[r] > a[t]) ? r : (a[s] > a[t]) ? t : s;
        }
    } 
}

// swap two integers.
void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// quicksort
void quicksort(int a[], int n, int pivotType) {
    // for the case of non-positive n as well a small speedup for single element array
    if(n <= 1)
        return;
    
    // move the pivot to 0th index
    swap(a, a + getPivot(pivotType, n, a));

    int l = 0, r = n - 1;
    while(1) {
        while(a[l] <= a[0] && l < r)
            l++;
        while(a[r] > a[0] && l < r)
            r--;
        if(l < r)
            swap(a + l, a + r);
        else break;
    }
    
    // find position of pivot and place it
    if(a[l] > a[0]) l--;
    swap(a, a + l);
    
    //recursion
    quicksort(a, l, pivotType);
    quicksort(a+l+1, n-l-1, pivotType);
}

// checks whether quicksort is correct
void check(int a[], int n) {
    int i = 0;
    for(; i < n-1; i++)
        if(a[i] > a[i+1]) {
            printf("Quicksort not working properly.");
        }
}

// calls quicksort and returns time taken
void benchmark(int n, int arr[], int pivot, int sorted) {
    // if large array, O(n^2) and already sorted
    if(n >= (int)1e6 && sorted && pivot == 0) {
        printf("  Very slow. ");
        return;
    }
    // benchmark
    clock_t t1, t2;
    t1 = clock();
    quicksort(arr, n, pivot);
    t2 = clock();
    check(arr, n);
    double runtime = (double)(t2 - t1) / (double)CLOCKS_PER_SEC;
    printf("  %6f   ", runtime);
}

// range of elements from [0, MAXA)
const int MAXA = 1e9;
const int MAXN = 1e7;

int main(void) {

    // names for pivots
    char* pivotName[4] = {"FIRST            ", "RANDOM           ",
    "MEDIAN OF THREE 1", "MEDIAN OF THREE 2"};
    
    printf("   n     |     Pivot        |    Random   |    Sorted    |    Almost Sorted    \n");
    
    // seed random with time
    srand((unsigned int)time(NULL));
    
    int n, i, *arr = (int*) malloc(sizeof(int)*(MAXN + 1));
    
    for(n = (int)10000; n <= MAXN; n *= 10) {
        int pivot;
        for(pivot = 0; pivot <= 3; pivot++) {
            
            // generate array
            for(i = 0; i < n; i++) {
                arr[i] = rand() % MAXA;
            }
            
            // call quicksort and print results
            printf("%8d   %s   ", n, pivotName[pivot]);
            benchmark(n, arr, pivot, 0); // unsorted
            benchmark(n, arr, pivot, 1); // sorted
            
            int k = n/100;
            while(k--) {
                int x1 = rand() % n;
                int x2 = rand() % n;
                swap(arr + x1, arr + x2);
            }
            benchmark(n, arr, pivot, 0); // Almost sorted
            
            printf("\n");
        }
        printf("\n");
    }
}