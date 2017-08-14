#include "stdio.h"
// node to store the best overall, best from contiguous left, right and the total sum;
typedef struct node {
	int best;
	int left;
	int right;
	int total;
} node;
// return max of two numbers.
int max(int a, int b) {
	return a > b ? a : b;
}
node maxSubarray(int l, int r, int a[]) {
	node ret; // return node
	if(l == r) {
		// base case of single element
		ret.best = ret.left = ret.right = ret.total = a[l];
	}
	else {
		int mid = (l + r) >> 1;
		// divide in two and solve left and right
		node lnode = maxSubarray(l, mid, a), rnode = maxSubarray(mid + 1, r, a);
		// recursive relations to combine left and right subarrays.
		ret.total= lnode.total + rnode.total;
		ret.left = max(lnode.left, lnode.total + rnode.left);
		ret.right = max(rnode.right, rnode.total + lnode.right);
		ret.best = max(max(lnode.best, rnode.best), max(ret.left, ret.right));
	}
	return ret;
}

int main() {
	int n;
	// input
	printf("Enter n: ");
	scanf("%d%*c", &n);
	int a[n], i;
	printf("Enter array: ");
	for(i = 0; i < n; i++)
		scanf("%d%*c", a + i);
	// output
	node ans = maxSubarray(0, n - 1, a);
	printf("ans: %d\n", ans.best);
}