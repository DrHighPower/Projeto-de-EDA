#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#include "../include/additional_functions.h"
#include "../include/user.h"
#include "../include/transport.h"
#include "../include/authentication.h"
#include "../include/rental.h"
#include "../include/graph.h"

#define MAX_LINE_LENGTH 1024

int edge_functions( char* text, char* from, char* to, Vertex** vertices, int vertices_size, int* vertices_pos) {
	printf("%s\n", text);

	// Get the node geocode
	printf("De: ");
	fgets(from, MAX_LINE_LENGTH / 3, stdin);
	newline_remove(from);

	// Get the vertex geocode
	printf("Para: ");
	fgets(to, MAX_LINE_LENGTH / 3, stdin);
	newline_remove(to);

	// Get the vertex by the geocode
	for (*vertices_pos = 0; *vertices_pos < vertices_size; *vertices_pos = *vertices_pos + 1) {
		if (strcmp(vertices[*vertices_pos]->geocode, to) == 0) break;
	}

	// Check the vertex was found in the array
	if (*vertices_pos == vertices_size) {
		printf("Vertice de destino não encontrado\n");
		return 0;
	}
	return 1;
}

#pragma region ManagerMenu
/*
	|--------------------------------------------------------------------------
	| Manager menu
	|--------------------------------------------------------------------------
	|
	| Creates a menu for the users with the manager type
	|
*/
void manager_menu(User* loaded_users, Transport* loaded_transport, Graph* loaded_graph, Vertex*** loaded_vertices, int* vertices_size) {
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
		printf("6. Adicionar vertice\n");
		printf("7. Remover vertice\n");
		printf("8. Adicionar aresta\n");
		printf("9. Editar aresta\n");
		printf("10. Remover aresta\n");
		printf("11. Adicionar meio de transporte a um vertice\n");
		printf("12. Remover meio de transporte de um vertice\n");
		printf("13. Adicionar utilizador a um vertice\n");
		printf("14. Remover utilizador de um vertice\n");
		printf("15. Salvar alterações\n");
		printf("16. Caminho para remover os meios de transporte\n");
		printf("17. Sair\n");
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

					Transport* edited_transport = edit_transport(&loaded_transport, edit_tranport_id);

					printf("Tipo: %s, Geocódigo: %s, Bateria: %d, Autonomia: %d, Preço: %.2f, Volume: %.2f\n",
						edited_transport->type, edited_transport->geocode, edited_transport->battery, edited_transport->autonomy, edited_transport->price, edited_transport->volume);
				}
				break;
			case 5:
				{
					// Get the user input
					int remove_transpot_id;
					printf("Id do meio de transporte a ser removido: ");
					scanf("%d", &remove_transpot_id);
					getchar();

					if (!remove_transport(&loaded_transport, remove_transpot_id)) printf("Ocorreu algum erro ao eliminar o meio de tranporte!");
				}
				break;
			case 6:
				{
					// Get the new geocode
					char new_geocode[MAX_LINE_LENGTH / 3];
					printf("Novo geocódigo a adicionar ao grafo: ");
					fgets(new_geocode, MAX_LINE_LENGTH / 3, stdin);
					newline_remove(new_geocode);

					// Inserts and checks if the geocode is not duplicated
					if (insert_node(loaded_graph, new_geocode)) {

						// Allocate memory for the new vertex
						(*loaded_vertices)[*vertices_size] = (Vertex*)malloc(sizeof(Vertex));

						// Reallocate memory for the array of vertices
						*vertices_size = *vertices_size + 1;
						*loaded_vertices = (Vertex**)realloc(*loaded_vertices, *vertices_size * sizeof(Vertex*));

						// Create new vertex
						(*loaded_vertices)[*vertices_size - 1] = create_vertex(new_geocode);
					}
					else printf("Vertice já existente no grafo.\n");
				}
				break;
			case 7:
				{
					// Get the geocode to be removed
					char remove_geocode[MAX_LINE_LENGTH / 3];
					printf("Geocódigo a remover do grafo: ");
					fgets(remove_geocode, MAX_LINE_LENGTH / 3, stdin);
					newline_remove(remove_geocode);

					// Get the vertex by the geocode
					int vertices_pos;
					for (vertices_pos = 0; vertices_pos < *vertices_size; vertices_pos++) {
						if (strcmp((*loaded_vertices)[vertices_pos]->geocode, remove_geocode) == 0) break;
					}

					// Check if the vertex was found and then remove it
					if (vertices_pos != *vertices_size) {
						*vertices_size = remove_vertex(&loaded_graph, (*loaded_vertices)[vertices_pos], *loaded_vertices, *vertices_size);
						remove_node(&loaded_graph, remove_geocode);
					}
					else printf("Vertice não encontrado no grafo.\n");
				}
				break;
			case 8:
				{
					char from[MAX_LINE_LENGTH / 3]; // Stores the node geocode that the vertex is gonna be connected to 
					char to[MAX_LINE_LENGTH / 3];	// Stores the vertex geocode
					float weight;					// Stores the weight
					int vertices_pos = 0;			// Stores the position of the vertex

					// Ask the user for input
					if (!edge_functions("Adicionar uma aresta", from, to, *loaded_vertices, *vertices_size, &vertices_pos)) break;
					
					// Get the weight
					printf("Distância, em metros, dos vertices: ");
					scanf("%f", &weight);

					if(!insert_edge(loaded_graph, (*loaded_vertices)[vertices_pos], from, weight)) printf("Vertices não encontrados ou já existe aresta\n");
				}
				break;
			case 9:
				{
					char from[MAX_LINE_LENGTH / 3]; // Stores the node geocode that the vertex is gonna be connected to 
					char to[MAX_LINE_LENGTH / 3];	// Stores the vertex geocode
					float weight;					// Stores the weight
					int vertices_pos = 0;			// Stores the position of the vertex

					// Ask the user for input
					if (!edge_functions("Editar uma aresta", from, to, *loaded_vertices, *vertices_size, &vertices_pos)) break;

					// Get the new weight
					printf("Nova distância, em metros, dos vertices: ");
					scanf("%f", &weight);

					if (!edit_edge(&loaded_graph, (*loaded_vertices)[vertices_pos], from, weight)) printf("Vertices não encontrados\n");
				}
				break;
			case 10:
				{
					char from[MAX_LINE_LENGTH / 3]; // Stores the node geocode that the vertex is gonna be connected to 
					char to[MAX_LINE_LENGTH / 3];	// Stores the vertex geocode
					float weight;					// Stores the weight
					int vertices_pos = 0;			// Stores the position of the vertex

					// Ask the user for input
					if (!edge_functions("Remover uma aresta", from, to, *loaded_vertices, *vertices_size, &vertices_pos)) break;

					if (!remove_edge(&loaded_graph, (*loaded_vertices)[vertices_pos], from)) printf("Vertices não encontrados\n");
				}
				break;
			case 11:
				{
					char geocode[MAX_LINE_LENGTH / 3]; // Stores the vertex geocode
					int transport_id;				   // Stores the tranport id
					int vertices_pos = 0;			   // Stores the position of the vertex 

					// Get the geocode
					printf("Geocódigo do vertice a adicionar o meio de transporte: ");
					fgets(geocode, MAX_LINE_LENGTH / 3, stdin);
					newline_remove(geocode);

					// Get the transport id
					printf("Id do meio de transporte a adicionar no vertice: ");
					scanf("%d", &transport_id);

					// Goes through all the vertices and removes all the transports with the same id, meaning that there cant be a duplicate
					for (int i = 0; i < *vertices_size; i++) {

						// If the transport is in another vertex it is removed
						remove_vertex_transport((*loaded_vertices)[i], transport_id);

						// Check if the vertex with the same geocode was found
						if (strcmp((*loaded_vertices)[i]->geocode, geocode) == 0) vertices_pos = i;
					}

					// Get the transport to add in the vertex
					Transport* added_transport = get_transport(loaded_transport, transport_id);

					add_vertex_transport((*loaded_vertices)[vertices_pos], added_transport);
				}
				break;
			case 12:
				{
					int transport_id; // Stores the tranport id
					int found = 0;	  // Stores a boolean to check if any transport was removed

					// Get the transport id
					printf("Id do meio de transporte que é para remover dos vertices: ");
					scanf("%d", &transport_id);

					// Goes through all the vertices and removes all the transports with the same id
					for (int i = 0; i < *vertices_size; i++) {
						if (remove_vertex_transport((*loaded_vertices)[i], transport_id)) found = 1;
					}

					// Check if the transport was removed
					if (!found) printf("Não foi possivel remover o meio de transporte\n");
				}
				break;
			case 13:
				{
					char geocode[MAX_LINE_LENGTH / 3]; // Stores the vertex geocode
					int user_id;					   // Stores the user id
					int vertices_pos = 0;			   // Stores the position of the vertex 

					// Get the geocode
					printf("Geocódigo do vertice a adicionar o utilizador: ");
					fgets(geocode, MAX_LINE_LENGTH / 3, stdin);
					newline_remove(geocode);

					// Get the transport id
					printf("Id do utilizador a adicionar no vertice: ");
					scanf("%d", &user_id);

					// Goes through all the vertices and removes all the users with the same id, meaning that there cant be a duplicate
					for (int i = 0; i < *vertices_size; i++) {

						// If the user is in another vertex it is removed
						remove_vertex_user((*loaded_vertices)[i], user_id);

						// Check if the vertex with the same geocode was found
						if (strcmp((*loaded_vertices)[i]->geocode, geocode) == 0) vertices_pos = i;
					}

					// Get the user to add in the vertex
					User* added_user = get_user(loaded_users, user_id);

					add_vertex_users((*loaded_vertices)[vertices_pos], added_user);
				}
				break;
			case 14:
				{
					int user_id;   // Stores the user id
					int found = 0; // Stores a boolean to check if any transport was removed

					// Get the user id
					printf("Id do utilizador que é para remover dos vertices: ");
					scanf("%d", &user_id);

					// Goes through all the vertices and removes all the users with the same id
					for (int i = 0; i < *vertices_size; i++) {
						if (remove_vertex_user((*loaded_vertices)[i], user_id)) found = 1;
					}

					// Check if the user was removed
					if (!found) printf("Não foi possivel remover o utilizador\n");
				}
				break;
			case 15:
				store_users(loaded_users, 0);
				store_transports(loaded_transport, 0);
				store_graph(loaded_graph, 0);
				store_vertices(*loaded_vertices, *vertices_size, 0);
				break;
			case 16:
				{
					char start_vertex[MAX_LINE_LENGTH / 3]; // Stores the starting position
					float truck_volume = 0;					// Stores the max truck volume
					int circuit_size = 0;					// Stores the size of the circuit

					// Get the starting point
					printf("Ponto de partida: ");
					fgets(start_vertex, MAX_LINE_LENGTH / 3, stdin);
					newline_remove(start_vertex);

					while (truck_volume < 2) {
						// Get the truck volume
						printf("Volume maximo em metros cúbicos do camião: ");
						scanf("%f", &truck_volume);

						if (truck_volume < 2) printf("O volume do camião tem de ser 2 ou mais metros cúbicos!\n");
					}

					// Get the circuit
					char** circuit = shortest_circuit(loaded_graph, *loaded_vertices, *vertices_size, start_vertex, truck_volume, &circuit_size);

					// Print the circuit
					for (int i = 0; i < circuit_size; i++) {
						printf("%s", circuit[i]);

						if (i != circuit_size - 1) printf(" -> ");
					}
				}
				break;
			case 17:
				break;
			default:
				// If the user's choice is invalid, print an error message
				printf("Escolha invalida!\n\n");
		}

	} while (choice != 16);
}
#pragma endregion

