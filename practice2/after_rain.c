typedef struct _NODE
{
    char color[10];
    struct _NODE *next;
} Node;

int n;
char buf[100];
int num1, num2;
Node *head;

// TEMPLATE CODE STRATS HERE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void insert(Node** head_ptr, char* color, int dest)
{
    Node *cursor, *new;
    int i = 0;

    for (cursor = *head_ptr; i < dest && cursor->next != NULL; i++)
        cursor = cursor->next;

    new = (Node*)malloc(sizeof(Node));
    strncpy(new->color, color, sizeof(new->color));
    new->next = cursor->next;
    cursor->next = new;

    return;
}

void erase1(Node** head_ptr, int dest)
{
    Node *cursor, *prev;
    int i = 0;

    for (cursor = *head_ptr; i < dest && cursor->next != NULL; i++) {
        prev = cursor;
        cursor = cursor->next;
    }

    prev->next = cursor->next;
    free(cursor);

    return;
}

void erase2(Node** head_ptr, char* color)
{
    Node *cursor, *prev;

    for (cursor = *head_ptr; cursor != NULL; ) {
        if (!strcmp(cursor->color, color)) {
            prev->next = cursor->next;
            free(cursor);
        } else {
            prev = cursor;
        }
        cursor = prev->next;
    }

    return;
}

void reverse(Node** head_ptr, int dest1, int dest2)
{
    Node *prev, *cursor, *next, *reverse_prev, *reverse_tail;
    int i = 0;

    for (cursor = *head_ptr; i < dest1 && cursor->next != NULL; i++) {
        prev = cursor;
        cursor = cursor->next;
    }

    reverse_prev = prev;
    reverse_tail = cursor;
    prev = cursor;
    cursor = cursor->next;

    for (i++; i <= dest2 && cursor != NULL; i++) {
        next = cursor->next;
        cursor->next = prev;
        prev = cursor;
        cursor = next;
    }

    reverse_prev->next = prev;
    reverse_tail->next = cursor;

    return;
}

// TEMPLATE CODE ENDS HERE

void show(Node **head) {
    Node *now = (*head)->next;
    while(now!=NULL) {
        printf("%s ", now->color);
        now = now->next;
    }
    puts("");
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int arg, char *argv[]) {
    head = (Node*)malloc(sizeof(Node)); // create an empty node
    memset(head->color,'\0',sizeof(head->color));
    head->next = NULL;
    scanf("%d",&n);
    while(n--) {
        scanf("%s",buf);
        if(!strcmp(buf,"insert")) {
            scanf("%s%d",buf,&num1);
            insert(&head, buf, num1); // insert <color> <dest>
        }
        else if(!strcmp(buf,"erase1")) {
            scanf("%d",&num1);
            erase1(&head, num1); // erase1 <dest>
        }
        else if(!strcmp(buf,"erase2")) {
            scanf("%s",buf);
            erase2(&head, buf); // erase2 <color>
        }
        else if(!strcmp(buf,"reverse")) {
            scanf("%d%d",&num1,&num2);
            reverse(&head, num1, num2); // reverse <dest1> <dest2>
        }
        else if(!strcmp(buf,"show")) {
            show(&head);
        }
    }
    return 0;
}