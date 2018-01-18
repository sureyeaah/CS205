// maximum bipartite matching
#include "stdio.h"
#include "string.h"

int graph[500][500] = {}, vis[500], match[500], n, m;

int min(int a,int b) {
	return a < b ? a : b;	
}
// bipartite matching
int bpm(int u) {
	int v;
	for(v = 0; v < n; v++) {
		if(graph[u][v] && !vis[v]) {
			vis[v] = 1;
			if(match[v] == -1 || bpm(v)) {
				match[v] = u;
				return 1;
			}
		}
	}
	return 0;
}
// finds if company and candidate have an edge.
int connected(char x[50], char y[50]) {
	int common = 0, cnt[26][2] = {};
	int i, len;
	for(i = 0, len = strlen(x); i < len; i++)
		if(isalpha(x[i])) cnt[x[i] < 'a' ? x[i] - 'A': x[i] - 'a'][0]++;
	for(i = 0, len = strlen(y); i < len; i++)
		if(isalpha(y[i])) cnt[y[i] < 'a' ? y[i] - 'A': y[i] - 'a'][1]++;
	for(i = 0; i < 26; i++)
		common += min(cnt[i][0], cnt[i][1]);
	return (common >= 2);
}
int main() {
	int i;
	// input
	printf("Enter the number of companies: ");
	scanf("%d%*c", &n);
	char companies[n][50];
	for(i = 0; i < n; i++)
		scanf("%[^\n]%*c", companies[i]);
	printf("Enter the number of candidates: ");
	scanf("%d%*c", &m);
	char names[m][50];
	for(i = 0; i < m; i++)
		scanf("%[^\n]%*c", names[i]);
	// graph generation
	for(i = 0; i < n; i++) {
		int j;
		for(j = 0; j < m; j++) {
			graph[i][j] = (connected(companies[i], names[j]));
		}
	}
	// initialize matching
	memset(match, -1, sizeof(int) * m);
	int count = 0;
	// run bipartite matching
	for(i = 0; i < n; i++) {
		memset(vis, 0, sizeof(int) * m);
		count += bpm(i);
	}
	// output
	printf("Maximum placement is %d.\n", count);
	for(i = 0; i < m; i++) {
		if(match[i] != -1)
			printf("%s is placed at %s.\n", names[i], companies[match[i]]);
		else printf("%s is unplaced.\n", names[i]);
	}
}
