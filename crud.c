#include "crud.h"
#include <stdlib.h>
#include <stdio.h>
#include "sqlite3.h"
#include <string.h>
	
	//char *resultID;
	
	sqlite3 *db;
	

	/*
	static int callbackID(void *unused, int count, char **data, char **columns)
	{
	   resultID = data[0] ? data[0] : "1";
	   return 0;
	}
	*/

	sqlite3 *Connect()
	{
		int rc;
		rc = sqlite3_open("dbCrud.db", &db);
		if (!rc)
		{
			return db;
		}
		else
		{
			printf("Error connecting to database.");
			exit(0);
		}
	}

	void Close(sqlite3 *db)
	{
		int rc;
		rc = sqlite3_close(db);
		if (!(rc == SQLITE_OK))
		{
			printf("Error desconnecting to database.");
			exit(0);
		}
	}
	
	/*
	void setIDforInsert()
	{
		db = Connect();
	    char *zErrMsg = 0;
	    int rc;
	    char *sql;
	    sql = "SELECT MAX(ID) + 1 from PERSON";
	
	    rc = sqlite3_exec(db, sql, callbackID, 0, &zErrMsg);
	    if( rc != SQLITE_OK ){
	      printf("SQL error: %s\n", zErrMsg);
	      sqlite3_free(zErrMsg);
	    }else{
	    }
	}
	*/
	
	
	int BeginTrans()
	{
	   	char *zErrMsg = 0;
	   	int rc;
	   	char *sql = malloc(500);
       	sql = "BEGIN TRANSACTION";

		rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
		if( rc != SQLITE_OK ){
		      sqlite3_free(zErrMsg);
		      return -1;
		}else{
			return 1;
		}
	}
	
	int Commit()
	{
	   	char *zErrMsg = 0;
	   	int rc;
	   	char *sql = malloc(7);
       	sql = "COMMIT";

		rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
		if( rc != SQLITE_OK ){
		      sqlite3_free(zErrMsg);
		      return -1;
		}else{
			return 1;
		}
	}
	
	
	int Rollback()
	{
	   	char *zErrMsg = 0;
	   	int rc;
	   	char *sql = malloc(9);
       	sql = "ROLLBACK";

		rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
		if( rc != SQLITE_OK ){
		      sqlite3_free(zErrMsg);
		      return -1;
		}else{
			return 1;
		}
	}
	
	
	int InsertPerson(int id, char* name, char* email)
	{
	   	char *zErrMsg = 0;
	   	int rc;
	   	char *sql = malloc(200);
       	sprintf(sql, "INSERT INTO PERSON VALUES (%d,'%s','%s')", id, name, email);

		rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
		if( rc != SQLITE_OK ){
		      sqlite3_free(zErrMsg);
		      return -1;
		}else{
			return 1;
		}
	}
	
	int InsertPhysicalPerson(int id, float salary, char* birthday, char* gender)
	{
		char *zErrMsg = 0;
	   	int rc;
	   	char *sql = malloc(200);
       	sprintf(sql, "INSERT INTO PHYSICALPERSON VALUES (%d, %d, %.2f,'%s','%s')", id, id, salary, birthday, gender);

		rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
		if( rc != SQLITE_OK ){
		      sqlite3_free(zErrMsg);
		      return -1;
		}else{
			return 1;
		}
	}

	void Insert_PhysicalPerson(char* name, char* email, float salary, char* birthday, char* gender)
	{
		db = Connect();
		
		//setIDforInsert();
		//strcpy(str, resultID);
		//int id = atoi(str);
		
		int id = 1;
		
		if(BeginTrans() == 1)
		{
			if(InsertPerson(id, name, email) == 1)
			{
				if(InsertPhysicalPerson(id, salary, birthday, gender) == 1)
				{
					Commit();
					Close(db);
					printf("Successful physical person registration.");
				}
				else
				{
					Rollback();
					Close(db);
					printf("Error registering Physical Person.");
				}
			}
			else
			{
				Rollback();
				Close(db);
				printf("Error registering Physical Person.");
			}
		}
	}
	
	
	int EditPerson(int id, char* name, char* email)
	{
	   	char *zErrMsg = 0;
	   	int rc;
	   	char *sql = malloc(200);
       	sprintf(sql, "UPDATE PERSON SET NAME = '%s', EMAIL = '%s' WHERE ID = %d", name, email, id);
		rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
		if( rc != SQLITE_OK ){
		      sqlite3_free(zErrMsg);
		      return -1;
		}else{
			return 1;
		}
	}
	
	int EditPhysicalPerson(int id, float salary, char* birthday, char* gender)
	{
		char *zErrMsg = 0;
	   	int rc;
	   	char *sql = malloc(200);
       	sprintf(sql, "UPDATE PHYSICALPERSON SET SALARY = %.2f, BIRTHDAY = '%s', GENDER = '%s' WHERE ID = %d", salary, birthday, gender, id);
		rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
		if( rc != SQLITE_OK ){
		      sqlite3_free(zErrMsg);
		      return -1;
		}else{
			return 1;
		}
	}

	void Edit_PhysicalPerson(int id, char* name, char* email, float salary, char* birthday, char* gender)
	{
		db = Connect();
		
		if(BeginTrans() == 1)
		{
			if(EditPerson(id, name, email) == 1)
			{
				if(EditPhysicalPerson(id, salary, birthday, gender) == 1)
				{
					Commit();
					Close(db);
					printf("Successful physical person record editing.");
				}
				else
				{
					Rollback();
					Close(db);
					printf("Error editing physical person record.");
				}
			}
			else
			{
				Rollback();
				Close(db);
				printf("Error editing physical person record.");
			}
		}
	}

	
	int DeletePerson(int id)
	{
	   	char *zErrMsg = 0;
	   	int rc;
	   	char *sql = malloc(200);
       	sprintf(sql, "DELETE FROM PERSON WHERE ID = %d", id);
		rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
		if( rc != SQLITE_OK ){
		      sqlite3_free(zErrMsg);
		      return -1;
		}else{
			return 1;
		}
	}
	
	int DeletePhysicalPerson(int id)
	{
		char *zErrMsg = 0;
	   	int rc;
	   	char *sql = malloc(200);
       	sprintf(sql, "DELETE FROM PHYSICALPERSON WHERE ID = %d", id);
		rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
		if( rc != SQLITE_OK ){
		      sqlite3_free(zErrMsg);
		      return -1;
		}else{
			return 1;
		}
	}

	void Delete_PhysicalPerson(int id)
	{
		db = Connect();
		
		if(BeginTrans() == 1)
		{
			if(DeletePhysicalPerson(id) == 1)
			{
				if(DeletePerson(id) == 1)
				{
					Commit();
					Close(db);
					printf("Success to delete.");
				}
				else
				{
					Rollback();
					Close(db);
					printf("Error deleting physical person record.");
				}
			}
			else
			{
				Rollback();
				Close(db);
				printf("Error deleting physical person record.");
			}
		}
	}
	
	static int callbackGET(void *unused, int count, char **data, char **columns)
	{
	   int i=0;
	   int l;
	   
	   for(l = 0; l < 30; l++)
	   {
			printf("-");
	   }
	   
	   printf("\n");
	   while(i<count) 
	   {
	      if((i == 3) || (i == 4))
	      {
	      	i++;
	      	continue;
		  }
		  
		  printf("%s = %s", columns[i], data[i] ? data[i] : "NULL");
		  printf("\n");
		  i++;
	   }
	   return 0;
	}
	
	void GetPhysicalPersonByID(int id)
	{
	   sqlite3 *db = Connect();
	   char *zErrMsg = 0;
	   int rc;
	   char *sql = malloc(200);
	   
	   sprintf(sql, "SELECT * FROM PERSON INNER JOIN PHYSICALPERSON ON PERSON.ID = PHYSICALPERSON.PERSON_ID WHERE PERSON.ID = %d", id);
	   rc = sqlite3_exec(db, sql, callbackGET, 0, &zErrMsg);
	   if( rc != SQLITE_OK ){
	      sqlite3_free(zErrMsg);
	      printf("Error when performing search by Physical Person.");
	   }else{
	   }
	   Close(db);
	}
	
	void GetPhysicalPersonByName(char* name)
	{
	   sqlite3 *db = Connect();
	   char *zErrMsg = 0;
	   int rc;
	   char *sql = malloc(200);
	   
	   sprintf(sql, "SELECT * FROM PERSON INNER JOIN PHYSICALPERSON ON PERSON.ID = PHYSICALPERSON.PERSON_ID WHERE PERSON.NAME LIKE '%s%%'", name);
	   rc = sqlite3_exec(db, sql, callbackGET, 0, &zErrMsg);
	   if( rc != SQLITE_OK ){
	      sqlite3_free(zErrMsg);
	      printf("Error when performing search by Physical Person.");
	   }else{
	   }
	   Close(db);
	}

	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
		
