#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// Graph
int n;
typedef struct edge {
    int u, v, inMst;
    double weight;
} edge;
edge edges[1000];
// Comparator function for sorting edges
int compare(const void* a, const void* b) {
    return (*(edge*)a).weight - (*(edge*)b).weight < 0 ? -1: 1;
}
// checks whether neighbours or not
int isNeighbour(int a[26], int b[26]) {
    int i, more = 0, less = 0;
    for(i = 0; i < 26; i++) {
        if(a[i] > b[i]) more += a[i] - b[i];
        else if (a[i] < b[i]) less += b[i] - a[i];
    }
    if(more == 1 && less == 0) return 1;
    if(less == 1 && more == 0) return 1;
    return (!more && !less);
}
// DSU
int par[1000], rank[1000];
void build() {
    int i = 0;
    for(i = 0; i < 2*n; i++) {
        par[i] = i;
        rank[i] = 0;
    }
}
// find set of i
int findSet(int i) {
    return par[i] == i ? i: (par[i] = findSet(par[i]));
}
// unite two sets
// return 1 if can unite, 0 if same set
int unite(int i, int j) {
    int x = findSet(i), y = findSet(j);
    if(x != y) {
        if(rank[x] < rank[y]) {
            par[x] = y;
        } else {
            par[y] = x;
            rank[y] += rank[y] == rank[x];
        }
        return 1;
    }
    return 0;
}
// add edge
void addEdge(int u, int v, double weight, int ind) {
    edges[ind].u = u;
    edges[ind].v = v;
    edges[ind].weight = weight;
    edges[ind].inMst = 0;
}
int main() {
    // get input
    printf("Enter the number of houses: ");
    scanf("%d%*c", &n);
    int i, j, len, w[1000] = {}, cnt[1000][26] = {}, edgeCount = 0;
    char* name[n];
    for(i = 0; i < n; i++) {
        name[i] = (char*) malloc(100*sizeof(char));
        printf("Enter a name lower case: ");
        scanf("%s", name[i]);
        // find character count
        for(j = 0, len = strlen(name[i]); j < len; j++) {
            int x = name[i][j] >= 'a' ? name[i][j] - 'a': name[i][j] - 'A';
            cnt[i][x]++;
            w[i] += (int)name[i][j];
        }
        // add edge from i to dummy node i + n.
        addEdge(i, n + i, w[i]/(1.0 * strlen(name[i])), edgeCount++);
    }
    // add edges between neighbours
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(i < j && isNeighbour(cnt[i], cnt[j]))
                addEdge(i, j, abs(w[i] - w[j]), edgeCount++);
        }
    }
    // sort edges
    qsort(edges, edgeCount, sizeof(edge), compare);
    // build and unite all dummy nodes
    build();
    for(i = 0; i < n; i++)
        unite(n, i + n);
    double cost = 0;
    // kruskal
    for(i = 0; i < edgeCount; i++) {
        if(unite(edges[i].u, edges[i].v)) {
            cost += edges[i].weight;
            edges[i].inMst = 1;
        }
    }
    // print drilling and pipeline site with costs.
    printf("Minimum Cost is - %lf.\n", cost);
    for(i = 0; i < edgeCount; i++) {
        if(edges[i].inMst && edges[i].u + n == edges[i].v)
            printf("Drill bore at %s %lf\n", name[edges[i].u], edges[i].weight);
    }
    for(i = 0; i < edgeCount; i++) {
        if(edges[i].inMst && edges[i].u + n != edges[i].v)
            printf("Pipeline: %s %s %lf\n", name[edges[i].u], name[edges[i].v], edges[i].weight);
    }
}