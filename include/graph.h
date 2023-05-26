/**
 * @file graph.h
 * @brief � o ficheiro que cont�m as difini��es necess�rias para utilizar o grafo.
 *
 * O graph.h � o ficheiro onde est�o declaradas a estrutura de dados e as fun��es que deixam a utilizar o grafo.
 *
 * @author Jo�o Telmo Barros Inverneiro
 */

typedef struct transportInformation Transport;
typedef struct userInformation User;

/**
 * @struct vertexInformation
 * @brief Estrutura dos dados de um v�rtice.
 *
 * Esta estrutura de dados cont�m as diferentes informa��es de um v�rtice.
 */
typedef struct vertexInformation {
	char *geocode;				/**< O geoc�digo do v�rtice. */
	int transport_quantity,		/**< A quantidade de transportes. */
		user_quantity;			/**< A quantidade de utilizadores. */
	Transport** transports;		/**< Vetor de transportes. */
	User** users;				/**< Vetor de utilizadores. */
} Vertex;

/**
 * @struct edgeInformation
 * @brief Estrutura dos dados de uma aresta.
 *
 * Esta estrutura de dados cont�m as diferentes informa��es de uma aresta, esta tamb�m � uma lista ligada.
 */
typedef struct edgeInformation {
	float weight;							/**< O peso da aresta. */
	struct vertexInformation* vertex;		/**< O endere�o do v�rtice ligado � aresta */
	struct edgeInformation* next;			/**< O endere�o do pr�ximo n� da lista ligada. */
} Edge;

/**
 * @struct graphInformation
 * @brief Estrutura dos dados de um grafo.
 *
 * Esta estrutura de dados cont�m o formato do grafo, este tamb�m � uma lista ligada..
 */
typedef struct graphInformation {
	char *geocode;						/**< O geoc�digo do v�rtice. */
	struct edgeInformation* edge;		/**< O endere�o da aresta ligado ao v�rtice */
	struct graphInformation* next;		/**< O endere�o do pr�ximo n� da lista ligada. */
} Graph;

/**
 * @brief Percorre a lista ligada das arestas e liberta cada n�.
 *
 * Percorre a lista ligada das arestas e liberta cada n� e torna o primeiro n� em NULL.
 *
 * @param head A lista ligada das arestas a ser libertada.
 */
void free_edge_list(Edge** head);

/**
 * @brief Percorre a lista ligada do grafo e liberta cada n�.
 *
 * Percorre a lista ligada do grafo e liberta cada n� e torna o primeiro n� em NULL.
 *
 * @param head A lista ligada do grafo a ser libertada.
 */
void free_graph(Graph** head);

/**
 * @brief Guarda o geoc�digo para membro da estrutura de dados correspondente.
 *
 * @param current A estrutura de dados que guarda os par�metros.
 * @param geocode O geoc�digo a ser guardado.
 */
void save_node(Graph* current, char* geocode);

/**
 * @brief Insere um novo v�rtice no grafo.
 *
 * Insere um novo v�rtice no grafo no �ltimo n� da lista ligada.
 *
 * @param head A lista ligada a receber um novo v�rtice no grafo.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 *
 * @see save_node
 *
 * @note O novo v�rtice s� fica guardado na mem�ria.
 */
int insert_node(Graph* head, char* geocode);

/**
 * @brief Remove um v�rtice no grafo.
 *
 * Remove um v�rtice no grafo de uma lista ligada.
 *
 * @param head A lista ligada a ter o v�rtice no grafo removido.
 * @param geocode O geoc�digo do v�rtice no grafo a ser removido.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 *
 * @note O v�rtice s� fica removido na mem�ria.
 */
int remove_node(Graph** head, char* geocode);

/**
 * @brief Insere uma nova aresta no grafo.
 *
 * Insere uma nova aresta no �ltimo n� da lista ligada.
 *
 * @param head O grafo a receber uma nova aresta.
 * @param vertex O v�rtice a ser guardado na nova aresta.
 * @param from O geoc�digo do v�rtice que a aresta vai estar ligada no grafo.
 * @param weight O peso da nova aresta.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 *
 * @note A nova aresta s� fica guardada na mem�ria.
 */
