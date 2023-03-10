#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "../include/user.h"
#include "../include/transport.h"


int main() {
	User* test = NULL;
	
	read_users(test, 1);

	return 0;
}