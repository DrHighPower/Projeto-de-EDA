#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/authentication.h"
#include "../include/user.h"
#include "../include/additional_functions.h"

#define MAX_PASSWORD_SIZE 20

#pragma region CheckNIF
/*
	|--------------------------------------------------------------------------
	| Check NIF
	|--------------------------------------------------------------------------
	|
	| Checks if the NIF exists in the linked list.
	| Returns the user's id with the same NIF if it exists, else it returns 0.
	|
*/
int check_NIF(User* head, char NIF[10]) {
	User* current = head;

	while (current != NULL) {
		if (strcmp(NIF, current->NIF) == 0) return current->id;
		current = current->next;
	}

	return 0;
}
#pragma endregion

#pragma region CheckPassword
/*
	|--------------------------------------------------------------------------
	| Check password
	|--------------------------------------------------------------------------
	|
	| Check if the user inputed the right password.
	| Returns the user's id if the password is correct, else it returns 0.
	|
*/
int check_password(User* head, int id,char *password) {
	User* current = head;

	while (current != NULL && id != 0) {
		if(current->id == id && strcmp(password, current->password) == 0) return current->id;
		current = current->next;
	}

	return 0;
}
#pragma endregion

#pragma region Login
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
	getchar();

	char password[MAX_PASSWORD_SIZE];
	printf("Introduza a sua password: ");
	fgets(password, MAX_PASSWORD_SIZE, stdin);
	newline_remove(password);

	// Check the NIF and password
	*id = check_password(head, check_NIF(head, NIF), password);
	return *id;
}
#pragma endregion

#pragma region Register
/*
	|--------------------------------------------------------------------------
	| Register
	|--------------------------------------------------------------------------
	|
	| Registers the user in the list, then it logins the user.
	|
*/
int registers(User** head, int* id, int bool) {
	*id = insert_user(head, bool);

	return *id;
}
#pragma endregion