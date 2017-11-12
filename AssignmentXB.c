#include "stdio.h"
#include "string.h"
#define S 8
int min(int a, int b) {
  return a < b ? a : b;
}
int dist[S][S] = {}, dp[1 << S][S], par[1 << S][S];
char* names[S] = {"Chennai", "Kolkata", "Indore", "Bengaluru", "Nagpur", "Ranchi", "Guwahati", "Hyderabad"};
// fill distances and round off
void distances() {
  dist[0][1] = 1366;
	dist[0][2] = 1172;
	dist[0][3] = 284;
	dist[0][4] = 1137;
	dist[0][5] = 1270;
	dist[0][6] = 1885;
	dist[0][7] = 520;
	dist[1][2] = 1286;
	dist[1][3] = 1560;
	dist[1][4] = 971;
	dist[1][5] = 325;
	dist[1][6] = 528;
	dist[1][7] = 1180;
	dist[2][3] = 1100;
	dist[2][4] = 383;
	dist[2][5] = 973;
	dist[2][6] = 1649;
  dist[2][7] = 653;
	dist[3][4] = 925;
	dist[3][5] = 1415;
	dist[3][6] = 2075;
  dist[3][7] = 499;
	dist[4][5] = 682; 
	dist[4][6] = 1392;
  dist[4][7] = 423;
	dist[5][6] = 713; 
  dist[5][7] = 973;
  dist[6][7] = 1671;
  int i, j;
  for(i = 0; i < S; i++) {
    for(j = 0; j < i; j ++) {
      dist[i][j] = dist[j][i];
    }
  }
  for(i = 0; i < S; i ++) {
    for(j = 0; j < S; j ++) {
      dist[i][j] = 100*(int)(dist[i][j]/100.0 + 0.5);
    }
  }
}
int main() {
  distances();
  // reset to infinity
  memset(dp, 63, sizeof(int)*S*(1 << S));
  int i, j, k;
  // base case
  for(i = 0; i < S; i++) {
    dp[1 << i][i] = 0;
  }
  // tsp
  for(i = 1; i < (1 << S); i++) {
    for(j = 0; j < S; j++) {
      if(i & (1 << j)) {
        for(k = 0; k < S; k++) {
          if(k != j && (i & (1 << k))) {
            if(dp[i][j] > dp[i ^ (1 << j)][k] + dist[j][k]) {
              dp[i][j] = dp[i ^ (1 << j)][k] + dist[j][k];
              par[i][j] = k;
            }
          }
        }
      }
    }
  }
  // final answer
  int st = 0, ans = 2e9;
  for(i = 0; i < S; i++) {
    if(ans > dp[(1 << S) - 1][i]) {
      ans = dp[(1 << S) - 1][i];
      st = i;
    }
  }
  int cur = (1 << S) - 1;
  printf("Order is: ");
  while(cur) {
    printf("%s ", names[st]);
    int nxt = par[cur][st];
    cur ^= (1 << st);
    st = nxt;
  }
  printf("\nShortest distance is %d km.\n", ans);
}
