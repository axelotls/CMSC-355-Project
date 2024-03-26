#define _GNU_SOURCE		//strcasestr is a nonstandard GNU extension, 
//we need this line while serching for matching last name
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p2-support.h"
#include <ctype.h>

dataBase_ptr db;
void create_record (char ID[], char first_name[], char last_name[], char email[],
		double salary, struct date hire_date, dataBase_ptr db)// specify parameters. Clues are in the initalize function.
{
	//define function. Clues are in the initalize function
	//do not forget to increase total number of employees in the database
	// Create a new employee record in the database
	strcpy(db->emp[db->total].ID, ID);
	strcpy(db->emp[db->total].first_name, first_name);
	strcpy(db->emp[db->total].last_name, last_name);
	strcpy(db->emp[db->total].email, email);
	db->emp[db->total].salary = salary;
	db->emp[db->total].hire_date = hire_date;

	// Increment the total count of employees
	db->total++;

}



void print_title ()// you can keep this fuction or remove if needed
{
	printf ("No. ID    Name          Email        Salary     Hire Date\n");
	printf ("--- ----- ------------- ------------ ---------- --/--/----\n");

}
void display (dataBase_ptr db) {
	char combinedName[14];
	print_title ();	
	for (int i = 0; i < db->total; i++)
	{
		snprintf(combinedName, (unsigned)sizeof(combinedName), "%s %s", db->emp[i].first_name, db->emp[i].last_name);
		printf("%-3d %5s %-13.13s %-13.12s$%9.2lf %02d/%02d/%4d\n",
				i,
				db->emp[i].ID,
				combinedName,
				db->emp[i].email,
				db->emp[i].salary,
				db->emp[i].hire_date.month,
				db->emp[i].hire_date.day,
				db->emp[i].hire_date.year);


	}
}
//fix save function. Save array into file: database_updated in the same format with the 
//database file.
void save (dataBase_ptr db)// this function is for saving the database into a text file
{
	FILE *dbfu;
	dbfu = fopen ("database_updated", "w");//open an Std IO file to write into
	if (dbfu == NULL)
	{
		printf ("File cannot be created");
		return;
	}
	for (int i = 0; i < db->total; i++)
	{
		fprintf (dbfu, "%s %s %s %s %.2lf %d/%d/%d\n",
				db->emp[i].ID,
				db->emp[i].first_name,
				db->emp[i].last_name,
				db->emp[i].email,
				db->emp[i].salary,
				db->emp[i].hire_date.month,
				db->emp[i].hire_date.day,
				db->emp[i].hire_date.year);


	}
	fclose (dbfu);//close file after writing
	return;

}
int IDcompare (const void * a, const void * b) {
	const employee *employeeA = (const employee *)a;
	const employee *employeeB = (const employee *)b;

	return strcmp(employeeA->ID, employeeB->ID);
}
void IDsort (dataBase_ptr db) {
	qsort(db->emp, db->total, sizeof(employee), IDcompare);
}

int dateCompare (const void * a, const void * b) {
	const employee *employeeA = (const employee *)a;
	const employee *employeeB = (const employee *)b;	


	if (employeeA->hire_date.year < employeeB->hire_date.year) {
		return -1;
	}
	else if(employeeA->hire_date.year > employeeB->hire_date.year) {
		return 1;
	}
	else {
		if (employeeA->hire_date.month < employeeB->hire_date.month) {
			return -1;
		} else if (employeeA->hire_date.month > employeeB->hire_date.month) {
			return 1;
		}
		else {
			if (employeeA->hire_date.day < employeeB->hire_date.day) {
				return -1;
			} else if (employeeA->hire_date.day > employeeB->hire_date.day) {
				return 1;
			}
			else {
				return 0;
			}
		}
	}
}

void dateSort (dataBase_ptr db) {
	qsort(db->emp, db->total, sizeof(employee), dateCompare);
}

