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
};

//Constants
const int MAX_STUDENTS = 23;
const int NUM_ASSIGNMENTS = 5;

//Function prototypes
void loadStudents(Student students[], int& count);
void displayAllStudentInfo(double grades[][NUM_ASSIGNMENTS], Student students[], int count);

void generateGrades(double grades[][NUM_ASSIGNMENTS], int count);
void CalculateAverages(double grades[][NUM_ASSIGNMENTS], Student students[], int count);

void updateAssignment(double grades[][NUM_ASSIGNMENTS], Student students[], int count);
void addStudent(Student students[], int& count, double grades[][NUM_ASSIGNMENTS]);
void saveStudents(Student students[], int count);

void highlightSearch(double grades[][NUM_ASSIGNMENTS], Student students[], int count);
