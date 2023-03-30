#include <stdio.h>
#include <string.h>
#include "student.h"

/*
****************************************************************************
Function Name: registerStudents
Purpose: To register a specified number of students by their student IDs.
Function in parameters: studentIds (2D character array) - the array to store the registered student IDs
Function out parameter: N/A
Version: 1
Author: Yun Wang
****************************************************************************
*/
void registerStudents(char studentIds[MAX_STUDENTS][ID_LENGTH + 1]) {
    printf("Welcome to the Student Registration System.\n\n");

    int numStudents;
    do {
        printf("Enter the number of students to register: ");
        scanf("%d", &numStudents);
        if (numStudents < 1 || numStudents > MAX_STUDENTS) {
            printf("Error: Invalid number of students entered.\n");
        }
    } while (numStudents < 1 || numStudents > MAX_STUDENTS);

    getchar();
    int i, j;
    for (i = 0; i < numStudents; i++) {
        char id[ID_LENGTH + 1];
        int validId = 0;
        while (!validId) {
            printf("Enter the student index[%d] student id [%d-digits]: ", i, ID_LENGTH);
            fgets(id, ID_LENGTH + 2, stdin);
            if (id[strlen(id) - 1] != '\n') {
                printf("Student Id must be 5 digits.\n");
                while (getchar() != '\n');
                continue;
            }
            id[strlen(id) - 1] = '\0';
            int idLength = strlen(id);
            int validDigits = 1;
            for (j = 0; j < idLength; j++) {
                if (!isdigit(id[j])) {
                    validDigits = 0;
                    break;
                }
            }
            if (idLength != ID_LENGTH || !validDigits) {
                printf("Student Id must be 5 digits.\n");
            } else {
                int duplicate = 0;
                for (j = 0; j < i; j++) {
                    if (strcmp(studentIds[j], id) == 0) {
                        duplicate = 1;
                        printf("Duplicate student ID entered. Please enter a new one.\n");
                        break;
                    }
                }
                if (!duplicate) {
                    strcpy(studentIds[i], id);
                    validId = 1;
                }
            }
        }
    }
}