#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
// return min of two numbers
int min(int a, int b) {
	return a < b ? a : b;
}

int n, i, m, j, k;
// shortest is length of shortes path, nxt is used to reconstruct shortest path
double x[100], y[100], shortest[100][100], nxt[100][100];
// prints shortest path from u to v
void printPath(int u, int v) {
	printf("Path from %d to %d with time %lf: %d ", 1 + u, 1 + v, shortest[u][v], 1 + u);
	while(u != v)  {
		u = nxt[u][v];
		printf("%d ", 1 + u);
	}
	printf("\n");
}

int main() {
	// get input
	printf("Enter number of localities: ");
	scanf("%d", &n);
	// reset
	memset(nxt, -1, sizeof nxt);
	for(i = 0 ; i < n; i++) {
		for(j = 0; j < n; j++) {
			shortest[i][j] = 1e9;
		}
	}
	for(i = 0 ; i < n; i ++) {
		shortest[i][i] = 0;
		printf("Enter coordinates of locality #%d: ", i + 1);
		scanf("%lf %lf", x + i, y + i);
	}
	// get edges 
	printf("Enter number of edges: ");
	scanf("%d", &m); 
	while(m--) {
		printf("Enter directed edge from i to j with traffic t -- i j t (1-indexed): ");
		int i, j; double traffic;
		scanf("%d %d %lf", &i, &j, &traffic);
		i--; j--;
		shortest[i][j] = pow(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2), 0.5) * traffic;
		nxt[i][j] = j;
	}
	// floyd warshall
	for(k = 0; k < n; k++) {
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++) {
				if(shortest[i][j] > shortest[i][k] + shortest[k][j]) {
					nxt[i][j] = nxt[i][k];
					shortest[i][j] = shortest[i][k] + shortest[k][j];
				}
			}
		}
	}
	// greedy strategy
	int done[100] = {}; // stores if we have already a dominos that can reach this location.
	while(1) {
		int curBest = -1, bestVal = 0;
		for(i = 0; i < n; i++) {
			int curCnt = 0;
			for(j = 0; j < n; j++) {
				if(!done[j] && shortest[i][j] <= 30) {
					curCnt++;
				}
			}
			// if current location can reach most places.
			if(curCnt > bestVal) {
				bestVal = curCnt;
				curBest = i;
			}
		}
		// if we can build a new dominos
		if(curBest == -1)
			break;
		printf("\nSetup a dominos at %d\n", curBest + 1);
		for(j = 0; j < n; j++) {
			if(!done[j] && shortest[curBest][j] <= 30) {
				printPath(curBest, j);
				done[j] = 1;
			}
		}
	}			
}
