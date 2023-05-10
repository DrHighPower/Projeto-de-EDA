#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "../include/user.h"
#include "../include/transport.h"
#include "../include/authentication.h"
#include "../include/rental.h"
#include "../include/graph.h"

#pragma region ManagerMenu
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
#pragma endregion

#pragma region Main
int main() {
	setlocale(LC_ALL, "Portuguese");
	setlocale(LC_NUMERIC, "English"); // Effects the decimal point formatting so its "." and not ",";
	
	Graph* loaded_graph = (Graph*)malloc(sizeof(Graph));
	loaded_graph->geocode = NULL;
	loaded_graph->edge = NULL;
	loaded_graph->next = NULL;

	/*insert_node(loaded_graph, "acabam.gols.durou");
	insert_node(loaded_graph, "latões.matos.sacos");
	insert_node(loaded_graph, "doçura.molho.idades");*/

	int array_size = 3;
	Vertex** array = (Vertex*)malloc(array_size+1 * sizeof(Vertex));
	/*array[0] = create_vertex("acabam.gols.durou");
	array[1] = create_vertex("latões.matos.sacos");
	array[2] = create_vertex("doçura.molho.idades");*/

	/*insert_edge(loaded_graph, array[1], "acabam.gols.durou", 10);
	insert_edge(loaded_graph, array[2], "acabam.gols.durou", 24);
	insert_edge(loaded_graph, array[0], "latões.matos.sacos", 3);
	insert_edge(loaded_graph, array[1], "doçura.molho.idades", 20);*/

	Transport* loaded_transports = (Transport*)malloc(sizeof(Transport));
	loaded_transports->next = NULL;
	loaded_transports = read_transports(loaded_transports, 0);

	User* loaded_users = (User*)malloc(sizeof(User));
	loaded_users->next = NULL;
	loaded_users = read_users(loaded_users, 0);

	/*add_vertex_transport(array[0], loaded_transports);
	add_vertex_transport(array[0], loaded_transports->next->next);
	add_vertex_transport(array[1], loaded_transports->next);*/

	/*add_vertex_users(array[0], loaded_users);
	add_vertex_users(array[2], loaded_users->next);
	add_vertex_users(array[2], loaded_users->next->next);*/

	//remove_node(&loaded_graph, "4");
	//remove_edge(&loaded_graph, array[0], "1");
	//array_size = remove_vertex(&loaded_graph, array[1], array, array_size);
	//remove_vertex_transport(array[1], 2);

	/*store_graph(loaded_graph, 1);
	store_vertices(array, array_size, 1);*/

	array = read_vertices(array, &array_size, loaded_transports, loaded_users, 1);
	loaded_graph = read_graph(loaded_graph, array, array_size, 1);

	int vertices_size = 2;
	Vertex** vertices = get_nearest_vertices(loaded_graph, &vertices_size,user_geodode(array, array_size, 1), 50);
	for (int i = 0; i < vertices_size - 2; i++) {
		for (int j = 0; j < vertices[i]->transport_quantity; j++) {
			if (strcmp(vertices[i]->transports[j]->type, "Trotinete") == 0)
				printf("Id: %d, Geocódigo: %s, Tipo: %s, Bateria: %d\n", vertices[i]->transports[j]->id, vertices[i]->geocode, vertices[i]->transports[j]->type, vertices[i]->transports[j]->battery);
		}
	}
	free(vertices);


	/*
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
			else printf("Utilizador não encontrado ou password errada.\n\n");
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
				{
					int transport_quant;
					Transport** autonomy_array = list_autonomy(loaded_transports, &transport_quant);

					// Prints all the sorted tranports
					for (int i = 0; i < transport_quant; i++) {
						printf("Id: %d\n", autonomy_array[i]->id);
						printf("Autonomy: %d\n", autonomy_array[i]->autonomy);
						printf("Bateria: %d\n", autonomy_array[i]->battery);
						printf("Preço: %.2f\n", autonomy_array[i]->price);
						printf("Volume: %.2fm3\n", autonomy_array[i]->volume);
						printf("Tipo: %s\n", autonomy_array[i]->type);
						printf("Geocódigo: %s\n", autonomy_array[i]->geocode);

						// Print a line until the last one
						if (i != transport_quant - 1) printf("-------------------------\n");
					}

					free(autonomy_array);
				}
				break;
			case 2:
				{
					int transport_quant;
					Transport** geocode_array = list_geocode(loaded_transports, &transport_quant);

					// Prints all the tranports with the same geocode
					for (int i = 0; i < transport_quant; i++) {
						printf("Id: %d\n", geocode_array[i]->id);
						printf("Autonomy: %d\n", geocode_array[i]->autonomy);
						printf("Bateria: %d\n", geocode_array[i]->battery);
						printf("Preço: %.2f\n", geocode_array[i]->price);
						printf("Volume: %.2fm3\n", geocode_array[i]->volume);
						printf("Tipo: %s\n", geocode_array[i]->type);
						printf("Geocódigo: %s\n", geocode_array[i]->geocode);

						// Print a line until the last one
						if (i != transport_quant - 1) printf("-------------------------\n");
					}

					free(geocode_array);
				}
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
	*/
	return 0;
}
#pragma endregion