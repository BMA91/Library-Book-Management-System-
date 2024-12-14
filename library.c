#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Stack.c" 
#include "Queue.c"

void fillbook(Book* book1) {
    
    printf("Enter the book's title: ");
    while (getchar() != '\n' && getchar() != EOF);
    if (fgets(book1->BookTitle, sizeof(book1->BookTitle), stdin) != NULL) {
        book1->BookTitle[strcspn(book1->BookTitle, "\n")] = '\0';
    } else {
        printf("Error reading the book title.\n");
    }
    printf("Enter the book's author: ");
    if (fgets(book1->AuthorName, sizeof(book1->AuthorName), stdin) != NULL) {
        book1->AuthorName[strcspn(book1->AuthorName, "\n")] = '\0';
    } else {
        printf("Error reading the author name\n");
    }
    printf("Enter the book's ID: ");
    scanf("%d", &book1->BookID);
    book1->AvailabilityStatus = true;
}

void AddBook(Book** head) {
    printf("______________________________________________________________\n\nhere we will be adding a book\n______________________________________________________________\n");
    
    Book* newBook = (Book*)malloc(sizeof(Book));
    fillbook(newBook);
    newBook->next = NULL;
    
    if (*head == NULL) {
        *head = newBook;
    } else {
        Book* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBook;
    }
}

void Display(Book* head) {
    printf("______________________________________________________________\n\nhere we will be displaying the books\n______________________________________________________________ \n");
    if (head == NULL) {
      printf("\n  The inventory is empty.\n");
    }else{
     int i=1;
      Book* temp = head;
      while (temp != NULL) {
          printf("\nbook number %d\n",i);i++;
          printf("_________________________\n");
          printf("Book ID: %d\n", temp->BookID);
          printf("Book Title: %s\n", temp->BookTitle);
          printf("Author Name: %s\n", temp->AuthorName);
          printf("Availability: %s\n", temp->AvailabilityStatus ? "Available" : "Not Available");
          printf("_________________________\n");
          temp = temp->next;
        }
    }
}

bool SearchBook(Book* head, int id) {
    
    Book* temp = head;
    while (temp != NULL) {
        if (temp->BookID == id) {
            return temp->AvailabilityStatus;
        }
        temp = temp->next;
    }
    return false;
    
}
void returnMenu(){
    char returnn[10];
    printf("\nPress enter to return to the menu:");
    while (getchar() != '\n' && getchar() != EOF);  
     if (fgets(returnn, sizeof(returnn), stdin) != NULL) {
        returnn[strcspn(returnn, "\n")] = '\0';}
    
}
int main() {
    Book* head = NULL;
    Queue* borrowQueue = create_queue();
    Stack* s = (Stack*)malloc(sizeof(Stack));
    InitStack(s);

    int choice, id;
    User user;

    printf("______________________________________________________________\n");
    printf("\n        Welcome to our Library Book Management System\n");
    
    while (1) {
        printf("______________________________________________________________\n");
        printf("\nWhat do you want to do?\n1: Add a book\n2: Search for a book\n3: Display all books\n4: Borrow a book \n5: Display all borrowed books \n6: Return a book\n7: Display recently returned books \n8: Process borrow requests\n9: Exit\nEnter(1-9): ");
        scanf("%d", &choice);
        while (choice < 0 || choice > 9) {
            printf("Enter again(1-9): ");
            scanf("%d", &choice);
        }

        switch (choice) {
            case 1:
                AddBook(&head);
                returnMenu();
                break;
            case 2:
                printf("______________________________________________________________\n\nSearching for a book availability\n______________________________________________________________\n");
                if (head == NULL) {
                    printf("\n  The inventory is empty.\n");
                } else {
                    printf("Enter the book ID to search: ");
                    scanf("%d", &id);
                    if (SearchBook(head, id)) {
                        printf("\nThe book is available.\n");
                    } else {
                        printf("\nThe book is not available.\n");
                    }
                }
                returnMenu();
                break;
            case 3:
                Display(head);
                returnMenu();
                break;
            case 6:
                ReturnBook(s, head);
                returnMenu();
                break;
            case 7:
                displayStack(s, head);
                returnMenu();
                break;
            case 4:
                printf("__________________________________________________________________________\n\nhere we will be borrowing books or adding your request to the request list\n__________________________________________________________________________\n");

                if (head == NULL) {
                 
                 printf("\n  The inventory is empty.\n");
                }else{
                printf("Enter user details:\n");
                printf("Enter your name: ");
                scanf("%s", user.name);
                printf("Enter user ID: ");
                scanf("%d", &user.userID);
                printf("Enter book ID to borrow: ");
                scanf("%d", &id);
                user.requestedBookID = id;
                BorrowBook(borrowQueue, head, user, id);
                }
                returnMenu();
                break;
            case 5:
                DisplayBorrowedBooks(head);
                returnMenu();
                break;
            case 8:
                ProcessRequests(borrowQueue, head);  // Call the ProcessRequests function
                returnMenu();
                break;
            case 9:
                printf("Exiting program.\n");
                free(s);
                free(borrowQueue);
                exit(0);
        }
    }
}



