#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

// main variables
Student studentDB[MAX_STUDENTS];
int studentCount = 0;

// clear screen function
void clearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayMenu()
{
    clearScreen();

    printf("\n==========Menu==========\n");
    printf("1. Add New Student\n");
    printf("2. Display All Students\n");
    printf("3. Search Students by ID\n");
    printf("4. Search Students by GPA\n");
    printf("5. Search Student by Major\n");
    printf("6. Exit\n");
    printf("=======================\n");
}
// saving data
void saveToFile()
{
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL)
    {
        printf("ERROR: Cannot open file for saving!\n");
        return;
    }

    // write each student as a formatted line
    for (int i = 0; i < studentCount; i++)
    {
        fprintf(fp, "%d|%s|%f|%s\n", 
                studentDB[i].id,
                studentDB[i].name,
                studentDB[i].gpa,
                studentDB[i].major);
    }

    fclose(fp);
}

void loadFromFile()
{
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL)
    {
        printf("No existing data file found. Starting with empty database.\n");
        return;
    }

    studentCount = 0;
    
    // read until end of the file
    while (fscanf(fp, "%d|%s|%f|%s\n",
                  &studentDB[studentCount].id,
                  studentDB[studentCount].name,
                  &studentDB[studentCount].gpa,
                  studentDB[studentCount].major) == 4)
    {
        studentCount++;
        if (studentCount >= MAX_STUDENTS)
        {
            printf("Warning: Maximum students reached while loading.\n");
            break;
        }
    }

    fclose(fp);
    
    if (studentCount > 0)
    {
        printf("Loaded %d students from %s\n", studentCount, DATA_FILE);
    }
    else
    {
        printf("No student data found in file.\n");
    }
}

