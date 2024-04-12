#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
int size = 0;
int ch;
struct patient_record
{
char fname[30];
char lname[30];
char address[50];
char disease_descriptio[50];
char sex;
int age;
int service;
} x[100];
//functions declaration.
void add();
void search();
void edit();
void list();
void delt();
void exit(int);
void gotoxy(int x, int y);
void draw_box(void);
int checkForNumber(char s[]);
int main()
{
    system("color F1");
int pos = 1;

char ch;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);




printf("\n\n\n\n\n\n\t\t\t\t#########################################\n\t\t\t\t#\t\tWELCOME TO\t\t#\n\t\t\t\t# OUR HOSPITAL MANAGEMENT SYSTEM\t#\n\t\t\t\t#########################################\n\n\n\npress any key to continue........");
getch();
system("cls");
char n[10], p[10], s;
int c;
do {

system("cls");
printf("\n\n\t\t\t\t*\n\t\t\t\t\t OUR HOSPITAL\n\t\t\t\t*");
printf("\n\n\n\t\t\t\tEnter your Username and pasword :)\n\n\t\t\t\t\tUsername:");
scanf("%s", &n);
printf("\n\t\t\t\t\tPassword:");
scanf("%s", &p);
if (((strcmp(n, "username")) || (strcmp(p, "password"))) != 0)
{
printf("\n your Password or Username is wrong\n Do you want to try again?[Y/N]");
scanf("%s", &s);
}
else
{
printf("\n\t\t\t\t\t....login successfull....");
getch();
system("cls");
draw_box();
do {
SetConsoleTextAttribute(console, 15);
gotoxy(40, 11);printf("1)Add a new patient. ");
gotoxy(40, 12);printf("2)search patient record. ");
gotoxy(40, 13);printf("3)search and edit records ");
gotoxy(40, 14);printf("4)list of patients. ");
gotoxy(40, 15);printf("5)delete patient record. ");
gotoxy(40, 16);printf("6)exit. ");
printf("\n");


switch (pos)
{
case(1):
SetConsoleTextAttribute(console, 240);
gotoxy(40, 11);printf("1)Add a new patient. ");
break;
case(2):
SetConsoleTextAttribute(console, 240);
gotoxy(40, 12);printf("2)search patient record. ");
break;
case(3):
SetConsoleTextAttribute(console, 240);
gotoxy(40, 13);printf("3)search and edit records ");
break;
case(4):
SetConsoleTextAttribute(console, 240);
gotoxy(40, 14);printf("4)list of patients. ");
break;
case(5):
SetConsoleTextAttribute(console, 240);
gotoxy(40, 15);printf("5)delete patient record. ");
break;
case(6):
SetConsoleTextAttribute(console, 240);
gotoxy(40, 16);printf("6)exit. ");
break;
}
ch = getch();
if (ch == -32)ch = getch();
if (ch == 72)
{
pos--;

if (pos == 0)pos = 6;

}
if (ch == 80)
{
pos++;
if (pos == 7)pos = 1;

}
if (ch == 13)
{
switch (pos)
{
case(1):
SetConsoleTextAttribute(console, 15);
system("cls");
add();
break;
case(2):
SetConsoleTextAttribute(console, 15);
system("cls");
search();

break;
case(3):
SetConsoleTextAttribute(console, 15);
system("cls");
edit();
break;


break;
case(4):
SetConsoleTextAttribute(console, 15);
system("cls");
list();
break;
case(5):
SetConsoleTextAttribute(console, 15);
system("cls");
delt();

break;
case(6):
SetConsoleTextAttribute(console, 15);
system("cls");
printf("\n\n\n\n\n\n\t\t\t\t#########################################\n\t\t\t\t#\t\t \t\t#\n \t\t\t\t# THANK YOU FOR VISITING \t \t#\n\t\t\t\t#########################################\n\n\n\npress any key to continue........");
exit(1);
break;
}
}


} while (1);

}
}while (s=='y'||s=='Y');






}
void add()
{
int check = 0;
int ch;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
do {
system("cls");
gotoxy(39,1);
printf("####.Add Patients Record.###\n");
do
{
printf("\n\n\t\tFirst Name: ");
fflush(stdin);
gets(x[size].fname);
if (strlen(x[size].fname) > 2 && strlen(x[size].fname) < 30&&checkForNumber(x[size].fname))
check = 1;
if (check == 1)
break;
else
printf("\n\n\t\t wrong entry first name must be more than two character and less than 30 character");
} while (1);
do
{
printf("\n\n\t\tLast Name: ");
fflush(stdin);
gets(x[size].lname);
if (strlen(x[size].lname) > 2 && strlen(x[size].lname) < 30&&checkForNumber(x[size].lname))
check = 2;
if (check == 2)
break;
else
printf("\n\n\t\t wrong entry last name must be more than two character and less than 30 character");

} while (1);
do
{
printf("\n\n\t\tGender[F/M]: ");
scanf("%s", &x[size].sex);
if ((x[size].sex == 'F' || x[size].sex == 'f') || (x[size].sex == 'm' || x[size].sex == 'M'))
check = 3;
if (check == 3)
break;
else
printf("\n\n\t\t\t\t invalid character f or F or m or M");

} while (1);

while(1){
printf("\n\n\t\tAge: ");
int temp = 0;
scanf("%d",&temp);
fflush(stdin);
if(temp>0&&temp<120){
x[size].age=temp;
break;}
}
do
{
printf("\n\n\t\tADDRESS: ");
fflush (stdin);
gets(x[size].address);
if (strlen(x[size].address) > 2 && strlen(x[size].address) < 50)
check = 4;
if (check == 4)
break;
else
printf("\n\n\t\t wrong entry address must be more than two character and less than 50 character");

} while (1);
int r=1;
while (r){
r=0;
printf("\n\n\t\tchoose your service as a number:\n\n\t\t1)Neurologist 2)Psychiatrist 3)Surgeon 4)Internist:");
scanf("%d", &x[size].service);
switch (x[size].service)
{
case 1:
printf("\n\n\t\tNeurologist");
break;
case 2:
printf("\n\n\t\tPsychiatrist");
break;
case 3:
printf("\n\n\t\tSurgeon");
break;
case 4:
printf("\n\n\t\tInternist");
break;
default:
printf("enter choice");
r=1;
break;
}}

do
{
printf("\n\n\t\tdisease description: ");
fflush(stdin);
gets(x[size].disease_descriptio);
if (strlen(x[size].disease_descriptio) > 2 && strlen(x[size].disease_descriptio) < 50)
check = 5;
if (check == 5)
break;
else
printf("\n\n\t\t wrong entry disease description must be more than two character and less than 50 character");

} while (1);
printf("\n\n\t\tyour room number is %d",room(size));
size++;
printf("\n\n\t\t\t\t information record succesfull\n");
printf("\n\n\t\t\t\t do you want add another record[y/N]?");
scanf("%s", &ch);
if (ch == 'n' || ch == 'N')
{
SetConsoleTextAttribute(console, 15);
system("cls");
draw_box();

}


} while ((ch == 'y') || (ch == 'Y'));


}
void list()
{
int i;
int ch;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);


