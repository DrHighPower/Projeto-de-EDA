#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "../include/user.h"
#include "../include/transport.h"
#include "../include/authentication.h"
#include "../include/rental.h"

/*
	|--------------------------------------------------------------------------
	| Manager menu
	|--------------------------------------------------------------------------
	|
	| Creates a menu for the users with the manager type
	|
*/
void manager_menu(User* loaded_users, Transport* loaded_transport) {
	// Variable that stores the user's choice
	int choice;

	do {
		// Print menu
		printf("\nMenu dos gestores:\n");
		printf("1. Adicionar utilizadores\n");
		printf("2. Remover utilizadores\n");
		printf("3. Adicionar meio de transporte\n");
		printf("4. Editar meio de transporte\n");
		printf("5. Remover meio de tranporte\n");
		printf("6. Salvar alterações\n");
		printf("7. Sair\n");
		printf("_________________________________\n");
		printf("Insira a sua escolha: ");

		// Read the user's choice
		scanf("%d", &choice);
		getchar();
		printf("\n");

		switch (choice) {
			case 1:
				{ // Use of curly brackets because you can't declare a variable inside a case statement
					
					// Get the user input
					int new_user_type;
					printf("Tipo do novo utilizador (Cliente: 0/Gestor: 1): ");
					scanf("%d", &new_user_type);
					getchar();

					insert_user(&loaded_users, new_user_type);
				}
				break;
			case 2:
				{
					// Get the user input
					int remove_user_id;
					printf("Id do utilizador a ser removido: ");
					scanf("%d", &remove_user_id);
					getchar();

					remove_user(&loaded_users, remove_user_id);
				}
				break;
			case 3:
				insert_tranport(&loaded_transport);
				break;
			case 4:
				{
					int edit_tranport_id;
					printf("Id do meio de transporte a ser editado: ");
					scanf("%d", &edit_tranport_id);
					getchar();

					edit_transport(&loaded_transport, edit_tranport_id);
				}
				break;
			case 5:
				{
					// Get the user input
					int remove_transpot_id;
					printf("Id do meio de transporte a ser removido: ");
					scanf("%d", &remove_transpot_id);
					getchar();

					remove_transport(&loaded_transport, remove_transpot_id);
				}
				break;
			case 6:
				store_users(loaded_users, 0);
				store_transports(loaded_transport, 0);
				break;
			case 7:
				break;
			default:
				// If the user's choice is invalid, print an error message
				printf("Escolha invalida!\n\n");
		}

	} while (choice != 7);
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	setlocale(LC_NUMERIC, "English"); // Effects the decimal point formatting so its "." and not ","

	// Load the users into the memory
	User* loaded_users = (User*)malloc(sizeof(User));
	loaded_users->next = NULL;

	loaded_users = read_users(loaded_users, 0);

	// Variable that stores the user's choice
	int choice;

	// Boolean variable for the while loop
	int bool = 1;

	// Variable that stores the user's id number
	int id;

	while (bool) {
		// Print menu
		printf("Autenticação:\n");
		printf("1. Iniciar sessão\n");
		printf("2. Registo\n");
		printf("________________\n");
		printf("Insira a sua escolha: ");

		// Read the user's choice
		scanf("%d", &choice);
		getchar();
		printf("\n");

		switch (choice) {
		case 1:
			if (login(loaded_users, &id)) bool = 0;
			else printf("Utilizador não encontrado.\n\n");
			break;
		case 2:
			if (registers(&loaded_users, &id, 0)) {
				bool = 0;

				// Save the new user in the file
				store_users(loaded_users, 0);
			}
			break;
		default:
			// If the user's choice is invalid, print an error message
			printf("Escolha invalida!\n\n");
		}
	}

	// Store the user's type
	int user_type = get_user_type(loaded_users, id);

	// Load the transports into the memory
	Transport* loaded_transports = (Transport*)malloc(sizeof(Transport));
	loaded_transports->next = NULL;

	loaded_transports = read_transports(loaded_transports, 0);

	do{
		// Print menu
		printf("\nMenu:\n");
		printf("1. Listagem dos meios de mobilidade por autonomia\n");
		printf("2. Listagem dos meios de mobilidade num geocódigo\n");
		printf("3. Editar dados do utilizador\n");
		printf("4. Alugar um meio de transporte\n");
		printf("5. Adicionar saldo\n");

		// Check if the user is a manager
		if (user_type) printf("7. Menu de gestores\n");

		printf("6. Sair\n");
		printf("_________________________________\n");
		printf("Insira a sua escolha: ");

		// Read the user's choice
		scanf("%d", &choice);
		getchar();
		printf("\n");

		switch (choice) {
			case 1:
				list_autonomy(loaded_transports);
				break;
			case 2:
				list_geocode(loaded_transports);
				break;
			case 3:
				edit_user(&loaded_users, id);
				break;
			case 4:
				{ // Use of curly brackets because you can't declare a variable inside a case statement
					
					// Store the transport id
					int transport_id = 0;

					// Get user's input
					printf("O id do meio de tranporte que quer alugar: ");
					scanf("%d", &transport_id);
					getchar();

					if (validate_transport(loaded_transports, transport_id)) store_rental(&loaded_users, loaded_transports, id, transport_id, 0);
					else printf("Meio de tranporte não encontrado.\n");
				}
				break;
			case 5:
				add_balance(&loaded_users, id, 0);
				break;
			case 6:
				break;
			case 7:
				if (user_type) {
					manager_menu(loaded_users, loaded_transports);
					break;
				}
			default:
				// If the user's choice is invalid, print an error message
				printf("Escolha invalida!\n");
		}

	} while (choice != 6);

	return 0;
}