enum UserType { Client, Manager };

typedef struct userInformation {
	int id, NIF;
	float balance;
	char *name, *residency;
	enum UserType type;
	struct userInformation* next;
} User;

int store_users(User* head, int bool);
void save_user(User* current, int id, int NIF, float balance, char* name, char* residency, enum UserType type);
int store_users(User* head, int bool);
int read_users(User* head, int bool);