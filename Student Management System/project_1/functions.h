/******************************************************************************************
 File Name    : functions.h
 Author       : Rawan Mohamed Fathy
 Description  : Student Management System
 ******************************************************************************************/

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>


struct student
{
	int id;
	char name[50];
	int age;
	float gpa;
};


struct node
{
	struct student data;
	struct node *next;
};

int  menuOptions(void);

void addStudent(const struct student *const ptr);

void displayStudents(void);
void searchHighestGPA(void);

void searchStudentByID(int id);
void updateStudent(int id);
void deleteStudent(int id);

float calculateAverageGPA(void);

#endif /* FUNCTIONS_H_ */
