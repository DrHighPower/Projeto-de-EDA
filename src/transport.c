#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/transport.h"
#include "../include/additional_functions.h"

#define MAX_LINE_LENGTH 1024

int store_transports(Transport* transport, int bool) {
	FILE* fp;

	// Open different files to write
	if(bool) fp = fopen("resources/transports.txt", "w");
	else fp = fopen("resources/transports.bin", "wb");

	if (fp != NULL){
		Transport* current = transport;

		// Run through the transport list
		while (current != NULL) {
			fprintf(fp, "%d;%d;%d;%f;%s;%s\n", current->id, current->battery, current->autonomy, current->price, current->type, current->geocode);
			current = current->next;
		}
		fclose(fp);

		return 1;
	}

	return 0;
}

int read_transports(Transport* transport, int bool) {
	FILE* fp;

	// Open different files to write
	if (bool) fp = fopen("resources/transports.txt", "r");
	else fp = fopen("resources/transports.bin", "rb");

	if (fp != NULL) {
		char file_info[MAX_LINE_LENGTH];
		char** split_file_info = NULL;
		
		// Run through every line
		while (fgets(file_info, MAX_LINE_LENGTH, fp) != NULL) {
			// Removing trailing newline character 
			newline_remove(file_info);

			// Splits the string of the line in the file
			int array_size = str_split(file_info, &split_file_info, ";");

			for (int i = 0; i < array_size; i++) {
				printf("%s\n", split_file_info[i]);
				free(split_file_info[i]);
			}
		}
		fclose(fp);

		return 1;
	}

	return 0;
}