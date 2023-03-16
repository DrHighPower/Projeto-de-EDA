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
 * @brief Faz o pagamento necess�rio para alugar um transporte.
 * 
 * Calcula e efetua o pagamento necess�rio para alugar um transporte, alterando o saldo do utilizador na lista ligada e no ficheiro.
 *
 * @param head_user A lista ligada dos utilizadores.
 * @param head_transport A lista ligada dos meios de transporte.
 * @param user_id O c�digo do utilizador a fazer o aluguer.
 * @param transport_id O c�digo do meio de transporte a ser alugado.
 * @param min_used O tempo em minutos que ocorreu o aluguer.
 * @param bool Identifica qual ficheiro a lista vai ser alterada. 
 *			   Se for 0 os dados s�o alterados num ficheiro binario, se for 1 s�o alterados num ficheiro de texto.
 * 
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 * 
 * @see store_users
 */
int pay_rental(User** head_user, Transport* head_transport, int user_id, int transport_id, int min_used, int bool);

/**
 * @brief Armazena o novo aluguer
 *
 * Faz o processo de obten��o de um novo aluguer, armazenando o aluguer num ficheiro.
 *
 * @param head_user A lista ligada dos utilizadores.
 * @param head_transport A lista ligada dos meios de transporte.
 * @param user_id O c�digo do utilizador a fazer o aluguer.
 * @param transport_id O c�digo do meio de transporte a ser alugado.
 * @param bool Identifica qual ficheiro a lista vai ser alterada.
 *			   Se for 0 os dados s�o alterados num ficheiro binario, se for 1 s�o alterados num ficheiro de texto.
 *
 * @return Se a fun��o for bem sucedida � devolvido 1, se n�o � devolvido 0.
 *
 * @see str_split
 * @see pay_rental
 */
int store_rental(User** head_user, Transport* head_transport, int user_id, int transport_id, int bool);