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

/**
 * @struct vertexInformation
 * @brief Estrutura dos dados de um vértice.
 *
 * Esta estrutura de dados contém as diferentes informações de um vértice.
 */
typedef struct vertexInformation {
	char *geocode;				/**< O geocódigo do vértice. */
	int transport_quantity,		/**< A quantidade de transportes. */
		user_quantity;			/**< A quantidade de utilizadores. */
	Transport** transports;		/**< Vetor de transportes. */
	User** users;				/**< Vetor de utilizadores. */
} Vertex;

/**
 * @struct edgeInformation
 * @brief Estrutura dos dados de uma aresta.
 *
 * Esta estrutura de dados contém as diferentes informações de uma aresta, esta também é uma lista ligada.
 */
typedef struct edgeInformation {
	float weight;							/**< O peso da aresta. */
	struct vertexInformation* vertex;		/**< O endereço do vértice ligado à aresta */
	struct edgeInformation* next;			/**< O endereço do próximo nó da lista ligada. */
} Edge;

/**
 * @struct graphInformation
 * @brief Estrutura dos dados de um grafo.
 *
 * Esta estrutura de dados contém o formato do grafo, este também é uma lista ligada..
 */
typedef struct graphInformation {
	char *geocode;						/**< O geocódigo do vértice. */
	struct edgeInformation* edge;		/**< O endereço da aresta ligado ao vértice */
	struct graphInformation* next;		/**< O endereço do próximo nó da lista ligada. */
} Graph;

/**
 * @brief Percorre a lista ligada das arestas e liberta cada nó.
 *
 * Percorre a lista ligada das arestas e liberta cada nó e torna o primeiro nó em NULL.
 *
 * @param head A lista ligada das arestas a ser libertada.
 */
void free_edge_list(Edge** head);

/**
 * @brief Percorre a lista ligada do grafo e liberta cada nó.
 *
 * Percorre a lista ligada do grafo e liberta cada nó e torna o primeiro nó em NULL.
 *
 * @param head A lista ligada do grafo a ser libertada.
 */
void free_graph(Graph** head);

/**
 * @brief Guarda o geocódigo para membro da estrutura de dados correspondente.
 *
 * @param current A estrutura de dados que guarda os parâmetros.
 * @param geocode O geocódigo a ser guardado.
 */
void save_node(Graph* current, char* geocode);

/**
 * @brief Insere um novo vértice no grafo.
 *
 * Insere um novo vértice no grafo no último nó da lista ligada.
 *
 * @param head A lista ligada a receber um novo vértice no grafo.
 *
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
 *
 * @see save_node
 *
 * @note O novo vértice só fica guardado na memória.
 */
int insert_node(Graph* head, char* geocode);

/**
 * @brief Remove um vértice no grafo.
 *
 * Remove um vértice no grafo de uma lista ligada.
 *
 * @param head A lista ligada a ter o vértice no grafo removido.
 * @param geocode O geocódigo do vértice no grafo a ser removido.
 *
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
 *
 * @note O vértice só fica removido na memória.
 */
int remove_node(Graph** head, char* geocode);

/**
 * @brief Insere uma nova aresta no grafo.
 *
 * Insere uma nova aresta no último nó da lista ligada.
 *
 * @param head O grafo a receber uma nova aresta.
 * @param vertex O vértice a ser guardado na nova aresta.
 * @param from O geocódigo do vértice que a aresta vai estar ligada no grafo.
 * @param weight O peso da nova aresta.
 *
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
 *
 * @note A nova aresta só fica guardada na memória.
 */
int insert_edge(Graph* head, Vertex* vertex, char* from, float weight);

/**
 * @brief Edita uma aresta.
 *
 * Edita uma aresta num grafo.
 *
 * @param head O grafo que tem a aresta que vai ser editada.
 * @param vertex O vértice que a aresta tem guardado.
 * @param from O geocódigo do vértice que a aresta esta ligada no grafo.
 * @param weight O novo peso da aresta.
 *
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
 *
 * @note A aresta só fica editada na memória.
 */
int edit_edge(Graph** head, Vertex* vertex, char* from, float weight);

/**
 * @brief Remove uma aresta.
 *
 * Remove uma aresta de um grafo.
 *
 * @param head O grafo que tem a aresta que vai ser removida.
 * @param vertex O vértice que a aresta tem guardado.
 * @param from O geocódigo do vértice que a aresta esta ligada no grafo.
 *
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
 *
 * @note A aresta só fica removida na memória.
 */
