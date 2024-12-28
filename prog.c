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

int main()
{
	
	return 0;
}

