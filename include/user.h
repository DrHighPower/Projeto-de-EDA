enum UserType { Client, Manager };

typedef struct userInformation {
	int id, NIF;
	float balance;
	char *name, *residency;
	enum UserType type;
	struct userInformation* next;
} User;