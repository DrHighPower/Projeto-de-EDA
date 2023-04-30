#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/graph.h"
#include "../include/transport.h"

#define MAX_LINE_LENGTH 1024

void save_node(Graph* current, char* geocode) {
	current->geocode = (char*)malloc(MAX_LINE_LENGTH / 3 * sizeof(char));
	strcpy(current->geocode, geocode);

	current->edge = NULL;
	current->next = NULL;
}

int insert_node(Graph* head, char* geocode) {
	Graph* current = head;

	// Goes to the last node in the list
	while (current->next != NULL) {
		// Check if there is a duplicated geocode
		if (strcmp(current->geocode, geocode) == 0) return 0;

		current = current->next;
	}

	// Check if its the first node
	if (current->geocode == NULL) {
		save_node(current, geocode);
	}
	else {
		current->next = (Graph*)malloc(sizeof(Graph));
		save_node(current->next, geocode);
	}

	return 1;
}

int remove_node(Graph** head, char* geocode) {
	Graph* current = *head;

	// Remove the first node
	if (strcmp(current->geocode, geocode) == 0 && current != NULL) {
		*head = current->next;
		free(current);
		return 1;
	}

	Graph* previous = NULL;

	// Remove the midle and last nodes
	while (current != NULL) {
		previous = current;
		current = current->next;

		if (current == NULL) return 0;

		if (strcmp(current->geocode, geocode) == 0) {
			if (current->next != NULL) previous->next = current->next;
			else previous->next = NULL;

			free(current);
			return 1;
		}
	}

	return 0;
}

int insert_edge(Graph* head, Vertex* vertex, char* from, float weight) {
	Graph* current = head;

	// Goes to the corresponding node
	while (strcmp(current->geocode, from) != 0) {
		current = current->next;

		// Return 0 if the node doesnt exist
		if (current == NULL) return 0;
	}

	Edge* current_edge = current->edge;

	// If the edge list is empty
	if (current_edge == NULL) {
		current_edge = (Edge*)malloc(sizeof(Edge));

		// Save the new info
		current_edge->weight = weight;
		current_edge->vertex = vertex;
		current_edge->next = NULL;
		current->edge = current_edge;

		return 1;
	}

	// Travel to the last edge
	while (current_edge->next != NULL) {
		// Return 0 if the vertex already exists
		if (strcmp(current_edge->vertex->geocode, vertex->geocode) == 0) return 0;
		current_edge = current_edge->next;
	}

	// Create the new edge
	if (strcmp(current_edge->vertex->geocode, vertex->geocode) != 0) {
		Edge* new_edge = (Edge*)malloc(sizeof(Edge));

		// Save the new info
		new_edge->weight = weight;
		new_edge->vertex = vertex;
		new_edge->next = NULL;
		current_edge->next = new_edge;
		return 1;
	}

	return 0;
}

int remove_edge(Graph** head, Vertex* vertex, char* from) {
	Graph* current = *head;

	// Goes to the corresponding node
	while (strcmp(current->geocode, from) != 0) {
		current = current->next;

		// Return 0 if the node doesnt exist
		if (current == NULL) return 0;
	}

	if (current->edge == NULL) return 0;
	Edge* current_edge = current->edge;

	// Remove the first node
	if (strcmp(current_edge->vertex->geocode, vertex->geocode) == 0) {
		current->edge = current_edge->next;
		free(current_edge);
		return 1;
	}

	Edge* previous_edge = NULL;

	// Remove the midle and last nodes
	while (current_edge != NULL) {
		previous_edge = current_edge;
		current_edge = current_edge->next;

		if (current_edge == NULL) return 0;

		if (strcmp(current_edge->vertex->geocode, vertex->geocode) == 0) {
			if (current_edge->next != NULL) previous_edge->next = current_edge->next;
			else previous_edge->next = NULL;

			free(current_edge);
			return 1;
		}
	}

	return 0;
}

Vertex* create_vertex(char* geocode) {
	Vertex* new_vertex = (Vertex*)malloc(sizeof(Vertex));
	new_vertex->geocode = (char*)malloc(MAX_LINE_LENGTH / 3 * sizeof(char));

	strcpy(new_vertex->geocode, geocode);
	new_vertex->transport_quantity = 0;
	new_vertex->transports = NULL;

	return new_vertex;
}

int remove_vertex(Graph** head, Vertex* vertex, Vertex** vertices, int array_size) {
	Graph* current = *head;

	// Remove all the edges with the same vertex in the graph
	while (current != NULL) {
		remove_edge(&current, vertex, current->geocode);
		current = current->next;
	}

	// Checks if the element was found
	int found = 0;
	for (int i = 0; i < array_size; i++) {
		if (strcmp(vertices[i]->geocode, vertex->geocode) == 0) found = 1;

		// Move every element down, and remove the last
		if (found && i + 1 <= array_size) vertices[i] = vertices[i + 1];
	}

	// Return the new array size
	return --array_size;
}

int add_vertex_transport(Vertex* vertex, Transport* transport) {
	vertex->transport_quantity++;
	vertex->transports = (Vertex*)realloc(vertex->transports, vertex->transport_quantity * sizeof(Vertex));
	vertex->transports[vertex->transport_quantity - 1] = transport;
}

int remove_vertex_transport(Vertex* vertex, int id) {

	// Checks if the element was found
	int found = 0;
	for (int i = 0; i < vertex->transport_quantity; i++) {
		if (vertex->transports[i]->id == id) found = 1;

		// Move every element down, and remove the last
		if (found && i + 1 <= vertex->transport_quantity) vertex->transports[i] = vertex->transports[i + 1];
	}

	if (found) {
		vertex->transport_quantity--;
		return 1;
	}
	else return 0;
}

int store_graph(Graph* head, int bool) {
	FILE* fp;

	// Open different files to write
	if (bool) fp = fopen("resources/graph.txt", "w");
	else fp = fopen("resources/graph.bin", "wb");

	if (fp == NULL) {
		printf("Ocorreu um erro a abrir o ficheiro\n");
		return 0;
	}

	Graph* current = head;

	// Go throught the graph
	while (current != NULL) {
		Edge* current_edge = current->edge;

		// Go through each edge
		while (current_edge != NULL) {
			fprintf(fp, "%s;%s;%.2f\n", current->geocode, current_edge->vertex->geocode, current_edge->weight);

			current_edge = current_edge->next;
		}

		current = current->next;
	}
	fclose(fp);

	return 1;
}

int store_vertices(Vertex** vertices, int array_size, int bool) {
	FILE* fp;

	// Open different files to write
	if (bool) fp = fopen("resources/vertices.txt", "w");
	else fp = fopen("resources/vertices.bin", "wb");

	if (fp == NULL) {
		printf("Ocorreu um erro a abrir o ficheiro\n");
		return 0;
	}

	// Go through the vertices array
	for (int i = 0; i < array_size; i++) {

		// Go through the transports array
		for (int j = 0; j < vertices[i]->transport_quantity; j++) {
			fprintf(fp, "%s;%d\n", vertices[i]->geocode, vertices[i]->transports[j]->id);
		}
		if(vertices[i]->transport_quantity == 0) fprintf(fp, "%s;\n", vertices[i]->geocode);
	}

	return 1;
}