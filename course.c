#include <stdio.h>
#include <string.h>
#include "course.h"

/*
****************************************************************************
Function Name: registerCourses
Purpose: To register a specified number of courses by their course IDs.
Function in parameters: courseIds (2D character array) - the array to store the registered course IDs
Function out parameter: N/A
Version: 1
Author: Yun Wang
****************************************************************************
*/
void registerCourses(char courseIds[MAX_COURSES][COURSE_ID_LENGTH + 1]) {
    int numCourses;

    do {
        printf("\nEnter the number of courses available: ");
        scanf("%d", &numCourses);
        if (numCourses < 1 || numCourses > MAX_COURSES) {
            printf("Error: Invalid number of courses entered.\n");
        }
    } while (numCourses < 1 || numCourses > MAX_COURSES);
    int i;
    for (i = 0; i < numCourses; i++) {
        int validId = 0;
        while (!validId) {
            printf("Enter the course index[%d] course id [%d-Alpha][%d-digits]: ", i, 3, 4);
            char id[COURSE_ID_LENGTH + 1];
            scanf("%s", id);
            int idLength = strlen(id);
            int validLength = (idLength == COURSE_ID_LENGTH);
            int validPrefix = 1;
            int j;
            for (j = 0; j < 3; j++) {
                if (!((id[j] >= 'A' && id[j] <= 'Z') || (id[j] >= 'a' && id[j] <= 'z'))) {
                    validPrefix = 0;
                    break;
                }
            }
            int validSuffix = 1;
            for (j = 3; j < idLength; j++) {
                if (id[j] < '0' || id[j] > '9') {
                    validSuffix = 0;
                    break;
                }
            }
            if (!validLength || !validPrefix || !validSuffix) {
                if (!validLength) {
                    printf("Incorrect Course Id length [%d-character Id]\n", COURSE_ID_LENGTH);
                }
                else {
                    printf("Incorrect Course Id input [%d-Alpha][%d-digits]\n", 3, 4);
                }
            }
            else {
                int duplicate = 0;
                int j;
                for (j = 0; j < i; j++) {
                    if (strcmp(courseIds[j], id) == 0) {
                        duplicate = 1;
                        printf("Duplicate course ID entered. Please enter a new one.\n");
                        break;
                    }
                }
                if (!duplicate) {
                    strcpy(courseIds[i], id);
                    validId = 1;
                }
            }
        }
    }
}