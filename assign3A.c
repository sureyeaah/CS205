#include "stdio.h"
#include "stdlib.h"
// index is the index where to look, n is number of elements, a is the array to search
int find_median(int index, int n, int a[]) {
	// base case
	if(n == 1) return a[0];
	// random pivot
	int pivot = (rand() % n), i = 0;
	// left and right of pivots and their array sizes.
	int left[n], right[n], lcount = 0, rcount = 0;
	// separate array
	for(i = 0; i < n; i++) {
		if(i == pivot) continue;
		if(a[i] <= a[pivot])
			left[lcount++] = a[i];
		else right[rcount++] = a[i];
	}
	// if pivot has exactly index to left, it's the answer
	if(lcount == index)
		return a[pivot];
	// if index is not in left, search right
	if(lcount < index)
		return find_median(index - lcount - 1, rcount, right);
	else
		return find_median(index, lcount, left);
			
}

int main() {
	int n;
	// get n 
	printf("Enter n: ");
	scanf("%d%*c", &n);
	// array
	int a[n+1], i = 0;
	// get array
	printf("Enter array elements space separated: ");
	for(; i < n; i++)
		scanf("%d%*c", a + i);
	// output
	int x = find_median((n-1)/2, n, a);
	printf("The median element is %d\n", x);
}