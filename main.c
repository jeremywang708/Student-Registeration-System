/*
* Title: Assignment #1 - Student Registration System
* Course: CST8234 C Language
* @Author: <<< Yun Wang - 041069121 >>>
* Lab Section: 012
* Professor: Surbhi Bahri
* Due date: 03/12/2023
* Submission date: 03/12/2023

* Requirement #1: {complete}
* Requirement #2: {complete}
* Requirement #3: {complete}
* Requirement #4: {complete}
* Requirement #5: {complete}
* Requirement #6: {complete}
* Requirement #7: {complete}
* Requirement #8: {complete}
* Requirement #9: {complete}
* Requirement #10: {complete}
* Requirement #11: {complete}
* Requirement #12: {complete}
* Requirement #13: {complete}
*/
#include <stdio.h>
#include "student.h"
#include "course.h"
#include "menu.h"

/*
****************************************************************************
Function Name: main
Purpose: To run the main registration system program by initializing the necessary variables, registering students and courses, and calling the menu function repeatedly until the user chooses to exit.
Function in parameters: None
Function out parameter: 
   0 (integer) - indicates successful execution of the program
Version: 1
Author: Yun Wang
****************************************************************************
*/
int main() {
    char studentIds[MAX_STUDENTS][ID_LENGTH + 1] = {0};
    char courseIds[MAX_COURSES][COURSE_ID_LENGTH + 1] = {0};
    char registeredIds[MAX_REGISTRATIONS][ID_LENGTH + 1 + COURSE_ID_LENGTH + 1][2];
    int numRegistrations = 0;
    int choice;

    registerStudents(studentIds);
    registerCourses(courseIds);
    
    while (1) {
        choice = menu(studentIds, courseIds, registeredIds, &numRegistrations);
        if (choice == 4) {
            break;
        }
    }

    return 0;
}
