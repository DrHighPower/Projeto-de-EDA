enum UserType { Client, Manager };

typedef struct userInformation {
	int id;
	float balance;
	char *name, *residency, NIF[10];
	enum UserType type;
	struct userInformation* next;
} User;

void free_user_list(User** head);
int store_users(User* head, int bool);
void save_user(User* current, int id, int NIF, float balance, char* name, char* residency, enum UserType type);
int store_users(User* head, int bool);
User* read_users(User* head, int bool);
int validate_NIF(char* number);
void insert_user(User** head, int user_type);