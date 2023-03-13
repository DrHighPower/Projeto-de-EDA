#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "../include/user.h"
#include "../include/transport.h"
#include "../include/authentication.h"

int main() {
	Transport* test = (Transport*)malloc(sizeof(Transport));
	test->next = NULL;

	test = read_transports(test, 1);

	list_geocode(test);
	
	/*User* test = (User*)malloc(sizeof(User));
	test->next = NULL;

	test = read_users(test, 1);

	edit_user(&test, 2);*/
	
	while (test != NULL) {
		printf("%d\n", test->id);
		test = test->next;
	}

	/*User* test = (User*)malloc(sizeof(User));
	test->next = NULL;

	test = read_users(test, 1);

	int id;
	registers(&test, &id);
	printf("%d", id);*/
	

	return 0;
}