do {
system("cls");
gotoxy(43, 0);
printf("##List Record Of Patients##\n\n\n\n");
printf(" the existing record\n\n\n ");
printf("FIRST_NAME LAST_NAME GENDER AGE ADDRESS SERVICE Disease_Description ROOM_NUMBER\n");
printf("--------------------------------------------------------------------------------------------------------------------\n");

for (i = 0;i < size;i++)
{
printf(" %s %s %c %d %s %d %s %d", x[i].fname, x[i].lname, x[i].sex, x[i].age, x[i].address, x[i].service, x[i].disease_descriptio, room(i));
printf("\n");

}
printf("\n\n\t\t\t\t do you want return to menu [y/N]?");
scanf("%s", &ch);
if (ch == 'y' || ch == 'Y')
{

SetConsoleTextAttribute(console, 15);
system("cls");
draw_box();
}
} while (ch == 'n' || ch == 'N');

}
void search(void)
{
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
char patient[30];
int i, ch, check = 0;
do
{
system("cls");
gotoxy(43, 0);
printf("------- search of patient record -------");
printf("\n\n\n enter the name to be viewed: ");
scanf("%s", &patient);
for (i = 0;i < size;i++) {
if (strcmp(patient, x[i].fname) == 0)
{
check = 1;
break;
}
}
if (check == 0)
printf("\n\n\n patient not found");
else
{ printf("\n\n\n the existing record\n\n\n ");
printf(" FIRST_NAME LAST_NAME GENDER AGE ADDRESS SERVICE Disease_Description ROOM_NUMBER\n");
printf("--------------------------------------------------------------------------------------------------------------------\n");
printf(" %s %s %c %d %s %d %s %d", x[i].fname, x[i].lname, x[i].sex, x[i].age, x[i].address, x[i].service, x[i].disease_descriptio, room(i));
}
printf("\n\n\n do you search about another record[y/N]?");
scanf("%s", &ch);
if (ch == 'n' || ch == 'N')
{

SetConsoleTextAttribute(console, 15);
system("cls");
draw_box();

}
} while ((ch == 'y') || (ch == 'Y'));



}
void edit(void)
{
int agentId ;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
char patient[30], update;
int i, ch, check = 0;
do
{
system("cls");
gotoxy(43, 0);
printf("------- edit of patient record -------");
printf("\n\n\n enter the name to be edited: ");
scanf("%s", &patient);
for (i = 0;i < 100;i++) {
if (strcmp(patient, x[i].fname) == 0)
{
check = 1;
agentId = i;
break;
}
}
if (check == 0)
printf("\n\n\n patient not found");
else
{
do
{
printf("\n\n\n");
gotoxy(43, 0);
printf("\n\n\n the existing record\n\n\n ");
printf(" FIRST_NAME LAST_NAME GENDER AGE ADDRESS SERVICE Disease_Description ROOM_NUMBER\n");
printf("-------------------------------------------------------------------------------------------------------------------\n");
printf(" %s %s %c %d %s %d %s %d", x[i].fname, x[i].lname, x[i].sex, x[i].age, x[i].address, x[i].service, x[i].disease_descriptio, room(i));

do
{
printf("\n\n\t\t\t\tFirst Name: ");
fflush(stdin);
gets(x[agentId].fname);
if (strlen(x[agentId].fname) > 2 && strlen(x[agentId].fname) < 30)
check = 1;
if (check == 1)
break;
else
printf("\n\n\t\t wrong entry first name must be more than two character and less than 30 character");
} while (1);
do
{
printf("\n\n\t\t\t\tLast Name: ");
fflush(stdin);
gets(x[agentId].lname);
if (strlen(x[agentId].lname) > 2 && strlen(x[agentId].lname) < 30)
check = 2;
if (check == 2)
break;
else
printf("\n\n\t\t wrong entry last name must be more than two character and less than 30 character");

} while (1);
do
{
printf("\n\n\t\t\t\t Gender[F/M]: ");
scanf("%s", &x[agentId].sex);
if ((x[agentId].sex == 'F' || x[agentId].sex == 'f') || (x[agentId].sex == 'm' || x[agentId].sex == 'M'))
check = 3;
if (check == 3)
break;
else
printf("\n\n\t\t\t\t invalid character");

} while (1);

while(1){
printf("\n\n\t\tAge: ");
int temp = 0;
scanf("%d",&temp);
fflush(stdin);
if(temp>0&&temp<120){
x[agentId].age=temp;
break;}
}

do
{
printf("\n\n\t\t\t\t ADDRESS: ");
fflush(stdin);
gets(x[agentId].address);
if (strlen(x[agentId].address) > 2 && strlen(x[agentId].address) < 50)
check = 4;
if (check == 4)
break;
else
printf("\n\n\t\t wrong entry address must be more than two character and less than 50 character");

} while (1);

int r=1;
while (r){
r=0;
printf("\n\n\t\tchoose your service as a number:\n\n\t\t1)Neurologist 2)Psychiatrist 3)Surgeon 4)Internist:");
scanf("%d", &x[size].service);
switch (x[size].service)
{
case 1:
printf("\n\n\t\tNeurologist");
break;
case 2:
printf("\n\n\t\tPsychiatrist");
break;
case 3:
printf("\n\n\t\tSurgeon");
break;
case 4:
printf("\n\n\t\tInternist");
break;
default:
printf("enter choice");
r=1;
break;
}}


do
{
printf("\n\n\t\t\t\t disease description: ");
fflush(stdin);
gets(x[agentId].disease_descriptio);
if (strlen(x[agentId].disease_descriptio) > 2 && strlen(x[agentId].disease_descriptio) < 50)
check = 5;
if (check == 5)
break;
else
printf("\n\n\t\t wrong entry disease description must be more than two character and less than 50 character");

} while (1);
printf("\n press U character for the updating operation :");
scanf("%s", &update);

} while (update != 'u' && update != 'U');
//size ++;
printf("\n\t\t\t\t\t patient record updated successfully .....");
}
// printf("\n\t\t\t\t\t patient record updated successfully .....");
printf("\n\n\n do you edited another record[y/N]?");
scanf("%s", &ch);
if (ch == 'n' || ch == 'N')
SetConsoleTextAttribute(console, 15);
system("cls");
draw_box();
} while ((ch == 'y') || (ch == 'Y'));

}

