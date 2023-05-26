/**
 * @file graph.h
 * @brief É o ficheiro que contém as difinições necessárias para utilizar o grafo.
 *
 * O graph.h é o ficheiro onde estão declaradas a estrutura de dados e as funções que deixam a utilizar o grafo.
 *
 * @author João Telmo Barros Inverneiro
 */

typedef struct transportInformation Transport;
typedef struct userInformation User;

typedef struct vertexInformation {
	char *geocode;
	int transport_quantity,
		user_quantity;
	Transport** transports;
	User** users;
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

void free_edge_list(Edge** head);
void free_graph(Graph** head);

void save_node(Graph* current, char* geocode);
int insert_node(Graph* head, char* geocode);
int remove_node(Graph** head, char* geocode);

int insert_edge(Graph* head, Vertex* vertex, char* from, float weight);
int edit_edge(Graph** head, Vertex* vertex, char* from, float weight);
int remove_edge(Graph** head, Vertex* vertex, char* from);

Vertex* create_vertex(char* geocode);
int remove_vertex(Graph** head, Vertex* vertex, Vertex** vertices, int array_size);

Vertex* add_vertex_transport(Vertex* vertex, Transport* transport);
Vertex* add_vertex_users(Vertex* vertex, User* user);

int remove_vertex_transport(Vertex* vertex, int id);
int remove_vertex_user(Vertex* vertex, int id);

int store_graph(Graph* head, int bool);
int store_vertices(Vertex** vertices, int array_size, int bool);

Graph* read_graph(Graph* head, Vertex** vertex, int vertex_size, int bool);
Vertex** read_vertices(Vertex** vertex, int* vertex_size, Transport* transports, User* users, int bool);

char* user_geodode(Vertex** vertex, int vertex_size, int id);
Vertex** nearest_vertices(Graph* head, Vertex*** vertices, int* vertices_size, int* vertices_pos, char* location, float radius, float travelled, char*** geocodes_array, int* geocodes_size, int* geocodes_pos);
Vertex** get_nearest_vertices(Graph* graph, int* size, char* location, float radius);

int get_vertex_pos(Graph* head, char* geocode);
char* shortest_distance(Graph* graph_head, Edge* edge_head, float* distances, int* visited, int current_pos, int vertices_quant);
int get_path(Graph* head, char** geocodes, int geocodes_size, char*** path, int* path_size, int path_pos, float radius, float travelled, int iteration, char* location, char* destination, int* found);
float shortest_path(Graph* head, char*** path, char* from, char* to, int vertices_quant, int* path_size, int* path_pos);
Vertex** reduced_battery(Vertex** vertices, int vertices_quant, int* new_vertices_size);
char** shortest_circuit(Graph* head, Vertex** vertices, int vertices_quant, char* start, float truck_volume, int* circuit_size);