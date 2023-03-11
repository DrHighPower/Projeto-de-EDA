#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "../include/user.h"
#include "../include/transport.h"

int main() {
	/*Transport* test = (Transport*)malloc(sizeof(Transport));
	test->next = NULL;

	test = read_transports(test, 1);

	insert_tranport(&test);
	*/
	
	User* test = (User*)malloc(sizeof(User));
	test->next = NULL;

	test = read_users(test, 1);

	insert_user(&test, 0);

	while (test != NULL) {
		printf("%d\n", test->id);
		test = test->next;
	}

	return 0;
}