#include "stdio.h"

int n, m, i, j, u[1000], v[1000], par[1000], st, nd;
double dist[1000], r[1000];
// relax edge
void relax(int u, int v, double r) {
    if(dist[u]*r > dist[v]) {
        dist[v] = dist[u]*r;
        par[v] = u;
    }
}
// print recursively the shortest path from st to u
void printPath(int u) {
    if(u != st)
        printPath(par[u]);
    printf("%d", u);
    if(u != nd)
        printf(" --> ");
    else printf("\n");
}
int main() {
    // input
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter the number of edges: ");
    scanf("%d", &m);
    for(i = 0; i < m; i++) {
        printf("Enter edge u v r, u and v are 1-index and r is reliability: ");
        scanf("%d %d %lf", u+i, v+i, r+i);
    }

    printf("Enter two vertices between which you need the reliable path: ");
    scanf("%d %d", &st, &nd);
    // reset
    for(i = 1; i <= n; i++) {
        dist[i] = -1.0;
    }
    // source at 0
    dist[st] = 1.0;
    // bellman ford
    for(i = 0; i < n-1; i++) {
        for(j = 0; j < m; j++) {
            relax(u[j], v[j], r[j]);
        }
    }
    // print path
    printPath(nd);
    printf("The probability of not failing on path is %lf.\n", dist[nd]);
}