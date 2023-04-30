/**
 * @file graph.h
 * @brief É o ficheiro que contém as difinições necessárias para utilizar o grafo.
 *
 * O graph.h é o ficheiro onde estão declaradas a estrutura de dados e as funções que deixam a utilizar o grafo.
 *
 * @author João Telmo Barros Inverneiro
 */

typedef struct transportInformation Transport;

typedef struct vertexInformation {
	char *geocode;
	int transport_quantity;
	Transport** transports;
} Vertex;

typedef struct edgeInformation {
	float weight;
	struct vertexInformation* vertex;
	struct edgeInformation* next;
} Edge;

typedef struct graphInformation {
	char *geocode;
	struct edgeInformation* edge;
	struct graphInformation* next;
} Graph;

void save_node(Graph* current, char* geocode);
int insert_node(Graph* head, char* geocode);
int remove_node(Graph** head, char* geocode);

int insert_edge(Graph* head, Vertex* vertex, char* from, float weight);
int remove_edge(Graph** head, Vertex* vertex, char* from);

Vertex* create_vertex(char* geocode);
int remove_vertex(Graph** head, Vertex* vertex, Vertex** vertices, int array_size);
int add_vertex_transport(Vertex* vertex, Transport* transport);
int remove_vertex_transport(Vertex* vertex, int id);

int store_graph(Graph* head, int bool);
int store_vertices(Vertex** vertices, int array_size, int bool);