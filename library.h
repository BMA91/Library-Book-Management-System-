#pragma once
// User structure
typedef struct User {
    int userID;
    char name[50];
    int requestedBookID;
    struct User *next;
} User;

typedef struct Book {
    int BookID;
    char BookTitle[100];
    char AuthorName[100];
    bool AvailabilityStatus;
    struct Book* next; // Pointer to the next Book in the list
} Book;
