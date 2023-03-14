#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/additional_functions.h"

char* string_dup(const char* source) {
	char* desteny = malloc(strlen(source) + 1);   // Space for length plus null
	if (desteny == NULL) return NULL;			  // No memory
	strcpy(desteny, source);                      // Copy the characters
	return desteny;								  // Return the new string
}


/*
	|--------------------------------------------------------------------------
	| Split string
	|--------------------------------------------------------------------------
	|
	|  Splits a string by a given delimiter and returns the array size.
	|
*/
int str_split(char* string, char*** split_string, const char* delim) {
    int array_size = 0;
    char* token = strtok(string, delim);

    while (token != NULL) {
        array_size++;

		// Resize the allocation of memory
        *split_string = (char**) realloc(*split_string, array_size * sizeof(char*));
        (*split_string)[array_size - 1] = string_dup(token);
        token = strtok(NULL, delim);
    }

    return array_size;
}

// Removes the trailing newline character from a string
void newline_remove(char* string) {
	int length = strlen(string);

	if (string[length - 1] == '\n') {
		string[length - 1] = '\0';
	}
}

/*
	|--------------------------------------------------------------------------
	| Add minutes to time
	|--------------------------------------------------------------------------
	|
	| The functions returns the sum of minutes to a given time.
	| It will also change the date if needed.
	|
*/
char* add_minutes(const char* time, const char* date, int minutes) {
	// Extract the hours and minutes from the time string
	int hours = atoi(time);
	int mins = atoi(time + 3);
	int carry = 0; // Carry over to the hours

	// Add minutes and carry over to the hours if needed
	mins += minutes;
	while (mins >= 60) {
		carry++;
		mins -= 60;
	}

	// Add hours and carry over to the next day if needed
	hours += carry;
	int days = 0;
	while (hours >= 24) {
		hours -= 24;
		days++;
	}

	// Create the new time string
	static char new_time[6];

	// Format the new time string
	sprintf(new_time, "%02d:%02d", hours, mins);

	// Extract the day, month, and year from the date string
	int day = atoi(date);
	int month = atoi(date + 3);
	int year = atoi(date + 6);

	// Add the number of days to the date
	day += days;
	while (day > 31) {
		day -= 31;
		month++;
	}
	while (month > 12) {
		month -= 12;
		year++;
	}

	// Create the new date string
	static char new_date[11];

	// Format the new date string
	sprintf(new_date, "%02d-%02d-%04d", day, month, year);

	// Return the new time and date strings
	static char new_time_date[17];
	sprintf(new_time_date, "%s %s", new_date, new_time);
	return new_time_date;
}