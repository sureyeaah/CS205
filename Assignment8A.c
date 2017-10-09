#include "stdio.h"
#include "stdlib.h"
// linked list
typedef struct List {
	struct List* nxt;
	int v;
} List;
// adjancey list and color array for bipartite
List **adjList;
int* color;
// add edge from u to v
void addEdge(int u, int v) {
	List* newNode = (List*)malloc(sizeof(List));
	newNode->v = v;
	newNode->nxt = adjList[u];
	adjList[u] = newNode;
}
// assume bipartite
int bipartite = 1;
void dfs(int u) {
	List* cur = adjList[u];
	while(cur) {
		if(color[cur->v]) {
			// if neighbour has same color, not bipartite
			if(color[u] == color[cur->v]) bipartite = 0;
		}
		else {
			// dfs on unvisited vertex
			// set opposite color
			color[cur->v] = color[u] == 1 ? 2 : 1;
			dfs(cur -> v);
		}
		cur = cur -> nxt;
	}
}
int main() {
	// get input
	int n, u, v, r, i;
	printf("Enter the number of players n: ");
	scanf("%d", &n);
	printf("Enter the number of rivalries r: ");
	scanf("%d", &r);
	// allocate memory for adjlist and color array.
	// color array works as visited array
	adjList = (List**) calloc(sizeof(List*), 1+n);
	color = (int*) calloc(sizeof(int), 1 + n);
	// get edges
	for(i = 0; i < r; i++) {
		printf("Enter pair of players that are rivals (Players are numbered from 1-n): ");
		scanf("%d %d", &u, &v);
		// self loops not allowed
		if(u == v) {
			printf("Invalid. You can't be your own rival.");
			return 0;
		}
		// if wrong label
		if(u < 1 || u > n || v < 1 || v > n) {
			printf("Invalid vertex label. Exiting.\n");		
		}
		addEdge(u, v);
		addEdge(v, u);
	}
	// dfs on unvisited nodes
	for(i = 1; i <= n; i++) {
		if(!color[i]) {
			// arbitrary color depending on whether i is even or odd
			color[i] = 1 + (i % 2);
			dfs(i);
		}
	}
	// if bipartite possible, print teams
	if(bipartite) {
		int j;
		for(j = 1; j <= 2; j++) {
			printf("Team %d: ", j);
			for(i = 1; i <= n; i++) {
				if(color[i] == j)
					printf("%d ", i);
			}
			printf("\n");
		}
	} else printf("Cannot make teams.\n");
}
