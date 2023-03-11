#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/transport.h"
#include "../include/additional_functions.h"

#define MAX_LINE_LENGTH 1024

// Traverses the list and frees each node
void free_transport_list(Transport** head) {
	Transport* current = *head;
	Transport* next;

	while (current->next != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL; // Reset the header pointer
}

void save_transport(Transport* current, int id, int battery, int autonomy, float price, char* type, char* geocode) {
	current->id = id;
	current->battery = battery;
	current->autonomy = autonomy;
	current->price = price;

	current->type = (char*)malloc(MAX_LINE_LENGTH / 3 * sizeof(char));
	strcpy(current->type, type);

	current->geocode = (char*)malloc(MAX_LINE_LENGTH / 3 * sizeof(char));
	strcpy(current->geocode, geocode);

	current->next = NULL;
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

Transport* read_transports(Transport* head, int bool) {
	FILE* fp;

	// Open different files to write
	if (bool) fp = fopen("resources/transports.txt", "r");
	else fp = fopen("resources/transports.bin", "rb");

	if (fp == NULL) {
		printf("Ocorreu um erro a abrir o ficheiro");
		return NULL;
	}

	char file_info[MAX_LINE_LENGTH];
	char** split_file_info = NULL;

	// Empties the transport list
	free_transport_list(&head);
	Transport* current = head;
		
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
	}
	fclose(fp);
	current->next = NULL;

	return head;
}

void insert_tranport(Transport** head) {
	Transport* current = *head;

	int battery, autonomy;
	float price;
	char type[MAX_LINE_LENGTH / 3], geocode[MAX_LINE_LENGTH / 3];

	printf("Bateria:");
	scanf("%d", &battery);

	printf("Autonomia:");
	scanf("%d", &autonomy);

	printf("Preço:");
	scanf("%f", &price);
	getchar();

	// Max size is a third of the max line length
	printf("Tipo:");
	fgets(type, MAX_LINE_LENGTH / 3, stdin);
	newline_remove(type);

	printf("Geocodigo:");
	fgets(geocode, MAX_LINE_LENGTH / 3, stdin);
	newline_remove(geocode);

	int isFirst = 1;

	// Go to last node in the list
	while (current->next != NULL) {
		current = current->next;
		isFirst = 0;
	}

	// Check if there is a first node
	if(isFirst) 
		save_transport(current, 1, battery, autonomy, price, type, geocode);
	else {
		current->next = (Transport*)malloc(sizeof(Transport));
		save_transport(current->next, current->id + 1, battery, autonomy, price, type, geocode);
	}
}