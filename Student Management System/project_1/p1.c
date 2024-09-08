/******************************************************************************************
 File Name    : p1.c
 Author       : Rawan Mohamed Fathy
 Description  : Student Management System
 ******************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	int choice,id;
	float AverageGPA;
	/*continues loop for The menu until the user decides to exit the program*/
	while(1){
				/*to check that user choose one of the list*/
				do{
				    choice=menuOptions();
			    }while(choice < 1 || choice > 8);
			switch(choice) {

					default  :
						printf("Invalid choice.Choose from this menu.");
						break;

					case 1   :  //Add a Student
								printf("--------------------------------------------------------------------------------------------\n");
								/*struct to store information of the student and send its address to the add function*/
								struct student newStudent;
								printf("Enter Student ID:");
								scanf("%d",&newStudent.id);
								fflush(stdin);
								printf("Enter Student name:");
								gets(newStudent.name);//to take string more than 2 words
								printf("Enter Student age:");
								scanf("%d",&newStudent.age);

								printf("Enter Student GPA (0.0:4.0):");
								scanf("%f",&newStudent.gpa);
								if(newStudent.gpa >=0 && newStudent.gpa <=4)
								{
								addStudent(&newStudent); //send address to add function to add it in the linked list
								}
								else
								{
									printf("\nGPA out of range (0.0:4.0).\n");
								}
								break;

					case 2   : //Display All Students
								displayStudents();
								break;

					case 3   : //Search for a Student by ID
								printf("Enter student ID to search: ");
								scanf("%d",&id);
								searchStudentByID(id);
								break;

					case 4   : //Update Student Information
								printf("\nEnter student ID to update it's information: ");
								scanf("%d",&id);
								fflush(stdin);
								updateStudent(id);
								break;

					case 5   : //Delete a Student
								printf("\nEnter student ID to Delete it's Data : ");
								scanf("%d",&id);
								deleteStudent(id);
								break;

					case 6   : //Calculate Average GPA
								AverageGPA=calculateAverageGPA();
								printf("--------------------------------------------------------------------------------------------\n");
								printf("\nAverageGPA = %.3f\n",AverageGPA);
								break;

					case 7   : //Find Student with Highest GPA
								searchHighestGPA();
								break;

					case 8   : //Exit the program
								printf("Exiting...");
								return 0;
								break;

					}
	}
}
