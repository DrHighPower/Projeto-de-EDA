/**
 * @file rental.h
 * @brief � o ficheiro que cont�m as difini��es necess�rias para fazer um aluguer.
 *
 * O rental.h � o ficheiro onde est�o declaradas as fun��es que possibilitam um utilizador alugar um transporte.
 *
 * @author Jo�o Telmo Barros Inverneiro
 */

typedef struct userInformation User;
typedef struct transportInformation Transport;

/**
 * @struct rentalInformation
 * @brief Estrutura dos dados de um aluguer.
 *
 * Esta estrutura de dados cont�m as diferentes informa��es de um aluguer.
 */
typedef struct rentalInformation {
	int user_id,			/**< O c�digo unico do utilizador. */
		transport_id;		/**< O c�digo unico do meio de transporte. */
	time_t start_time;		/**< N�mero epoch do in�cio do aluguer. */
} Rental;

/**
 * @brief Verifica o status do aluguer de um meio de transporte com um determinado c�digo.
 *
 * @param head A lista ligada de meios de transporte.
 * @param id O c�digo unico do transporte.
 * 
 * @return Devolve 1 se o transporte com o c�digo fornecido est� alugado, 0 se estiver dispon�vel para alugar ou n�o for encontrado.
 */
int check_rental(Transport* head, int id);

/**
 * @brief Inicia um processo de aluguer de um utilizador e de um meio de transporte.
 *
 * Inicia um processo de aluguer de um utilizador e de um meio de transporte. Ele verifica se tanto o utilizador quanto o transporte s�o v�lidos.
 * 
 * @param user O utilizador a alugar.
 * @param transport O meio de transporte a ser alugado.
 *
 * @return Um apontador para a estrutura que representa o processo de aluguer iniciado ou NULL se o processo de aluguer n�o pode ser iniciado.
 */
Rental* start_rental(User* user, Transport* transport);

/**
 * @brief Faz o pagamento necess�rio do alugo de um transporte.
 * 
 * Calcula e efetua o pagamento necess�rio para alugar um transporte, alterando o saldo do utilizador na lista ligada e no ficheiro.
 *
 * @param user O utilizador que alugou.
 * @param transport O transporte alugado.
 * @param minutes_used O tempo em minutos que ocorreu o aluguer.
 */
void pay_rental(User* user, Transport* transport, int minutes_used);

/**
 * @brief Armazena o novo aluguer.
 *
 * Faz o processo de obten��o da data final do aluguer e armazena este num ficheiro.
 * 
 * @param rental Estrutura que t�m a informa��o do novo aluguer. 
 * @param minutes_used O tempo em minutos que ocorreu o aluguer.
 * @param bool Identifica qual ficheiro a lista vai ser alterada.
 *			   Se for 0 os dados s�o alterados num ficheiro binario, se for 1 s�o alterados num ficheiro de texto.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 *
 * @see str_split
 */
int store_rental(Rental* rental, int minutes_used, int bool);

/**
 * @brief P�ra um processo de aluguer e executa as opera��es necess�rias.
 *
 * @param rental Estrutura que t�m a informa��o do aluguer.
 * @param head_user A lista ligada dos utilizadores.
 * @param head_transport A lista ligada dos meios de transporte
 * @param bool Identifica qual ficheiro a lista vai ser alterada.
 *			   Se for 0 os dados s�o alterados num ficheiro binario, se for 1 s�o alterados num ficheiro de texto.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 *
 * @see get_user
 * @see get_transport
 * @see pay_rental
 * @see store_users
 * @see store_rental
 * 
 * @note Atualiza todos os dados dos utilizadoes no ficheiro.
 */
int stop_rental(Rental** rental, User* head_user, Transport* head_transport, int bool);