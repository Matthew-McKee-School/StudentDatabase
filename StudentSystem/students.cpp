#include "students.h"
void loadStudents(Student students[], int& count) {
    ifstream inputFile("students.txt");
    while (inputFile >> students[count].id >> students[count].firstName >> students[count].lastName >> students[count].grade) {
        count = count + 1;
    }
}

void generateGrades(double grades[][NUM_ASSIGNMENTS], int count) {
    double grade;
    for (int y = 0; y < count; y++) {
        for (int x = 0; x < NUM_ASSIGNMENTS; x++) {
            grade = rand() % 41 + 60;
            grades[y][x] = grade;
        }
    }
}

void CalculateAverages(double grades[][NUM_ASSIGNMENTS], Student students[], int count) {
    double total;
    for (int y = 0; y < count; y++) {
        total = 0;
        for (int x = 0; x < NUM_ASSIGNMENTS; x++) {
            total = total + grades[y][x];
        }
        students[y].grade = total / NUM_ASSIGNMENTS;
    }
}

void displayAllStudentInfo(double grades[][NUM_ASSIGNMENTS], Student students[], int count) {
    for (int y = 0; y < count; y++) {
        cout << students[y].id << "\t" << students[y].firstName << "\t\t" << students[y].lastName << "\t\t";
        for (int x = 0; x < NUM_ASSIGNMENTS; x++) {
            cout << grades[y][x] << " ";
        }
        cout << students[y].grade << "\n";
    }
}

void updateAssignment(double grades[][NUM_ASSIGNMENTS], Student students[], int count) {
    int id_num;
    int grade_num;
    double updated_grade;
    cout << "What is the id of the student that you would like to update an assignment grade for: ";
    cin >> id_num;
    cout << "Which assignment did you want to update: ";
    cin >> grade_num;
    cout << "What should the grade be: ";
    cin >> updated_grade;
    for (int x = 0; x < count; x++) {
        if (students[x].id == id_num) {
            grades[x][grade_num - 1] = updated_grade;
        }
    }
    CalculateAverages(grades, students, count);
    displayAllStudentInfo(grades, students, count);
}

void addStudent(Student students[], int& count, double grades[][NUM_ASSIGNMENTS]) {
    cout << "What is the new student's first name: ";
    cin >> students[count].firstName;
    cout << "What is the new student's last name: ";
    cin >> students[count].lastName;
    cout << "What is the new student's id number: ";
    cin >> students[count].id;
    for (int x = 0; x < NUM_ASSIGNMENTS; x++) {
        cout << "Add assignment #" << x + 1 << ": ";
        cin >> grades[count][x];
    }
    cout << "new student has been added.\n\n";
    count++;
    CalculateAverages(grades, students, count);
}

void saveStudents(Student students[], int count) {
    ofstream outputFile("students.txt");

    for (int x = 0; x < count; x++) {
        outputFile << students[x].id << " " << students[x].firstName << " " << students[x].lastName << " " << students[x].grade << "\n";
    }
}

void highlightSearch(double grades[][NUM_ASSIGNMENTS], Student students[], int count) {
    int highlight_choice;
    cout << "1. Highlight Student (Row)\n2. Highlight Assignment (Columm)\n Choice: ";
    cin >> highlight_choice;

    if (highlight_choice == 1) {
        int student_choice;
        cout << "Input the student id you want highlighted: ";
        cin >> student_choice;

        for (int y = 0; y < count; y++) {
            if (students[y].id == student_choice) {
                cout << "\033[33m";
            }
            cout << students[y].id << "\t" << students[y].firstName << "\t" << students[y].lastName << "\t";
            for (int x = 0; x < NUM_ASSIGNMENTS; x++) {
                cout << grades[y][x] << " ";
            }
            cout << students[y].grade << "\n";
            if (students[y].id == student_choice) {
                cout << "\033[0m";
            }
        }
    }
    else if (highlight_choice == 2) {
        int assignment_choice;
        cout << "Input the student assignment you want highlighted (1-5): ";
        cin >> assignment_choice;
        for (int y = 0; y < count; y++) {
            cout << students[y].id << "\t" << students[y].firstName << "\t" << students[y].lastName << "\t";
            for (int x = 0; x < NUM_ASSIGNMENTS; x++) {
                if (assignment_choice == x + 1) {
                    cout << "\033[33m";
                }
                cout << grades[y][x] << " ";
                if (assignment_choice == x + 1) {
                    cout << "\033[0m";
                }
            }
            cout << students[y].grade << "\n";
        }
    }
}