int remove_edge(Graph** head, Vertex* vertex, char* from);

/**
 * @brief Cria um novo vértice com o geocódigo dado.
 *
 * Aloca memória dinamicamente para o novo vértice, guardando o geocódigo inserido.
 *
 * @param geocode O geocódigo a ser atribuido ao novo vértice.
 * 
 * @return Um apontador para o novo vértice.
 *
 * @note O vértice só fica guardado na memória.
 */
Vertex* create_vertex(char* geocode);

/**
 * @brief Remove um vértice do grafo e atualiza o vetor dos vértices.
 *
 * Remove o vértice do grafo junto com todas as arestas conectadas a esse, também atualiza o vetor dos vértices.
 *
 * @param head O grafo que vai ter o vertice removido.
 * @param vertex O vértice a ser removido.
 * @param vertices O vetor que representa todos os vértices no grafo.
 * @param array_size O tamanho atual do vetor dos vértices.
 *
 * @return O tamanho atualizado do vetor de vértices após a remoção.
 *
 * @see remove_edge
 * 
 * @note O vertice só fica removido na memória.
 */
int remove_vertex(Graph** head, Vertex* vertex, Vertex** vertices, int array_size);

/**
 * @brief Adiciona um meio de transporte a um vértice.
 *
 * Adiciona um dado meio de transporte a um vértice, atualizando o geocódigo do meio de transporte.
 *
 * @param vertex Vértice onde o meio de transporte vai ser adicionado.
 * @param transport O meio de transporte a ser adicionado ao vértice.
 *
 * @return Um apontador para o vertice atualizado.
 *
 * @note O meio de transporte é só adicionado na memória.
 */
Vertex* add_vertex_transport(Vertex* vertex, Transport* transport);

/**
 * @brief Adiciona um utilizador a um vértice.
 *
 * Adiciona um dado utilizador a um vértice inserido.
 *
 * @param vertex Vértice onde o utilizador vai ser adicionado.
 * @param user O utilizador a ser adicionado ao vértice.
 *
 * @return Um apontador para o vertice atualizado.
 *
 * @note O utilizador é só adicionado na memória.
 */
Vertex* add_vertex_users(Vertex* vertex, User* user);

/**
 * @brief Remove um meio de transporte de um vértice.
 *
 * Remove um meio de transporte pelo seu id de um dado vértice, diminuindo também o 'transport_quantity' do vértice.
 *
 * @param vertex Vértice onde o meio de transporte vai ser removido.
 * @param id O id do meio de transporte a ser removido do vértice.
 *
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
 *
 * @note O meio de transporte é só removido na memória.
 */
int remove_vertex_transport(Vertex* vertex, int id);

/**
 * @brief Remove um utilizador de um vértice.
 *
 * Remove um utilizador pelo seu id de um dado vértice, diminuindo também o 'user_quantity' do vértice.
 *
 * @param vertex Vértice onde o utilizador vai ser removido.
 * @param id O id do utilizador a ser removido do vértice.
 *
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
 *
 * @note O utilizador é só removido na memória.
 */
int remove_vertex_user(Vertex* vertex, int id);

/**
 * @brief Armazena o grafo num ficheiro.
 *
 * Armazena cada nó do grafo numa diferente linha de um ficheiro.
 *
 * @param head O grafo a ser armazenado.
 * @param bool Identifica qual ficheiro o grafo vai ser armazenado.
 *			   Se for 0 os dados são armazenados num ficheiro binario, se for 1 são armazenados num ficheiro de texto.
 *
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
 */
int store_graph(Graph* head, int bool);

/**
 * @brief Armazena os vértices num ficheiro.
 *
 * Armazena cada vértice numa diferente linha de um ficheiro.
 *
 * @param vertices O vetor de vértices a ser aemazenados.
 * @param array_size O tamanho do vetor de vértices.
 * @param bool Identifica qual ficheiro o grafo vai ser armazenado.
 *			   Se for 0 os dados são armazenados num ficheiro binario, se for 1 são armazenados num ficheiro de texto.
 *
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
 */
int store_vertices(Vertex** vertices, int array_size, int bool);