int insert_edge(Graph* head, Vertex* vertex, char* from, float weight);

/**
 * @brief Edita uma aresta.
 *
 * Edita uma aresta num grafo.
 *
 * @param head O grafo que tem a aresta que vai ser editada.
 * @param vertex O v�rtice que a aresta tem guardado.
 * @param from O geoc�digo do v�rtice que a aresta esta ligada no grafo.
 * @param weight O novo peso da aresta.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 *
 * @note A aresta s� fica editada na mem�ria.
 */
int edit_edge(Graph** head, Vertex* vertex, char* from, float weight);

/**
 * @brief Remove uma aresta.
 *
 * Remove uma aresta de um grafo.
 *
 * @param head O grafo que tem a aresta que vai ser removida.
 * @param vertex O v�rtice que a aresta tem guardado.
 * @param from O geoc�digo do v�rtice que a aresta esta ligada no grafo.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 *
 * @note A aresta s� fica removida na mem�ria.
 */
int remove_edge(Graph** head, Vertex* vertex, char* from);

/**
 * @brief Cria um novo v�rtice com o geoc�digo dado.
 *
 * Aloca mem�ria dinamicamente para o novo v�rtice, guardando o geoc�digo inserido.
 *
 * @param geocode O geoc�digo a ser atribuido ao novo v�rtice.
 * 
 * @return Um apontador para o novo v�rtice.
 *
 * @note O v�rtice s� fica guardado na mem�ria.
 */
Vertex* create_vertex(char* geocode);

/**
 * @brief Remove um v�rtice do grafo e atualiza o vetor dos v�rtices.
 *
 * Remove o v�rtice do grafo junto com todas as arestas conectadas a esse, tamb�m atualiza o vetor dos v�rtices.
 *
 * @param head O grafo que vai ter o vertice removido.
 * @param vertex O v�rtice a ser removido.
 * @param vertices O vetor que representa todos os v�rtices no grafo.
 * @param array_size O tamanho atual do vetor dos v�rtices.
 *
 * @return O tamanho atualizado do vetor de v�rtices ap�s a remo��o.
 *
 * @see remove_edge
 * 
 * @note O vertice s� fica removido na mem�ria.
 */
int remove_vertex(Graph** head, Vertex* vertex, Vertex** vertices, int array_size);

/**
 * @brief Adiciona um meio de transporte a um v�rtice.
 *
 * Adiciona um dado meio de transporte a um v�rtice, atualizando o geoc�digo do meio de transporte.
 *
 * @param vertex V�rtice onde o meio de transporte vai ser adicionado.
 * @param transport O meio de transporte a ser adicionado ao v�rtice.
 *
 * @return Um apontador para o vertice atualizado.
 *
 * @note O meio de transporte � s� adicionado na mem�ria.
 */
Vertex* add_vertex_transport(Vertex* vertex, Transport* transport);

/**
 * @brief Adiciona um utilizador a um v�rtice.
 *
 * Adiciona um dado utilizador a um v�rtice inserido.
 *
 * @param vertex V�rtice onde o utilizador vai ser adicionado.
 * @param user O utilizador a ser adicionado ao v�rtice.
 *
 * @return Um apontador para o vertice atualizado.
 *
 * @note O utilizador � s� adicionado na mem�ria.
 */
Vertex* add_vertex_users(Vertex* vertex, User* user);

/**
 * @brief Remove um meio de transporte de um v�rtice.
 *
 * Remove um meio de transporte pelo seu id de um dado v�rtice, diminuindo tamb�m o 'transport_quantity' do v�rtice.
 *
 * @param vertex V�rtice onde o meio de transporte vai ser removido.
 * @param id O id do meio de transporte a ser removido do v�rtice.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 *
 * @note O meio de transporte � s� removido na mem�ria.
 */
