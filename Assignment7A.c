// median of median algorithm for O(n) selection
#include "stdio.h"

// finds median of array with <= 5 elements
int paritition5(int a[], int n);

// swaps two integers
void swap(int *a, int *b);

// finds pivot using median of medians algorithm
int pivot(int arr[], int l, int r);

// partition an array around pivotIndex and returns new found pivotIndex
int partition(int arr[], int l, int r, int pivotInd);

// returns kth largest element in subarray a[l...r]
int kth(int a[], int l, int r, int k);


int main(void) {
	// get input
	int n, i, k;
	printf("Enter n, number of elements: ");
	scanf("%d%*c", &n);
	int arr[n];
	for(i = 0; i < n; i++) {
		printf("Enter array element: ");
		scanf("%d%*c", arr + i);
	}
	printf("Enter k, kth  element that you want to find (1-based): ");
	scanf("%d%*c", &k);
	// k should be valid
	if(k <= 0 || k > n) {
		printf("No such element. Value of k is >= 1 and <= n)");
		return 0;
	}
	// get answer
	int ans = kth(arr, 0, n-1, k-1);
	printf("%dth element in the array is %d.\n", k, arr[ans]);
	return 0;
}


void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


int partition5(int a[], int l, int r) {
	int i, j, tmp[5], n = r - l + 1;
	for(i = l; i <= r; i++)
		tmp[i - l] = a[i];
	// sort five elements
	for(i = 0; i < n; i++) {
		for (j = 1; j < n; j++) {
			if(tmp[j-1] > tmp[j]) {
				swap(tmp + j - 1, tmp + j);
			}
		}
	}
	// return element of median
	for(i = l; i <= r; i++)
		if(tmp[n >> 1] == a[i])
			return i;
}


int kth(int a[], int l, int r, int k) {
	while(l <= r) {
		// base case
		if(l == r)
			return l;
		int pivotInd = pivot(a, l, r);
		pivotInd = partition(a, l, r, pivotInd);
		if(k == pivotInd)
			return k;
		else if(k < pivotInd)
			r = pivotInd - 1;
		else
			l = pivotInd + 1;
	}
}
int pivot(int arr[], int l, int r) {
	int size = r - l + 1;
	// for small array, return median
	if(size <= 5)
		return partition5(arr, l, r);
	int i, medSize = 0;
	for(i = l; i <= r; i +=5) {
		// end of the current 5 element block
		int end = i + 4;
		// if 5 elements not available.
		if(end > r)
			end = r;
		int med = partition5(arr, i, end);
		// move median to beginning n/5 portion of the array
		swap(arr + med, arr + l + (i - l)/5);
		medSize++;
	}
	// find median of medians;
	return kth(arr, l, l + medSize - 1, medSize/2);
}

int partition(int arr[], int l, int r, int pivotInd) {
	int i, x = arr[pivotInd], j = l;
	// move the pivot element to the end of the array
	swap(arr + pivotInd, arr + r);
	// partition the elements.
	for(i = l; i < r; i++) {
		if(arr[i] < x) {
			swap(arr + i, arr + j);
			j++;
		}
	}
	// move the pivot to intended location in the paritioning.
	swap(arr + r, arr + j);
	// return the new index of the pivot element.
	return j;
}
