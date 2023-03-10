#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/transport.h"
#include "../include/additional_functions.h"

#define MAX_LINE_LENGTH 1024

// Traverses the list and frees each node
void free_transport_list(Transport* head) {
	Transport* current = head;
	while (current != NULL) {
		Transport* temp = current;
		current = current->next;
		free(temp);
	}
	head = NULL; // Reset the header pointer
}

void save_transport(Transport* current, int id, int battery, int autonomy, float price, char* type, char* geocode) {
	current->id = id;
	current->battery = battery;
	current->autonomy = autonomy;
	current->price = price;
	current->type = type;
	current->geocode = geocode;
}

int store_transports(Transport* head, int bool) {
	FILE* fp;

	// Open different files to write
	if(bool) fp = fopen("resources/transports.txt", "w");
	else fp = fopen("resources/transports.bin", "wb");

	if (fp == NULL) {
		printf("Ocorreu um erro a abrir o ficheiro");
		return 0;
	}

	Transport* current = head;

	// Run through the transport list
	while (current != NULL) {
		fprintf(fp, "%d;%d;%d;%.2f;%s;%s\n", current->id, current->battery, current->autonomy, current->price, current->type, current->geocode);
		current = current->next;
	}
	fclose(fp);

	return 1;
}

int read_transports(Transport* head, int bool) {
	FILE* fp;

	// Open different files to write
	if (bool) fp = fopen("resources/transports.txt", "r");
	else fp = fopen("resources/transports.bin", "rb");

	if (fp == NULL) {
		printf("Ocorreu um erro a abrir o ficheiro");
		return 0;
	}

	char file_info[MAX_LINE_LENGTH];
	char** split_file_info = NULL;

	// Empties the transport list
	free_transport_list(head);
	Transport* current = NULL;
		
	// Run through every line
	while (fgets(file_info, MAX_LINE_LENGTH, fp) != NULL) {
		// Removing trailing newline character 
		newline_remove(file_info);

		// Splits the string of the line in the file
		int array_size = str_split(file_info, &split_file_info, ";");

		// Save the line info 
		Transport* new_transport = (Transport*) malloc(sizeof(Transport));
		save_transport(new_transport,
						atoi(split_file_info[0]), atoi(split_file_info[1]),
						atoi(split_file_info[2]), atof(split_file_info[3]),
						split_file_info[4], split_file_info[5]);

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
	current->next = NULL;

	return 1;
}