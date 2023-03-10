#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/user.h"
#include "../include/additional_functions.h"

#define MAX_LINE_LENGTH 1024

// Traverses the list and frees each node
void free_user_list(User* head) {
	User* current = head;
	while (current != NULL) {
		User* temp = current;
		current = current->next;
		free(temp);
	}
	head = NULL; // Reset the header pointer
}

void save_user(User* current, int id, int NIF, float balance, char* name, char* residency, enum UserType type) {
	current->id = id;
	current->NIF = NIF;
	current->balance = balance;
	current->name = name;
	current->residency = residency;
	current->type = type;
}

int store_users(User* head, int bool) {
	FILE* fp;

	// Open different files to write
	if (bool) fp = fopen("resources/users.txt", "w");
	else fp = fopen("resources/users.bin", "wb");

	if (fp == NULL) {
		printf("Ocorreu um erro a abrir o ficheiro");
		return 0;
	}

	User* current = head;

	// Run through the user list
	while (current != NULL) {
		fprintf(fp, "%d;%d;%.2f;%s;%s;%d\n", current->id, current->NIF, current->balance, current->name, current->residency, current->type);
		current = current->next;
	}
	fclose(fp);

	return 1;
}

int read_users(User* head, int bool) {
	FILE* fp;

	// Open different files to write
	if (bool) fp = fopen("resources/users.txt", "r");
	else fp = fopen("resources/users.bin", "rb");

	if (fp == NULL) {
		printf("Ocorreu um erro a abrir o ficheiro");
		return 0;
	}

	char file_info[MAX_LINE_LENGTH];
	char** split_file_info = NULL;

	// Empties the transport list
	free_user_list(head);
	User* current = NULL;

	// Run through every line
	while (fgets(file_info, MAX_LINE_LENGTH, fp) != NULL) {
		// Removing trailing newline character 
		newline_remove(file_info);

		// Splits the string of the line in the file
		int array_size = str_split(file_info, &split_file_info, ";");

		// Save the line info 
		User* new_transport = (User*)malloc(sizeof(User));
		save_user(new_transport,
			atoi(split_file_info[0]), atoi(split_file_info[1]),
			atof(split_file_info[2]), split_file_info[3],
			split_file_info[4], atoi(split_file_info[5]));

		// Add the info into the last node
		if (current == NULL) {
			head = new_transport;
			current = head;
		}
		else {
			current->next = new_transport;
			current = current->next;
		}

		// Free the memory
		for (int i = 0; i < array_size; i++) {
			free(split_file_info[i]);
		}
		free(new_transport);
	}
	fclose(fp);

	return 1;
}