/**
 * @brief Lê o grafo de um ficheiro.
 *
 * Lê o grafo de um ficheiro e salva cada um num nó do grafo.
 *
 * @param head O grafo a ser armazenado.
 * @param vertex Vetor dos vértices que representa todos os vertices no grafo.
 * @param vertex_size O tamanho do vetor de vértices.
 * @param bool Identifica qual ficheiro vai ser lido.
 *			   Se for 0 os dados são lidos de um ficheiro binario, se for 1 são lidos de um ficheiro de texto.
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
 * @brief Lê os vértices do grafo num ficheiro.
 *
 * Lê os vértices do grafo num ficheiro e cria um vetor de vértices.
 *
 * @param vertex Um vetor para guardar os vértices.
 * @param vertex_size O tamanho do vetor de vértices.
 * @param transports A lista ligado dos meios de tranporte a ser guardados nos vértices.
 * @param users A lista ligado dos utilizadores a ser guardados nos vértices.
 * @param bool Identifica qual ficheiro vai ser lido.
 *			   Se for 0 os dados são lidos de um ficheiro binario, se for 1 são lidos de um ficheiro de texto.
 *
 * @return Um apontador para o vetor de vértices.
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
 * @brief Devolve o geocódigo do vértice associado a um id de um utilizador
 *
 * Retorna o geocódigo do vértice que contém o utilizador associado ao id.
 *
 * @param vertex O vetor de vértices.
 * @param vertex_size O tamanho do vetor de vértices.
 * @param id O código do utilizador a ser procurado.
 *
 * @return O geocódigo do vértice que contém o utilizador.
 */
char* user_geodode(Vertex** vertex, int vertex_size, int id);

/**
 * @brief Devolve os vértices mais próximos dentro de um raio especificado de um determinado local.
 *
 * Função recursiva que procura num grafo e devolve os vértices mais próximos dentro de um raio.
 *
 * @param head O grafo a ser procurado os vértices mais próximos.
 * @param vertices Vetor de vértices que armazena os vértices mais próximos.
 * @param vertices_size O tamanho do vetor de vértices.
 * @param vertices_pos  A posição atual do vetor de vértices.
 * @param location A localização atual para procurar os vértices mais próximos.
 * @param radius O raio máximo de procura dos vértices mais próximos.
 * @param travelled O peso cumulativo das arestas percorridas a partir do local inicial.
 * @param geocodes_array O vetor de geocódigos para indicar os vértices visitados.
 * @param geocodes_size O tamanho do vetor de geocódigos.
 * @param geocodes_pos A posição atual do vetor de geocódigos.
 *
 * @return O vetor dos vértices mais próximos.
 */
Vertex** nearest_vertices(Graph* head, Vertex*** vertices, int* vertices_size, int* vertices_pos, char* location, float radius, float travelled, char*** geocodes_array, int* geocodes_size, int* geocodes_pos);

/**
 * @brief A função de configuração para a função 'nearest_vertices'
 *
 * @param graph O grafo a ser procurado os vértices mais próximos.
 * @param size O tamanho do vetor de vértices.
 * @param location O local inicial para procurar os vértices mais próximos.
 * @param radius O raio máximo de procura dos vértices mais próximos.
 * 
 * @return O vetor dos vértices mais próximos, ou NULL se não for inserido uma localização valida.
 * 
 * @see nearest_vertices
 */
Vertex** get_nearest_vertices(Graph* graph, int* size, char* location, float radius);

/**
 * @brief Devolve a posição de um vértice pelo geocódigo no grafo.
 *
 * Procura um vértice pelo geocódigo no grafo inserido, devolvendo a sua posição na lista ligado do grafo.
 * 
 * @param head O grafo a ser procurado.
 * @param geocode O geocódigo do vértice a ser encontrado.
 *
 * @return A posição do vértice, se não for encontrado é devolvido -1.
 */
int get_vertex_pos(Graph* head, char* geocode);

/**
 * @brief Calcula o geocódigo com a menor distancia da localização atual.
 * 
 * Calcula o geocódigo de um vértice que tem a menor distancia do vértice atual.
 *
 * @param graph_head O grafo que contém os vértices.
 * @param edge_head A lista ligada das aresta que contém as conexões entre os vértices.
 * @param distances Vetor que guarda as distâncias atuais entre a localização inicial para cada vértice.
 * @param visited Vetor que indica quais os vértices foram visitados.
 * @param current_pos A posição atual no grafo.
 * @param vertices_quant Quantidade de vértices no grafo.
 *
 * @return O geocódigo vertice com a menor distância da localização atual.
 * 
 * @see get_vertex_pos
 */