int IDsearch(dataBase_ptr db, char id[]) {
	char combinedName[14] = {'\0'};
	print_title();

	char IDtrim[6]; // Increase the size to accommodate the formatted ID
	int count = strlen(id);

	if (count <= 5) {
		int numZeros = 5 - count;
		for (int i = 0; i < numZeros; i++) {
			IDtrim[i] = '0';
		}
		for (int i = 0; i < count; i++) {
			IDtrim[numZeros + i] = id[i];
		}
		IDtrim[5] = '\0';

		for (int i = 0; i < db->total; i++) {
			if ((strcmp(db->emp[i].ID,IDtrim) == 0)) {
				snprintf(combinedName,  (unsigned)sizeof(combinedName), "%s %s", db->emp[i].first_name, db->emp[i].last_name);
				printf("%-3d %5s %-13.13s %-13.12s$%9.2lf %02d/%02d/%4d\n",
						i,
						db->emp[i].ID,
						combinedName,
						db->emp[i].email,
						db->emp[i].salary,
						db->emp[i].hire_date.month,
						db->emp[i].hire_date.day,
						db->emp[i].hire_date.year);
				return i;
			}
		}
	}
	if (combinedName[0] == '\0') {
		printf("None");
	}
	return -1;

}


void NameSearch(dataBase_ptr db, char name[]) {
	char combinedName[14] = {'\0'};
	char lastNameLower[14];
	print_title();

	for (int i = 0; i < strlen(name); i++) {
		name[i] = tolower((unsigned char)name[i]);
	}

	for (int i = 0; i < db->total; i++) {
		strcpy(lastNameLower, db->emp[i].last_name);


		for (int j = 0; j < strlen(lastNameLower); j++) {
			lastNameLower[j] = tolower((unsigned char)lastNameLower[j]);
		}


		if ((strstr(lastNameLower, name) != NULL)) {
			snprintf(combinedName,  (unsigned)sizeof(combinedName), "%s %s", db->emp[i].first_name, db->emp[i].last_name);
			printf("%-3d %5s %-13.13s %-13.12s$%9.2lf %02d/%02d/%4d\n",
					i,
					db->emp[i].ID,
					combinedName,
					db->emp[i].email,
					db->emp[i].salary,
					db->emp[i].hire_date.month,
					db->emp[i].hire_date.day,
					db->emp[i].hire_date.year);
		}


	}
	if (combinedName[0] == '\0') {
		printf("None");
	}
}

void IDdelete(dataBase_ptr db, char id[]) {
	char combinedName[14] = {'\0'};
	int index = IDsearch(db, id);
	snprintf(combinedName,  (unsigned)sizeof(combinedName), "%s %s", db->emp[index].first_name, db->emp[index].last_name);

	if (index > -1) {
		for (int j = index; j < db->total - 1; j++) {
			db->emp[j] = db->emp[j + 1];
		}
		db->total--;
		return;
	}

}

void quit(dataBase_ptr db) {	
	free(db->emp);
	free(db);

}

void display_menu (struct DataBase *db)
{
	int input = 0;
	char name[11];	
	char id[7];
	char idDELETE[7];
	int total = db->total;
	while (input != 8)
	{
		puts
			("\n**************************************************************");
		printf
			(  "********** Employee Database - Total Employees: %03d **********\n", total);//you need to fix this line so that total employees in the database is printed
		puts
			("**************************************************************\n");
		puts ("Choose one of the menu options below:");
		puts ("1. Sort by ID");
		puts ("2. Sort by Hire Date");
		puts ("3. Display all employees");
		puts ("4. Search employees by ID");
		puts ("5. Search employees by Last Name");
		puts ("6. Delete employee by ID");
		puts ("7. Save");
		puts ("8. Exit");

		scanf ("%d", &input);

		switch (input)
		{
			case 1:
				IDsort(db);
				break;
			case 2:
				dateSort(db);
				break;
			case 3:
				display(db);
				break;
			case 4:
				printf("\nEnter an employee ID: \n");
				scanf("%6s", id);
				IDsearch(db, id);
				break;
			case 5:
				printf("\nEnter an employee last name: \n");
				scanf("%10s", name);
				NameSearch(db, name);			
				break;
			case 6:
				printf("\nEnter an employee ID to DELETE: \n");
				scanf("%6s", idDELETE);
				IDdelete(db, idDELETE);
				total = db->total;
				break;
			case 7:
				save (db);
				break;
			case 8:
				quit(db);
				printf("Bye!\n");
				break;

		}
	}

}
