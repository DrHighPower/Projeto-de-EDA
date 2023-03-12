#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/authentication.h"
#include "../include/user.h"

#define MAX_LINE_LENGTH 1024

int check_NIF(User* head, char NIF[10]) {
	User* current = head;

	while (current != NULL) {
		if (strcmp(NIF, current->NIF) == 0) return current->id;
		current = current->next;
	}

	return 0;
}

/*
	|--------------------------------------------------------------------------
	| Login
	|--------------------------------------------------------------------------
	|
	| Logins the user saving its id in a variable
	|
*/
int login(User* head, int *id) {
	// Get the users NIF
	char NIF[10];
	printf("Introduza o seu NIF: ");
	fgets(NIF, 10, stdin);

	// Get the id corresponding to a NIF
	*id = check_NIF(head, NIF);
	return *id;
}

/*
	|--------------------------------------------------------------------------
	| Register
	|--------------------------------------------------------------------------
	|
	| Registers the user in the list, then it logins the user.
	|
*/
int registers(User** head, int* id) {
	*id = insert_user(head, 0);
}