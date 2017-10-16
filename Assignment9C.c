#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int dp[100][100];
// return min of two numbers
int min(int a, int b) {
	return a < b ? a : b;
}
// finds edit distance between two strings.
int editDistance(char a[100], char b[100]) {
	int n = strlen(a), m = strlen(b), i, j;
	// base
	dp[0][0] = 0;
	for(i = 1; i <= n; i++) {
		dp[i][0] = i;
	}
	for(j = 1; j <= m; j++) {
		dp[0][j] = j;
	}
	// recurrence
	for(i = 1; i <= n; i++) {
		for(j = 1; j <= m; j++) {
			if(a[i-1] == b[j-1])
				dp[i][j] = dp[i-1][j-1];
			else dp[i][j] = 1 + min(dp[i-1][j-1], min(dp[i][j-1], dp[i-1][j]));
		}
	}
	return dp[n][m];
}
// dist stores edit distance
int n, i, j, k, dist[100][100];
// shortest is length of shortes path, nxt is used to reconstruct shortest path
double traffic[100][100], shortest[100][100], nxt[100][100];
char name[100][100];
// prints shortest path from u to v
void printPath(int u, int v) {
	printf("Path from %s to %s with time %lf: %s ", name[u], name[v], shortest[u][v], name[u]);
	while(u != v)  {
		u = nxt[u][v];
		printf("%s ", name[u]);
	}
	printf("\n");
}

int main() {
	// get input
	printf("Enter number of localities: ");
	scanf("%d", &n);
	for(i = 0 ; i < n; i ++) {
		printf("Enter name of locality #%d: ", i);
		scanf("%s", name[i]);
	}
	// reset
	memset(nxt, -1, sizeof nxt);
	memset(shortest, 63, sizeof shortest);
	// get traffic matrix 
	for(i = 0 ; i < n; i++) {
		printf("Enter values of traffic for #%d: ", i);
		shortest[i][i] = 0;
		for(j = 0; j < n; j++) {
			scanf("%lf", traffic[i] + j);
			dist[i][j] = editDistance(name[i], name[j]);
			shortest[i][j] = dist[i][j] * traffic[i][j];
			nxt[i][j] = j;
		}
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
	int done[100] = {}; // stores if we have already a dominos for this location.
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
		printf("\nSetup a dominos at %s\n", name[curBest]);
		for(j = 0; j < n; j++) {
			if(!done[j] && shortest[curBest][j] <= 30) {
				printPath(curBest, j);
				done[j] = 1;
			}
		}
	}			
}
