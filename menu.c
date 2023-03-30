#include <stdio.h>
#include "menu.h"
#include "student.h"
#include "course.h"

/*
****************************************************************************
Function Name: menu
Purpose: To display the main menu of the registration system and call the appropriate function based on the user's choice.
Function in parameters: 
   studentIds (2D character array) - the array containing the registered student IDs
   courseIds (2D character array) - the array containing the available course IDs
   registeredIds (3D character array) - the array containing the registered student IDs, course IDs, and registration statuses
   numRegistrations (integer pointer) - the number of registered students
Function out parameter: 
   choice (integer) - the user's choice from the menu
Version: 1
Author: Yun Wang
****************************************************************************
*/
int menu(char studentIds[MAX_STUDENTS][ID_LENGTH + 1], char courseIds[MAX_COURSES][COURSE_ID_LENGTH + 1], char registeredIds[MAX_REGISTRATIONS][ID_LENGTH + 1 + COURSE_ID_LENGTH + 1][2], int *numRegistrations) {
    int choice;

    printf("\nMain Menu:\n");
    printf("[1] Register a student into a course.\n");
    printf("[2] Drop a student from a course.\n");
    printf("[3] Display registration table.\n");
    printf("[4] Exit.\n");
    printf("Enter an option from the menu: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            displayLists(studentIds, courseIds, registeredIds, numRegistrations);
            break;
        case 2:
            dropStudent(registeredIds, numRegistrations);
            break;
        case 3:
            printRegistrationTable(registeredIds, numRegistrations);
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }

    return choice;
}


/*
****************************************************************************
Function Name: displayLists
Purpose: To display lists of registered students and available courses, and to register a student for a course.
Function in parameters: 
   studentIds (2D character array) - the array containing the registered student IDs
   courseIds (2D character array) - the array containing the available course IDs
   registeredIds (3D character array) - the array containing the registered student IDs, course IDs, and registration statuses
   numRegistrations (integer pointer) - the number of registered students
Function out parameter: N/A
Version: 1
Author: Yun Wang
****************************************************************************
*/
void displayLists(char studentIds[MAX_STUDENTS][ID_LENGTH + 1], char courseIds[MAX_COURSES][COURSE_ID_LENGTH + 1], char registeredIds[MAX_REGISTRATIONS][ID_LENGTH + 1 + COURSE_ID_LENGTH + 1][2], int *numRegistrations) {
    int i;

    /* Display list of registered students */
    printf("List of registered students:\n");
    for (i = 0; i < MAX_STUDENTS; i++) {
        if (studentIds[i][0] != '\0') {
            printf("Index %d  %s\n", i, studentIds[i]);
        }
    }

    char studentId[ID_LENGTH + 1];
    int validId = 0;

    /* Prompt user to enter student ID and validate input */
    while (!validId) {
        printf("\nEnter the student's ID to register a course (5 digits): ");
        scanf("%s", studentId);

        /* Check if ID is valid (5 digits and in the array) */
        int foundId = 0;
        for (i = 0; i < MAX_STUDENTS; i++) {
            if (strcmp(studentId, studentIds[i]) == 0) {
                foundId = 1;
                break;
            }
        }
        if (foundId && strlen(studentId) == 5) {
            validId = 1;
        } else {
            printf("Student Id must be 5 digits.\n");
        }
    }

    /* Display list of available courses */
    printf("\nList of available courses:\n");
    for (i = 0; i < MAX_COURSES; i++) {
        if (courseIds[i][0] != '\0') {
            printf("Index %d  %s\n", i, courseIds[i]);
        }
    }

    char courseId[COURSE_ID_LENGTH + 1];
    int validCourseId = 0;

    /* Prompt user to enter course ID and validate input */
    while (!validCourseId) {
        printf("\nEnter the course id [3-Alphas)[4-digits]: ");
        scanf("%s", courseId);

        /* Check if ID is valid (3 alphas followed by 4 digits and in the array) */
        int foundId = 0;
        for (i = 0; i < MAX_COURSES; i++) {
            if (strcmp(courseId, courseIds[i]) == 0) {
                foundId = 1;
                break;
            }
        }
        if (foundId && strlen(courseId) == 7 && isalpha(courseId[0]) && isalpha(courseId[1]) && isalpha(courseId[2]) && isdigit(courseId[3]) && isdigit(courseId[4]) && isdigit(courseId[5]) && isdigit(courseId[6])) {
            validCourseId = 1;
        } else {
            printf("Incorrect Course Id length [7-character Id].\n");
        }
    }

        /* Check if student is already registered for the course */
        int duplicate = 0;
        int previouslyDropped = 0;
        for (i = 0; i < *numRegistrations; i++) {
            char regStudentId[ID_LENGTH + 1];
            char regCourseId[COURSE_ID_LENGTH + 1];
            char status[2];
            sscanf(registeredIds[i], "%s %s %s", regStudentId, regCourseId, status);
            if (strcmp(studentId, regStudentId) == 0 && strcmp(courseId, regCourseId) == 0) {
                if (strcmp(status, "R") == 0) {
                    duplicate = 1;
                    break;
                } else if (strcmp(status, "D") == 0) {
                    previouslyDropped = 1;
                    break;
                }
            }
        }
        if (duplicate) {
            printf("Already on record.\nStudent id %s cannot register to course %s.\nRegistration Unsuccessful.\n", studentId, courseId);
        } else if (previouslyDropped) {
            printf("Student id %s has dropped out from course %s.\nStudent id %s cannot register to course %s.\nRegistration Unsuccessful.\n", studentId, courseId, studentId, courseId);
        } else {
            /* Store registered student and course IDs in registeredIds array */
            sprintf(registeredIds[*numRegistrations], "%s %s %s", studentId, courseId, "R");
            (*numRegistrations)++;
            /* Confirm registration */
            printf("\nRegistration successful.\n");
        }
}


