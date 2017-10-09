#include "stdio.h"
#include "stdlib.h"

int max(int a, int b) {
	return a > b ? a : b;	
}
// LInked list
typedef struct List {
	struct List* nxt;
	int v;
} List;
// adjaceny list and visited array
List **adjList;
int* visited;
// add edge from u to v
void addEdge(int u, int v) {
	List* newNode = (List*)malloc(sizeof(List));
	newNode->v = v;
	newNode->nxt = adjList[u];
	adjList[u] = newNode;
}
// returns edge count found so far. (Since undirected, each edge is counted twice)
int dfs(int u) {
	// mark as visited
	visited[u] = 1;
	List* cur = adjList[u];
	// total edges found in dfs tree
	int edges = 0;
	while(cur) {
		edges++;
		// if not yet visited, dfs on it
		if(!visited[cur->v]) {
			edges += dfs(cur -> v);
		}
		cur = cur -> nxt;
	}
	// return number of edges found
	return edges;
}
int main() {
	// get input
	int n, u, v, m, i;
	printf("Enter the number of players n: ");
	scanf("%d", &n);
	printf("Enter the number of edges m: ");
	scanf("%d", &m);
	// reset
	adjList = (List**) calloc(sizeof(List*), 1+n);
	visited = (int*) calloc(sizeof(int), 1 + n);
	// get edges
	for(i = 0; i < m; i++) {
		printf("Enter undirected edge u v (vertices labelled from 1 to n): ");
		scanf("%d %d", &u, &v);
		if(u < 1 || u > n || v < 1 || v > n) {
			printf("Invalid vertex label. Exiting.\n");		
		}
		addEdge(u, v);
		addEdge(v, u);
	}
	// get max edge count by dfs
	int maxEdgeCount = 0;
	for(i = 1; i <= n; i++) {
		if(!visited[i]) {
			int edgeCount = dfs(i)/2; // divide by 2 because undirected
			maxEdgeCount = max(edgeCount, maxEdgeCount);
		}
	}
	// print answer
	printf("The maximum edge count in a connected component is %d\n", maxEdgeCount);
}
