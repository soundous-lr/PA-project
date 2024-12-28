#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_ROLE 10
#define MAX_TITLE 100
#define MAX_AUTHOR 100
#define MAX_BOOKS 100
#define MAX_USERS 100
#define MAX_BORROW_LIMIT 3 // Maximum quantity of a single book a member can borrow
 


// marwa part (variables are to be modified after others add their codes )
// Structure for books
typedef struct {
    int id;
    char title[100];
    char author[100];
    float price;
    int quantity;
} Book;

// Structure for borrow records
typedef struct {
    char username[50];
    int bookID;
    int quantityBorrowed;
} BorrowRecord;

const char *booksFile = "books.txt";
const char *borrowRecordsFile = "borrow_records.txt";

// Function prototypes
int getBorrowedQuantity(const char *username, int bookID);
void updateBorrowRecord(const char *username, int bookID, int borrowedQuantity);
void borrowBook(const char *username);

// Function to get the quantity of a specific book already borrowed by a user
int getBorrowedQuantity(const char *username, int bookID) {
    FILE *file = fopen(borrowRecordsFile, "r");
    if (file == NULL) {
        return 0; // No records yet
    }

    BorrowRecord record;
    while (fscanf(file, "%s %d %d", record.username, &record.bookID, &record.quantityBorrowed) != EOF) {
        if (strcmp(record.username, username) == 0 && record.bookID == bookID) {
            fclose(file);
            return record.quantityBorrowed;
        }
    }

    fclose(file);
    return 0; // No record found
}

// Function to update the borrow record of a user
void updateBorrowRecord(const char *username, int bookID, int borrowedQuantity) {
    FILE *file = fopen(borrowRecordsFile, "r");
    FILE *temp = fopen("temp_records.txt", "w");

    if (file == NULL) {
        file = fopen("temp_records.txt", "w"); // Create a new file if none exists
    }

    BorrowRecord record;
    int found = 0;

    while (file && fscanf(file, "%s %d %d", record.username, &record.bookID, &record.quantityBorrowed) != EOF) {
        if (strcmp(record.username, username) == 0 && record.bookID == bookID) {
            found = 1;
            record.quantityBorrowed += borrowedQuantity;
        }
        fprintf(temp, "%s %d %d\n", record.username, record.bookID, record.quantityBorrowed);
    }

    if (!found) {
        fprintf(temp, "%s %d %d\n", username, bookID, borrowedQuantity);
    }

    if (file) fclose(file);
    fclose(temp);

<<<<<<< HEAD
int main() {
	
    User loggedInUser;
    int choice;

    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser(&loggedInUser)) {
                    printf("Login successful. Welcome, %s!\n", loggedInUser.username);

                    while (1) {
                        printf("\n1. View Books\n");
                        if (strcmp(loggedInUser.role, "Admin") == 0) {
                            printf("2. Add Book\n");
                            printf("3. Update Book\n");
                            printf("4. Delete Book\n");
                        } else if (strcmp(loggedInUser.role, "Member") == 0) {
                            printf("2. Borrow Book\n");
                        }
                        printf("5. Logout\n");
                        printf("Enter your choice: ");
                        scanf("%d", &choice);

                        if (choice == 5) break;

                        switch (choice) {
                            case 1:
                                viewBooks();
                                break;
                            case 2:
                                if (strcmp(loggedInUser.role, "Admin") == 0) {
                                    addBook();
                                } else {
                                    borrowBook(&loggedInUser);
                                }
                                break;
                            case 3:
                                if (strcmp(loggedInUser.role, "Admin") == 0) {
                                    updateBook();
                                }
                                break;
                            case 4:
                                if (strcmp(loggedInUser.role, "Admin") == 0) {
                                    deleteBook();
                                }
                                break;
                            default:
                                printf("Invalid choice.\n");
                                break;
                        }
                    }
                }
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    return 0;
=======
    remove(borrowRecordsFile);
    rename("temp_records.txt", borrowRecordsFile);
>>>>>>> 93064f737105cc27b9e85a47315d8e662b6ba994
}

