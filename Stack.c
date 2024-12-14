#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "library.h"

typedef struct Estack* Stack;
typedef struct Estack {
    Book* Data;
    Stack Next;
} SNode;

void InitStack(Stack* P) {
    *P = NULL;
}

void Push(Stack* S, Book* x) {
    Stack V = (Stack)malloc(sizeof(SNode));
    if (V == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    V->Data = x;
    V->Next = *S;
    *S = V;
}

void Pop(Stack* S, Book** poppedBook) {
    if (*S == NULL) {
        printf("Stack underflow! No items to pop.\n");
        *poppedBook = NULL;
        return;
    }
    Stack V = *S;
    *poppedBook = V->Data;
    *S = V->Next;
    free(V);
}

bool isSEmpty(Stack s) {
    return s == NULL;
}

Book* Top(Stack S) {
    if (S == NULL) {
        printf("Stack is empty!\n");
        return NULL;
    }
    return S->Data;
}
//stack operations:

void ReturnBook(Stack* s,  Book* head){
    printf("______________________________________________________________\n\nhere we will be returning book\n______________________________________________________________");
    
    int id,userID;
    if (head == NULL) {
     printf("\n\n  The inventory is empty.\n");
    }else{
    Book* temp = head;
    Book* RBook = (Book*)malloc(sizeof(Book)); 
    printf("\nwhat is your ID:");
    scanf("%d",&userID);
    printf("Enter the book ID to return: ");
    scanf("%d", &id);

    while (temp != NULL) {
        if (temp->BookID == id) {
            temp->AvailabilityStatus=true;
            strcpy(RBook->AuthorName, temp->AuthorName);
            strcpy(RBook->BookTitle, temp->BookTitle);
            RBook->BookID = temp->BookID;
            RBook->AvailabilityStatus = true;
            Push(s, RBook); 
            printf("\n Book '%s' has been returned to the library.\n",temp->BookTitle);
            return;
        }
        temp = temp->next;
    }
    printf("Book not found.\n");
    free(RBook); 
    }
    
}

void displayStack(Stack* s, Book* head) {
   printf("______________________________________________________________\n\nhere we will be displaying the returned books\n______________________________________________________________\n");
    if (head == NULL) {
      printf("\n The inventory is empty.\n");
    }else{
    if (isSEmpty(*s)) {
        printf("The stack is empty.\n");
        return;
    }

    Stack tempStack;
    InitStack(&tempStack);
    Book* tempBook;
    int i=1;
    while (!isSEmpty(*s)) {

        Pop(s, &tempBook);
        printf("\nbook number %d\n",i);i++;
        printf("_________________________\n");
        printf("Book ID: %d\n", tempBook->BookID);
        printf("Book Title: %s\n", tempBook->BookTitle);
        printf("Author Name: %s\n", tempBook->AuthorName);
        printf("Availability: %s\n", tempBook->AvailabilityStatus ? "Available" : "Not Available");
        printf("_________________________\n");
        Push(&tempStack, tempBook); 
    }

    
    while (!isSEmpty(tempStack)) {
        Pop(&tempStack, &tempBook);
        Push(s, tempBook);
    }
    
    }
}