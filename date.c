#include<stdio.h>
#include <stdlib.h>
#include "date.h"

int day;
int month;
int year;

int ValidDay()
{
	if ((day > 0) && (day < 32))
	{
		if (day == 29)
		{
			if ((month == 2) && ((year % 4) == 0))
			{
				return 1;
			}
			else
			{
				printf( "Invalid month's day.");
				exit(0);
			}
		}

		if (day == 30)
		{
			if (month == 4)
			{
				return 1;
			}

			if (month == 6)
			{
				return 1;
			}

			if (month == 9)
			{
				return 1;
			}

			if (month == 11)
			{
				return 1;
			}
		}

		return 1;
	}
	else
	{
		printf( "Invalid month's day.");
		exit(0);
	}
}


int ValidMonth()
{
	if (month > 0 && month < 13)
	{
		return 1;
	}
	else
	{
		printf( "Invalid month.");
		exit(0);
	}
}

int ValidYear()
{
	if (year > 1700)
	{
		return 1;
	}
	else
	{
		printf( "Invalid year.");
		exit(0);
	}
}

char * Date(int p_year, int p_month, int p_day)
{
	char *date = malloc(11);
	year = p_year;
	ValidYear();
	month = p_month;
	ValidMonth();
	day = p_day;
	ValidDay();
	sprintf(date, "%d-%d-%d", year, month, day);
	return date;
}























