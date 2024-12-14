#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

// Node structure for the queue
// Node structure for the queue
// Node structure for the queue
typedef struct Node {
    User user;              // Represents the User object
    struct Node* next;
} Node;
typedef struct {
    Node* head;
    Node* tail;
    int size;
} Queue;
// Function prototypes
// Queue* create_queue();
// int size(Queue* q);
// bool is_Qempty(Queue* q);
// User top(Queue* q, bool* status);
// void enqueue(Queue* q, User user);
// User dequeue(Queue* q, bool* status);
// void destroy_queue(Queue* q);

// void ProcessRequests(Queue* borrowQueue, Book* head);
// void BorrowBook(Queue* borrowQueue, Book* head, User user, int bookID);
// void DisplayBorrowedBooks(Book* head);
// Function to display the borrow request books
bool is_Qempty(Queue* q) {
    if (q->size == 0)
    {
       return true;
    }else{
        return false;
    }
     
}
User top(Queue* q, bool* status) {
    if (is_Qempty(q)) {
        *status = false;
        User emptyUser = {0};
        return emptyUser;
    }
    *status = true;
    return q->head->user;
}

void enqueue(Queue* q, User user) {
    Node* newNode = malloc(sizeof(Node));
    newNode->user = user;
    newNode->next = NULL;

    if (is_Qempty(q)) {
        q->head = newNode;
        q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
    q->size++;
}

User dequeue(Queue* q, bool* status) {
 
    if (is_Qempty(q)) {
        *status = false;
        User emptyUser = {0};
        return emptyUser;
    }

    *status = true;
    Node* oldHead = q->head;
    User user = oldHead->user;

    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }

    free(oldHead);
    q->size--;
    return user;
}

void DisplayBorrowedBooks(Book* head) {
    printf("______________________________________________________________\n\nDisplaying all borrowed books:\n______________________________________________________________\n");
    if (head == NULL) {
        printf("\n  The inventory is empty.\n");
        return;
    }
    
    Book* temp = head;
    int i = 1;
    bool found = false;
    while (temp != NULL) {
        if (!temp->AvailabilityStatus) {
            printf("\nBorrowed Book %d\n", i++);
            printf("_________________________\n");
            printf("Book ID: %d\n", temp->BookID);
            printf("Book Title: %s\n", temp->BookTitle);
            printf("Author Name: %s\n", temp->AuthorName);
            printf("Availability: Not Available\n");
            printf("_________________________\n");
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("\n No books are currently borrowed.\n");
    }
}


void ProcessRequests(Queue* borrowQueue, Book* head) {
    printf("______________________________________________________________\n\nProcessing borrow requests\n______________________________________________________________\n");
    if (head == NULL) {
      printf("\n  The inventory is empty.\n");
    }else{
    if (borrowQueue->size == 0) {
        printf("\n No borrow requests to process.\n");
        return;
    }
    
    bool status;// why you didnt initialize it
    User user = dequeue(borrowQueue, &status);
    
    // If there are no borrow requests, status will be false
    if (!status) {
        printf("No borrow requests in the queue.\n");
        return;
    }

    Book* current = head;
    while (current != NULL) {
        if (current->BookID == user.requestedBookID) {
            if (current->AvailabilityStatus) {
                // Process the request: the book is available
                printf("\nBook '%s' has been issued to %s.\n", current->BookTitle, user.name);
                current->AvailabilityStatus = false;  // Mark the book as unavailable
                return;
            }else {
                // Book is unavailable, keep the request in the queue
                printf("\nBook '%s' is still unavailable. Keeping request for %s.\n", current->BookTitle, user.name);
                enqueue(borrowQueue, user);  // Re-enqueue the user
                return;
            }
        }
        current = current->next;
    }
    printf("Book ID %d not found in the inventory.\n", user.requestedBookID);
    }
}


void BorrowBook(Queue* borrowQueue, Book* head, User user, int bookID) {
    
    Book* current = head;
    while (current != NULL) {
        if (current->BookID == bookID) {
            if (current->AvailabilityStatus) {
                printf("\n Book '%s' borrowed by %s.\n", current->BookTitle, user.name);
                current->AvailabilityStatus = false;  // Mark book as borrowed
                return;
            } else {
                printf("\n Book '%s' is unavailable. Adding %s to the borrow request list.\n", current->BookTitle, user.name);
                enqueue(borrowQueue, user);  // Add user to the borrow queue
                return;
            }
        }
        current = current->next;
    }
    printf("\n Book ID %d not found in the inventory.\n", bookID);
    
}

Queue* create_queue() {
    Queue* q = malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

int size(Queue* q) {
    return q->size;
}







