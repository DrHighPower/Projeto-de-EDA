#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "../include/rental.h"
#include "../include/additional_functions.h"

int store_rental(int user_id, int transport_id, int bool) {
	FILE* fp;

	// Open different files to write
	if (bool) fp = fopen("resources/rentals.txt", "a");
	else fp = fopen("resources/rentals.bin", "ab");

	if (fp == NULL) {
		printf("Ocorreu um erro a abrir o ficheiro\n");
		return 0;
	}

	// Store the users input
	char start_date[11], start_time[6];
	int min_used = 0;

	printf("Introduza a data em que o aluguer foi inciado (dd-mm-aa): ");
	fgets(start_date, 11, stdin);
	getchar();

	printf("Introduza a hora em que o aluguer foi iniciado (hh:mm): ");
	fgets(start_time, 6, stdin);

	printf("Introduza o tempo em minutos da duração do aluguer: ");
	scanf("%d", &min_used);
	getchar();

	// Add the minutes to the time
	char* endDateTime = { add_minutes(start_time, start_date, min_used) };

	// Splits the string into a array
	char** endDateTimeArray = NULL;
	str_split(endDateTime, &endDateTimeArray, " ");

	fprintf(fp, "%d;%d;%s;%s;%s;%s\n", user_id, transport_id, start_date, start_time, endDateTimeArray[0], endDateTimeArray[1]);
	fclose(fp);

	return 1;
}