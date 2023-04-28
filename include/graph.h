/**
 * @file graph.h
 * @brief � o ficheiro que cont�m as difini��es necess�rias para utilizar o grafo.
 *
 * O graph.h � o ficheiro onde est�o declaradas a estrutura de dados e as fun��es que deixam a utilizar o grafo.
 *
 * @author Jo�o Telmo Barros Inverneiro
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
int insert_edge(Graph* head, Vertex* vertex, char* from, float weight);
Vertex* create_vertex(char* geocode);
int add_transport(Vertex* vertex, Transport* transport);