#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/transport.h"
#include "../include/additional_functions.h"

#define MAX_LINE_LENGTH 1024

#pragma region FreeTransportList
/*
	|--------------------------------------------------------------------------
	| Free the list
	|--------------------------------------------------------------------------
	|
	| Traverses the linked list and frees each node and makes
	| the first node NULL.
	|
*/
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
#pragma endregion

#pragma region SaveTransport
/*
	|--------------------------------------------------------------------------
	| Save transport
	|--------------------------------------------------------------------------
	|
	| Saves each parameter to its corresponding struct member.
	|
*/
void save_transport(Transport* current, int id, int battery, int autonomy, float price, float volume, char* type, char* geocode) {
	current->id = id;
	current->battery = battery;
	current->autonomy = autonomy;
	current->price = price;
	current->volume = volume;

	current->type = (char*)malloc(MAX_LINE_LENGTH / 3 * sizeof(char));
	strcpy(current->type, type);

	current->geocode = (char*)malloc(MAX_LINE_LENGTH / 3 * sizeof(char));
	strcpy(current->geocode, geocode);

	current->next = NULL;
}
#pragma endregion

#pragma region StoreTransports
/*
	|--------------------------------------------------------------------------
	| Store transports
	|--------------------------------------------------------------------------
	|
	| Stores each node of the linked list on a different line in a file.
	| If the bool parameter is 0 it stores the info inside a binary file,
	| if the bool parameter is 1 it stores the info inside a text file.
	| Return a boolean value accordingly.
	|
*/
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
		fprintf(fp, "%d;%d;%d;%.2f;%s;%s;%.2f\n", current->id, current->battery, current->autonomy, current->price, current->type, current->geocode, current->volume);
		current = current->next;
	}
	fclose(fp);

	return 1;
}
#pragma endregion

#pragma region ReadTransports
/*
	|--------------------------------------------------------------------------
	| Read transports
	|--------------------------------------------------------------------------
	|
	| Reads the transports from a file and returns a linked list 
	| with each line of the file in each node.
	| If the bool parameter is 0 it reads from the binary file,
	| if the bool parameter is 1 it reads from the text file.
	|
*/
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
						atoi(split_file_info[2]), atof(split_file_info[3]), atof(split_file_info[6]),
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
#pragma endregion

#pragma region InsertTransport
/*
	|--------------------------------------------------------------------------
	| Insert transport
	|--------------------------------------------------------------------------
	|
	| Inserts a new transport into the last node of the linked list.
	|
*/
void insert_tranport(Transport** head) {
	Transport* current = *head;

	int battery, autonomy;
	float price, volume;
	char type[MAX_LINE_LENGTH / 3], geocode[MAX_LINE_LENGTH / 3];

	printf("Bateria: ");
	scanf("%d", &battery);

	printf("Autonomia: ");
	scanf("%d", &autonomy);

	printf("Preço: ");
	scanf("%f", &price);
	getchar();

	printf("Volume em metros cúbicos: ");
	scanf("%f", &volume);
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
		save_transport(current, 1, battery, autonomy, price, volume, type, geocode);
	else {
		current->next = (Transport*)malloc(sizeof(Transport));
		save_transport(current->next, current->id + 1, battery, autonomy, price, volume, type, geocode);
	}
}
#pragma endregion

#pragma region RemoveTransport
/*
	|--------------------------------------------------------------------------
	| Remove transport
	|--------------------------------------------------------------------------
	|
	| Removes a transport from the given linked list using 
	| the given transport id.
	| Returns a boolean value accordingly.
	|
*/
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
#pragma endregion

#pragma region EditTransport
/*
	|--------------------------------------------------------------------------
	| Edit transport
	|--------------------------------------------------------------------------
	|
	| Edits a transport from the given linked list using 
	| the given transport id.
	| Returns a boolean value accordingly.
	|
*/
int edit_transport(Transport** head, int id) {
	Transport* current = *head;

	while (current != NULL) {
		if (current->id == id) {
			printf("Tipo: %s, Geocódigo: %s, Bateria: %d, Autonomia: %d, Preço: %.2f, Volume: %.2f\n",
				current->type, current->geocode, current->battery, current->autonomy, current->price, current->volume);

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

			printf("Insira o novo volume em metros cúbicos: ");
			scanf("%f", &current->volume);
			getchar();

			printf("Tipo: %s, Geocódigo: %s, Bateria: %d, Autonomia: %d, Preço: %.2f, Volume: %.2f\n",
				current->type, current->geocode, current->battery, current->autonomy, current->price, current->volume);

			return 1;
		}

		current = current->next;
	}

	return 0;
}
#pragma endregion

#pragma region ListAutonomy
/*
	|--------------------------------------------------------------------------
	| List of transports by autonomy
	|--------------------------------------------------------------------------
	|
	| Returns a list of transports by descending order of autonomy.
	|
*/
Transport** list_autonomy(Transport* head, int* transport_quant) {
	Transport* current = head;

	// Stores the size of the array for a dynamic array
	// and saves the quantity of transports
	*transport_quant = 0;
	int array_size = 2;
	Transport** array = (Transport*) malloc(array_size * sizeof(Transport));

	while (current != NULL) {
		array[*transport_quant] = current;
		array_size++;

		// Resizes the array size
		array = (Transport*) realloc(array, array_size * sizeof(Transport));

		current = current->next;
		*transport_quant = *transport_quant + 1;
	}

	// Reverse bubble sort throught the array to sort it in descending order of autonomy
	for (int i = 0; i < *transport_quant - 1; i++) {
		for (int j = 0; j < *transport_quant - i - 1; j++) {
			if (array[j]->autonomy < array[j + 1]->autonomy) {
				Transport* temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}

	return array;
}
#pragma endregion

#pragma region ListGeocode
/*
	|--------------------------------------------------------------------------
	| List of transports with a geocode
	|--------------------------------------------------------------------------
	|
	| Prints a list of transports in a location with a certain geocode. 
	|
*/
Transport** list_geocode(Transport* head, int* transport_quant) {
	Transport* current = head;
	char geocode[MAX_LINE_LENGTH / 3];

	// User input
	printf("Geocódigo a pesquisar: ");
	fgets(geocode, MAX_LINE_LENGTH / 3, stdin);
	newline_remove(geocode);

	// Stores the size of the array for a dynamic array
	// and saves the quantity of transports
	*transport_quant = 0;
	int array_size = 2;
	Transport** array = (Transport*)malloc(array_size * sizeof(Transport));

	while (current != NULL) {
		if (strcmp(current->geocode, geocode) == 0) {
			array[*transport_quant] = current;
			array_size++;

			// Resizes the array size
			array = (Transport*)realloc(array, array_size * sizeof(Transport));
			*transport_quant = *transport_quant + 1;
		}
		current = current->next;
	}

	return array;
}
#pragma endregion

#pragma region ValidateTransport
/*
	|--------------------------------------------------------------------------
	| Validate transport
	|--------------------------------------------------------------------------
	|
	| Verifies if the given id matches with a existing transport id in
	| the linked list.
	| Return a boolean value accordingly.
	|
*/
int validate_transport(Transport* head, int id) {
	Transport* current = head;

	while (current != NULL) {
		if (current->id == id) return 1;
		current = current->next;
	}

	return 0;
}
#pragma endregion