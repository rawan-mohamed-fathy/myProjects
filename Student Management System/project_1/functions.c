#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "functions.h"

struct node *head = NULL;
/************************************************************************************
 * Function Name   : menuOptions
 * Function Inputs : void
 * Description     : Function to print menu options.
 ************************************************************************************/
int menuOptions(void)
{
	/*to display the menu and get the choice from user*/
	int choice;
	printf("--------------------------------------------------------------------------------------------\n");
	printf("1. Add a Student\n");
	printf("2. Display All Students\n");
	printf("3. Search for a Student by ID\n");
	printf("4. Update Student Information\n");
	printf("5. Delete a Student\n");
	printf("6. Calculate Average GPA\n");
	printf("7. Find Student with Highest GPA\n");
	printf("8. Exit\n");
	printf("\n");
	printf("Enter choice:");
	scanf("%d",&choice);
	printf("\n");

	return choice;
}

/************************************************************************************
 * Function Name   : addStudent
 * Function Inputs : const struct student *const ptr
 * Description     : Function to collect new student details
 *	 	 	 	 	 from the user and adds them to the student
 *	 	 	 	 	 linked list.
 ************************************************************************************/
void addStudent(const struct student *const ptr)
{

	 // Check if ID already exists
	    struct node *check_id = head;
	    /*loop to the end of the linked list*/
	    while (check_id != NULL) {
	        if (check_id->data.id == ptr->id) {
	        	printf("--------------------------------------------------------------------------------------------\n");
	            printf("Error: This ID is already reserved.\n");
	            return;
	        }
	        check_id = check_id->next;
	    }
	    //the id is not present before so create the new node
	    //create a new node
	   struct node *link = (struct node*) malloc(sizeof(struct node));
	   //check if the node is created or not
	   assert(link != NULL);
	   //store data in the node
	   link->data = *ptr;

	   //point the next pointer to the old head node //insert first
	   link->next = head;

	   //point the head to the new first node
	   head = link;
}

/************************************************************************************
 * Function Name   : displayStudents
 * Function Inputs : void
 * Description     : Function to display the details of all
 *	 	 	 	 	 students currently in the system.
 ************************************************************************************/
void displayStudents(void)
{
	   struct node *ptr = head;
	   //check if the linked list is empty or not
	   if(ptr == NULL)
	   {
		   printf("--------------------------------------------------------------------------------------------\n");
		   printf("No students are present in Linked list.\n");
	   }
	   else{
		   printf("--------------------------------------------------------------------------------------------\n");
		   //start looping from the head until the last node and display the information
		   while(ptr != NULL)
		   {
			 printf("[ ID: %d , Name: %s , Age: %d , GPA: %.2f]\n",ptr->data.id,ptr->data.name,ptr->data.age,ptr->data.gpa);
			 ptr = ptr->next;
		   }
	   }
}

/************************************************************************************
 * Function Name   : searchStudentByID
 * Function Inputs : int id
 * Description     : Function to search for a student by their
 * 					 ID and display their details if found.
 ************************************************************************************/
void searchStudentByID(int id)
{

	// pointer to loop in linked list
		struct node *current = NULL;
		//check if the linked list is empty or not
		if(head==NULL)
		{
			 printf("--------------------------------------------------------------------------------------------\n");
			 printf("Linked List is empty.\n");
			 return;
		}

		// start checking from the first node to the end of the linked list
		current = head;
		while(current != NULL)
		{
			if(current->data.id == id)
			{
				printf("--------------------------------------------------------------------------------------------\n");
				printf("[ ID: %d , Name: %s , Age: %d , GPA: %.2f]\n",current->data.id,current->data.name,current->data.age,current->data.gpa);
				return;
			}
			current = current->next;
		}
		// item not found in the list
		printf("--------------------------------------------------------------------------------------------\n");
		printf("Student with ID %d not found.\n",id);
}

/************************************************************************************
 * Function Name   : updateStudent
 * Function Inputs : int id
 * Description     : Function to update the details of
 * 					 a student with the given ID.
 ************************************************************************************/

