#include "Students.h"
#include <iostream>
#include <fstream>
#include <iomanip>    // required for setw

using namespace std;

void loadStudents(StudentNode*& head)
{
    ifstream file("students.txt");
    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    // We no longer need a tail pointer tracking block here
    Student tempStudent;

    while (file >> tempStudent.firstName
        >> tempStudent.lastName
        >> tempStudent.id)
    {
        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            file >> tempStudent.assignments[j];

        file >> tempStudent.average;

        for (int j = 0; j < NUM_COURSES; j++)
            file >> tempStudent.courses[j];

        // 1. Allocate a brand new node on the heap
        StudentNode* newNode = new StudentNode();
        newNode->data = tempStudent;

        // 2. Point the new node's next to whatever the current head is pointing to
        newNode->next = head;

        // 3. Move the head pointer to point to our newly created node
        head = newNode;
    }

    file.close();
}

void calculateAllAverages(StudentNode* head) {
    StudentNode* current = head;
    while (current != nullptr){
        double total = 0;
        for (int x = 0; x < NUM_ASSIGNMENTS; x++) {
            total += current->data.assignments[x];
        }
        current->data.average = total / NUM_ASSIGNMENTS;
        current = current->next;
    }
}

// ================ DISPLAY =================
void displayStudents(StudentNode* head)
{
    cout << "\n"
        << setw(8) << "ID"
        << setw(15) << "LName"
        << setw(15) << "FName";

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        cout << setw(6) << ("A" + to_string(j + 1));

    cout << setw(8) << "AVG"
        << setw(10) << "C1"
        << setw(10) << "C2"
        << setw(10) << "C3"
        << endl;

    StudentNode* current = head;

    while (current != nullptr)
    {
        cout << setw(8) << current->data.id
            << setw(15) << current->data.lastName
            << setw(15) << current->data.firstName;

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            cout << setw(6) << current->data.assignments[j];

        cout << setw(8) << current->data.average;

        for (int j = 0; j < NUM_COURSES; j++)
            cout << setw(10) << current->data.courses[j];

        cout << endl;

        current = current->next; // move to next node
    }
}

void addStudent(StudentNode*& head) {
    StudentNode* newStudent = new StudentNode();
    cout << "What is the new student's first name: ";
    cin >> newStudent->data.firstName;
    cout << "What is the new student's last name: ";
    cin >> newStudent->data.lastName;
    cout << "What is the new student's id number: ";
    cin >> newStudent->data.id;
    for (int x = 0; x < NUM_ASSIGNMENTS; x++) {
        cout << "Add assignment #" << x + 1 << ": ";
        cin >> newStudent->data.assignments[x];
    }
    for (int y = 0; y < 3; y++) {
        cout << "Add course #" << y + 1 << ": ";
        cin >> newStudent->data.courses[y];
    }
    
    newStudent->next = head;
    head = newStudent;
    cout << "new student has been added.\n\n";
    calculateAllAverages(head);
    saveStudents(head);
    displayStudents(head);
}

void saveStudents(StudentNode* head) {
    StudentNode* current = head;
    ofstream outputFile("Students.txt");

    while (current != nullptr){
        outputFile << current->data.firstName << " " << current->data.lastName << " " << current->data.id << " ";
        for (int y = 0; y < NUM_ASSIGNMENTS; y++) {
            outputFile << current->data.assignments[y] << " ";
        }
        outputFile << current->data.average << " ";
        for (int z = 0; z < 3; z++) {
            outputFile << current->data.courses[z] << " ";
        }
        outputFile << "\n";

        current = current->next;
    }
    outputFile.close();
}

void searchByCourse(StudentNode* head) {
    StudentNode* current = head;
    string selected_course;
    cout << "What course would you like to search by: ";
    cin >> selected_course;

    while (current != nullptr){
        for (int y = 0; y < 3; y++) {
            if (current->data.courses[y] == selected_course) {
                cout << current->data.id << " " << current->data.firstName << " " << current->data.lastName << endl;
            }
        }
        current = current->next;
    }
    cout << endl;
}

void showAssignmentAverage(StudentNode* head) {
    double total=0;
    double average;
    for (int y = 0; y < 5; y++) {
        int counter = 0;
        StudentNode* current = head;
        while (current != nullptr){
            total = total + current->data.assignments[y];
            counter++;
            current = current->next;
        }
        average = total / counter;
        cout << "A" << y + 1 << ": " << average << endl;
        total = 0;
    }
    cout << endl;
}

void showHardestAssignment(StudentNode* head) {
    double averages[5];
    int total = 0;
    double lowest = 101;
    int lowest_a_num;
    for (int y = 0; y < 5; y++) {
        StudentNode* current = head;
        int counter = 0;
        while (current != nullptr){
            total = total + current->data.assignments[y];
            counter++;
            current = current->next;
        }
        averages[y] = total / counter;
        total = 0;
        if (averages[y] < lowest) {
            lowest = averages[y];
            lowest_a_num = y + 1;
        }
    }
    cout << "Hardest: A" << lowest_a_num << " (" << lowest << ")\n\n";
}

void courseEnrollment(StudentNode* head) {
    StudentNode* current = head;
    int hist = 0;
    int engl = 0;
    int math = 0;
    int csci = 0;
    int comp = 0;
    int stat = 0;
    int biol = 0;
    
    while (current != nullptr){
        for (int y = 0; y < 3; y++) {
            if (current->data.courses[y] == "HIST210") {
                hist++;
            }
            else if (current->data.courses[y] == "ENGL150") {
                engl++;
            }
            else if (current->data.courses[y] == "MATH102") {
                math++;
            }
            else if (current->data.courses[y] == "CSCI101") {
                csci++;
            }
            else if (current->data.courses[y] == "COMP220") {
                comp++;
            }
            else if (current->data.courses[y] == "STAT110") {
                stat++;
            }
            else{
                biol++;
            }
        }
        current = current->next;
    }
    cout << "HIST210: " << hist << endl;
    cout << "ENGL150: " << engl << endl;
    cout << "MATH102: " << math << endl;
    cout << "CSCI101: " << csci << endl;
    cout << "COMP220: " << comp << endl;
    cout << "STAT110: " << stat << endl;
    cout << "BIOL120: " << biol << endl << endl;
}

void atRiskStudents(StudentNode* head) {
    StudentNode* current = head;
    bool assignment_failed;
    while (current != nullptr) {
        assignment_failed = false;
        for (int y = 0; y < 5; y++) {
            if (current->data.assignments[y] < 50) {
                assignment_failed = true;
            }
        }
        if (assignment_failed == true && current->data.average < 60 && current->data.average > 49) {
            cout << current->data.id << " " << current->data.firstName << " " << current->data.lastName << endl;
        }    
        current = current->next;
    }
    cout << endl;
}

void sortByAverage(StudentNode* head) {
    StudentNode* current = head;
    while (current != nullptr) {
        StudentNode* smallest = current;
        StudentNode* nextNode = current->next;
        while (nextNode != nullptr) {
            if (nextNode->data.average > smallest->data.average) {
                smallest = nextNode;
            }
            nextNode = nextNode->next;
        }
        swap(current->data, smallest->data);
        current = current->next;
    }
    displayStudents(head);
}

void deleteList(StudentNode*& head) {
    StudentNode* current = head;

    while (current != nullptr) {
        StudentNode* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}

