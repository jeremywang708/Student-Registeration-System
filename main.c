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
