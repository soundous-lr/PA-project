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

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char role[MAX_ROLE]; // "Admin" or "Member"
} User;

typedef struct {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    float price;
    int quantity;
} Book;


void registerUser();
int loginUser(User *loggedInUser);
void addBook();
void viewBooks();
void updateBook();
void deleteBook();
void borrowBook(User *loggedInUser);
int generateBookID();
int readUsers(User users[]);
int readBooks(Book books[]);



// main function 

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

