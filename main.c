#include <stdio.h>
#include <stdlib.h>
#include "crud.h"
#include "sqlite3.h"
#include "date.h"

void (*Insert_PhysicalPerson_ptr)(char* , char* , float , char* , char* );
void (*Edit_PhysicalPerson_ptr)(int , char* , char* , float , char* , char* );
void (*Delete_PhysicalPerson_ptr)(int);
void (*GetPhysicalPersonByID_ptr)(int);
void (*GetPhysicalPersonByName_ptr)(char*);
				
int main() {
	
	int i = 1;
	int op = 0;
	char *date = "";
	int l;
	
	printf("Registration's System\n");
	
	while(i != 0)
	{
		for(l=0;l<35;l++)
		{
			printf("-");
		}			
		printf("\n1 - Insert Physical Person");
		printf("\n2 - Edit Physical Person");
		printf("\n3 - Delete Physical Person");
		printf("\n4 - Get Physical Person By ID");
		printf("\n5 - Get Physical Person By Name\n");
		
		for(l=0;l<35;l++)
		{
			printf("-");
		}			
		
		printf("\nOption's number.: ");
		scanf("%d", &op);
		
		switch(op)
		{
			case 1:
				printf("\nInserting...\n");
				Insert_PhysicalPerson_ptr = &Insert_PhysicalPerson;
				date = Date(1981,11,12);
				Insert_PhysicalPerson_ptr("Personal 01", "personal@test.xxx", 3333.77, date, "M");
				break;
			
			case 2:
				printf("\nEditing...\n");
				Edit_PhysicalPerson_ptr = &Edit_PhysicalPerson;
				date = Date(1981,12,11);
				Edit_PhysicalPerson_ptr(1, "Personal 02", "personal2@test.xxx", 7777.33, date, "F");
				break;
				
			case 3:
				printf("\nDeleting...\n");
				Delete_PhysicalPerson_ptr = &Delete_PhysicalPerson;
				Delete_PhysicalPerson_ptr(1);
				break;
				
			case 4:
				printf("\nSearching by id...\n");
				GetPhysicalPersonByID_ptr = &GetPhysicalPersonByID;
				GetPhysicalPersonByID_ptr(1);
				break;
				
			case 5:
				printf("\nSearching by name...\n");
				GetPhysicalPersonByName_ptr = &GetPhysicalPersonByName;
				GetPhysicalPersonByName_ptr("Per");
				break;
				
			default:
				printf("\nInvalid's Option.");
				break;
				
		}
		
		printf("\n\nContinue?");
		scanf("%d", &i);
		printf("\n\n");
	}
	
	printf("\n\nFinished.\n\n");
	
	system("PAUSE");
	return 0;
}


