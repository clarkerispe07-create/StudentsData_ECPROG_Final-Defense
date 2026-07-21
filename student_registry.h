#ifndef DATABASE_H
#define DATABASE_H

#define MAX_STUDENTS 100
#define DATA_FILE "students.txt"

typedef struct {
    int id;
    char name[50];
    float gpa;
    char major[50];
} Student;

// function Declarations(prototypes)
void displayMenu();
void saveToFile();
void loadFromFile();
void addStudent();
void displayAllStudents();
void searchByID();
void searchByGPA();
void searchByMajor();
void clearScreen(); // for clear view

#endif