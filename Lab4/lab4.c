/*

Lab: 4
Spring 2023
Name: Vladimir Ceban

*/

// Includes
#include <stdio.h>
#include <string.h>

// Defines
#define SIZE 10

int main(void);
void empty_stdin(void);
void removeExtras(void);

void insert(void);
void show_all(void);
void show_by_hours(int);
int check_duplicate(char[SIZE]);
void deletebycode(char[SIZE]);
void deletebyhour(int);

// Global variables

// define structure of Flight that has code, hour, and minute
typedef struct Flight
{
	char code[SIZE + 1];
	int hour;
	int minute;
	// name it Flight
} Flight;

// initialize SIZE(10) flights, each has structure of Flight
Flight Flights[SIZE];

// flights counter
int flightCount = 0;

// Functions
void insert(void)
{
	int hour, minute, flagCode, flagHour, flagMinute;
	char code[SIZE + 1];
	flagCode = flagHour = flagMinute = 0;
	Flight *p;
	p = Flights;

	printf("Please, enter the code of the flight:\n");
	if (scanf("%s", code) != 1)
	{
		empty_stdin();
		printf("Error: you can enter only one string of characters at a time. Please try again.\n");
		return;
	}
	else if (strlen(code) <= 0 || strlen(code) > SIZE)
	{
		empty_stdin();
		printf("Error: code can be from 1 to 10 characters. Please try again.\n");
		return;
	}
	else if (check_duplicate(code) != 0)
	{
		empty_stdin();
		printf("Error: codes can't duplicate. Please try again.\n");
		return;
	}
	else
	{
		empty_stdin();
		flagCode = 1;
	}

	printf("Please, enter the hour of the flight's departure:\n");
	if (scanf("%d", &hour) != 1)
	{
		empty_stdin();
		printf("Error: hour should be a single integer. Please try again.\n");
		return;
	}
	else if (hour < 0 || hour > 23)
	{
		empty_stdin();
		printf("Error: hour can be an integer from 0 to 23. Please try again.\n");
		return;
	}
	else
	{
		empty_stdin();
		flagHour = 1;
	}

	printf("Please, enter the minute of the flight's departure:\n");
	if (scanf("%d", &minute) != 1)
	{
		empty_stdin();
		printf("Error: minute should be a single integer. Please try again.\n");
		return;
	}
	else if (minute < 0 || minute > 59)
	{
		empty_stdin();
		printf("Error: minute can be an integer from 0 to 59. Please try again.\n");
		return;
	}
	else
	{
		empty_stdin();
		flagMinute = 1;
	}

	if (flagCode == 1 && flagHour == 1 && flagMinute == 1)
	{
		int i, position;
		int time = (hour * 60) + minute;
		// if there are not flights scheduled yet - schedule to 1st position
		if (flightCount == 0)
		{
			position = 0;
		}
		else
		{
			for (i = 0; i < SIZE; i++)
			{
				if (time < p[i].hour * 60 + p[i].minute)
				{
					// position is set to first element that is smaller
					position = i;
					break;
				}
				else
				{
					// position is set to the first empty element
					if (strlen(p[i].code) == 0)
					{
						position = i;
						break;
					}
				}
			}
			// sort arrays with respect to position
			for (i = SIZE - 1; i > position; i--)
			{
				// copy elements from x-1 to x, where x starts at the end of the array
				strcpy(p[i].code, p[i - 1].code);
				p[i].hour = p[i - 1].hour;
				p[i].minute = p[i - 1].minute;
			}
		}
		// place data into arrays
		p = &Flights[position];

		strcpy(p->code, code);
		p->hour = hour;
		p->minute = minute;
		flightCount++;
		printf("Sucess: your flight was scheduled.\n");
	}
	return;
}
void show_all(void)
{
	int i;
	Flight *p;
	p = Flights;

	if (flightCount > 0)
	{
		for (i = 0; i != flightCount; i++, p++)
		{
			if (strlen(p->code) > 0)
			{
				printf("%d. Code: %s Time: %d:%02d\n", i + 1, p->code, p->hour, p->minute);
			}
		}

		// // DEBUG
		// printf("DEBUG:\n");
		// for (i = 0, p = Flights; i < SIZE; i++, p++)
		// {

		// 	printf("%d. Code: %s Time: %d:%02d\n", i + 1, p->code, p->hour, p->minute);
		// }
		// printf("Flights scheduled: %d\n", flightCount);

		printf("Returning to the main menu...\n");
		return;
	}
	else
	{
		printf("Error: the schedule is empty. Please schedule a flight first.\n");
		return;
	}
}
void show_by_hours(int hour)
{
	int i;
	int flag = 0;
	Flight *p;
	p = Flights;

	for (i = 0; i != flightCount; i++, p++)
	{
		if (p->hour == hour)
		{
			printf("%d. Code: %s Time: %d:%02d\n", i + 1, p->code, p->hour, p->minute);
			flag++;
		}
	}

	if (flag < 1)
	{
		printf("Error: no flights are scheduled for this hour. Please try again.\n");
	}

	printf("Returning to the main menu...\n");
	return;
}
void empty_stdin(void) // helper function to avoid repeating error messages on wrong inputs
{
	int c = getchar();

	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}
