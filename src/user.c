#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/user.h"
#include "../include/additional_functions.h"

#define MAX_LINE_LENGTH 1024

/*
	|--------------------------------------------------------------------------
	| Free the list
	|--------------------------------------------------------------------------
	|
	| Traverses the linked list and frees each node and makes
	| the first node NULL.
	|
*/
void free_user_list(User** head) {
	User* current = *head;
	User* next;

	while (current->next != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL; // Reset the header pointer
}

/*
	|--------------------------------------------------------------------------
	| Save user
	|--------------------------------------------------------------------------
	|
	| Saves each parameter to its corresponding struct member.
	|
*/
void save_user(User* current, int id, float balance, char* name, char* residency, char NIF[10], enum UserType type) {
	current->id = id;
	current->balance = balance;

	current->name = (char*)malloc(MAX_LINE_LENGTH / 3 * sizeof(char));
	strcpy(current->name, name);

	current->residency = (char*)malloc(MAX_LINE_LENGTH / 3 * sizeof(char));
	strcpy(current->residency, residency);

	strcpy(current->NIF, NIF);

	current->type = type;
	current->next = NULL;
}

/*
	|--------------------------------------------------------------------------
	| Store users
	|--------------------------------------------------------------------------
	|
	| Stores each node of the linked list on a different line in a file.
	| If the bool parameter is 0 it stores the info inside a binary file,
	| if the bool parameter is 1 it stores the info inside a text file.
	| Return a boolean value accordingly.
	|
*/
int store_users(User* head, int bool) {
	FILE* fp;

	// Open different files to write
	if (bool) fp = fopen("resources/users.txt", "w");
	else fp = fopen("resources/users.bin", "wb");

	if (fp == NULL) {
		printf("Ocorreu um erro a abrir o ficheiro\n");
		return 0;
	}

	User* current = head;

	// Run through the user list
	while (current != NULL) {
		fprintf(fp, "%d;%.2f;%s;%s;%s;%d\n", current->id, current->balance, current->name, current->residency, current->NIF, current->type);
		current = current->next;
	}
	fclose(fp);

	return 1;
}

/*
	|--------------------------------------------------------------------------
	| Read users
	|--------------------------------------------------------------------------
	|
	| Reads the users from a file and returns a linked list with each line 
	| of the file in each node.
	| If the bool parameter is 0 it reads from the binary file,
	| if the bool parameter is 1 it reads from the text file.
	|
*/
User* read_users(User* head, int bool) {
	FILE* fp;

	// Open different files to write
	if (bool) fp = fopen("resources/users.txt", "r");
	else fp = fopen("resources/users.bin", "rb");

	if (fp == NULL) {
		printf("Ocorreu um erro a abrir o ficheiro\n");
		return NULL;
	}

	char file_info[MAX_LINE_LENGTH];
	char** split_file_info = NULL;

	// Empties the user list
	free_user_list(&head);
	User* current = head;

	// Run through every line
	while (fgets(file_info, MAX_LINE_LENGTH, fp) != NULL) {
		// Removing trailing newline character 
		newline_remove(file_info);

		// Splits the string of the line in the file
		int array_size = str_split(file_info, &split_file_info, ";");

		// Save the line info 
		User* new_user = (User*)malloc(sizeof(User));
		save_user(new_user,
			atoi(split_file_info[0]), atof(split_file_info[1]), 
			split_file_info[2], split_file_info[3], 
			split_file_info[4], atoi(split_file_info[5]));

		// Add the info into the last node
		if (current == NULL) {
			head = new_user;
			current = head;
		}
		else {
			current->next = new_user;
			current = current->next;
		}

		// Free the memory
		for (int i = 0; i < array_size; i++) {
			free(split_file_info[i]);
		}
	}
	fclose(fp);

	return head;
}

/*
	|--------------------------------------------------------------------------
	| Vilidate NIF
	|--------------------------------------------------------------------------
	|
	| Verifies if the given parameter is a possible NIF, returning a
	| boolean accordingly.
	|
*/
int validate_NIF(char* number) {
	const int max = 9;

	//Check if is numeric and has 9 digits
	if (strlen(number) != max) return 0;
	for (int i = 0; i < max; i++) {
		if (number[i] < '0' || number[i] > '9') return 0;
	}

	int check_sum = 0;

	//Calculating check_sum
	for (int i = 0; i < max - 1; i++) check_sum += (number[i] - '0') * (max - i);
	int check_digit = 11 - (check_sum % 11);

	// If the check_digit is higher than 9 set it to 0
	if (check_digit > 9) check_digit = 0;

	// Verify the check_digit with the control digit
	return check_digit == number[max - 1] - '0';
}

/*
	|--------------------------------------------------------------------------
	| Insert user
	|--------------------------------------------------------------------------
	|
	| Inserts a new user into the last node of the linked list.
	| Returns the id of the new user.
	|
*/
int insert_user(User** head, int user_type) {
	User* current = NULL;

	int id = 0;
	char name[MAX_LINE_LENGTH / 3], residency[MAX_LINE_LENGTH / 3], NIF[10];

	// Max size is a third of the max line length
	printf("Nome: ");
	fgets(name, MAX_LINE_LENGTH / 3, stdin);
	newline_remove(name);

	// Check if its a possible NIF
	int valid_nif = 1;
	do {
		printf("NIF: ");
		fgets(NIF, 10, stdin);
		newline_remove(NIF);

		// Throw error message
		if (validate_NIF(NIF)) valid_nif = 0;
		else {
			printf("Ocorreu um erro: NIF invalido\n");
			continue;
		}

		current = *head;

		// Check if the NIF is already registered
		while (current != NULL) {
			if (strcmp(NIF, current->NIF) == 0) {
				valid_nif = 1;

				printf("Ocorreu um erro: NIF já registado\n");
				getchar();

				break;
			}
			current = current->next;
		}
	} while (valid_nif);
	getchar();

	printf("Residencia: ");
	fgets(residency, MAX_LINE_LENGTH / 3, stdin);
	newline_remove(residency);

	current = *head;
	int isFirst = 1;

	// Go to last node in the list
	while (current->next != NULL) {
		current = current->next;
		isFirst = 0;
	}

	// Check if there is a first node
	if (isFirst) {
		id = 1;
		save_user(current, id, 0, name, residency, NIF, user_type);
	}else{
		id = current->id + 1;
		current->next = (User*)malloc(sizeof(User));
		save_user(current->next, current->id + 1, 0, name, residency, NIF, user_type);
	}

	return id;
}

/*
	|--------------------------------------------------------------------------
	| Remove user
	|--------------------------------------------------------------------------
	|
	| Removes a user from the given linked list using the given user id.
	| Returns a boolean value accordingly.
	|
*/
int remove_user(User** head, int id) {
	User* current = *head;

	// Remove the first node
	if (current->id == id && current != NULL) {
		*head = current->next;
		free(current);
		return 1;
	}

	User* previous = NULL;

	// Remove the midle and last nodes
	while (current != NULL) {
		previous = current;
		current = current->next;

		if (current->id == id) {
			if (current->next != NULL) previous->next = current->next;
			else previous->next = NULL;

			free(current);
			return 1;
		}
	}

	return 0;
}

/*
	|--------------------------------------------------------------------------
	| Edit user
	|--------------------------------------------------------------------------
	|
	| Edits a user from the given linked list using the given user id.
	| Returns a boolean value accordingly.
	|
*/
int edit_user(User** head, int id) {
	User* current = *head;

	while (current != NULL) {
		if (current->id == id) {
			printf("Nome: %s, Residencia: %s, NIF: %s\n",
				current->name, current->residency, current->NIF);

			// Max size is a third of the max line length
			printf("Insira o novo nome: ");
			fgets(current->name, MAX_LINE_LENGTH / 3, stdin);
			newline_remove(current->name);

			printf("Insira o nova residencia: ");
			fgets(current->residency, MAX_LINE_LENGTH / 3, stdin);
			newline_remove(current->residency);

			// Check if its a possible NIF
			int valid_nif = 1;
			char NIF[10];
			do {
				printf("Insira o novo NIF: ");
				fgets(NIF, 10, stdin);
				newline_remove(NIF);

				// Throw error message
				if (validate_NIF(NIF)) valid_nif = 0;
				else {
					printf("Ocorreu um erro: NIF invalido\n");
					continue;
				}

				User* check = *head;

				// Check if the NIF is already registered
				while (check != NULL) {
					if (strcmp(NIF, check->NIF) == 0 && strcmp(NIF, current->NIF) != 0) {
						valid_nif = 1;

						printf("Ocorreu um erro: NIF já registado\n");
						getchar();

						break;
					}
					check = check->next;
				}
			} while (valid_nif);
			getchar();

			printf("Nome: %s, Residencia: %s, NIF: %s\n",
				current->name, current->residency, current->NIF);

			return 1;
		}

		current = current->next;
	}

	return 0;
}

/*
	|--------------------------------------------------------------------------
	| Get the user type
	|--------------------------------------------------------------------------
	|
	| Returns the user type by the given id.
	|
*/
int get_user_type(User* head, int id) {
	User* current = head;

	while (current != NULL) {
		if (current->id == id) return current->type;

		current = current->next;
	}

	return -1;
}

/*
	|--------------------------------------------------------------------------
	| Add to balance
	|--------------------------------------------------------------------------
	|
	| Adds a amount to the balance of a user in the linked list 
	| and in the file.
	| If the bool parameter is 0 it stores the new balance 
	| inside a binary file, if the bool parameter is 1 it stores the new 
	| balance inside a text file.
	|
*/
int add_balance(User** head, int id, int bool) {
	User* current = *head;
	float balance_added = 0;

	// Get user's input
	printf("Quanto a adicionar ao saldo: ");
	scanf("%f", &balance_added);
	getchar();

	while (current != NULL) {
		if (current->id == id) {
			current->balance += balance_added;
			store_users(*head, bool);
			return 1;
		}
			
		current = current->next;
	}

	return 0;
}