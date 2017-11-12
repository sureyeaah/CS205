#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define inf ((int)1e9)
int par[6000], u[100000], v[100000], r[100000], st, nd, dist[6000];
char loc[6000][20];
void relax(int u, int v, int r) {
    if(dist[u] + r < dist[v]) {
        dist[v] = dist[u] + r;
        par[v] = u;
    }
}
void printPath(int u) {
    if(u != st)
        printPath(par[u]);
    printf("%s", loc[u]);
    if(u != nd)
        printf(" --> ");
    else printf("\n");
}

int isRelated(char x[20], char y[20]) {
	int a = strlen(x), b = strlen(y), i, slope = b - a, cnt[26][2] = {}, val;
	for(i = 0; i < a; i ++) {
		val = x[i] < 'a' ? x[i] - 'A': x[i] - 'a';
		cnt[val][0]++;
	}
	for(i = 0; i < b; i ++) {
		val = y[i] < 'a' ? y[i] - 'A': y[i] - 'a';
		cnt[val][1]++;
	}
	int common = 0;
	for(i = 0; i < 26; i++) {
		common += min(cnt[i][0], cnt[i][1]);
	}
//	if(!slope) return 1;
	if(slope > 0 && abs(slope) <= 2 && common >= abs(slope)) return 1;
	return 0;
}

int getDistance(char x[20], char y[20]) {
	int dist = 0, a = strlen(x), b = strlen(y), i;
	for(i = 0; i < a || i < b; i ++) {
		dist +=abs((i < a ? (int)x[i]: 0) - (i < b ? (int)y[i]: 0));
	}
	return dist;
}
int main() {
	srand(time(NULL));
	int n, i, j, m = 0;
	printf("Enter the number of localities: ");
	scanf("%d%*c", &n);
	for(i = 0; i < n; i++) {
		printf("Enter the locality name: ");
		scanf("%s", loc[i]);
		dist[i] = inf;
	}
	st = rand() % n;
	nd = rand() % n;
	dist[st] = 0;
	// generate edges
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j ++) {
			if(j == i || isRelated(loc[i], loc[j]) <= 0) continue;
			int d = getDistance(loc[i], loc[j]);
			u[m] = i; v[m] = j; r[m] = d;
			m++;
		}
	}
	// bellman ford
	for(i = 0; i < n-1; i++) {
		for(j = 0; j < m; j++) {
			relax(u[j], v[j], r[j]);
		}
	}
	if(dist[nd] < inf) {
		printPath(nd);
		printf("Shortest distance from %s to %s is %d.\n", loc[st], loc[nd], dist[nd]);
	} else printf("Shortest path from %s to %s doesn't exist.\n", loc[st], loc[nd]);
}