int check_duplicate(char code[SIZE])
{
	int i;
	int flag = 0;
	Flight *p;
	p = Flights;
	for (i = 0; i < SIZE; i++, p++)
	{
		if (strcmp(p->code, code) == 0)
		{
			flag++;
		}
	}
	return flag;
}
void deletebycode(char code[SIZE])
{
	int i, j;
	Flight *p;
	for (i = 0, p = Flights; i < SIZE; i++, p++)
	{
		if (strcmp(p->code, code) == 0)
		{
			printf("Flight #%s at %d:%02d is deleted\n", p->code, p->hour, p->minute);
			for (j = i; j < flightCount - 1; j++)
			{
				p[j - i] = p[j - i + 1];
			}
			flightCount--;
			removeExtras();
			return;
		}
	}
	printf("Error: there is no such flight scheduled yet. Please try again.\n");
	return;
}
void deletebyhour(int hour)
{
	int i, j;
	Flight *p;
	for (i = 0, p = Flights; i < flightCount; i++, p++)
	{
		if (p->hour == hour)
		{
			printf("Flight #%s at %d:%02d is deleted\n", p->code, p->hour, p->minute);
			for (j = i; j < flightCount - 1; j++)
			{
				p[j - i] = p[j - i + 1];
			}
			i--;
			p--;
			flightCount--;
		}
		else if (p->hour > hour)
		{
			removeExtras();
			printf("Returning to the main menu...\n");
			return;
		}
	}
	printf("Error: There are no flights scheduled for %d o'clock. Returning to the main menu...\n", hour);
	return;
}
void removeExtras(void)
{
	int i;
	Flight *p;
	// Wipes all flights after flightCount to clear entries for new flights
	for (i = flightCount, p = Flights + flightCount; i < SIZE; i++, p++)
	{
		p->code[0] = '\0';
		p->hour = 0;
		p->minute = 0;
	}
}

// Main
int main(void)
{
	int option;

	printf("Welcome to the Flighty Flighters Inc flight scheduling system. Please choose one of these options:\n\n1. Add a flight to the schedule\n2. Show all scheduled flights\n3. Show all flights scheduled for a specific hour\n4. Delete a flight with code\n5. Delete all flights at a given hour\n\n0. Quit\n");

	while (1)
	{
		if (scanf("%d", &option) != 1)
		{
			printf("Error: invalid menu option. Aborting...\n");
			return 1;
		}

		switch (option)
		{
		case 1:
			empty_stdin();
			if (flightCount < SIZE)
			{
				insert();
			}
			else
			{
				printf("Error: the schedule is full. Please try again tomorrow.\n");
			}
			break;

		case 2:
			empty_stdin();
			show_all();
			break;

		case 3:
			empty_stdin();
			int hour;
			if (flightCount < 1)
			{
				empty_stdin();
				printf("Error: the schedule is empty. Please schedule a flight first.\n");
			}
			else
			{
				printf("Please enter the hour you would like to search for:\n");
				if (scanf("%d", &hour) != 1)
				{
					empty_stdin();
					printf("Error: hour should be a single integer. Please try again.\n");
				}
				else if (hour < 0 || hour > 23)
				{
					printf("Error: hour can be an integer from 0 to 23. Please try again\n");
				}
				else
				{
					empty_stdin();
					show_by_hours(hour);
				}
			}
			break;

		case 4:
			empty_stdin();
			char code[SIZE];
			printf("Please enter an alpha-numeric flight code (1 to 9 characters) you'd like to delete:\n");
			if (flightCount < 1)
			{
				empty_stdin();
				printf("The schedule is empty. Please schedule a flight first.\n");
			}
			else
			{
				if (scanf("%s", code) != 1)
				{
					empty_stdin();
					printf("Error: you can enter only one code at a time. Please try again.\n");
				}
				else if (strlen(code) <= 0 || strlen(code) >= SIZE)
				{
					printf("Error: Code can be from 1 to 9 characters. Please try again.\n");
				}
				else
				{
					empty_stdin();
					deletebycode(code);
				}
			}
			break;

		case 5:
			empty_stdin();
			int hourToDelete;
			printf("Please enter the hour for which you'd like to delete all flights:\n");
			if (flightCount < 1)
			{
				empty_stdin();
				printf("The schedule is empty. Please schedule a flight first.\n");
			}
			else
			{
				if (scanf("%d", &hourToDelete) != 1)
				{
					empty_stdin();
					printf("Error: you can enter only one hour at a time. Please try again.\n");
				}
				else if (hourToDelete < 0 || hourToDelete > 23)
				{
					printf("Error: hour can be an integer from 0 to 23. Please try again\n");
				}
				else
				{
					empty_stdin();
					deletebyhour(hourToDelete);
				}
			}
			break;

		case 0:
			empty_stdin();
			printf("Goodbye!\n");
			return 0;

		default:
			empty_stdin();
			printf("Error: invalid menu option.\n");
		}
	}
}
