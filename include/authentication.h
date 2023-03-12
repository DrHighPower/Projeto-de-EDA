typedef struct userInformation User;

int check_NIF(User* head, char NIF[10]);
int login(User* head, int* id);
int registers(User** head, int* id);