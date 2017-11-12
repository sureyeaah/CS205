#include "stdio.h"
#define inf ((int)1e9)
int min(int a, int b) {
  return a < b ? a : b;
}
int abs(int a) {
  return a < 0 ? -a : a;
}
int main() {
  int n, i, j, d;
  printf("Enter the number of words: ");
  scanf("%d%*c", &n);
  char words[n][6];
  for(i = 0; i < n; i++) {
    printf("Enter word: ");
    scanf("%s", words[i]);
  }
  printf("Enter value of threshold d: ");
  scanf("%d%*c", &d);
  // get edge weights
  int dist[n][n], access[n][n];
  for(i = 0; i < n; i++) {
    for(j = 0; j < n; j++) {
      dist[i][j] = access[i][j] = 0;
      if(i == j) continue;
      int k, same = 0, diff = 0, weight = 0;
      for(k = 0; k < 5; k++) {
        if(words[i][k] == words[j][k]) same++;
        diff += (int)(words[i][k]) - (int)(words[j][k]);
        weight += abs((int)(words[i][k]) - (int)(words[j][k]));
      }
      dist[i][j] = (same == 4 && diff > 0) ? weight: inf;
    }
  }
  printf("Graph matrix:\n");
  for(i = 0; i < n; i++) {
    for(j = 0; j < n;j ++) {
      if(dist[i][j] < inf) printf("%3d ", dist[i][j]);
      else printf("--- ");
    }
    printf("\n");
  }
  // floyd warshall
  int k;
  for(k = 0; k < n; k ++) {
    for(i = 0; i < n; i++) {
      for(j = 0; j < n;j ++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        if(dist[i][j] < d) access[i][j] = 1;
      }
    }
  }
  for(k = 0; k < n; k ++) {
    for(i = 0; i < n; i++) {
      for(j = 0; j < n;j ++) {
        access[i][j] |= (access[i][k] & access[k][j]);
      }
    }
  }
  printf("Cost matrix:\n");
  for(i = 0; i < n; i++) {
    for(j = 0; j < n;j ++) {
      if(dist[i][j] < inf) printf("%3d ", dist[i][j]);
      else printf("inf ");
    }
    printf("\n");
  }
  // check who can access whom.
  for(i = 0; i < n; i++) {
    printf("%s can access ", words[i]);
    for(j = 0; j < n; j++) {
      if(access[i][j]) {
        printf("%s,", words[j]);
      }
    }
    printf("\n");
  }
}