void updateStudent(int id)
{

	struct node *current = NULL;
	//check if the linked list is empty or not
		if(head==NULL)
		{
			 printf("--------------------------------------------------------------------------------------------\n");
			 printf("Linked List is empty.\n");
			 return;
		}

		// start checking from the first node
		current = head;
		while(current != NULL)
		{
			if(current->data.id == id)
			{
				//the id is found
				printf("--------------------------------------------------------------------------------------------\n");
				printf("\nEnter new details for the student with ID %d : \n",id);
				printf("Enter New Student name:");
				//scanf("%s",current->data.name);
				gets(current->data.name);
				printf("Enter New Student age:");
				scanf("%d",&current->data.age);

				printf("Enter New Student GPA (0.0:4.0):");
				scanf("%f",&current->data.gpa);
				if(current->data.gpa >=0 && current->data.gpa<=4)
				{
					printf("--------------------------------------------------------------------------------------------\n");
					printf("Update successful!\n");
					return;
				}
				else
				{
					printf("\nGPA out of range (0.0:4.0).\n");
					return;
				}
			}
			current = current->next;
		}
		// item not found in the list
		printf("--------------------------------------------------------------------------------------------\n");
		printf("Student was not found.\n");
}

/************************************************************************************
 * Function Name   : calculateAverageGPA
 * Function Inputs : void
 * Description     : Function to calculate and return
 * 					 the average GPA of all students.
 ************************************************************************************/

float calculateAverageGPA(void)
{
		float avgGPA=0.0 , sumGPA=0.0;
		int numberOfStudents=0; //count

		struct node *current = NULL;
		//check if the linked list is empty or not
		if(head==NULL)
		{
			 return 0.0;
		}
		//start looping from head
		current = head;
		numberOfStudents=1; //increase number of student to calculate the size of the linked list

		while(current != NULL)
		{
			sumGPA = sumGPA + current->data.gpa;
			current = current->next;
			numberOfStudents++;//calculate the size of the linked list
		}
		numberOfStudents--;    //to get the actual size as condition check to the end of the linked list to get the all GPA
		avgGPA = (sumGPA/numberOfStudents);
		return avgGPA;
}

/************************************************************************************
 * Function Name   : searchHighestGPA
 * Function Inputs : void
 * Description     : Function to find and display
 * 					 the student with the highest GPA..
 ************************************************************************************/

void searchHighestGPA(void)
{
		struct node *current = NULL;

	//check if the linked list is empty
		if(head==NULL)
		{
			 printf("--------------------------------------------------------------------------------------------\n");
			 printf("Linked List is empty.\n");
			 return;
		}

		else{
			 current = head; //start loop from head
			 struct student maxGPA = current->data; // make new struct to store the all maxGPA information to print it

			 while (current != NULL) {
				 if (current->data.gpa > maxGPA.gpa) { //compare the GPA to get the max value
					maxGPA = current->data;
				 }
				 current = current->next;
			 }
			 //display the information
			 printf("--------------------------------------------------------------------------------------------\n");
			 printf("Student with highest GPA:\n");
			 printf("[ ID: %d , Name: %s , Age: %d , GPA: %.2f]\n",maxGPA.id, maxGPA.name, maxGPA.age, maxGPA.gpa);
		}
}

/************************************************************************************
 * Function Name   : deleteStudent
 * Function Inputs : int id
 * Description     : Function to delete a student
 * 					 from the linked list by their ID.
 ************************************************************************************/

void deleteStudent(int id)
{
		// pointer to loop in linked list
		struct node *current = NULL;
		struct node *prev = NULL;

		// pointer to point the node that will be deleted
		struct node * delete_node = NULL;

		//check if the linked list is empty
		if(head==NULL)
		{
			printf("--------------------------------------------------------------------------------------------\n");
			printf("Linked List is empty.\n");
			return;
		}

		//check the first node in the linked list
		else if(head->data.id == id)
		{
			delete_node = head;
			// move head to next node
			head = head->next;
			printf("--------------------------------------------------------------------------------------------\n");
			printf("Student with ID %d deleted Successfully.\n", id);
			free(delete_node);
			return;
		}

		else
		{
			//check the rest of nodes in the linked list
			current = head->next;
			prev = head;
			while(current != NULL)
			{
				if(current->data.id == id)
				{
					//element found
					delete_node = current;
					prev->next = current->next;
					printf("--------------------------------------------------------------------------------------------\n");
					printf("Student with ID %d deleted Successfully.\n", id);
					free(delete_node);
					return;
				}
				prev = current;
				current = current->next;
			}

			//in case the data not found in the linked list
			if(delete_node == NULL)
			{
				printf("--------------------------------------------------------------------------------------------\n");
				printf("Student with ID %d not found in the List.\n",id);
			}
		}
}


