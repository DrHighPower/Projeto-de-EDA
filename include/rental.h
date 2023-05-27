/**
 * @file rental.h
 * @brief É o ficheiro que contém as difinições necessárias para fazer um aluguer.
 *
 * O rental.h é o ficheiro onde estão declaradas as funções que possibilitam um utilizador alugar um transporte.
 *
 * @author João Telmo Barros Inverneiro
 */

typedef struct userInformation User;
typedef struct transportInformation Transport;

/**
 * @struct rentalInformation
 * @brief Estrutura dos dados de um aluguer.
 *
 * Esta estrutura de dados contém as diferentes informações de um aluguer.
 */
typedef struct rentalInformation {
	int user_id,			/**< O código unico do utilizador. */
		transport_id;		/**< O código unico do meio de transporte. */
	time_t start_time;		/**< Número epoch do início do aluguer. */
} Rental;

/**
 * @brief Verifica o status do aluguer de um meio de transporte com um determinado código.
 *
 * @param head A lista ligada de meios de transporte.
 * @param id O código unico do transporte.
 * 
 * @return Devolve 1 se o transporte com o código fornecido está alugado, 0 se estiver disponível para alugar ou não for encontrado.
 */
int check_rental(Transport* head, int id);

/**
 * @brief Inicia um processo de aluguer de um utilizador e de um meio de transporte.
 *
 * Inicia um processo de aluguer de um utilizador e de um meio de transporte. Ele verifica se tanto o utilizador quanto o transporte são válidos.
 * 
 * @param user O utilizador a alugar.
 * @param transport O meio de transporte a ser alugado.
 *
 * @return Um apontador para a estrutura que representa o processo de aluguer iniciado ou NULL se o processo de aluguer não pode ser iniciado.
 */
Rental* start_rental(User* user, Transport* transport);

/**
 * @brief Faz o pagamento necessário do alugo de um transporte.
 * 
 * Calcula e efetua o pagamento necessário para alugar um transporte, alterando o saldo do utilizador na lista ligada e no ficheiro.
 *
 * @param user O utilizador que alugou.
 * @param transport O transporte alugado.
 * @param minutes_used O tempo em minutos que ocorreu o aluguer.
 */
void pay_rental(User* user, Transport* transport, int minutes_used);

/**
 * @brief Armazena o novo aluguer.
 *
 * Faz o processo de obtenção da data final do aluguer e armazena este num ficheiro.
 * 
 * @param rental Estrutura que têm a informação do novo aluguer. 
 * @param minutes_used O tempo em minutos que ocorreu o aluguer.
 * @param bool Identifica qual ficheiro a lista vai ser alterada.
 *			   Se for 0 os dados são alterados num ficheiro binario, se for 1 são alterados num ficheiro de texto.
 *
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
 *
 * @see str_split
 */
int store_rental(Rental* rental, int minutes_used, int bool);

/**
 * @brief Pára um processo de aluguer e executa as operações necessárias.
 *
 * @param rental Estrutura que têm a informação do aluguer.
 * @param head_user A lista ligada dos utilizadores.
 * @param head_transport A lista ligada dos meios de transporte
 * @param bool Identifica qual ficheiro a lista vai ser alterada.
 *			   Se for 0 os dados são alterados num ficheiro binario, se for 1 são alterados num ficheiro de texto.
 *
 * @return Se a função for bem sucedida é devolvido 1, se não é devolvido 0.
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