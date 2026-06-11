#include "students.h"

int main()
{
    srand(time(0));
    int count = 0;
    double grades[MAX_STUDENTS][NUM_ASSIGNMENTS];
    Student students[MAX_STUDENTS];
    int menu_choice;

    loadStudents(students, count);
    generateGrades(grades, count);
    CalculateAverages(grades, students, count);
    do {
        cout << "1. Display all student info \n2. Update assignment \n3. Add student \n4. Save to file \n5. Highlight student / assignment \n6. Exit\n\n";
        cin >> menu_choice;
        switch (menu_choice) {
        case 1:
            displayAllStudentInfo(grades, students, count);
            break;
        case 2:
            updateAssignment(grades, students, count);
            break;
        case 3:
            addStudent(students, count, grades);
            break;
        case 4:
            saveStudents(students, count);
            break;
        case 5:
            highlightSearch(grades, students, count);
            break;
        case 6:
            cout << "Bye!";
            break;
        }
    } while (menu_choice != 6);
}