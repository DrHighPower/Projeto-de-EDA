#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "../include/rental.h"
#include "../include/additional_functions.h"
#include "../include/transport.h"
#include "../include/user.h"

int pay_rental(User** head_user, Transport* head_transport, int user_id, int transport_id, int min_used, int bool) {
	User* current_user = *head_user;
	Transport* current_transport = head_transport;

	// Get to the position of the respective ids in the lists
	while (current_user != NULL && current_user->id != user_id) {
		current_user = current_user->next;
	}
	while (current_transport != NULL && current_transport->id != transport_id) {
		current_transport = current_transport->next;
	}

	// Save the payment needed
	float payment = current_transport->price * min_used;

	// Check if the user's balance is enough to make the payment
	if (current_user->balance > payment) {
		current_user->balance -= payment;

		store_users(*head_user, bool);
	}
	else {
		printf("Saldo insuficiente!\n");
		return 0;
	}

	return 1;
}

int store_rental(User** head_user, Transport* head_transport, int user_id, int transport_id, int bool) {
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

	if (!pay_rental(head_user, head_transport, user_id, transport_id, min_used, bool)) {
		fclose(fp);
		return 0;
	}

	fprintf(fp, "%d;%d;%s;%s;%s;%s\n", user_id, transport_id, start_date, start_time, endDateTimeArray[0], endDateTimeArray[1]);
	fclose(fp);

	return 0;
}