void delt(void)
{
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
char patient[30];
int i, ch, check = 0;
do
{
system("cls");
gotoxy(43, 0);
printf("------- search of patient record -------");
printf("\n\n\n enter the name to be viewed: ");
scanf("%s", &patient);
for (i = 0;i < size;++i) {
if (strcmp(x[i].fname, patient) == 0)
{
size--;
check = 1;
break;
}

}

if (check == 1)
{
for (;i < size;i++)
{
strcpy(x[i].fname, x[i + 1].fname);
strcpy(x[i].lname, x[i + 1].lname);
x[i].sex = x[i + 1].sex;
x[i].age = x[i + 1].age;
strcpy(x[i].address, x[i + 1].address);
x[i].service = x[i + 1].service;
strcpy(x[i].disease_descriptio, x[i + 1].disease_descriptio);
}
printf("\n\n\t\t .....deleting is done.....\n\n");
}
else
printf("\n\n\t\t not found \n\n");
printf("\n\n\n do you try again [y/N]?");
scanf("%s", &ch);
if (ch == 'n' || ch == 'N')
{
SetConsoleTextAttribute(console, 15);
system("cls");
draw_box();

}
} while ((ch == 'y') || (ch == 'Y'));


}

void gotoxy(int x, int y)
{
COORD coord = { 0,0 };
coord.X = x;
coord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void draw_box(void)
{
int i;
gotoxy(39, 10);
printf("%c", 201);
for (i = 1;i < 33;i++)
{
printf("%c", 205);
}
printf("%c", 187);
gotoxy(39, 11);
printf("%c", 186);
for (i = 1;i < 33;i++)
{
printf("%c", 32);
}
printf("%c", 186);

gotoxy(39, 12);
printf("%c", 186);
for (i = 1;i < 33;i++)
{
printf("%c", 32);
}
printf("%c", 186);

gotoxy(39, 13);
printf("%c", 186);
for (i = 1;i < 33;i++)
{
printf("%c", 32);
}
printf("%c", 186);

gotoxy(39, 14);
printf("%c", 186);
for (i = 1;i < 33;i++)
{
printf("%c", 32);
}
printf("%c", 186);

gotoxy(39, 15);
printf("%c", 186);
for (i = 1;i < 33;i++)
{
printf("%c", 32);
}
printf("%c", 186);
gotoxy(39, 16);
printf("%c", 186);
for (i = 1;i < 33;i++)
{
printf("%c", 32);
}
printf("%c", 186);

gotoxy(39, 17);
printf("%c", 200);
for (i = 1;i < 33;i++)
{
printf("%c", 205);
}
printf("%c", 188);



}
int room (int size)
{
int j;
j=size+1;
return(j);
}
int checkForNumber(char s[]){
for(int i=0;s[i]!='\0';i++)
{
if(s[i]=='0'||s[i]=='1'||s[i]=='2'||s[i]=='3'||s[i]=='5'||s[i]=='6'||s[i]=='7'||s[i]=='8'||s[i]=='9')
{
return 0;
}



}
return 1;

}