int remove_vertex_transport(Vertex* vertex, int id);

/**
 * @brief Remove um utilizador de um v�rtice.
 *
 * Remove um utilizador pelo seu id de um dado v�rtice, diminuindo tamb�m o 'user_quantity' do v�rtice.
 *
 * @param vertex V�rtice onde o utilizador vai ser removido.
 * @param id O id do utilizador a ser removido do v�rtice.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 *
 * @note O utilizador � s� removido na mem�ria.
 */
int remove_vertex_user(Vertex* vertex, int id);

/**
 * @brief Armazena o grafo num ficheiro.
 *
 * Armazena cada n� do grafo numa diferente linha de um ficheiro.
 *
 * @param head O grafo a ser armazenado.
 * @param bool Identifica qual ficheiro o grafo vai ser armazenado.
 *			   Se for 0 os dados s�o armazenados num ficheiro binario, se for 1 s�o armazenados num ficheiro de texto.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 */
int store_graph(Graph* head, int bool);

/**
 * @brief Armazena os v�rtices num ficheiro.
 *
 * Armazena cada v�rtice numa diferente linha de um ficheiro.
 *
 * @param vertices O vetor de v�rtices a ser aemazenados.
 * @param array_size O tamanho do vetor de v�rtices.
 * @param bool Identifica qual ficheiro o grafo vai ser armazenado.
 *			   Se for 0 os dados s�o armazenados num ficheiro binario, se for 1 s�o armazenados num ficheiro de texto.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 */
int store_vertices(Vertex** vertices, int array_size, int bool);

/**
 * @brief L� o grafo de um ficheiro.
 *
 * L� o grafo de um ficheiro e salva cada um num n� do grafo.
 *
 * @param head O grafo a ser armazenado.
 * @param vertex Vetor dos v�rtices que representa todos os vertices no grafo.
 * @param vertex_size O tamanho do vetor de v�rtices.
 * @param bool Identifica qual ficheiro vai ser lido.
 *			   Se for 0 os dados s�o lidos de um ficheiro binario, se for 1 s�o lidos de um ficheiro de texto.
 *
 * @return Um apontador para o grafo lido.
 *
 * @see free_graph
 * @see insert_node
 * @see newline_remove
 * @see str_split
 * @see insert_edge
 */
Graph* read_graph(Graph* head, Vertex** vertex, int vertex_size, int bool);

/**
 * @brief L� os v�rtices do grafo num ficheiro.
 *
 * L� os v�rtices do grafo num ficheiro e cria um vetor de v�rtices.
 *
 * @param vertex Um vetor para guardar os v�rtices.
 * @param vertex_size O tamanho do vetor de v�rtices.
 * @param transports A lista ligado dos meios de tranporte a ser guardados nos v�rtices.
 * @param users A lista ligado dos utilizadores a ser guardados nos v�rtices.
 * @param bool Identifica qual ficheiro vai ser lido.
 *			   Se for 0 os dados s�o lidos de um ficheiro binario, se for 1 s�o lidos de um ficheiro de texto.
 *
 * @return Um apontador para o vetor de v�rtices.
 *
 * @see newline_remove
 * @see str_split
 * @see create_vertex
 * @see add_vertex_transport
 * @see get_transport
 * @see add_vertex_users
 * @see get_user
 */
Vertex** read_vertices(Vertex** vertex, int* vertex_size, Transport* transports, User* users, int bool);

/**
 * @brief Devolve o geoc�digo do v�rtice associado a um id de um utilizador
 *
 * Retorna o geoc�digo do v�rtice que cont�m o utilizador associado ao id.
 *
 * @param vertex O vetor de v�rtices.
 * @param vertex_size O tamanho do vetor de v�rtices.
 * @param id O c�digo do utilizador a ser procurado.
 *
 * @return O geoc�digo do v�rtice que cont�m o utilizador.
 */