// Function to borrow a book
void borrowBook(const char *username) {
    FILE *file = fopen(booksFile, "r");
    if (file == NULL) {
        printf("Error: Could not open books file.\n");
        return;
    }

    printf("=== Available Books ===\n");
    char line[150];
    while (fgets(line, sizeof(line), file)) {
        Book book;
        sscanf(line, "%d,%[^,],%[^,],%f,%d", &book.id, book.title, book.author, &book.price, &book.quantity);
        if (book.quantity > 0) {
            printf("ID: %d | Title: %s | Author: %s | Price: %.2f | Quantity: %d\n", 
                   book.id, book.title, book.author, book.price, book.quantity);
        }
    }
    fclose(file);

    int bookID;
    printf("\nEnter the ID of the book you want to borrow: ");
    if (scanf("%d", &bookID) != 1) {
        printf("Error: Invalid input.\n");
        return;
    }

    file = fopen(booksFile, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error: Could not create temporary file.\n");
        fclose(file);
        return;
    }

    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        Book book;
        sscanf(line, "%d,%[^,],%[^,],%f,%d", &book.id, book.title, book.author, &book.price, &book.quantity);

        if (book.id == bookID) {
            found = 1;
            int alreadyBorrowed = getBorrowedQuantity(username, bookID);

            if (book.quantity > 0 && alreadyBorrowed < MAX_BORROW_LIMIT) {
                int borrowQuantity = 1; // For simplicity, allow borrowing one book at a time
                if (alreadyBorrowed + borrowQuantity > MAX_BORROW_LIMIT) {
                    printf("Error: Borrowing limit exceeded for '%s'. You can only borrow up to %d copies.\n", 
                           book.title, MAX_BORROW_LIMIT);
                } else {
                    book.quantity -= borrowQuantity;
                    updateBorrowRecord(username, bookID, borrowQuantity);
                    printf("You have successfully borrowed '%s'.\n", book.title);
                }
            } else if (book.quantity == 0) {
                printf("Sorry, '%s' is currently unavailable.\n", book.title);
            } else {
                printf("Error: You have already borrowed the maximum allowed copies of '%s'.\n", book.title);
            }
        }

        fprintf(temp, "%d,%s,%s,%.2f,%d\n", book.id, book.title, book.author, book.price, book.quantity);
    }

    fclose(file);
    fclose(temp);

    if (!found) {
        printf("Error: Book with ID %d not found.\n", bookID);
        remove("temp.txt");
        return;
    }

    remove(booksFile);
    rename("temp.txt", booksFile);
}

<<<<<<< HEAD
// main function  
// fait par LERHLERH Soundous 

=======

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char role[MAX_ROLE]; // "Admin" or "Member"
} User;


void registerUser();
int loginUser(User *loggedInUser);
void addBook();
void viewBooks();
void updateBook();
void deleteBook();
int generateBookID();
int readUsers(User users[]);
int readBooks(Book books[]);



// The main function to test the borrowBook function
>>>>>>> 0d5a64906e0a641e7998e8be4d7dc5f22c590ee1
int main() {
	
    User loggedInUser;
    int choice;

    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser(&loggedInUser)) {
                    printf("Login successful. Welcome, %s!\n", loggedInUser.username);

                    while (1) {
                        printf("\n1. View Books\n");
                        if (strcmp(loggedInUser.role, "Admin") == 0) {
                            printf("2. Add Book\n");
                            printf("3. Update Book\n");
                            printf("4. Delete Book\n");
                        } else if (strcmp(loggedInUser.role, "Member") == 0) {
                            printf("2. Borrow Book\n");
                        }
                        printf("5. Logout\n");
                        printf("Enter your choice: ");
                        scanf("%d", &choice);

                        if (choice == 5) break;

                        switch (choice) {
                            case 1:
                                viewBooks();
                                break;
                            case 2:
                                if (strcmp(loggedInUser.role, "Admin") == 0) {
                                    addBook();
                                } else {
                                    borrowBook(&loggedInUser);
                                }
                                break;
                            case 3:
                                if (strcmp(loggedInUser.role, "Admin") == 0) {
                                    updateBook();
                                }
                                break;
                            case 4:
                                if (strcmp(loggedInUser.role, "Admin") == 0) {
                                    deleteBook();
                                }
                                break;
                            default:
                                printf("Invalid choice.\n");
                                break;
                        }
                    }
                }
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    return 0;
}
