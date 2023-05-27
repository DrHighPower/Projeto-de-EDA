/**
 * @file transport.h
 * @brief É o ficheiro que contém as difinições necessárias para mexer com os meios de transporte.
 *
 * O transport.h é o ficheiro onde estão declaradas a estrutura de dados e as funções que dão acesso a mexer com os dados dos meios de transporte.
 *
 * @author João Telmo Barros Inverneiro
 */

/**
* @struct transportInformation
* @brief Estrutura dos dados de um meio de transporte.
*
* Esta estrutura de dados contém o formato que os dados do meio de transporte são guardados, esta também é uma lista ligada.
*/
typedef struct transportInformation {
	int id,								/**< O código unico de cada meio de transporte. */
		battery,						/**< A bateria do meio de transporte. */
		autonomy,						/**< A autonomia do meio de transporte. */
		rented;							/**< Indica se o transporte está alugado. */
	float price,						/**< O preço do meio de transporte. */
		  volume;						/**< O volume do meio de transporte em metros cúbicos. */
	char *type,							/**< O tipo do meio de transporte. */
		 *geocode;						/**< O geocódigo do meio de transporte. */
	struct transportInformation* next;	/**< O endereço do próximo nó da lista ligada. */
} Transport;

/**
 * @brief Percorre a lista ligada e liberta cada nó.
 *
 * Percorre a lista ligada e liberta cada nó e torna o primeiro nó em NULL.
 *
 * @param head A lista ligada a ser libertada.
 */
void free_transport_list(Transport** head);

/**
 * @brief Guarda cada parâmetro para cada membro da estrutura de dados correspondente.
 *
 * @param current A estrutura de dados que guarda os parâmetros.
 * @param id O código a ser guardado.
 * @param battery A bateria a ser guardada.
 * @param autonomy A autonomia a ser guardada.
 * @param price O preço a ser guardado.
 * @param volume O volume em metros cúbicos a ser guardado.
 * @param type O tipo de meio de transporte a ser guardado.
 * @param geocode O geocódigo a ser guardado.
 */
void save_transport(Transport* current, int id, int battery, int autonomy, float price, float volume, char* type, char* geocode);

/**
 * @brief Armazena os meios de transporte num ficheiro.
 *
 * Armazena cada nó da lista ligada numa diferente linha de um ficheiro.
 *
 * @param head A lista ligada a ser armazenada.
 * @param bool Identifica qual ficheiro a lista vai ser armazenada.
 *			   Se for 0 os dados são armazenados num ficheiro binario, se for 1 são armazenados num ficheiro de texto.
 *
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
 */
int store_transports(Transport* head, int bool);

/**
 * @brief Lê os meios de transporte de um ficheiro.
 *
 * Lê os meios de transporte de um ficheiro e salva cada um num nó da lista ligada.
 *
 * @param head A lista ligada a ser armazenada.
 * @param bool Identifica qual ficheiro vai ser lido.
 *			   Se for 0 os dados são lidos de um ficheiro binario, se for 1 são lidos de um ficheiro de texto.
 *
 * @return A lista ligada com os dados dos meios de transporte.
 *
 * @see free_transport_list
 * @see newline_remove
 * @see save_transport
 */
Transport* read_transports(Transport* head, int bool);

/**
 * @brief Insere um novo meio de transporte.
 *
 * Insere um novo meio de transporte no último nó da lista ligada.
 *
 * @param head A lista ligada a receber um novo meio de transporte.
 *
 * @return O código unico do novo transporte.
 * 
 * @see newline_remove
 * @see save_transport
 * 
 * @note O novo meio de transporte só fica guardado na memória.
 */
int insert_tranport(Transport** head);

/**
 * @brief Remove um meio de transporte.
 *
 * Remove um meio de transporte de uma lista ligada.
 *
 * @param head A lista ligada a ter o meio de transporte removido.
 * @param id O código unico do meio de transporte a ser removido.
 *
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
 * 
 * @note O meio de transporte só fica removido na memória.
 */
int remove_transport(Transport** head, int id);

/**
 * @brief Edita um meio de transporte.
 *
 * Edita um meio de transporte numa lista ligada.
 *
 * @param head A lista ligada a ter o meio de transporte editado.
 * @param id O código unico do meio de transporte a ser editado
 *
 * @return Se a função for bem sucedida é devolvido o meio de transporte editado, se não é devolvido NULL.
 *
 * @see newline_remove
 * 
 * @note O meio de transporte só fica editado na memória.
 */
Transport* edit_transport(Transport** head, int id);

/**
 * @brief Retorna uma lista de transportes por ordem decrescente de autonomia.
 *
 * @param head A lista ligada a ser retornada.
 * @param transport_quant Quantidade de transportes.
 * 
 * @see list_geocode
 */
Transport** list_autonomy(Transport* head, int* transport_quant);

/**
 * @brief Retorna uma lista de transportes em um local com um determinado geocódigo.
 *
 * @param head A lista ligada a ser retornada.
 * @param transport_quant Quantidade de transportes.
 *
 * @see list_autonomy
 */
Transport** list_geocode(Transport* head, int* transport_quant);

/**
 * @brief Retorna um meio de transporte.
 *
 * Retorna um meio de transporte se o dado código corresponde com um meio de transporte na lista ligada.
 * 
 * @param head A lista ligada a ser percorrida.
 * @param id O código do transporte a ser retornado.
 *
 * @return Se a função for bem sucedida é devolvido o transporte, se não é devolvido NULL.
 */
Transport* get_transport(Transport* head, int id);