/*
****************************************************************************
Function Name: dropStudent
Purpose: To drop the registration of a student from a course.
Function in parameters: 
   registeredIds (3D character array) - the array containing the registered student IDs, course IDs, and registration statuses
   numRegistrations (integer pointer) - the number of registered students
Function out parameter: N/A
Version: 1
Author: Yun Wang
****************************************************************************
*/
void dropStudent(char registeredIds[MAX_REGISTRATIONS][ID_LENGTH + 1 + COURSE_ID_LENGTH + 1][2], int *numRegistrations) {
    printRegistrationTable(registeredIds, numRegistrations);

    int index;
    printf("Please select Index number to drop student registration: ");
    scanf("%d", &index);

    if (index < 0 || index >= *numRegistrations) {
        printf("Invalid index. Please enter a valid index number.\n");
        return;
    }

    char studentId[ID_LENGTH + 1];
    char courseId[COURSE_ID_LENGTH + 1];
    char status[2];
    sscanf(registeredIds[index], "%s %s %s", studentId, courseId, status);

    /* Set the registration status to "D" */
    status[0] = 'D';

    /* Set the student ID and course ID fields to be the same as the original IDs */
    strcpy(registeredIds[index], "");
    strcat(registeredIds[index], studentId);
    strcat(registeredIds[index], " ");
    strcat(registeredIds[index], courseId);
    strcat(registeredIds[index], " ");
    strcat(registeredIds[index], status);

    printf("Drop course successfully.\n");
    printRegistrationTable(registeredIds, numRegistrations);
}


/*
****************************************************************************
Function Name: printRegistrationTable
Purpose: To print a table of registered students and their corresponding course registrations.
Function in parameters: 
   registeredIds (3D character array) - the array containing the registered student IDs, course IDs, and registration statuses
   numRegistrations (integer pointer) - the number of registered students
Function out parameter: N/A
Version: 1
Author: Yun Wang
****************************************************************************
*/
void printRegistrationTable(char registeredIds[MAX_REGISTRATIONS][ID_LENGTH + 1 + COURSE_ID_LENGTH + 1][2], int *numRegistrations) {
    int i;
    printf("\n");
    printf("%50s\n", "Registration Table");
    printf("%103s\n", " ");
    printf("%-22s%-22s%-22s%-22s\n", "Registration Index", "Student ID", "Course ID", "Registration Status");
    printf("%103s\n", " ");
    for (i = 0; i < *numRegistrations; i++) {
        char studentId[ID_LENGTH + 1];
        char courseId[COURSE_ID_LENGTH + 1];
        char status[2];
        sscanf(registeredIds[i], "%s %s %s", studentId, courseId, status);
        printf("%-22d%-22s%-22s%-22s\n", i, studentId, courseId, strcmp(status, "R") == 0 ? "R" : "D");
    }
}

