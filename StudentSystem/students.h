#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

//Struct
struct Student {
    string firstName;
    string lastName;
    int id;
    double grade;
    int grades[5];
    string courses[3];
};

//Constants
const int MAX_STUDENTS = 100;
const int NUM_ASSIGNMENTS = 5;

//Function prototypes
void loadStudents(Student students[], int& count);

void CalculateAverages(Student* s, int count);

void addStudent(Student students[], int& count);
void saveStudents(Student students[], int count);

void displayStudents(Student students[], int count);

void searchByCourse(Student students[], int count);
void showAssignmentAverage(Student students[], int count);
void showHardestAssignment(Student students[], int count);
void courseEnrollment(Student students[], int count);
void atRiskStudents(Student students[], int count);

void sortByAverage(Student students[], int count);