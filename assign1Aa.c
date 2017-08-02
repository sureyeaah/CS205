#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// linked list
typedef struct list {
    char* name;
    struct list* next;
} list;
list* head;
// array to store names.
char* name[1000];
// number of students.
int n;
// gets a single integer. Must be followed by newline.
int getint() {
    int ret;
    scanf("%d", &ret);
    if(getchar()!='\n') {
        printf("Invalid input. Enter integer followed by newline. Terminating.\n");
        exit(0);
    }
    return ret;
}
// gets a string
char* getString() {
    int tmp = 0, cursz = 100;
    char* ret = (char*) malloc(sizeof(char)*100);
    int i = 0;
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
    return ret;
}
// gets a sub string
char* getSubString(char * s, int len) {
    char* ret = (char*) malloc(sizeof(char)*(len + 2));
    int i = 0;
    for(; i <= len; i++) {
        ret[i] = s[i];
    }
    ret[i] = '\0';
    return ret;
}

// function that checks whether first lenp characters of p are a prefix of s.
int isPrefix(char * s, char * p, int lenp) {
    int lens = strlen(s);
    if(lenp <= lens) {
        int i = 0;
        for(; i <= lenp; i++) {
            if(s[i] != p[i]) return 0;
        }
        return 1;
    }
    return 0;
}
// prints linked list
void print(list* node) {
    printf("\n---SORTED---\n");
    while(node) {
        int i;
        for(i = 0; i < n; i++) {
            if(isPrefix(name[i], node->name, strlen(node->name)-1)) {
                printf("%s\n", name[i]);
                break;
            }
        }
        node = node -> next;
    }
    printf("---\n\n");
}
// sorts a linked list by pointer manipulation O(n^2)
void sort(list* node) {
    int changed = 1;
    while(changed) {
        changed = 0;
        list* l = node, *prev = NULL;
        while(l->next) {
            list* r = l->next;
            if(strcmp(l->name, r->name) > 0) {
                changed = 1;
                l -> next = r-> next;
                r-> next = l;
                if(prev) prev->next = r;
                else node = r;
                prev = r;
            } else {
                prev = l;
                l = r;
            }
        }
    }
    head = node;
}
int main() {
    head = NULL;
    int i;
    printf("Enter n: ");
    n = getint();
    // get names
    for(i = 0; i < n; i++) {
        printf("Enter name(case sensitive): ");
        name[i] = getString();
    }
    // get unique prefix for each name O(n^3)
    for(i = 0; i < n; i++) {
        int len = strlen(name[i]);
        int j = 0;
        for(; j < len; j++) {
            int k = 0;
            for(; k < n; k++) {
                if(k != i && isPrefix(name[k], name[i], j)) {
                    break;
                }
            }
            if(k == n) break;
        }
        list* newNode = (list*) malloc(sizeof(list));
        newNode->next = head;
        newNode->name = getSubString(name[i], j);
        head = newNode;
    }
    // sort and print linked list
    sort(head);
    print(head);
    return 0;
}