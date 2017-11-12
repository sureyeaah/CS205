#include "stdio.h"
#include "string.h"
int min(int a, int b) {
	return a < b ? a : b;
}
#define S 5000
int n, s, t, f[S][S], path[S], c[S][S], vis[S];
int dfs(int u, int ind) {	
	path[ind] = u;
	vis[u] = 1;
	if(u == t) return ind + 1;
	int i;
	for(i = s; i <= t; i++) {
		if(c[u][i] - f[u][i] > 0 && !vis[i]) {
			int ret = dfs(i, ind + 1);
			if(ret) return ret;
		}
	}
	return 0;
}
int flow() {
	int i;
	while(1) {
		memset(vis, 0, sizeof(int) * S);
		int pathLen = dfs(s, 0);
		if(pathLen) {
			int minEdge = 2e9;
			for(i = 0; i < pathLen - 1; i++) {
				minEdge = min(minEdge, c[path[i]][path[i+1]] - f[path[i]][path[i+1]]);
			}
			for(i = 0; i < pathLen - 1; i++) {
				f[path[i]][path[i+1]] += minEdge;
				f[path[i+1]][path[i]] -= minEdge;				
			}
		} else break;
	}
	int ans = 0;
	for(i = 0; i <= t; i++) ans += f[s][i];
	return ans;
}
int main() {
	int i, j;
	printf("Enter the number of vertices n: ");
	scanf("%d", &n);
	s = 0, t = n + 1;
	for(i = 0; i <= n + 1; i++) {
		for(i = 0; i <= n + 1; i++) {
			c[i][j] = f[i][j] = 0;
		}
	}
	for(i = 1; i <= n; i++) {
		for(j = 1; j <= n; j++) {
			if(i != j && j - i > 0 && j-i <= 3) c[i][j] = i + j;
		}
	}
	for(i = 1; i <= n/4; i++)
		c[s][i] = i;
	for(i = (3*n - 1) / 4 + 1; i <= n; i++)
		c[i][t] = i;
		
	printf("The maximum flow is %d\n", flow());
}