void addStudent()
{
    clearScreen();

    Student newStudent;
    char input[100];
    int temp;
    int duplicate;

    if (studentCount >= MAX_STUDENTS) {
        printf("ERROR: Student database is full!\n");
        return;
    }

    

    // get Id
    get_id:
    do {
        printf("Enter Student ID or enter 0 to undo: ");
        scanf("%s", input);
        
        if (strcmp(input, "0") == 0) {
            return;
        }

    if (sscanf(input, "%d", &temp) != 1) {
        printf("Invalid Choice! Numbers Only.\n");// check for char input
        goto get_id;  // Go back
    }

newStudent.id = temp;
        
        duplicate = 0;
        for (int i = 0; i < studentCount; i++) {
            if (studentDB[i].id == newStudent.id) {
                duplicate = 1;
                break;
            }
        }
        
        if (duplicate) {
            printf("ERROR: ID %d already exists!\n", newStudent.id);
            printf("Type '0' to go back or try again.\n\n");
        }
        
    } while (duplicate);

    // get Name
    get_name:
    do {
        printf("Enter Student Name or enter 0 to undo: ");
        scanf("%s", input);
        
        if (strcmp(input, "0") == 0) {
            goto get_id;  // go back to id
        }
        
        if (strlen(input) == 0) {
            printf("Name cannot be empty!\n");
            printf("Type '0' to go back or try again.\n\n");
        } else {
            strcpy(newStudent.name, input);
        }
        
    } while (strlen(newStudent.name) == 0);

    // get gpa
    get_gpa:
    do {
        printf("Enter Student GPA (0.0 - 5.0): ");
        scanf("%s", input);
        
        if (strcmp(input, "0") == 0) {
            goto get_name;  // go back to name
        }
        
        sscanf(input, "%f", &newStudent.gpa);
        
        if (newStudent.gpa < 0 || newStudent.gpa > 5.0) {
            printf("Invalid GPA! Must be between 0.0 and 5.0\n");
            printf("Type '0' to go back or try again.\n\n");
        }
        
    } while (newStudent.gpa < 0 || newStudent.gpa > 5.0);

    // get Major
    get_major:
    do {
        printf("Enter Student Major: ");
        scanf("%s", input);
        
        if (strcmp(input, "0") == 0) {
            goto get_gpa;  // go back to gpa
        }
        
        if (strlen(input) == 0) {
            printf("Major cannot be empty!\n");
            printf("Type '0' to go back or try again.\n\n");
        } else {
            strcpy(newStudent.major, input);
        }
        
    } while (strlen(newStudent.major) == 0);

    // add Student
    studentDB[studentCount] = newStudent;
    studentCount++;
    saveToFile();
      printf("\nStudent added successfully!\n");

       printf("\nPress Enter to continue...");
    getchar();
    getchar();
}
void displayAllStudents()
{
    clearScreen(); // clear screen for cleaner view

    if (studentCount == 0)
    {
        printf("No students in the database!\n");

         printf("\nPress Enter to continue...");
    getchar();
    getchar();
        return;
    }

    printf("\n========== All Students ==========\n");
    printf("%-10s %-20s %-10s %-15s\n", "ID", "Name", "GPA", "Major");
    printf("----------------------------------------\n");

    for (int i = 0; i < studentCount; i++)
    {
        printf("%-10d %-20s %-10.2f %-15s\n",
               studentDB[i].id,
               studentDB[i].name,
               studentDB[i].gpa,
               studentDB[i].major);
    }
    printf("===================================\n");
    printf("Total Students: %d\n", studentCount);

     printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

void searchByID()
{
    clearScreen();

    int id, found = 0;

    if (studentCount == 0)
    {
        printf("No students in the database!\n");
        return;
    }

    printf("Enter Student ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++)
    {
        if (studentDB[i].id == id)
        {
            printf("\nStudent Found:\n");
            printf("ID: %d\n", studentDB[i].id);
            printf("Name: %s\n", studentDB[i].name);
            printf("GPA: %.2f\n", studentDB[i].gpa);
            printf("Major: %s\n", studentDB[i].major);
            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("Student with ID %d not found!\n", id);
    }
}

void searchByGPA()
{
    clearScreen();

    float minGPA, maxGPA;
    int found = 0;

    if (studentCount == 0)
    {
        printf("No students in the database!\n");
        return;
    }

    printf("Enter minimum GPA: ");
    scanf("%f", &minGPA);
    printf("Enter maximum GPA: ");
    scanf("%f", &maxGPA);

    printf("\n========== Students with GPA %.2f - %.2f ==========\n", minGPA, maxGPA);
    printf("%-10s %-20s %-10s %-15s\n", "ID", "Name", "GPA", "Major");
    printf("------------------------------------------------\n");

    for (int i = 0; i < studentCount; i++)
    {
        if (studentDB[i].gpa >= minGPA && studentDB[i].gpa <= maxGPA)
        {
            printf("%-10d %-20s %-10.2f %-15s\n",
                   studentDB[i].id,
                   studentDB[i].name,
                   studentDB[i].gpa,
                   studentDB[i].major);
            found = 1;
        }
    }

    if (found == 0)
    {
        printf("No students found with GPA in that range!\n");
    }
    printf("==================================================\n");
}

void searchByMajor()
{
    clearScreen();

    char major[50];
    int found = 0;

    if (studentCount == 0)
    {
        printf("No students in the database!\n");
        return;
    }

    printf("Enter Major to search: ");
    scanf(" %s", major);

    printf("\n========== Students in %s ==========\n", major);
    printf("%-10s %-20s %-10s\n", "ID", "Name", "GPA");
    printf("------------------------------------\n");

    for (int i = 0; i < studentCount; i++)
    {
        if (strcmp(studentDB[i].major, major) == 0)
        {
            printf("%-10d %-20s %-10.2f\n",
                   studentDB[i].id,
                   studentDB[i].name,
                   studentDB[i].gpa);
            found = 1;
        }
    }

    if (found == 0)
    {
        printf("No students found with major: %s\n", major);
    }
    printf("==========================================\n");
}