char* user_geodode(Vertex** vertex, int vertex_size, int id);

/**
 * @brief Devolve os v�rtices mais pr�ximos dentro de um raio especificado de um determinado local.
 *
 * Fun��o recursiva que procura num grafo e devolve os v�rtices mais pr�ximos dentro de um raio.
 *
 * @param head O grafo a ser procurado os v�rtices mais pr�ximos.
 * @param vertices Vetor de v�rtices que armazena os v�rtices mais pr�ximos.
 * @param vertices_size O tamanho do vetor de v�rtices.
 * @param vertices_pos  A posi��o atual do vetor de v�rtices.
 * @param location A localiza��o atual para procurar os v�rtices mais pr�ximos.
 * @param radius O raio m�ximo de procura dos v�rtices mais pr�ximos.
 * @param travelled O peso cumulativo das arestas percorridas a partir do local inicial.
 * @param geocodes_array O vetor de geoc�digos para indicar os v�rtices visitados.
 * @param geocodes_size O tamanho do vetor de geoc�digos.
 * @param geocodes_pos A posi��o atual do vetor de geoc�digos.
 *
 * @return O vetor dos v�rtices mais pr�ximos.
 */
Vertex** nearest_vertices(Graph* head, Vertex*** vertices, int* vertices_size, int* vertices_pos, char* location, float radius, float travelled, char*** geocodes_array, int* geocodes_size, int* geocodes_pos);

/**
 * @brief A fun��o de configura��o para a fun��o 'nearest_vertices'
 *
 * @param graph O grafo a ser procurado os v�rtices mais pr�ximos.
 * @param size O tamanho do vetor de v�rtices.
 * @param location O local inicial para procurar os v�rtices mais pr�ximos.
 * @param radius O raio m�ximo de procura dos v�rtices mais pr�ximos.
 * 
 * @return O vetor dos v�rtices mais pr�ximos, ou NULL se n�o for inserido uma localiza��o valida.
 * 
 * @see nearest_vertices
 */
Vertex** get_nearest_vertices(Graph* graph, int* size, char* location, float radius);

/**
 * @brief Devolve a posi��o de um v�rtice pelo geoc�digo no grafo.
 *
 * Procura um v�rtice pelo geoc�digo no grafo inserido, devolvendo a sua posi��o na lista ligado do grafo.
 * 
 * @param head O grafo a ser procurado.
 * @param geocode O geoc�digo do v�rtice a ser encontrado.
 *
 * @return A posi��o do v�rtice, se n�o for encontrado � devolvido -1.
 */
int get_vertex_pos(Graph* head, char* geocode);

/**
 * @brief Calcula o geoc�digo com a menor distancia da localiza��o atual.
 * 
 * Calcula o geoc�digo de um v�rtice que tem a menor distancia do v�rtice atual.
 *
 * @param graph_head O grafo que cont�m os v�rtices.
 * @param edge_head A lista ligada das aresta que cont�m as conex�es entre os v�rtices.
 * @param distances Vetor que guarda as dist�ncias atuais entre a localiza��o inicial para cada v�rtice.
 * @param visited Vetor que indica quais os v�rtices foram visitados.
 * @param current_pos A posi��o atual no grafo.
 * @param vertices_quant Quantidade de v�rtices no grafo.
 *
 * @return O geoc�digo vertice com a menor dist�ncia da localiza��o atual.
 * 
 * @see get_vertex_pos
 */
char* shortest_distance(Graph* graph_head, Edge* edge_head, float* distances, int* visited, int current_pos, int vertices_quant);

