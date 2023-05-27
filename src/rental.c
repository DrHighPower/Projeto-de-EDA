#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/rental.h"
#include "../include/additional_functions.h"
#include "../include/transport.h"
#include "../include/user.h"

#pragma region CheckRental
/*
	|--------------------------------------------------------------------------
	| Check if transport is rented
	|--------------------------------------------------------------------------
	|
	| Checks the rental status of a transport with a given id.
	| Returns 1 if the transport with the given id is rented, 0 if it is 
	| available for rent or not found.
	|
*/
int check_rental(Transport* head, int id) {
	Transport* current = head;

	// Go through the transport linked list
	while (current != NULL) {
		if (current->id == id && current->rented == 1) return 1;
		else if(current->id == id) return 0;

		current = current->next;
	}

	return 0;
}
#pragma endregion

#pragma region StartRental
/*
	|--------------------------------------------------------------------------
	| Start rental
	|--------------------------------------------------------------------------
	|
	| Initiates a rental process for a user and a transport. 
	| It verifies if both the user and transport are valid.
	| Returns a pointer to the Rental struct representing the started 
	| rental process, or NULL if the rental process could not be started.
	|
*/
Rental* start_rental(User* user, Transport* transport) {
	if (user == NULL && transport == NULL) return NULL;

	// Check if the user has enough balance
	if (user->balance >= transport->price) {
		Rental* new_rental = (Rental*)malloc(sizeof(Rental));

		// Get the current time
		time(&new_rental->start_time);

		// Store the user and transport
		new_rental->user_id = user->id;
		new_rental->transport_id = transport->id;

		// Change the boolean check
		transport->rented = 1;

		return new_rental;
	}

	return NULL;
}
#pragma endregion

#pragma region PayRental
/*
	|--------------------------------------------------------------------------
	| Pay for the rental
	|--------------------------------------------------------------------------
	|
	| Calculates and makes the payment needed to rent the transport,
	| changing the users balance in the linked.
	|
*/
void pay_rental(User* user, Transport* transport, int minutes_used) {
	
	// Pay for at leat one minute
	if (minutes_used < 1) minutes_used = 1;

	// Save the payment needed
	float payment = transport->price * minutes_used;

	// Make the payment
	user->balance -= payment;
	if (user->balance < 0) user->balance = 0;
}
#pragma endregion

#pragma region StoreRental
/*
	|--------------------------------------------------------------------------
	| Store the new rental
	|--------------------------------------------------------------------------
	|
	| Stores the rental in a file.
	| If the bool parameter is 0 it stores the rental inside a binary file,
	| if the bool parameter is 1 it stores the rental inside a text file.
	| Returns a boolean value accordingly.
	|
*/
int store_rental(Rental* rental, int minutes_used, int bool) {
	FILE* fp;

	// Open different files to write
	if (bool) fp = fopen("resources/rentals.txt", "a");
	else fp = fopen("resources/rentals.bin", "ab");

	if (fp == NULL) {
		printf("Ocorreu um erro a abrir o ficheiro\n");
		return 0;
	}

	// Stores the timestamp
	struct tm  timestamp;

	// Stores the starting date and timr
	char start_date[11], start_time[6];

	// Get the starting date and starting time
	timestamp = *localtime(&rental->start_time);
	strftime(start_date, sizeof(start_date), "%d-%m-%Y", &timestamp);
	strftime(start_time, sizeof(start_time), "%H:%M", &timestamp);

	// Add the minutes to the time
	char* endDateTime = { add_minutes(start_time, start_date, minutes_used) };

	// Splits the string into a array
	char** endDateTimeArray = NULL;
	str_split(endDateTime, &endDateTimeArray, " ");

	fprintf(fp, "%d;%d;%s;%s;%s;%s\n", rental->user_id, rental->transport_id, start_date, start_time, endDateTimeArray[0], endDateTimeArray[1]);
	fclose(fp);

	free(endDateTimeArray);

	return 1;
}
#pragma endregion

#pragma region StopRental
/*
	|--------------------------------------------------------------------------
	| Start rental
	|--------------------------------------------------------------------------
	|
	| Stops a rental process and performs necessary operations.
	| Returns 1 if the rental process was stopped and all necessary 
	| operations were performed successfully, 0 otherwise.
	|
*/
int stop_rental(Rental** rental, User* head_user, Transport* head_transport, int bool) {

	// Stores the current time
	time_t current_time;
	time(&current_time);

	// Stores the minutes the transport was used
	int minutes_used = (current_time - (*rental)->start_time) / 60;

	// Stores the user and the transported that where in the rental
	User* user = get_user(head_user, (*rental)->user_id);
	Transport* transport = get_transport(head_transport, (*rental)->transport_id);

	// Pay the rental and change the user balance in the file
	pay_rental(user, transport, minutes_used);
	if(!store_users(head_user, bool)) return 0;

	// Store the new rental
	if (!store_rental(*rental, minutes_used, bool)) return 0;

	*rental = NULL;

	return 1;
}
#pragma endregion