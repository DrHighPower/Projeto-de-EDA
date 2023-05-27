/**
 * @file transport.h
 * @brief � o ficheiro que cont�m as difini��es necess�rias para mexer com os meios de transporte.
 *
 * O transport.h � o ficheiro onde est�o declaradas a estrutura de dados e as fun��es que d�o acesso a mexer com os dados dos meios de transporte.
 *
 * @author Jo�o Telmo Barros Inverneiro
 */

/**
* @struct transportInformation
* @brief Estrutura dos dados de um meio de transporte.
*
* Esta estrutura de dados cont�m o formato que os dados do meio de transporte s�o guardados, esta tamb�m � uma lista ligada.
*/
typedef struct transportInformation {
	int id,								/**< O c�digo unico de cada meio de transporte. */
		battery,						/**< A bateria do meio de transporte. */
		autonomy,						/**< A autonomia do meio de transporte. */
		rented;							/**< Indica se o transporte est� alugado. */
	float price,						/**< O pre�o do meio de transporte. */
		  volume;						/**< O volume do meio de transporte em metros c�bicos. */
	char *type,							/**< O tipo do meio de transporte. */
		 *geocode;						/**< O geoc�digo do meio de transporte. */
	struct transportInformation* next;	/**< O endere�o do pr�ximo n� da lista ligada. */
} Transport;

/**
 * @brief Percorre a lista ligada e liberta cada n�.
 *
 * Percorre a lista ligada e liberta cada n� e torna o primeiro n� em NULL.
 *
 * @param head A lista ligada a ser libertada.
 */
void free_transport_list(Transport** head);

/**
 * @brief Guarda cada par�metro para cada membro da estrutura de dados correspondente.
 *
 * @param current A estrutura de dados que guarda os par�metros.
 * @param id O c�digo a ser guardado.
 * @param battery A bateria a ser guardada.
 * @param autonomy A autonomia a ser guardada.
 * @param price O pre�o a ser guardado.
 * @param volume O volume em metros c�bicos a ser guardado.
 * @param type O tipo de meio de transporte a ser guardado.
 * @param geocode O geoc�digo a ser guardado.
 */
void save_transport(Transport* current, int id, int battery, int autonomy, float price, float volume, char* type, char* geocode);

/**
 * @brief Armazena os meios de transporte num ficheiro.
 *
 * Armazena cada n� da lista ligada numa diferente linha de um ficheiro.
 *
 * @param head A lista ligada a ser armazenada.
 * @param bool Identifica qual ficheiro a lista vai ser armazenada.
 *			   Se for 0 os dados s�o armazenados num ficheiro binario, se for 1 s�o armazenados num ficheiro de texto.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 */
int store_transports(Transport* head, int bool);

/**
 * @brief L� os meios de transporte de um ficheiro.
 *
 * L� os meios de transporte de um ficheiro e salva cada um num n� da lista ligada.
 *
 * @param head A lista ligada a ser armazenada.
 * @param bool Identifica qual ficheiro vai ser lido.
 *			   Se for 0 os dados s�o lidos de um ficheiro binario, se for 1 s�o lidos de um ficheiro de texto.
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
 * Insere um novo meio de transporte no �ltimo n� da lista ligada.
 *
 * @param head A lista ligada a receber um novo meio de transporte.
 *
 * @return O c�digo unico do novo transporte.
 * 
 * @see newline_remove
 * @see save_transport
 * 
 * @note O novo meio de transporte s� fica guardado na mem�ria.
 */
int insert_tranport(Transport** head);

/**
 * @brief Remove um meio de transporte.
 *
 * Remove um meio de transporte de uma lista ligada.
 *
 * @param head A lista ligada a ter o meio de transporte removido.
 * @param id O c�digo unico do meio de transporte a ser removido.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 * 
 * @note O meio de transporte s� fica removido na mem�ria.
 */
int remove_transport(Transport** head, int id);

/**
 * @brief Edita um meio de transporte.
 *
 * Edita um meio de transporte numa lista ligada.
 *
 * @param head A lista ligada a ter o meio de transporte editado.
 * @param id O c�digo unico do meio de transporte a ser editado
 *
 * @return Se a fun��o for bem sucedida � devolvido o meio de transporte editado, se n�o � devolvido NULL.
 *
 * @see newline_remove
 * 
 * @note O meio de transporte s� fica editado na mem�ria.
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
 * @brief Retorna uma lista de transportes em um local com um determinado geoc�digo.
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
 * Retorna um meio de transporte se o dado c�digo corresponde com um meio de transporte na lista ligada.
 * 
 * @param head A lista ligada a ser percorrida.
 * @param id O c�digo do transporte a ser retornado.
 *
 * @return Se a fun��o for bem sucedida � devolvido o transporte, se n�o � devolvido NULL.
 */
Transport* get_transport(Transport* head, int id);