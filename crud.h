#ifndef CRUD_H_
#define CRUD_H_
     
#include "sqlite3.h"

void Insert_PhysicalPerson(char* name, char* email, float salary, char* birthday, char* gender);
void Edit_PhysicalPerson(int id, char* name, char* email, float salary, char* birthday, char* gender);
void Delete_PhysicalPerson(int id);
void GetPhysicalPersonByID(int id);
void GetPhysicalPersonByName(char* name);

#endif