#pragma region Main
int main() {
	setlocale(LC_ALL, "Portuguese");
	setlocale(LC_NUMERIC, "English"); // Effects the decimal point formatting so its "." and not ",";
	
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

	// Load the vertices into the memory
	int vertices_size = 2;
	Vertex** loaded_vertices = (Vertex*)malloc(vertices_size * sizeof(Vertex));

	loaded_vertices = read_vertices(loaded_vertices, &vertices_size, loaded_transports, loaded_users, 0);

	// Load the graph into the memory
	Graph* loaded_graph = (Graph*)malloc(sizeof(Graph));
	loaded_graph->geocode = NULL;
	loaded_graph->edge = NULL;
	loaded_graph->next = NULL;

	loaded_graph = read_graph(loaded_graph, loaded_vertices, vertices_size, 0);

	// Stores the rental process
	Rental* rented = NULL;

	do{
		// Print menu
		printf("\nMenu:\n");
		printf("1. Listagem dos meios de mobilidade por autonomia\n");
		printf("2. Listagem dos meios de mobilidade num geocódigo\n");
		printf("3. Editar dados do utilizador\n");
		printf("4. Alugar um meio de transporte\n");
		printf("5. Párar de alugar um meio de transporte\n");
		printf("6. Adicionar saldo\n");
		printf("7. Meios de transporte num raio\n");

		// Check if the user is a manager
		if (user_type) printf("9. Menu de gestores\n");

		printf("8. Sair\n");
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
				{
					User* edited_user = edit_user(&loaded_users, id);
					printf("Nome: %s, Residencia: %s, NIF: %s\n",
						edited_user->name, edited_user->residency, edited_user->NIF);
				}
				break;
			case 4:
				{ // Use of curly brackets because you can't declare a variable inside a case statement
					
					int transport_id = 0; // Store the transport id
					char choise;		  // Stores the user's choice

					// Check if the user is already renting a transport
					if (rented != NULL) {
						printf("Já está a alugar um meio de transporte, quer continuar? (S/N)\n");
						scanf("%c", &choise);
						getchar();

						if (choise == 'N' || choise == 'n') break;
						
						stop_rental(&rented, loaded_users, loaded_transports, 0);
					}

					// Get user's input
					printf("O id do meio de tranporte que quer alugar: ");
					scanf("%d", &transport_id);
					getchar();

					// Get the transport to be rented
					Transport* to_rent = get_transport(loaded_transports, transport_id);
					if (to_rent == NULL) {
						printf("O meio de transporte não foi encontrado.");
						break;
					}

					// Get user's choice
					printf("\nPreço por minuto: %.2f\n", to_rent->price);
					printf("Quer continuar o processo de aluguer? (S/N)\n");
					scanf("%c", &choise);
					getchar();

					if (choise == 'N' || choise == 'n') break;

					if (!check_rental(loaded_transports, transport_id)) {
						rented = start_rental(get_user(loaded_users, id), to_rent);
						printf("O meio de transporte foi alugado.");
					}
					else printf("O meio de transporte já está a ser alugado.");
				}
				break;
			case 5:
				if(stop_rental(&rented, loaded_users, loaded_transports, 0)) printf("O meio de transporte parou de ser alugado.");
				else printf("Ocorreu um erro a parar de alugar");
				break;
			case 6:
				add_balance(&loaded_users, id, 0);
				break;
			case 7:
				{
					float searched_radius = 0;				 // Stores the radius the user will search for transports
					char searched_type[MAX_LINE_LENGTH / 3]; // Stores the transport type searched

					// Get radius
					printf("Qual é o raio que quer procurar por um meio de transporte?\n");
					scanf("%f", &searched_radius);
					getchar(); // Get the new line character

					// Get the type
					printf("Qual o tipo de transporte a procurar?\n");
					fgets(searched_type, MAX_LINE_LENGTH / 3, stdin);
					newline_remove(searched_type);
					
					// Get the tranports in the radius
					int near_vertices_size = 2, has_transport = 0;
					Vertex** near_vertices = get_nearest_vertices(loaded_graph, &near_vertices_size, user_geodode(loaded_vertices, vertices_size, id), searched_radius);
					
					// Go through the vertices and transports array
					for (int i = 0; i < near_vertices_size - 2; i++) {
						for (int j = 0; j < near_vertices[i]->transport_quantity; j++) {

							// Check if its the transport type searched
							if (strcmp(near_vertices[i]->transports[j]->type, searched_type) == 0) {

								// Print the transporte info
								printf("Id: %d, Geocódigo: %s, Tipo: %s, Bateria: %d\n", near_vertices[i]->transports[j]->id, near_vertices[i]->geocode, near_vertices[i]->transports[j]->type, near_vertices[i]->transports[j]->battery);
								has_transport = 1;
							}	
						}
					}
					free(near_vertices);

					// Print if no transport was found
					if (!has_transport) printf("Nenhum transporte foi encontrado.\n");
				}
				break;
			case 8:
				break;
			case 9:
				if (user_type) {
					manager_menu(loaded_users, loaded_transports, loaded_graph, &loaded_vertices, &vertices_size);
					break;
				}
			default:
				// If the user's choice is invalid, print an error message
				printf("Escolha invalida!\n");
		}

		// Check if the user still has money to continue renting the transport
		if (rented != NULL) {
			User* current_user = get_user(loaded_users, id);
			Transport* rented_transport = get_transport(loaded_transports, rented->transport_id);

			// Stores the current time
			time_t current_time;
			time(&current_time);

			// Get the minutes
			int minutes_passed = (current_time - rented->start_time) / 60;
			if (minutes_passed < 1) minutes_passed = 1;

			// Check users money
			if (current_user->balance < rented_transport->price * minutes_passed) {
				stop_rental(&rented, loaded_users, loaded_transports, 0);
				printf("O aluguer do transporte acabou!\n");
			}
		}

	} while (choice != 8);

	return 0;
}
#pragma endregion