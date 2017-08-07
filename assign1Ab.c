#include "stdio.h"
#include "stdlib.h"

// returns 1 if x is vowel assuming alphabet
int weight(char x) {
    if (x < 'a') x = x - 'A' + 'a';
    return x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u';
}
// linked list
typedef struct List {
    struct List * next;
    char val;
    int pos;
} List;
// adds node to linked list at top
List* addNode(List* head, char val, int pos) {
    List* newNode = (List*) malloc(sizeof(List));
    newNode->val = val;
    newNode->pos = pos;
    newNode->next = head;
    return newNode;
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
// sort takes a linked List head's address.
void sort(List** head) {
    int changed = 1;
    List* node = *head;
    while(changed) {
        changed = 0;
        List* l = node, *prev = NULL;
        while(l->next) {
            List* r = l->next;
            if(weight(l->val) < weight(r->val) || (weight(l->val) == weight(r->val) && l->pos > r->pos)) {
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
    *head = node;
}

// prints linked List
void print(List* node) {
    while(node) {
        printf("%c%c", node -> val, (node->next ? '>': '\n'));
        node = node -> next;
    }
}

// checks if b list is prefix of a. We know length b is less than equal to a's.
int equal(List* a, List* b) {
    while(a && b) {
        if(a -> val != b -> val) return 0;
        a = a->next; b = b->next;
    }
    return 1;
}
// frees linked list
void eraseList(List* a) {
    List* b;
    while(a) {
        b = a;
        a = a->next;
        free(b);
    }
}
// palindrome printer. O(n^3). Reverse sub linked list and compares them.
int printPalindromes(List* head) {
    int found = 0;
    List* l = head, *r, *iter, *rev = NULL;
    while(r = l->next) {
        eraseList(rev); // erase reverse of sub linked list
        rev = NULL;
        rev = addNode(rev, l->val, l->pos); // add first node
        while(r) {
            rev = addNode(rev, r->val, r->pos); // add further nodes on top to reverse
            if(equal(l, rev)) {
                // found palindrome
                found = 1;
                iter = l;
                printf("Palindrome: ");
                while(1) {
                    printf("%c%c", iter->val, (iter == r ? '\n': '>'));
                    if(iter == r) break;
                    iter = iter->next;
                }
            }
            r = r->next;
        }
        l = l->next;
    }
    return found;
}

int main() {
    List* head[2] = {};
    int n = getint(), i;
    for(i = 0; i < n; i++) {
        printf("Enter name: ");
        char* name = getString();
        head[i>=n/2] = addNode(head[i>=n/2], name[0], i);
        free(name);
    }
    // sort and print
    for(i = 0; i < 2; i++) {
        sort(&head[i]);
        printf("Sorted: ");
        print(head[i]);
    }
    // print palindromes in each and report if none found.
    for(i = 0; i < 2; i++) {
        printf("\nPalindromes in list %d\n", i + 1);
        if(!printPalindromes(head[i]))
            printf("None found.\n");
        printf("\n");
    }
    return 0;
}