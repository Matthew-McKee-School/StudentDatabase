#include "students.h"

int main()
{
    int count = 0;
    double grades[MAX_STUDENTS][NUM_ASSIGNMENTS];
    Student students[MAX_STUDENTS];
    int menu_choice;

    loadStudents(students, count);
    do {
        cout << "1. Display all students \n2. Search by course \n3. Assignment average \n4. Hardest assignment \n5. Course enrollment \n6. Sort by average \n7. Add student \n8. At risk students \n9. Save students \n10. Exit \n\n";
        
        cout << "Which of the above menu options would you like to do: ";
        cin >> menu_choice;
        switch (menu_choice) {
        case 1:
            displayStudents(students, count);
            break;
        case 2:
            searchByCourse(students, count);
            break;
        case 3:
            showAssignmentAverage(students, count);
            break;
        case 4:
            showHardestAssignment(students, count);
            break;
        case 5:
            courseEnrollment(students, count);
            break;
        case 6:
            sortByAverage(students, count);
            break;
        case 7:
            addStudent(students, count);
            break;
        case 8:
            atRiskStudents(students, count);
            break;
        case 9:
            saveStudents(students, count);
            break;
        case 10:
            cout << "Bye";
            break;
        }
    } while (menu_choice != 10);
}