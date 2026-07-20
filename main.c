#include <stdio.h>
#include "database.h"

int main()
{
    int choice;

    loadFromFile();

    do
    {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayAllStudents();
            break;
        case 3:
            searchByID();
            break;
        case 4:
            searchByGPA();
            break;
        case 5:
            searchByMajor();
            break;
        case 6:
            printf("Saving data before exiting...\n");
            saveToFile();
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice! Please select 1-6.\n");
        }
    } while (choice != 6);

    return 0;
}