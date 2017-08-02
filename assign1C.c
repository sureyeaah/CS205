#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// book struct
typedef struct Book {
    int sno, issued;
    char * title, * author;
} Book;

// list to store books
typedef struct list {
    struct list* next;
    Book book;
} list;

// list head
list* head ;

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
// changes issue status of book
void changeBook(int newVal) {
    printf("Enter serial: ");
    int serial = getint();
    list* tmpnod = head;
    while(tmpnod) {
        if(tmpnod->book.sno == serial) {
            if(tmpnod->book.issued == newVal) {
                // already status is same of issue.
                printf("INVALID. Issue status is the same.\n");
            } else {
                // not same. We are good to change.
                tmpnod->book.issued = newVal;
                printf("Issue status changed.\n");
            }
            return;
        }
        tmpnod = tmpnod -> next;
    }
    // not found
    printf("INVALID! no such book\n");
}

// displays book
void display(Book book) {
    printf("Serial number: %d\n", book.sno);
    printf("Author: %s\n", book.author);
    printf("Title: %s\n", book.title);
    printf("---\n");
}

int main() {
    head = NULL;
    while(1) {
        // show options
        printf("\nAvailable options: \n");
        printf("a - Make a new entry of book\n");
        printf("b - View Details of a book\n");
        printf("c - Show list of available books\n");
        printf("d - Issue a book\n");
        printf("e - Return a book\n");
        printf("f - Exit\n");
        char option, tmp; int cnt = 0;
        scanf("%c", &option);
        while(scanf("%c", &tmp) && tmp != '\n') cnt++;
        // check valid input
        if(cnt || option < 'a' || option > 'f') {
            printf("invalid input. Only enter single lowercase character from a-f\n");
            continue;
        }
        if(option == 'a') {
            // add a new book to the top of the linked list
            list* newNode = (list*) malloc(sizeof(list));
            newNode->next = head;
            head = newNode;
            printf("Enter serial no.: ");
            char tmp; int cnt = 0;
            scanf("%d", &(head->book.sno));
            while (scanf("%c", &tmp) && tmp != '\n') {
                cnt++;
            }
            // invalid input
            if(cnt) {
                printf("Invalid input. Enter integer followed by Enter key.\n");
                continue;
            }
            head->book.issued = 0;
            printf("Enter author: ");
            head->book.author = getString();
            printf("Enter title: ");
            head->book.title = getString();
        } else if (option == 'b') {
            // show options
            printf("1 - By serial No.\n");
            printf("2 - By Title\n");
            printf("3 - By Author\n");
            printf("Enter one integer from 1-3:");
            int type = getint();
            if(type < 1 || type > 3) {
                printf("Invalid.\n");
                continue;
            }
            // check which option was selected
            list* tmpnod = head;
            if(type == 1) {
                int serial = getint();
                while(tmpnod) {
                    if(tmpnod->book.sno == serial) {
                        display(tmpnod->book);
                        break;
                    }
                    tmpnod = tmpnod -> next;
                }
                if(!tmpnod) printf("Not found.\n");
            } else if(type == 2) {
                // by title
                printf("Enter title: ");
                char* tmp = getString();
                while(tmpnod) {
                    if(0 == strcmp(tmp, tmpnod->book.title)) {
                        display(tmpnod->book);
                        break;
                    }
                    tmpnod = tmpnod -> next;
                }
                if(!tmpnod) printf("Not found.\n");
            } else {
                // by author
                printf("Enter author: ");
                char* tmp = getString();
                int found = 0;
                while(tmpnod) {
                    if(0 == strcmp(tmp, tmpnod->book.author)) {
                        display(tmpnod->book);
                        found++;
                    }
                    tmpnod = tmpnod -> next;
                }
                if(!found) printf("Not found.\n");
            }
        } else if(option == 'c') {
            // display all book
            list* tmpnod = head;
            while(tmpnod) {
                if(!tmpnod->book.issued) {
                    display(tmpnod->book);
                }
                tmpnod = tmpnod -> next;
            }
        } else if(option == 'd') {
            changeBook(1);
        } else if (option == 'e') {
            changeBook(0);
        } else {
            printf("Exiting\n");
            break;
        }
    }
    return 0;
}