char* shortest_distance(Graph* graph_head, Edge* edge_head, float* distances, int* visited, int current_pos, int vertices_quant);

/**
 * @brief Encontra recursivamente um caminho entre dois vértices no grafo.
 *
 * Procura recursivamente por um caminho entre dois vértices no grafo inserido, 
 * explorando os vértices adjacentes a partir da localização atual, considerando o raio dado e a distância percorrida.
 *
 * @param head O grafo que contêm os vértices.
 * @param geocodes Vetor de geocódigos dos vértices que já foram visitados.
 * @param geocodes_size O tamanho do vetor de geocódigos.
 * @param path Vetor que armazena o caminho entre os vértices de origem e de destino.
 * @param path_size O tamanho do vetor 'path'.
 * @param path_pos A posição atual no vetor 'path'.
 * @param radius O raio máximo de procura.
 * @param travelled A distância total já procurada.
 * @param iteration A iteração atual da função recursiva.
 * @param location A localização atual no gráfico.
 * @param destination O vértice de destino.
 * @param found O parâmetro que indica se o vértice de destino foi encontrado.
 *
 * @return Se o caminho for encontrado é devolvido 1, se não é devolvido 0.
 * 
 * @see has_string
 */
int get_path(Graph* head, char** geocodes, int geocodes_size, char*** path, int* path_size, int path_pos, float radius, float travelled, int iteration, char* location, char* destination, int* found);

/**
 * @brief Encontra o caminho mais curto entre dois vértices num grafo.
 *
 * Calcula o caminho mais curto entre dois vértices no grafo utilizando o algoritmo de Dijkstra.
 *
 * @param head O grafo que contêm os vértices.
 * @param path Vetor que armazena o caminho entre os vértices de origem e de destino.
 * @param from O vértice de origem do caminho.
 * @param to O vértice de destino do caminho.
 * @param vertices_quant O número total de vértices no grafo.
 * @param path_size O tamanho do vetor 'path'.
 * @param path_pos A posição atual no vetor 'path'.
 *
 * @return A distância total percorrida no caminho mais curto ou -1 se nenhum caminho for encontrado.
 *
 * @see get_vertex_pos
 * @see shortest_distance
 * @see get_path
 * @see string_dup
 */
float shortest_path(Graph* head, char*** path, char* from, char* to, int vertices_quant, int* path_size, int* path_pos);

/**
 * @brief Devolve um vetor dos vértices com meios de transporte que têm 50% ou menos de bateria.
 *
 * Reduz o número de vértices filtrando os vértices que possuem transportes com um nível de bateria superior a 50%.
 *
 * @param vertices O vetor de vértices a ser filtrado.
 * @param vertices_quant O número total de vértices no vetor.
 * @param new_vertices_size Um apontador para o novo tamanho do vetor de vértices.
 *
 * @return Um vetor de vértices reduzidos com base no nível da bateria dos meios de transporte.
 *
 * @see remove_vertex_transport
 */
Vertex** reduced_battery(Vertex** vertices, int vertices_quant, int* new_vertices_size);

/**
 * @brief Encontra o circuito mais curto com base nos níveis de bateria e no volume do caminhão.
 *
 * Calcula o circuito mais curto que visita vértices com transportes com níveis de bateria reduzidos.
 * É utilizado uma combinação de cálculos de caminho mais curto e restrições de volume para determinar o circuito.
 * Quando necessário volta ao vértice inicial para esvaziar o camião.
 *
 * @param head O grafo que contêm os vértices.
 * @param vertices Vetor de vértices.
 * @param vertices_quant O número total de vértices no vetor.
 * @param start O geocódigo inicial para o circuito.
 * @param truck_volume O volume máximo que o camião consegue levar.
 * @param circuit_size Um apontador para o tamanho do circuito final.
 *
 * @return Um vetor de geocódigos que representa o circuito mais curto.
 *
 * @see reduced_battery
 * @see shortest_path
 * @see string_dup
 * @see remove_vertex_transport
 * @see remove_vertex
 * @see create_vertex
 */
char** shortest_circuit(Graph* head, Vertex** vertices, int vertices_quant, char* start, float truck_volume, int* circuit_size);