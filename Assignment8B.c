#include "stdio.h"
#include "stdlib.h"
#include "string.h"
int adjMat[100][100];
int visited[100];

const int GRAY = 2;
const int BLACK = 1;
// checks whether we can change string a to b.
int canTransform(char a[6], char b[6]) {
	int cnt[26] = {}, i;
	// get which characters are unequal in count
	for(i = 0; i < 5; i++) {
		cnt[a[i] - 'a']++;
		cnt[b[i] - 'a']--;
	}
	int excess = 0, deficit = 0, firstInExcess = 0;
	for(i = 0; i < 26; i++) {
		if(cnt[i] > 0)  {
			excess += cnt[i];
			if(i == a[0] - 'a')
				firstInExcess = 1;
		} else if(cnt[i] < 0)
			deficit++;
	}
	// if count of all characters is same
	if(excess == 0 && deficit == 0)
		return 1;
	// if only the count of first character is in excess by 1
	if(excess == 1 && firstInExcess)
		return 1;
	// cannot transform
	return 0;
}

int n, cycle = 0; // number of vertices, initially assume no cycle
// Performs dfs
// used for both cycle checking as well checking which vertices are reachable
void dfs(int u) {
	int i;
	// set current vertex as discovered(gray)
	visited[u] = GRAY;
	for(i = 0; i < n; i++) {
		// if edge present
		if(adjMat[u][i]) {
			if(visited[i] == GRAY)
				cycle = 1;
			else if(!visited[i])
				dfs(i);
		}
	}
	// set current vertex as explored(black)
	visited[u] = BLACK;
}
int main() {
	int i, j;
	// Get Input
	printf("Enter the number of strings: ");
	scanf("%d%*c", &n);
	char words[n][6];
	for(i = 0; i < n; i++) {
		scanf("%s", words[i]);
	}
	// Reset visited array and adjMat
	memset(visited, 0, sizeof(int)*100);
	memset(adjMat, 0, sizeof(int)*10000);
	// Generate Matrix
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			if(i != j && canTransform(words[i], words[j]))
				adjMat[i][j] = 1;
		}
	}
	// Perform dfs to get cycles
	for(i = 0; i < n; i++) {
		if(!visited[i]) {
			dfs(i);
		}
	}
	// print whether cyclic
	if(cycle)
		printf("GRAPH IS CYCLIC\n");
	else printf("GRAPH IS ACYCLIC\n");
	// Print matrix header
	printf("# | ");
	for(i = 0; i < n; i++)
		printf("%d ", i);
	printf("\n");
	// generate and print the matrix
	for(i = 0; i < n; i++) {
		// reset visited array and perform dfs
		memset(visited, 0, sizeof(int)*100);
		dfs(i);
		// print visited status
		printf("%d | ", i);
		for(j = 0; j < n; j++)
			printf("%d ", visited[j]);
		printf("\n");
	}
}
