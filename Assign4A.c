#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"
// Patient information
typedef struct Patient {
    char* name;
    int time, weight;
} Patient;

// Priority queue
typedef struct priority_queue {
    Patient* heap[1001];
    int size;
} priority_queue;
// returns whether given priority queue is empty or not
int isEmpty(const priority_queue *pq);
// add element to a priority queue
void push(priority_queue *pq, const Patient *elem);
// remove the top element
void pop(priority_queue *pq);
// gets string
char* getString();

// gets number of common alphabets between two strings
int commonCount(char* a, char* b);
// sort on basis of time of arrival
int comp(const void* lhs, const void* rhs);
// global data
int n;
char* doctor;
Patient patients[1001];

int main(void) {
    // get input
    printf("Enter number of patients: ");
    scanf("%d%*c", &n);
    int i, j;
    for(i = 0; i < n; i++) {
        printf("Enter name of  patient #%d: ", i + 1);
        patients[i].name = getString();
        printf("Enter time of arrival for patient #%d in hhmm (e.g. 0800): ", i + 1);
        scanf("%d%*c", &patients[i].time);
    }
    printf("Enter doctor name: ");
    doctor = getString();
    // compute similarity
    for(i = 0; i < n; i++) 
        patients[i].weight = commonCount(patients[i].name, doctor);
    // sort patients
    qsort(patients, n, sizeof(Patient), comp);
    for(i = 0, j = 0; i < n && j < 2400; ) {
        if(patients[i].time == j) {

        }
    }
    return 0;
}

// -------- function definitions ----------
char* getString() {
    int tmp = 0, cursz = 100;
    char* ret = (char*) malloc(sizeof(char)*100);
    int i = 0;
    do {
        for(; i < cursz; i++) {
            scanf("%c", ret + i);
            if(ret[i] == '\n') {
                ret[i] = '\0';
                break;
            }
            else if(i == cursz-1) {
                cursz += 100;
                ret = (char*)realloc(ret, cursz);
            }
        }
        if(!i) printf("Try again: ");
    } while(!i);
    return ret;
}

int commonCount(char* a, char* b) {
    int i, len, cnt[26] = {}, common = 0;
    for(i = 0, len = strlen(a); i < len; i++) {
        if(isalpha(a[i])) {
            cnt[tolower(a[i]) - 'a'] = 1;
        }
    }
    for(i = 0, len = strlen(b); i < len; i++) {
        if(isalpha(b[i])) {
            if (cnt[tolower(b[i]) - 'a'] == 1) {
                cnt[tolower(b[i]) - 'a'] = 2;
                common++;
            }
        }
    }
    return common;
}

int comp(const void* lhs, const void* rhs) {
    return ((Patient*)lhs)->time <= ((Patient*)rhs)->time;
}
int isEmpty(const priority_queue *pq) {
    return !(pq->size);
}
void push(priority_queue *pq, const Patient *elem) {
    pq -> size++;

}
void pop(priority_queue *pq) {
    
}