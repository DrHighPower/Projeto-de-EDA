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
		printf("Ocorreu um erro a abrir o ficheiro\n");
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
		printf("Ocorreu um erro a abrir o ficheiro\n");
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

	printf("Bateria: ");
	scanf("%d", &battery);

	printf("Autonomia: ");
	scanf("%d", &autonomy);

	printf("Preço: ");
	scanf("%f", &price);
	getchar();

	// Max size is a third of the max line length
	printf("Tipo: ");
	fgets(type, MAX_LINE_LENGTH / 3, stdin);
	newline_remove(type);

	printf("Geocódigo: ");
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

int remove_transport(Transport** head, int id) {
	Transport* current = *head;

	// Remove the first node
	if (current->id == id && current != NULL) {
		*head = current->next;
		free(current);
		return 1;
	}

	Transport* previous = NULL;

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

int edit_transport(Transport** head, int id) {
	Transport* current = *head;

	while (current != NULL) {
		if (current->id == id) {
			printf("Tipo: %s, Geocódigo: %s, Bateria: %d, Autonomia: %d, Preço: %.2f\n", 
					current->type, current->geocode, current->battery, current->autonomy, current->price);

			// Max size is a third of the max line length
			printf("Insira o novo tipo: ");
			fgets(current->type, MAX_LINE_LENGTH / 3, stdin);
			newline_remove(current->type);

			printf("Insira o novo geocódigo: ");
			fgets(current->geocode, MAX_LINE_LENGTH / 3, stdin);
			newline_remove(current->geocode);

			printf("Insira o nova bateria: ");
			scanf("%d", &current->battery);

			printf("Insira o nova autonomia: ");
			scanf("%d", &current->autonomy);

			printf("Insira o novo preço: ");
			scanf("%f", &current->price);
			getchar();

			printf("Tipo: %s, Geocódigo: %s, Bateria: %d, Autonomia: %d, Preço: %.2f\n",
				current->type, current->geocode, current->battery, current->autonomy, current->price);

			return 1;
		}

		current = current->next;
	}

	return 0;
}

void list_autonomy(Transport* head) {
	Transport* current = head;

	// Stores the size of the array for a dynamic array
	// and saves the quantity of transports
	int array_size = 2, transport_quant = 0;
	Transport** array = (Transport*) malloc(array_size * sizeof(Transport));

	while (current != NULL) {
		array[transport_quant] = current;
		array_size++;

		// Resizes the array size
		array = (Transport*) realloc(array, array_size * sizeof(Transport));

		current = current->next;
		transport_quant++;
	}

	// Reverse bubble sort throught the array to sort it in descending order of autonomy
	for (int i = 0; i < transport_quant - 1; i++) {
		for (int j = 0; j < transport_quant - i - 1; j++) {
			if (array[j]->autonomy < array[j + 1]->autonomy) {
				Transport* temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}

	// Prints all the sorted tranports
	for (int i = 0; i < transport_quant; i++) {
		printf("Id: %d\n", array[i]->id);
		printf("Autonomy: %d\n", array[i]->autonomy);
		printf("Bateria: %d\n", array[i]->battery);
		printf("Preço: %.2f\n", array[i]->price);
		printf("Tipo: %s\n", array[i]->type);
		printf("Geocódigo: %s\n", array[i]->geocode);

		// Print a line until the last one
		if (i != transport_quant - 1) printf("-------------------------\n");
	}

	free(array);
}

void list_geocode(Transport* head) {
	Transport* current = head;
	char geocode[MAX_LINE_LENGTH / 3];

	// User input
	printf("Geocódigo a pesquisar: ");
	fgets(geocode, MAX_LINE_LENGTH / 3, stdin);
	newline_remove(geocode);

	while (current != NULL) {
		if (strcmp(current->geocode, geocode) == 0) {
			printf("Id: %d\n", current->id);
			printf("Autonomy: %d\n", current->autonomy);
			printf("Bateria: %d\n", current->battery);
			printf("Preço: %.2f\n", current->price);
			printf("Tipo: %s\n", current->type);
			printf("Geocódigo: %s\n", current->geocode);

			// Print a line until the last one
			if (current->next != NULL) printf("-------------------------\n");
		}
		current = current->next;
	}
}

int validate_transport(Transport* head, int id) {
	Transport* current = head;

	while (current != NULL) {
		if (current->id == id) return 1;
		current = current->next;
	}

	return 0;
}