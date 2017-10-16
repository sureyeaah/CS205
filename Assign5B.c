/*
    assign5B
    COUNT SORT
    Shaurya Gupta
    1601CS43
*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// max runs used for COUNT SORT
#define MAX_RUNS 30000

// gets arbitrary length string from user 
char* getString() {
    int tmp = 0, cursz = 100;
    char* ret = (char*) malloc(sizeof(char)*100);
    int i = 0;
    for(; i < cursz; i++) {
        scanf("%c", ret + i);
        if(ret[i] == '\n') {
            ret[i] = '\0';
            break;
        } else if(!isalpha(ret[i])) {
            i--;
            continue;
        }
        else if(i == cursz-1) {
            cursz += 100;
            ret = (char*)realloc(ret, cursz);
        }
    }
    return ret;
}
// information about player
typedef struct player {
    char* name;
    int runs, nameLen;
} player;


// sort strings from Least Significant to Most significant
// radix sort
void radixSort(player arr[], int n, int len) {
    if(!len)
        return;
    int i, ind[27] = {};
    player tmp[n];
    for(i = 0; i < n; i++) {
        if(arr[i].nameLen < len)
            ind[0]++;
        else ind[tolower(arr[i].name[len-1]) - 'a' + 1]++;
    }
    for(i = 0; i < 26; i++)
        ind[i + 1] += ind[i];
    for(i = n-1; i >= 0; i--) {
        if(arr[i].nameLen < len)
            tmp[--ind[0]] = arr[i];
        else tmp[--ind[tolower(arr[i].name[len-1]) - 'a' + 1]] = arr[i];
    }
    memcpy(arr, tmp, sizeof(player) * n);
    radixSort(arr, n, len - 1);
}

// count sort on runs
void countSort(player arr[], int m) {
    int cnt[MAX_RUNS + 1] = {}, i = 0;
    player tmp[m];
    for (; i < m; i++)
        cnt[arr[i].runs]++;
    for (i = MAX_RUNS-1; i >= 0; i--)
        cnt[i] += cnt[i+1];
    for (i = m-1; i >= 0; i--)
        tmp[--cnt[arr[i].runs]] = arr[i];
    memcpy(arr, tmp, sizeof(player) * m);
}

int main(void) {
    int m, i, j, maxLen = 0;
    // array for each run
    printf("Enter number of players: ");
    scanf("%d%*c", &m);
    player arr[m + 1];
    // get information about each player
    for(i = 0; i < m; i ++) {
        printf("Enter name and press ENTER: ");
        arr[i].name = getString();
        arr[i].nameLen = strlen(arr[i].name);
        if(maxLen < arr[i].nameLen)
            maxLen = arr[i].nameLen;
        printf("Enter number of runs: ");
        scanf("%d%*c", &(arr[i].runs));
        // negative run
        if(arr[i].runs < 0) {
            printf("runs should be non negative. exiting.");
            return 0;
        } else if (arr[i].runs > MAX_RUNS) {
            // too many runs
            printf("Too many runs. Not even sachin has those many.\n");
            return 0;
        }
    }
    radixSort(arr, m, maxLen);
    countSort(arr, m);
    // output
    printf ("Sorted:\n");
    for (i = 0; i < m; i++)
        printf("%d. %d - %s\n", i + 1, arr[i].runs, arr[i].name);
    return 0;
}