#include "students.h"
void loadStudents(Student students[], int& count) {
    cout << "Loading students...\n";
    ifstream inputFile("Students.txt");

    if (!inputFile) {
        cout << "ERROR: file not found!\n";
        return;
    }
    while (inputFile >> students[count].firstName >> students[count].lastName >> students[count].id) {
        for (int x = 0; x < 5; x++) {
            inputFile >> students[count].grades[x];
        }
        inputFile >> students[count].grade;
        for (int y = 0; y < 3; y++) {
            inputFile >> students[count].courses[y];
        }
        count = count + 1;
    }
}

void CalculateAverages(Student* s, int count) {
    double total;
    for (int y = 0; y < count; y++) {
        total = 0;
        for (int x = 0; x < NUM_ASSIGNMENTS; x++) {
            total = total + (s + y)->grades[x];
        }
        (s+y)->grade = total / NUM_ASSIGNMENTS;
    }
}

// ================= DISPLAY =================
void displayStudents(Student students[], int count)
{
    cout << "\nID\tLName\t\tFName\t\t";

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        cout << "A" << j + 1 << "\t";

    cout << "AVG\tC1\tC2\tC3\n";

    for (int i = 0; i < count; i++)
    {
        cout << students[i].id << "\t"
            << students[i].lastName << "      \t"
            << students[i].firstName << "      \t";

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            cout << students[i].grades[j] << "\t";

        cout << students[i].grade << "\t";

        for (int j = 0; j < 3; j++)
            cout << students[i].courses[j] << "\t";

        cout << endl;
    }
}

void addStudent(Student students[], int& count) {
    cout << "What is the new student's first name: ";
    cin >> students[count].firstName;
    cout << "What is the new student's last name: ";
    cin >> students[count].lastName;
    cout << "What is the new student's id number: ";
    cin >> students[count].id;
    for (int x = 0; x < NUM_ASSIGNMENTS; x++) {
        cout << "Add assignment #" << x + 1 << ": ";
        cin >> students[count].grades[x];
    }
    for (int y = 0; y < 3; y++) {
        cout << "Add course #" << y + 1 << ": ";
        cin >> students[count].courses[y];
    }
    cout << "new student has been added.\n\n";
    count++;
    CalculateAverages(students, count);
    saveStudents(students, count);
    displayStudents(students, count);
}

void saveStudents(Student students[], int count) {
    ofstream outputFile("Students.txt");

    for (int x = 0; x < count; x++) {
        outputFile << students[x].firstName << " " << students[x].lastName << " " << students[x].id << " ";
        for (int y = 0; y < NUM_ASSIGNMENTS; y++) {
            outputFile << students[x].grades[y] << " ";
        }
        outputFile << students[x].grade << " ";
        for (int z = 0; z < 3; z++) {
            outputFile << students[x].courses[z] << " ";
        }
        outputFile << "\n";
    }
}

void searchByCourse(Student students[], int count) {
    string selected_course;
    cout << "What course would you like to search by: ";
    cin >> selected_course;

    for (int x = 0; x < count; x++) {
        for (int y = 0; y < 3; y++) {
            if (students[x].courses[y] == selected_course) {
                cout << students[x].id << " " << students[x].firstName << " " << students[x].lastName << endl;
            }
        }
    }
    cout << endl;
}

void showAssignmentAverage(Student students[], int count) {
    int total=0;
    double average;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < count; x++) {
            total = total + students[x].grades[y];
        }
        average = total / count;
        cout << "A" << y + 1 << ": " << average << endl;
        total = 0;
    }
    cout << endl;
}

void showHardestAssignment(Student students[], int count) {
    double averages[5];
    int total = 0;
    double lowest = 101;
    int lowest_a_num;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < count; x++) {
            total = total + students[x].grades[y];
        }
        averages[y] = total / count;
        total = 0;
        if (averages[y] < lowest) {
            lowest = averages[y];
            lowest_a_num = y + 1;
        }
    }
    cout << "Hardest: A" << lowest_a_num << " (" << lowest << ")\n\n";
}

void courseEnrollment(Student students[], int count) {
    int hist = 0;
    int engl = 0;
    int math = 0;
    int csci = 0;
    int comp = 0;
    int stat = 0;
    int biol = 0;
    
    for (int x = 0; x < count; x++) {
        for (int y = 0; y < 3; y++) {
            if (students[x].courses[y] == "HIST210") {
                hist++;
            }
            else if (students[x].courses[y] == "ENGL150") {
                engl++;
            }
            else if (students[x].courses[y] == "MATH102") {
                math++;
            }
            else if (students[x].courses[y] == "CSCI101") {
                csci++;
            }
            else if (students[x].courses[y] == "COMP220") {
                comp++;
            }
            else if (students[x].courses[y] == "STAT110") {
                stat++;
            }
            else{
                biol++;
            }
        }
    }
    cout << "HIST210: " << hist << endl;
    cout << "ENGL150: " << engl << endl;
    cout << "MATH102: " << math << endl;
    cout << "CSCI101: " << csci << endl;
    cout << "COMP220: " << comp << endl;
    cout << "STAT110: " << stat << endl;
    cout << "BIOL120: " << biol << endl << endl;
}

void atRiskStudents(Student students[], int count) {
    bool assignment_failed;
    for (int x = 0; x < count; x++) {
        assignment_failed = false;
        for (int y = 0; y < 5; y++) {
            if (students[x].grades[y] < 50) {
                assignment_failed = true;
            }
        }
        if (assignment_failed == true && students[x].grade < 60 && students[x].grade > 49) {
            cout << students[x].id << " " << students[x].firstName << " " << students[x].lastName << endl;
        }    
    }
    cout << endl;
}

void sortByAverage(Student students[], int count) {
    int smallest;
    for (int x = 0; x < count; x++) {
        smallest = x;
        for (int y = x + 1; y < count; y++) {
            if (students[y].grade > students[smallest].grade) {
                smallest = y;
            }
        }
        swap(students[x], students[smallest]);
    }
    displayStudents(students, count);
}

