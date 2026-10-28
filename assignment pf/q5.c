#include <stdio.h>
#include <string.h>

void displayMenu() {
    printf("\n===== UNIVERSITY LIBRARY MANAGEMENT SYSTEM =====\n");
    printf("1. Member Registration\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void registerMember(char name[], int *studentID, int *memberType) {
    printf("\nEnter member name: ");
    scanf(" %[^\n]", name);
    printf("Enter student ID: ");
    scanf("%d", studentID);
    printf("Enter membership type (1 for Student, 2 for Faculty): ");
    scanf("%d", memberType);
    while (*memberType != 1 && *memberType != 2) {
        printf("Invalid type! Enter 1 for Student, 2 for Faculty: ");
        scanf("%d", memberType);
    }
    printf("Registration successful!\n");
}

void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks) {
    printf("\n-------------------------------------------------\n");
    printf(" ID\t\tTitle\t\t\tCopies\n");
    printf("-------------------------------------------------\n");
    for(int i = 0; i < totalBooks; i++) {
        printf(" %d\t%-22s\t%d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
    }
    printf("-------------------------------------------------\n");
}

void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType) {
    if(*borrowedCount >= 3) {
        printf("Error: A member can borrow a maximum of 3 books at a time!\n");
        return;
    }
    int id, days, found = -1;
    printf("Enter book ID to borrow: ");
    scanf("%d", &id);
    for(int i = 0; i < totalBooks; i++) {
        if(bookIDs[i] == id) {
            found = i;
            break;
        }
    }
    if(found == -1) {
        printf("Invalid book ID!\n");
        return;
    }
    if(availableCopies[found] <= 0) {
        printf("Sorry, no copies available for this book!\n");
        return;
    }
    printf("Enter number of days you intend to keep the book: ");
    scanf("%d", &days);
    while(days <= 0) {
        printf("Invalid days! Must be positive. Re-enter: ");
        scanf("%d", &days);
    }
    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;
    availableCopies[found]--;
    printf("Book borrowed successfully!\n");
}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine) {
    if(*borrowedCount == 0) {
        printf("You have not borrowed any books!\n");
        return 0;
    }
    int id, foundIndex = -1;
    printf("Enter book ID to return: ");
    scanf("%d", &id);
    for(int i = 0; i < *borrowedCount; i++) {
        if(borrowedBookIDs[i] == id) {
            foundIndex = i;
            break;
        }
    }
    if(foundIndex == -1) {
        printf("Error: You have not borrowed this book!\n");
        return 0;
    }
    int actualDays;
    printf("Enter actual number of days the book was kept: ");
    scanf("%d", &actualDays);
    while(actualDays <= 0) {
        printf("Invalid days! Must be positive. Re-enter: ");
        scanf("%d", &actualDays);
    }
    int allowedDays = (memberType == 1) ? 14 : 30;
    float fine = 0;
    if(actualDays > allowedDays) {
        int extraDays = actualDays - allowedDays;
        float rate = (memberType == 1) ? 20.0 : 10.0;
        fine = extraDays * rate;
    }
    char code[20];
    printf("Enter membership code (or type NONE): ");
    scanf(" %[^\n]", code);
    if(strcmp(code, "LIB2026") == 0) {
        fine = fine * 0.5;
        printf("Membership code verified! 50%% waiver applied.\n");
    } else {
        printf("No waiver applied.\n");
    }
    *totalFine += fine;
    for(int i = 0; i < totalBooks; i++) {
        if(bookIDs[i] == id) {
            availableCopies[i]++;
            break;
        }
    }
    for(int i = foundIndex; i < *borrowedCount - 1; i++) {
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    }
    (*borrowedCount)--;
    printf("Book returned successfully! Fine for this return: Rs. %.2f\n", fine);
    return fine;
}

void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver) {
    printf("\n MEMBER RECORD \n");
    printf("Name: %s\n", name);
    printf("ID: %d\n", studentID);
    printf("Type: %s\n", (memberType == 1) ? "Student" : "Faculty");
    printf("Currently Borrowed Books: ");
    if(borrowedCount == 0) {
        printf("None\n");
    } else {
        for(int i = 0; i < borrowedCount; i++) {
            printf("%d ", borrowedBookIDs[i]);
        }
        printf("\n");
    }
    printf("Total Fine Charged: Rs. %.2f\n", totalFine);
 }

int main() {
    int bookIDs[4] = {101, 102, 103, 104};
    char bookTitles[4][50] = {"Programming in C", "Data Structures", "Database Systems", "Computer Networks"};
    int availableCopies[4] = {5, 3, 0, 4};
    char name[50] = "";
    int studentID = 0;
    int memberType = 1;
    int borrowedBookIDs[3];
    int borrowedCount = 0;
    float totalFine = 0;
    float fineAfterWaiver = 0;
    int choice;
    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = 0;
        }
        switch(choice) {
            case 1:
                registerMember(name, &studentID, &memberType);
                break;
            case 2:
                displayBooks(bookIDs, bookTitles, availableCopies, 4);
                break;
            case 3:
                borrowBook(bookIDs, bookTitles, availableCopies, 4, borrowedBookIDs, &borrowedCount, memberType);
                break;
            case 4:
                returnBook(bookIDs, availableCopies, 4, borrowedBookIDs, &borrowedCount, memberType, &totalFine);
                break;
            case 5:
                displayMemberRecord(name, studentID, memberType, borrowedBookIDs, borrowedCount, totalFine, fineAfterWaiver);
                break;
            case 6:
                printf("Exiting system. Thank you!\n");
                break;
            default:
                printf("Invalid choice! Please choose between 1 and 6.\n");
        }
    } while(choice != 6);
    return 0;
}
