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
		autonomy;						/**< A autonomia do meio de transporte. */
	float price;						/**< O pre�o do meio de transporte. */
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
 * @param type O tipo de meio de transporte a ser guardado.
 * @param geocode O geoc�digo a ser guardado.
 */
void save_transport(Transport* current, int id, int battery, int autonomy, float price, char* type, char* geocode);

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
 * @see newline_remove
 * @see save_transport
 * 
 * @note O novo meio de transporte s� fica guardado na mem�ria.
 */
void insert_tranport(Transport** head);

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
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 *
 * @see newline_remove
 * 
 * @note O meio de transporte s� fica editado na mem�ria.
 */
int edit_transport(Transport** head, int id);

/**
 * @brief Imprime uma lista de transportes por ordem decrescente de autonomia.
 *
 * @param head A lista ligada a ser imprimida.
 * 
 * @see list_geocode
 */
void list_autonomy(Transport* head);

/**
 * @brief Imprime uma lista de transportes em um local com um determinado geoc�digo.
 *
 * @param head A lista ligada a ser imprimida.
 *
 * @see list_autonomy
 */
void list_geocode(Transport* head);

/**
 * @brief Verifica a exist�ncia de um meio de transporte.
 *
 * Verifica se o dado c�digo corresponde com um meio de transporte na lista ligada.
 * 
 * @param head A lista ligada a ser percorrida.
 * @param id O c�digo a ser verificado.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 */
int validate_transport(Transport* head, int id);