/**
 * @brief Encontra recursivamente um caminho entre dois v�rtices no grafo.
 *
 * Procura recursivamente por um caminho entre dois v�rtices no grafo inserido, 
 * explorando os v�rtices adjacentes a partir da localiza��o atual, considerando o raio dado e a dist�ncia percorrida.
 *
 * @param head O grafo que cont�m os v�rtices.
 * @param geocodes Vetor de geoc�digos dos v�rtices que j� foram visitados.
 * @param geocodes_size O tamanho do vetor de geoc�digos.
 * @param path Vetor que armazena o caminho entre os v�rtices de origem e de destino.
 * @param path_size O tamanho do vetor 'path'.
 * @param path_pos A posi��o atual no vetor 'path'.
 * @param radius O raio m�ximo de procura.
 * @param travelled A dist�ncia total j� procurada.
 * @param iteration A itera��o atual da fun��o recursiva.
 * @param location A localiza��o atual no gr�fico.
 * @param destination O v�rtice de destino.
 * @param found O par�metro que indica se o v�rtice de destino foi encontrado.
 *
 * @return Se o caminho for encontrado � devolvido 1, se n�o � devolvido 0.
 * 
 * @see has_string
 */
int get_path(Graph* head, char** geocodes, int geocodes_size, char*** path, int* path_size, int path_pos, float radius, float travelled, int iteration, char* location, char* destination, int* found);

/**
 * @brief Encontra o caminho mais curto entre dois v�rtices num grafo.
 *
 * Calcula o caminho mais curto entre dois v�rtices no grafo utilizando o algoritmo de Dijkstra.
 *
 * @param head O grafo que cont�m os v�rtices.
 * @param path Vetor que armazena o caminho entre os v�rtices de origem e de destino.
 * @param from O v�rtice de origem do caminho.
 * @param to O v�rtice de destino do caminho.
 * @param vertices_quant O n�mero total de v�rtices no grafo.
 * @param path_size O tamanho do vetor 'path'.
 * @param path_pos A posi��o atual no vetor 'path'.
 *
 * @return A dist�ncia total percorrida no caminho mais curto ou -1 se nenhum caminho for encontrado.
 *
 * @see get_vertex_pos
 * @see shortest_distance
 * @see get_path
 * @see string_dup
 */
float shortest_path(Graph* head, char*** path, char* from, char* to, int vertices_quant, int* path_size, int* path_pos);

/**
 * @brief Devolve um vetor dos v�rtices com meios de transporte que t�m 50% ou menos de bateria.
 *
 * Reduz o n�mero de v�rtices filtrando os v�rtices que possuem transportes com um n�vel de bateria superior a 50%.
 *
 * @param vertices O vetor de v�rtices a ser filtrado.
 * @param vertices_quant O n�mero total de v�rtices no vetor.
 * @param new_vertices_size Um apontador para o novo tamanho do vetor de v�rtices.
 *
 * @return Um vetor de v�rtices reduzidos com base no n�vel da bateria dos meios de transporte.
 *
 * @see remove_vertex_transport
 */
Vertex** reduced_battery(Vertex** vertices, int vertices_quant, int* new_vertices_size);

/**
 * @brief Encontra o circuito mais curto com base nos n�veis de bateria e no volume do caminh�o.
 *
 * Calcula o circuito mais curto que visita v�rtices com transportes com n�veis de bateria reduzidos.
 * � utilizado uma combina��o de c�lculos de caminho mais curto e restri��es de volume para determinar o circuito.
 * Quando necess�rio volta ao v�rtice inicial para esvaziar o cami�o.
 *
 * @param head O grafo que cont�m os v�rtices.
 * @param vertices Vetor de v�rtices.
 * @param vertices_quant O n�mero total de v�rtices no vetor.
 * @param start O geoc�digo inicial para o circuito.
 * @param truck_volume O volume m�ximo que o cami�o consegue levar.
 * @param circuit_size Um apontador para o tamanho do circuito final.
 *
 * @return Um vetor de geoc�digos que representa o circuito mais curto.
 *
 * @see reduced_battery
 * @see shortest_path
 * @see string_dup
 * @see remove_vertex_transport
 * @see remove_vertex
 * @see create_vertex
 */
char** shortest_circuit(Graph* head, Vertex** vertices, int vertices_quant, char* start, float truck_volume, int* circuit_size);