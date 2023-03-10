#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "../include/user.h"
#include "../include/transport.h"


int main() {
	Transport* test = NULL;
	
	read_transports(test, 1);

	/*
	Transport* test = malloc(sizeof(Transport));

	test->id = 1;
	test->battery = 123;
	test->autonomy = 23;
	test->price = 10.99;
	test->type = "Bike";
	test->geocode = "acabam.gols.durou";
	

	test->next = malloc(sizeof(Transport));
	test->next->id = 1;
	test->next->battery = 22;
	test->next->autonomy = 35;
	test->next->price = 5;
	test->next->type = "Your mmo";
	test->next->geocode = "assa";
	test->next->next = NULL;

	storeTransports(test, 0);*/

	return 0;
}