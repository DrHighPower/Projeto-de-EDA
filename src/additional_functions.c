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

